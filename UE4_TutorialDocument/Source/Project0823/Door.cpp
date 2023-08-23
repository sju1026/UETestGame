// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	CloseTime = 3.0f;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	OriginRotation = GetActorRotation();
	GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Open, 0.03f, true);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	DoorDeltatime += DeltaTime;
}

void ADoor::Open() {
	if (!bOpen) {
		bOpen = true;
		DoorDeltatime = 0.0f;
	}

	FRotator rotation = GetActorRotation();
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(0.0f, 90.0f, DoorDeltatime), 0.0f);
	SetActorRotation(rotation);
	if (DoorDeltatime > 1.0f) {
		GetWorldTimerManager().ClearTimer(DoorTimerHandle);
		GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Close, 0.03f, true, CloseTime);
	}
}

void ADoor::Close()
{
	if (bOpen) {
		bOpen = false;
		DoorDeltatime = 0.0f;
	}

	FRotator rotation = GetActorRotation();
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(90.0f, 0.0f, DoorDeltatime), 0.0f);
	SetActorRotation(rotation);
	if (DoorDeltatime > 1.0f) {
		GetWorldTimerManager().ClearTimer(DoorTimerHandle);
	}
}

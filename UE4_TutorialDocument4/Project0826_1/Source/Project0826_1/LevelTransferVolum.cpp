// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolum.h"
#include "Project0826_1Character.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ALevelTransferVolum::ALevelTransferVolum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevelTransferVolum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransferVolum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransferVolum::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AProject0826_1Character* Character = Cast<AProject0826_1Character>(OtherActor);
	if (Character) {
		UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
	}
}
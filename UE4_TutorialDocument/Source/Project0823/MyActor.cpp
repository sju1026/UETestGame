// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// UE_LOG(LogTemp, Warning, TEXT("Construct"));
	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;
	/*CharacterName = TEXT("베르");
	bAttackable = true;*/

	str = TEXT("Test");

}

void AMyActor::CallFromCpp_Implementation()
{
	str.Append(TEXT("_Implementation"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	CallFromCpp();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Error, TEXT("Tick"));
}

void AMyActor::FunctionName() {

}

void AMyActor::CalculateDPS() {
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AMyActor::PostInitProperties()
{
	Super::PostInitProperties();
	CalculateDPS();
}

void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateDPS();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}


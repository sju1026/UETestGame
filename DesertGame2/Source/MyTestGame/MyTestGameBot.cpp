// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameBot.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectile.h"
#include "MyTestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

AMyTestGameBot::AMyTestGameBot()
{
	WeaponCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollisionSphere"));
	WeaponCollisionSphere->InitSphereRadius(20.0f);
	WeaponCollisionSphere->AttachTo(GetMesh(), "DamageSocket");

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMyTestGameBot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AMyTestCharacter::StaticClass()) && PlayAnimMontage(montage) > 0.2f) {
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Player Hit!");
	}
}

int AMyTestGameBot::melee_attack_Implementation()
{
	if (montage) {
		PlayAnimMontage(montage);

		if (MyCharacterName == "Range" && MyBullet) {
			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(80.0f, 30.0f, 10.0f));

			UWorld* const WRLD = GetWorld();
			if (WRLD != NULL) {
				WRLD->SpawnActor<AMyProjectile>(MyBullet, SpawnLocation, SpawnRotation);
			}
		}
	}
	return 0;
}

UAnimMontage* AMyTestGameBot::get_montage() const
{
	return montage;
}
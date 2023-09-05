// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameBot.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectile.h"
#include "Engine/World.h"

AMyTestGameBot::AMyTestGameBot()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}




int AMyTestGameBot::melee_attack_Implementation()
{
	if (montage) {
		PlayAnimMontage(montage);

		if (MyBotName == "Range" && MyBullet) {
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
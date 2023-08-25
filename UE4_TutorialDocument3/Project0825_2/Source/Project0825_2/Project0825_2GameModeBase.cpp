// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project0825_2GameModeBase.h"

void AProject0825_2GameModeBase::StartPlay() {
	Super::StartPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	}
}
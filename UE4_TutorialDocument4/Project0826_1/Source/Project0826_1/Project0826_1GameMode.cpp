// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project0826_1GameMode.h"
#include "Project0826_1Character.h"
#include "UObject/ConstructorHelpers.h"

AProject0826_1GameMode::AProject0826_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

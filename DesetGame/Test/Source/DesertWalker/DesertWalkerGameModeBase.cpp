// Copyright Epic Games, Inc. All Rights Reserved.


#include "DesertWalkerGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ADesertWalkerGameModeBase::BeginPlay() {
	Super::BeginPlay();

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();
}
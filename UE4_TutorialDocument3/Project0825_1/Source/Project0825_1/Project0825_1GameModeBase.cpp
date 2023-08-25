// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project0825_1GameModeBase.h"
#include <Blueprint/UserWidget.h>

void AProject0825_1GameModeBase::BeginPlay() {
	Super::BeginPlay();
	CHangeMenuWidget(StartingWidgetClass);
}

void AProject0825_1GameModeBase::CHangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}
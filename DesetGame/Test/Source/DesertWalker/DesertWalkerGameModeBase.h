// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DesertWalkerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DESERTWALKER_API ADesertWalkerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> HUDWidget;
};

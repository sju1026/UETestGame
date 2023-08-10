// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "MyTestGameCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API AMyTestGameCharacter : public ABasicCharacter
{
	GENERATED_BODY()
	
public:
	AMyTestGameCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FolloCamera;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

private:
	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus();
};

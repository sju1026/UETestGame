// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UCLASS()
class DESERTWALKER_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Attack_Melee();

	UFUNCTION(BlueprintCallable)
	void Attack_Melee_End();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDuringAttack;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* AttackCombo_AnimMt;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* LastAttack_Anims;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//	UAnimMontage* Attack_Melee_Anim01;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//	UAnimMontage* Attack_Melee_Anim02;

	//UPROPERTY(EditDefaultsOnly, Category = Pawn)
	//	UAnimMontage* Attack_Melee_Anim03;

	int ComboAttack_Num;
};

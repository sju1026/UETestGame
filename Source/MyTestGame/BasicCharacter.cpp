// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "MyTestWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	//HitFX = ParticleAsset.Object;

	isDuringAttack = false;
	ComboAttack_Num = 0;
	myHealth = 0.f;
	myMaxHealth = 100.0f;

	myHealth = myMaxHealth;
}

////////////////////////////////////////////////////////////////////////
// Weapon

USkeletalMeshComponent* ABasicCharacter::GetSpesificPawnMesh() const
{
	return GetMesh();
}

FName ABasicCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ABasicCharacter::EquipWeapon(AMyTestWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}


void ABasicCharacter::AddWeapon(AMyTestWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ABasicCharacter::SetCurrentWeapon(AMyTestWeapon* NewWeapon, AMyTestWeapon* LastWeapon)
{
	AMyTestWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon)
	{
		NewWeapon->SetOwninPawn(this);
		NewWeapon->OnEquip(LastWeapon);


	}
}

void ABasicCharacter::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	if (DefaultInventoryClasses[0])
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* WRLD = GetWorld();
		AMyTestWeapon* NewWeapon = WRLD->SpawnActor<AMyTestWeapon>(DefaultInventoryClasses[0], SpawnInfo);
		AddWeapon(NewWeapon);
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}

}

//----------------------------------------------------------------------

void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage, 1.0f);
	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}

}

void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{

	myHealth = FMath::Min(0.f, myHealth);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller != NULL)
	{
		Controller->UnPossess();
	}

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasicCharacter::DeathAnimationEnd, DeathAnimDuration, false);

}

void ABasicCharacter::DeathAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasicCharacter::Attack_Melee()
{
	if (!isDuringAttack)
	{
		if (ComboAttack_Num < 3)
		{
			int tmp_Num = rand() % 3 + 1;
			FString PlaySection = "Attack_" + FString::FromInt(tmp_Num);
			PlayAnimMontage(Attack_AnimMontage, 1.f, FName(*PlaySection));
			ComboAttack_Num++;

			isDuringAttack = true;

		}
		else
		{
			PlayAnimMontage(Attack_AnimMontage, 1.f, FName("Attack04"));
			ComboAttack_Num = 0;

			isDuringAttack = true;
		}
	}
}

void ABasicCharacter::Attack_Melee_End()
{
	isDuringAttack = false;
}


float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{


	if (myHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (myGetDamage > 0.f)
	{
		myHealth -= myGetDamage;
	}


	if (myHealth <= 0)
	{
		PlayAnimMontage(Death_AnimMontage, 1.0f);
		Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), myHealth));
	}


	return myGetDamage;
}



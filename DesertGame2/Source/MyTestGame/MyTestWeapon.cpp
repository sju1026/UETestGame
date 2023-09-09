// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestWeapon.h"
#include "MyTestCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"

// Sets default values
AMyTestWeapon::AMyTestWeapon(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(5.f, 5.f, 5.f));
	WeaponCollision->AttachTo(WeaponMesh, "DamageSocket");

}

// ==============================Weapon===================================
void AMyTestWeapon::SetOwningPawn(ABasicCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AMyTestWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpesificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachTo(PawnMesh, AttachPoint);
	}
}

void AMyTestWeapon::OnEquip(const AMyTestWeapon* LastWeapon)
{
	AttachMeshToPawn();
	WeaponMesh->SetHiddenInGame(false);
}

void AMyTestWeapon::OnUnEqip()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->SetHiddenInGame(true);
}

// =======================================================================

// Called when the game starts or when spawned
void AMyTestWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTestWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTestWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// AMyTestCharacter* MyPlayer = Cast<AMyTestCharacter>(StaticClass());

	if (OtherActor->IsA(AActor::StaticClass())) { // && MyPlayer->isDuringAttack
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "ApplyDamage!");
	}
}


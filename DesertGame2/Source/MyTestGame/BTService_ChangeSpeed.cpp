// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"
#include "MyTestGameBot.h"
#include "MyTestGameAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed() {
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Chage Speed");

}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* mode_momory)
{
	Super::OnBecomeRelevant(owner_comp, mode_momory);
	auto const cont = owner_comp.GetAIOwner();
	AMyTestGameBot* const npcBot = Cast<AMyTestGameBot>(cont->GetPawn());
	npcBot->GetCharacterMovement()->MaxWalkSpeed = speed;
}

FString UBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the NpcBot speed");
}

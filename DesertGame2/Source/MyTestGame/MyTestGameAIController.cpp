// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "MyTestCharacter.h"
#include "MyTestGameBot.h"
#include "blackboard_keys.h"

AMyTestGameAIController::AMyTestGameAIController(FObjectInitializer const& object_intializer) {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/_My/AI/BT_MyTestGameBot.BT_MyTestGameBot'"));
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_tree_Comp = object_intializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_intializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	setup_perception_system();
}

void AMyTestGameAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(btree);
	behavior_tree_Comp->StartTree(*btree);
}

void AMyTestGameAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}

	/*AMyTestGameBot* Bot = Cast<AMyTestGameBot>(pawn);
	if (Bot && Bot->BotBehavior) {
		if (Bot->BotBehavior->BlackboardAsset) {
			blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}
		behavior_tree_Comp->StartTree(*(Bot->BotBehavior));
	}*/
}

void AMyTestGameAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AMyTestGameAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) {
		return FRotator(0.0f, 0.0f, 0.0f);
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}


void AMyTestGameAIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<AMyTestCharacter>(actor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Find Player!!!!");
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

UBlackboardComponent* AMyTestGameAIController::get_blackboard() const
{
	return blackboard;
}

void AMyTestGameAIController::setup_perception_system()
{
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	sight_config->SightRadius = 500.0f;
	sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
	sight_config->PeripheralVisionAngleDegrees = 90.0f;
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyTestGameAIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}

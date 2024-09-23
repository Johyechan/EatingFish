// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/BTs/BTTask_NormalAttack.h"
#include "Enemies/Character/EFEnemyFishBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "AIModule/Classes/AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemies/Character/EFEnemyFishBase.h"

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEFEnemyFishBase* Self = Cast<AEFEnemyFishBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Self) {
		Self->DoAttack();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

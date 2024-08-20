// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/BTs/BTTask_NormalAttack.h"
#include "Enemies/Character/EFEnemyFishBase.h"

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEFEnemyFishBase* Self = Cast<AEFEnemyFishBase>(OwnerComp.GetOwner());
	if (Self) {
		Self->DoAttack();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

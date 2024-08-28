// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/EFEnemyFishAI.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "Character/EFCharacterPlayer.h"

AEFEnemyFishAI::AEFEnemyFishAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/EF/AI/EFFishBB.EFFishBB"));
	if (BBAssetRef.Object) {
		BBoard = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/EF/AI/EFFishBT.EFFishBT"));
	if (BTAssetRef.Object) {
		Tree = BTAssetRef.Object;
	}
}

void AEFEnemyFishAI::RunAI()
{
	UBlackboardComponent* BBPtr = Blackboard.Get();
	if (UseBlackboard(BBoard, BBPtr)) {
		AEFCharacterPlayer* Ctrl = Cast<AEFCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Ctrl) {
			Blackboard->SetValueAsObject(TEXT("Target"), Ctrl);
			UE_LOG(LogTemp, Warning, TEXT("TARGETSETTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"));
		}

		bool RunRes = RunBehaviorTree(Tree);
		ensure(RunRes);
	}
}

void AEFEnemyFishAI::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp) {
		BTComp->StopTree();
	}
}

void AEFEnemyFishAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

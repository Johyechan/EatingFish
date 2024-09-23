// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EFEnemyFishAI.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API AEFEnemyFishAI : public AAIController
{
	GENERATED_BODY()

public:
	AEFEnemyFishAI();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, Category = MyBTs)
	TObjectPtr<class UBlackboardData> BBoard;

	UPROPERTY(VisibleAnywhere, Category = MyBTs)
	TObjectPtr<class UBehaviorTree> Tree;
};

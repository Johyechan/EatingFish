// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EFEnemySource.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EATINGFISH_API UEFEnemySource : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEFEnemySource();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void SpawnEnemy();

protected:
	UPROPERTY()
	TArray<TSubclassOf<class AEFEnemyFishBase>> SpawnableEnemies;
	
	UPROPERTY(EditAnywhere, Category = SpawnParams)
	float SpawnGap;

	UPROPERTY(EditAnywhere, Category = SpawnParams)
	float SpawnRange;

	FTimerHandle SpawnTimer;
};

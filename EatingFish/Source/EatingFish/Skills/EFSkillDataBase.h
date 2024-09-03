// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/EFStatusEntities.h"
#include "EFSkillDataBase.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API UEFSkillDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float Range;

	virtual void Use(IEFStatusEntities* User);
	virtual uint8 GetSkillUseState();

	FPrimaryAssetId GetPrimaryAssetId() const override {
		return FPrimaryAssetId("EFSkillDataBase", GetFName());
	}
};

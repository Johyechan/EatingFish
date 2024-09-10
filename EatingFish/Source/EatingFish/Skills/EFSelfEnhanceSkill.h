// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/EFSkillDataBase.h"
#include "EFSelfEnhanceSkill.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API UEFSelfEnhanceSkill : public UEFSkillDataBase
{
	GENERATED_BODY()

public:
	virtual void Use(IEFStatusEntities* User) override;
	virtual uint8 GetSkillUseState() override;
	
	void RemoveEff(IEFStatusEntities* User);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	EStatusType UpStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float MultAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float EffectTime;

	FTimerHandle EffectTimeHandle;
};

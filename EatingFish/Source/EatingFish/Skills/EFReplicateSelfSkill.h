// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/EFSkillDataBase.h"
#include "EFReplicateSelfSkill.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API UEFReplicateSelfSkill : public UEFSkillDataBase
{
	GENERATED_BODY()
	
public:
	virtual void Use(IEFStatusEntities* User) override;
	virtual uint8 GetSkillUseState() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Duplicate)
	float CopyRange;

};

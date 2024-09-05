// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/EFSkillDataBase.h"
#include "EFFlameThrowSkill.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API UEFFlameThrowSkill : public UEFSkillDataBase
{
	GENERATED_BODY()

public :
	virtual void Use(IEFStatusEntities* User) override;
	virtual uint8 GetSkillUseState() override;

	void ShootFlame(IEFStatusEntities* User);

	void EndFlame(IEFStatusEntities* User);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float PowerMult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	float FlameTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	uint8 FlameCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skills)
	TObjectPtr<class UMaterialInterface> OverlayMat;

	FTimerHandle FlameTickHandle;
	FTimerHandle FlameCountHandle;
};

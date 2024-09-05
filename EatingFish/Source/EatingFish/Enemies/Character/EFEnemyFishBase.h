// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Interface/EFSkillUsers.h"
#include "GameFramework/Character.h"
#include "Game/EFStat.h"
#include "Character/EFStatusEntities.h"
#include "EFEnemyFishBase.generated.h"

UCLASS()
class EATINGFISH_API AEFEnemyFishBase : public ACharacter, public IEFSkillUsers, public IEFStatusEntities
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEFEnemyFishBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetAtkRange();
	float GetLife();

	virtual void DecreaseHp(float Amt);
	virtual void DoDie();

	virtual void DoAttack();

	virtual void Bite();

	void DeleteSelf();

	void EndAnim(UAnimMontage* Montage, bool IsPropEnded);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> AttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> DieAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> SkillAnim;

	FEFStat Status;

	void UseSkill() override; // Called by BTNode
	uint8 ExamineSkillUse(AActor* Target) override; // condition check in BT

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TArray<TObjectPtr<class UEFSkillDataBase>> Skills;

	// IEFStatusEntities을(를) 통해 상속됨
	FEFStat GetStat() override;
	void SetStat(float Amount, EStatusType Type) override;
};

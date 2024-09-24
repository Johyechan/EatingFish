// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Character/EFEnemyFishFire.h"
#include "Skills/EFSkillDataBase.h"

AEFEnemyFishFire::AEFEnemyFishFire()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FishObjRef(TEXT("/Game/AnimatedFantasyFish/Meshes/SM_Ancient_fish.SM_Ancient_fish"));
	if (FishObjRef.Object) {
		GetMesh()->SetSkeletalMesh(FishObjRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimRef(TEXT("/Game/AnimatedFantasyFish/Animations/EFAnim_Ancient_fish_attacking_Montage.EFAnim_Ancient_fish_attacking_Montage"));
	if (AttackAnimRef.Object) {
		AttackAnim = AttackAnimRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DieAnimRef(TEXT("/Game/AnimatedFantasyFish/Animations/EFAnim_Ancient_fish_death_Montage.EFAnim_Ancient_fish_death_Montage"));
	if (DieAnimRef.Object) {
		DieAnim = DieAnimRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SkillAnimRef(TEXT("/Game/AnimatedFantasyFish/Animations/EFAnim_Ancient_fish_skill_Montage.EFAnim_Ancient_fish_skill_Montage"));
	if (SkillAnimRef.Object) {
		SkillAnim = SkillAnimRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClassRef(TEXT("/Game/EF/Animations/EFFireFishAnim.EFFireFishAnim_C"));
	if (AnimClassRef.Class) {
		GetMesh()->SetAnimClass(AnimClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UEFSkillDataBase> FlameThrowRef(TEXT("/Game/EF/Datas/EFFlameThrow.EFFlameThrow"));
	if (FlameThrowRef.Object) {
		Skills.Add(FlameThrowRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UEFSkillDataBase> PowerUpRef(TEXT("/Game/EF/Datas/EFPowerUp.EFPowerUp"));
	if (PowerUpRef.Object) {
		Skills.Add(PowerUpRef.Object);
	}
	
	Status.MaxLife = 500;
	Status.AtkRange = 125;
}

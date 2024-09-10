// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/EFFlameThrowSkill.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInterface.h"

void UEFFlameThrowSkill::Use(IEFStatusEntities* User)
{
	ACharacter* UserCharacter = Cast<ACharacter>(User);
	if (UserCharacter) {
		UserCharacter->GetMesh()->SetOverlayMaterial(OverlayMat);
	}

	GetWorld()->GetTimerManager().SetTimer(FlameTickHandle, FTimerDelegate::CreateLambda([this, User]() {ShootFlame(User); }), FlameTick, true);

	GetWorld()->GetTimerManager().SetTimer(FlameCountHandle, FTimerDelegate::CreateLambda([this, User]() {EndFlame(User); }), FlameTick * FlameCount, false);
}

uint8 UEFFlameThrowSkill::GetSkillUseState()
{
	return Super::GetSkillUseState();
	
}

void UEFFlameThrowSkill::ShootFlame(IEFStatusEntities* User)
{
	FHitResult OutHitRes;
	FCollisionQueryParams Params;

	APawn* UserPawn = Cast<APawn>(User);
	if (UserPawn) {
		const FVector StartPos = UserPawn->GetActorLocation();
		const FVector EndPos = StartPos + UserPawn->GetActorForwardVector() * Range;

		bool IsHit = GetWorld()->SweepSingleByChannel(OutHitRes, StartPos, EndPos, FQuat::Identity, ECC_Camera /*�����÷��̾�����ϴ�ä��*/, FCollisionShape::MakeSphere(Range), Params);
		if (IsHit) {
			UGameplayStatics::ApplyDamage(OutHitRes.GetActor(), User->GetStat().Power * PowerMult, UserPawn->GetController(), nullptr, nullptr);
		}

		
	}
}

void UEFFlameThrowSkill::EndFlame(IEFStatusEntities* User)
{
	FlameTickHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, Cooldown, false);

	ACharacter* UserCharacter = Cast<ACharacter>(User);
	if (UserCharacter) {
		UserCharacter->GetMesh()->SetOverlayMaterial(nullptr);
	}
}

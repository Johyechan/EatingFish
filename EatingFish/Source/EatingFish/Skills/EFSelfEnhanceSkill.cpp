// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/EFSelfEnhanceSkill.h"

void UEFSelfEnhanceSkill::Use(IEFStatusEntities* User)
{
	Super::Use(User);
	float V = 0;
	switch (UpStat)
	{
	case EStatusType::MaxLife:
		V = User->GetStat().MaxLife;
		break;
	case EStatusType::Power:
		V = User->GetStat().Power;
		break;
	case EStatusType::AtkRange:
		V = User->GetStat().AtkRange;
		break;
	case EStatusType::MoveSpeed:
		V = User->GetStat().MoveSpeed;
		break;
	}
	User->SetStat(V * MultAmount, UpStat);

	GetWorld()->GetTimerManager().SetTimer(EffectTimeHandle, FTimerDelegate::CreateLambda([this, User]() {RemoveEff(User); }), EffectTime, false);
}

uint8 UEFSelfEnhanceSkill::GetSkillUseState()
{
	return Super::GetSkillUseState();
}

void UEFSelfEnhanceSkill::RemoveEff(IEFStatusEntities* User)
{
	float V = 0;
	switch (UpStat)
	{
	case EStatusType::MaxLife:
		V = User->GetStat().MaxLife;
		break;
	case EStatusType::Power:
		V = User->GetStat().Power;
		break;
	case EStatusType::AtkRange:
		V = User->GetStat().AtkRange;
		break;
	case EStatusType::MoveSpeed:
		V = User->GetStat().MoveSpeed;
		break;
	}
	User->SetStat(V / MultAmount, UpStat);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/EFSkillDataBase.h"

void UEFSkillDataBase::Use(IEFStatusEntities* User)
{
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, Cooldown, false);
}

uint8 UEFSkillDataBase::GetSkillUseState()
{
	return CooldownHandle.IsValid() && !GetWorld()->GetTimerManager().IsTimerActive(CooldownHandle);
}

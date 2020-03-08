// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureStatManagerComponent.h"

DEFINE_LOG_CATEGORY(LogCreatureStatManagerComponent);

UCreatureStatManagerComponent::UCreatureStatManagerComponent()
{
	AddStat(EStatTypeEnum::Health, 0);
	AddStat(EStatTypeEnum::MaxHealth, 0);
	AddStat(EStatTypeEnum::Damage, 0);
	AddStat(EStatTypeEnum::AutoAttackRange, 0);
}

float UCreatureStatManagerComponent::GetHealth()
{
	float Health;
	GetModifiedStatValue(EStatTypeEnum::Health, Health);

	float MaxHealth;
	GetModifiedStatValue(EStatTypeEnum::MaxHealth, MaxHealth);

	float CheckedHealth = Health > MaxHealth ? MaxHealth : Health;
	CheckedHealth = CheckedHealth < 0 ? 0 : CheckedHealth;

	if (CheckedHealth != Health)
	{
		SetStat(EStatTypeEnum::Health, CheckedHealth);
	}

	return CheckedHealth;
}
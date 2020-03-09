// Fill out your copyright notice in the Description page of Project Settings.

#include "StatManagerHelpers.h"

#include "Components/StatManagerComponent.h"

DEFINE_LOG_CATEGORY(LogStatManagerHelpers);

UStatManagerHelpers::UStatManagerHelpers()
{
}

UStatManagerHelpers::~UStatManagerHelpers()
{
}

float UStatManagerHelpers::GetHealth(UStatManagerComponent* StatManagerComponent)
{
	if (StatManagerComponent == nullptr)
	{
		return -1;
	}

	float Health;
	StatManagerComponent->GetModifiedStatValue(EStatTypeEnum::Health, Health);

	float MaxHealth;
	StatManagerComponent->GetModifiedStatValue(EStatTypeEnum::MaxHealth, MaxHealth);

	float CheckedHealth = Health > MaxHealth ? MaxHealth : Health;
	CheckedHealth = CheckedHealth < 0 ? 0 : CheckedHealth;

	if (CheckedHealth != Health)
	{
		StatManagerComponent->SetStat(EStatTypeEnum::Health, CheckedHealth);
	}

	return CheckedHealth;
}
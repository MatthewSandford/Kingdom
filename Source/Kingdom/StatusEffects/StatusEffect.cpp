// Fill out your copyright notice in the Description page of Project Settings.

#include "StatusEffect.h"

UStatusEffect::UStatusEffect()
	: Period(INVALID_PERIOD)
	, Duration(INVALID_DURATION)
	, PeriodTimer(0)
	, DurationRemaining(INVALID_DURATION)
{
}

UStatusEffect::~UStatusEffect()
{
}

void UStatusEffect::Init()
{
	if (Duration != INVALID_DURATION)
	{
		DurationRemaining = Duration;
	}
	PostInit();
}

void UStatusEffect::Tick(float DeltaTime)
{
	if (!HasEnded())
	{
		if (Period != INVALID_PERIOD)
		{
			PeriodTimer += DeltaTime;
			if (PeriodTimer >= Period)
			{
				PeriodTimer -= Period;
				DoTick();
			}
		}

		if (Duration != INVALID_DURATION)
		{
			DurationRemaining -= DeltaTime;
			DurationRemaining = DurationRemaining < 0 ? 0 : DurationRemaining;
		}
	}
}
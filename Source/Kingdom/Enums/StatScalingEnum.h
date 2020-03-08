// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)	
enum class EStatScalingEnum : uint8
{
	Flat 				UMETA(DisplayName = "Flat"),
	PercentageBase		UMETA(DisplayName = "Percentage Base"),
	PercentageModified	UMETA(DisplayName = "Percentage Modified"),
	PercentageBonus		UMETA(DisplayName = "Percentage Bonus")
};
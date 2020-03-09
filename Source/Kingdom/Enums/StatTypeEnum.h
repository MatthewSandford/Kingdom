// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)	
enum class EStatTypeEnum : uint8
{
	Health 				UMETA(DisplayName = "Health"),
	MaxHealth 			UMETA(DisplayName = "MaxHealth"),
	Damage				UMETA(DisplayName = "Damage"),
	AttackSpeed			UMETA(DisplayName = "Attack Speed"),
	AutoAttackRange		UMETA(DisplayName = "Auto Attack Range"),
	CooldownReduction	UMETA(DisplayName = "CooldownReduction")
};
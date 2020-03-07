// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EActivateAbilityResultEnum : uint8
{
	CostsNotSatisfied 		UMETA(DisplayName = "Costs not satisfied"),
	Success					UMETA(DisplayName = "Success"),
};
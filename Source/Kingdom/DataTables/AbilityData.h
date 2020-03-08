// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/StatTypeEnum.h"
#include "Game/Abilities/Ability.h"
#include "StatScaling.h"

#include "AbilityData.generated.h"

USTRUCT(BlueprintType)
struct FAbilityData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStatScaling> Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAbility> Ability;
};
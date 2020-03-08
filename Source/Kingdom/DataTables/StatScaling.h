// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/StatScalingEnum.h"
#include "Enums/StatTypeEnum.h"

#include "StatScaling.generated.h"

USTRUCT(BlueprintType)
struct FStatScaling : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatTypeEnum StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatScalingEnum Scaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};
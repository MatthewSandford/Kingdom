// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/StatTypeEnum.h"
#include "Misc/Constants.h"
#include "Misc/Types.h"
#include "UObject/Class.h"

#include "StatModifier.generated.h"

UCLASS(BlueprintType)
class KINGDOM_API UStatModifier : public UObject
{
	GENERATED_BODY()

public:
	UStatModifier();
	virtual ~UStatModifier();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 Priority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	EStatTypeEnum StatType;

	virtual float GetModifiedStatValue(float StatValue) const { return 0; }
};

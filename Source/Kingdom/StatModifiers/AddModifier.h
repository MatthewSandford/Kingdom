// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatModifiers/StatModifier.h"

#include "AddModifier.generated.h"

UCLASS(BlueprintType)
class KINGDOM_API UAddModifier : public UStatModifier
{
	GENERATED_BODY()

public:
	UAddModifier();
	~UAddModifier();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float AddValue;

	virtual float GetModifiedStatValue(float StatValue) const override;
};

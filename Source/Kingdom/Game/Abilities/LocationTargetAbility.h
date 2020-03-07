// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"

#include "LocationTargetAbility.generated.h"

UCLASS(Blueprintable)
class KINGDOM_API ULocationTargetAbility : public UAbility
{
	GENERATED_BODY()

public:

	// --- Public Variables ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetLocation;

	// --- Public Function ---

	ULocationTargetAbility();
	~ULocationTargetAbility();
};

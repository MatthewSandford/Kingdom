// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"

#include "SkillShotAbility.generated.h"

UCLASS(Blueprintable)
class KINGDOM_API USkillShotAbility : public UAbility
{
	GENERATED_BODY()

public:

	// --- Public Variables ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetLocation;

	// --- Public Function ---

	USkillShotAbility();
	~USkillShotAbility();
};

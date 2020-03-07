// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatManagerComponent.h"
#include "CreatureStatManagerComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCreatureStatManagerComponent, Log, All);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KINGDOM_API UCreatureStatManagerComponent : public UStatManagerComponent
{
	GENERATED_BODY()

public:
	UCreatureStatManagerComponent();

	// Health:

	UFUNCTION(BlueprintCallable)
	float GetHealth();
};
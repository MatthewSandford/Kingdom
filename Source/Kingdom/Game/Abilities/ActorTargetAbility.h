// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "GameFramework/Actor.h"

#include "ActorTargetAbility.generated.h"

UCLASS(Blueprintable)
class KINGDOM_API UActorTargetAbility : public UAbility
{
	GENERATED_BODY()

public:

	// --- Public Variables ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor;

	// --- Public Function ---

	UActorTargetAbility();
	~UActorTargetAbility();
};

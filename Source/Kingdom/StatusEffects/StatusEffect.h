// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatModifiers/StatModifier.h"
#include "Misc/Types.h"
#include "UObject/Class.h"

#include "StatusEffect.generated.h"

#define INVALID_PERIOD -1.0f
#define INVALID_DURATION -1.0f

UCLASS(Blueprintable)
class KINGDOM_API UStatusEffect : public UObject
{
	GENERATED_BODY()

public:
	UStatusEffect();
	virtual ~UStatusEffect();

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void PostInit();

	UFUNCTION(BlueprintImplementableEvent)
	void Apply();

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void End();

	bool HasEnded() { return DurationRemaining == 0; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float Period;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float Duration;

	UPROPERTY(BlueprintReadOnly)
	AActor* Actor;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void DoTick();

private:
	float PeriodTimer;
	float DurationRemaining;

};

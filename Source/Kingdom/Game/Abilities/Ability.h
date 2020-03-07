// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Task.h"
#include "Enums/ActivateAbilityResult.h"
#include "Enums/AbilityTypeEnum.h"
#include "Enums/StatTypeEnum.h"

#include "Ability.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAbility, Log, All);

class UStatManagerComponent;

UCLASS(Blueprintable)
class KINGDOM_API UAbility : public UTask
{
	GENERATED_BODY()

public:

	// --- Public Variables ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStatTypeEnum, float> Cost;

	// --- Public Functions ---

	UAbility();
	~UAbility();

	UFUNCTION(BlueprintCallable)
	float GetCooldownTimer() const { return CooldownTimer; }

	virtual bool CanExecute_Implementation() override final;
	virtual void Execute_Implementation() override final;
	void Tick(float DeltaTime);

protected:

	// --- Protected Variables ---
	EAbilityTypeEnum AbilityType;

	// --- Protected Functions ---

	UFUNCTION(BlueprintImplementableEvent)
	void PreActivateAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateAbility();

	UFUNCTION(BlueprintNativeEvent)
	EActivateAbilityResultEnum CanActivate();

	virtual EActivateAbilityResultEnum CanActivate_Implementation() { return EActivateAbilityResultEnum::Success; };

private:

	// --- Private Variables ---
	float CooldownTimer;

	// --- Private Functions ---
	bool HasCosts() const;
	void ReduceCooldown(float DeltaTime);
	UStatManagerComponent* GetActorStatManagerComponent() const;
};

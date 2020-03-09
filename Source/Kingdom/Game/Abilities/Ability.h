// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Task.h"
#include "Enums/ActivateAbilityResult.h"
#include "Enums/AbilityTypeEnum.h"
#include "Enums/StatTypeEnum.h"

#include "Ability.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAbility, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateAbilityEvent, UAbility*, AbilityTask);

struct FAbilityData;
class UStatManagerComponent;

UCLASS(Blueprintable)
class KINGDOM_API UAbility : public UTask
{
	GENERATED_BODY()

public:

	UAbility();
	~UAbility();

	UFUNCTION(BlueprintNativeEvent)
	float GetCooldown();

	virtual float GetCooldown_Implementation();

	virtual bool CanExecute_Implementation() override final;
	virtual void Execute_Implementation() override final;

	EAbilityTypeEnum GetAbilityType() const { return AbilityType; }
	static bool CanPayCosts(FName AbilityName, const AActor* Actor, const UObject* Caller);
	static const FAbilityData* GetAbilityData(FName AbilityName, const UObject* Caller);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityName;

	FActivateAbilityEvent ActivateAbilityEvent;

protected:

	EAbilityTypeEnum AbilityType;

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateAbility();

	UFUNCTION(BlueprintNativeEvent)
	EActivateAbilityResultEnum CanActivate();

	static UStatManagerComponent* GetStatManagerComponent(const AActor* Actor);
	virtual EActivateAbilityResultEnum CanActivate_Implementation() { return EActivateAbilityResultEnum::Success; };
};

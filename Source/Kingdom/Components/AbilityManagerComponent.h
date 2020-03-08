// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/Abilities/Ability.h"

#include "AbilityManagerComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAbilityManageComponent, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	struct Ability
	{
		Ability()
			: Timer(0)
		{
		}

		FName AbilityName;
		float Timer;
		float Cooldown;
		TSubclassOf<class UAbility> AbilityTask;
	};

public:	
	UAbilityManagerComponent();

	UFUNCTION(BlueprintCallable)
	UAbility* GetAbilityTask(int32 Index);

	UFUNCTION(BlueprintCallable)
	int32 AddAbility(FName AbilityName);

	UFUNCTION(BlueprintCallable)
	float GetCooldownTimer(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	void SetTargets(const AActor* InTargetActor, FVector InTargetLocation);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	Ability* GetAbility(FName AbilityName);
	void TickAbilities(float DeltaTime);

	UFUNCTION()
	void AbilityActivated(FName AbilityName);

	FVector TargetLocation;
	const AActor* TargetActor;
	TArray<Ability> Abilities;
};

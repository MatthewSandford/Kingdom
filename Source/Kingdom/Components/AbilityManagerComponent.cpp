// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityManagerComponent.h"

#include "DataTables/AbilityData.h"
#include "Game/KingdomGameInstance.h"
#include "StatManagerComponent.h"

DEFINE_LOG_CATEGORY(LogAbilityManageComponent);

UAbilityManagerComponent::UAbilityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

int32 UAbilityManagerComponent::AddAbility(FName AbilityName)
{
	const FAbilityData* AbilityData = UAbility::GetAbilityData(AbilityName, this);
	if (AbilityData == nullptr)
	{
		UE_LOG(LogAbilityManageComponent, Error, TEXT("No ability data found for %s"), *AbilityName.ToString());
		return -1;
	}

	AbilityTracker NewAbilityTracker;
	NewAbilityTracker.AbilityName = AbilityName;
	NewAbilityTracker.Cooldown = AbilityData->Cooldown;
	NewAbilityTracker.AbilityTask = AbilityData->Ability;

	return Abilities.Add(NewAbilityTracker);
}

UAbility* UAbilityManagerComponent::GetAbilityTaskToCastByName(FName AbilityName)
{
	AbilityTracker* Ability = GetAbilityTracker(AbilityName);
	if (!CanCastAbility(*Ability))
	{
		return nullptr;
	}

	return GetAbilityTaskToCast(*Ability);
}

UAbility* UAbilityManagerComponent::GetAbilityTaskToCastByIndex(int32 Index)
{
	AbilityTracker* Ability = GetAbilityTracker(Index);
	if (Ability == nullptr)
	{
		return nullptr;
	}

	return GetAbilityTaskToCast(*Ability);
}

float UAbilityManagerComponent::GetCooldownTimerByName(FName AbilityName)
{
	const AbilityTracker* Ability = GetAbilityTracker(AbilityName);
	if (Ability == nullptr)
	{
		return -1;
	}

	return Ability->Timer;
}

float UAbilityManagerComponent::GetCooldownTimerByIndex(int32 Index)
{
	const AbilityTracker* Ability = GetAbilityTracker(Index);
	if (Ability == nullptr)
	{
		return -1;
	}

	return Ability->Timer;
}

void UAbilityManagerComponent::SetTargets(const AActor* InTargetActor, FVector InTargetLocation)
{
	TargetActor = InTargetActor;
	TargetLocation = InTargetLocation;
}

void UAbilityManagerComponent::TickAbilities(float DeltaTime)
{
	for (AbilityTracker& Ability : Abilities)
	{
		if (Ability.Timer > 0)
		{
			Ability.Timer -= DeltaTime;
			Ability.Timer = Ability.Timer < 0 ? 0 : Ability.Timer;
		}
	}
}

void UAbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	TickAbilities(DeltaTime);
}

UAbilityManagerComponent::AbilityTracker* UAbilityManagerComponent::GetAbilityTracker(int32 Index)
{
	if (Index >= Abilities.Num() && Index < 0)
	{
		UE_LOG(LogAbilityManageComponent, Error, TEXT("Invalid index: %d"), Index);
		return nullptr;
	}
	return &Abilities[Index];
}

UAbilityManagerComponent::AbilityTracker* UAbilityManagerComponent::GetAbilityTracker(FName AbilityName)
{
	for (AbilityTracker& Ability : Abilities)
	{
		if (Ability.AbilityName == AbilityName)
		{
			return &Ability;
		}
	}
	return nullptr;
}

bool UAbilityManagerComponent::CanCastAbility(const AbilityTracker& Ability)
{
	return Ability.Timer == 0 && UAbility::CanPayCosts(Ability.AbilityName, GetOwner(), this);
}

UAbility* UAbilityManagerComponent::GetAbilityTaskToCast(const AbilityTracker& Ability)
{
	if (!CanCastAbility(Ability))
	{
		return nullptr;
	}

	UAbility* AbilityTask = NewObject<UAbility>(GetOwner(), Ability.AbilityTask);
	AbilityTask->Controller = Cast<APawn>(GetOwner())->GetController();
	AbilityTask->ActivateAbilityEvent.AddDynamic(this, &UAbilityManagerComponent::AbilityActivated);

	return AbilityTask;
}

void UAbilityManagerComponent::AbilityActivated(UAbility* AbilityTask)
{
	AbilityTracker* Ability = GetAbilityTracker(AbilityTask->AbilityName);
	if (Ability == nullptr)
	{
		return;
	}

	Ability->Timer = AbilityTask->GetCooldown();

	const FAbilityData* AbilityData = UAbility::GetAbilityData(AbilityTask->AbilityName, this);
	if (AbilityData == nullptr)
	{
		return;
	}

	TArray<UStatManagerComponent*> OwnedComponents;
	GetOwner()->GetComponents<UStatManagerComponent>(OwnedComponents);

	if (OwnedComponents.Num() != 1)
	{
		UE_LOG(LogAbilityManageComponent, Error, TEXT("Owning actor does not have the correct number of stat manager components"));
		return;
	}

	UStatManagerComponent* StatManagerComponent = OwnedComponents[0];
	if (StatManagerComponent == nullptr)
	{
		return;
	}

	for (const FStatScaling& Scaling : AbilityData->Cost)
	{
		float CostValue = 0.0f;
		StatManagerComponent->GetStatScalingValue(Scaling, CostValue);
		StatManagerComponent->DecrementStat(Scaling.StatType, CostValue);
	}
}
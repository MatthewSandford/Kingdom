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

	Ability NewAbility;
	NewAbility.AbilityName = AbilityName;
	NewAbility.Cooldown = AbilityData->Cooldown;
	NewAbility.AbilityTask = AbilityData->Ability;

	return Abilities.Add(NewAbility);
}

UAbility* UAbilityManagerComponent::GetAbilityTask(int32 Index)
{
	if (Index >= Abilities.Num() && Index < 0)
	{
		UE_LOG(LogAbilityManageComponent, Error, TEXT("Invalid index: %d"), Index);
		return false;
	}

	const Ability& Ability = Abilities[0];
	UAbility* AbilityTask = NewObject<UAbility>(this, Ability.AbilityTask);
	AbilityTask->Controller = Cast<APawn>(GetOwner())->GetController();
	AbilityTask->ActivateAbilityEvent.AddDynamic(this, &UAbilityManagerComponent::AbilityActivated);

	return AbilityTask;
}

float UAbilityManagerComponent::GetCooldownTimer(int32 Index) const
{
	if (Index >= 0 && Index < Abilities.Num())
	{
		UE_LOG(LogAbilityManageComponent, Error, TEXT("Invalid index: %d"), Index);
		return 0.0f;
	}
	return Abilities[Index].Timer;
}

void UAbilityManagerComponent::TickAbilities(float DeltaTime)
{
	for (const Ability& Ability : Abilities)
	{
	}
}

void UAbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	TickAbilities(DeltaTime);
}

void UAbilityManagerComponent::SetTargets(const AActor* InTargetActor, FVector InTargetLocation)
{
	TargetActor = InTargetActor;
	TargetLocation = InTargetLocation;
}

UAbilityManagerComponent::Ability* UAbilityManagerComponent::GetAbility(FName AbilityName)
{
	for (Ability& Ability : Abilities)
	{
		if (Ability.AbilityName == AbilityName)
		{
			return &Ability;
		}
	}
	return nullptr;
}

void UAbilityManagerComponent::AbilityActivated(FName AbilityName)
{
	Ability* Ability = GetAbility(AbilityName);
	if (Ability == nullptr)
	{
		return;
	}

	Ability->Timer = Ability->Cooldown;

	const FAbilityData* AbilityData = UAbility::GetAbilityData(AbilityName, this);
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
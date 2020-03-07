// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"

#include "Components/StatManagerComponent.h"

DEFINE_LOG_CATEGORY(LogAbility);

UAbility::UAbility() 
	: AbilityType(EAbilityTypeEnum::Simple)
	, CooldownTimer(0)
{
}

UAbility::~UAbility()
{
}

bool UAbility::HasCosts() const
{
	UStatManagerComponent* StatManagerComponent = GetActorStatManagerComponent();
	if (!StatManagerComponent)
	{
		return false;
	}

	for (const auto& Pair : Cost)
	{
		float StatValue = 0.0f;
		StatManagerComponent->GetBaseStatValue(Pair.Key, StatValue);

		if (StatValue < Pair.Value)
		{
			return false;
		}
	}

	return true;
}

bool UAbility::CanExecute_Implementation()
{
	if (!HasCosts() || CooldownTimer != 0)
	{
		return false;
	}
	return CanActivate() == EActivateAbilityResultEnum::Success;
}

void UAbility::Execute_Implementation()
{
	PreActivateAbility();

	EActivateAbilityResultEnum ActivateAbilityResult = CanActivate();
	if (ActivateAbilityResult != EActivateAbilityResultEnum::Success)
	{
		return;
	}

	UStatManagerComponent* StatManagerComponent = GetActorStatManagerComponent();
	if (!StatManagerComponent)
	{
		return;
	}

	for (const auto& Pair : Cost)
	{
		StatManagerComponent->DecrementStat(Pair.Key, Pair.Value);
	}

	CooldownTimer = Cooldown;
	ActivateAbility();
}

void UAbility::ReduceCooldown(float DeltaTime)
{
	if (CooldownTimer != 0)
	{
		CooldownTimer -= DeltaTime;
		CooldownTimer = CooldownTimer < 0 ? 0 : CooldownTimer;
	}
}

void UAbility::Tick(float DeltaTime)
{
	ReduceCooldown(DeltaTime);
}

UStatManagerComponent* UAbility::GetActorStatManagerComponent() const
{
	AActor* Actor = Controller->GetPawn();
	if (Actor == nullptr)
	{
		UE_LOG(LogAbility, Log, TEXT("No owning actor"));
		return nullptr;
	}

	TArray<UStatManagerComponent*> OwnedComponents;
	Actor->GetComponents<UStatManagerComponent>(OwnedComponents);

	if (OwnedComponents.Num() != 1)
	{
		UE_LOG(LogAbility, Log, TEXT("Owning actor does not have the correct number of stat manager components"));
		return nullptr;
	}

	return OwnedComponents[0];
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitiesComponent.h"

UAbilitiesComponent::UAbilitiesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

int32 UAbilitiesComponent::AddAbility(UAbility* Ability)
{
	return Abilities.Add(Ability);
}

UAbility* UAbilitiesComponent::GetAbility(int32 Index)
{
	if (Index >= 0 && Index < Abilities.Num())
	{
		return Abilities[Index];
	}
	return nullptr;
}

void UAbilitiesComponent::TickAbilities(float DeltaTime)
{
	for (auto* Ability : Abilities)
	{
		Ability->Tick(DeltaTime);
	}
}

void UAbilitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	TickAbilities(DeltaTime);
}


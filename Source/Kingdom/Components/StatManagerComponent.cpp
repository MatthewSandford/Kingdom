// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManagerComponent.h"

DEFINE_LOG_CATEGORY(LogStatManagerComponent);

UStatManagerComponent::UStatManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UStatManagerComponent::AddStat(EStatTypeEnum StatType, float Value)
{
	if (!Stats.Contains(StatType))
	{
		Stats.Add(StatType, Value);
		return true;
	}
	return false;
}

bool UStatManagerComponent::SetStat(EStatTypeEnum StatType, float Value)
{
	if (float* StatValue = Stats.Find(StatType))
	{
		*StatValue = Value;
		return true;
	}
	return false;
}

bool UStatManagerComponent::IncrementStat(EStatTypeEnum StatType, float Value)
{
	if (float* StatValue = Stats.Find(StatType))
	{
		*StatValue += Value;
		return true;
	}
	return false;
}

bool UStatManagerComponent::DecrementStat(EStatTypeEnum StatType, float Value)
{
	if (float* StatValue = Stats.Find(StatType))
	{
		*StatValue -= Value;
		return true;
	}
	return false;
}
bool UStatManagerComponent::GetBaseStatValue(EStatTypeEnum StatType, float& OutValue)
{
	if (float* StatValue = Stats.Find(StatType))
	{
		OutValue = *StatValue;
		return true;
	}

	UE_LOG(LogStatManagerComponent, Error, TEXT("Actor does not have stat %d"), StatType);
	return false;
}

bool UStatManagerComponent::GetModifiedStatValue(EStatTypeEnum StatType, float& OutValue)
{
	float StatValue = 0;
	if (!GetBaseStatValue(StatType, StatValue))
	{
		return false;
	}

	if (ModifierPriorityMap* PriorityMap = StatModifiers.Find(StatType))
	{
		for (const auto& PriorityMapPair : *PriorityMap)
		{
			for (const TWeakObjectPtr<UStatModifier>& StatModifier : PriorityMapPair.Value)
			{
				StatValue = StatModifier->GetModifiedStatValue(StatValue);
			}
		}
	}

	OutValue = StatValue;
	return true;
}
bool UStatManagerComponent::RemoveStat(EStatTypeEnum StatType)
{
	return Stats.Remove(StatType) > 0;
}

void UStatManagerComponent::AddStatusEffect(UStatusEffect* StatusEffect)
{
	if (!StatusEffect)
	{
		UE_LOG(LogStatManagerComponent, Error, TEXT("Trying to add null status effect"));
		return;
	}

	StatusEffect->Init();
	StatusEffect->Actor = GetOwner();
	StatusEffect->Apply();
	StatusEffects.Add(StatusEffect);

	// Now there is an active status effect enable ticking to process it's duration
	SetComponentTickEnabled(true);
}

bool UStatManagerComponent::RemoveStatusEffect(UStatusEffect* StatusEffect)
{
	if (!StatusEffect)
	{
		UE_LOG(LogStatManagerComponent, Error, TEXT("Trying to remove null status effect"));
		return false;
	}

	if (!StatusEffects.Contains(StatusEffect))
	{
		UE_LOG(LogStatManagerComponent, Error, TEXT("Could not find status effect to remove"));
		return false;
	}

	StatusEffect->End();
	StatusEffects.Remove(StatusEffect);

	// If there are now no active status effects disable ticking
	if (StatusEffects.Num() == 0)
	{
		SetComponentTickEnabled(false);
	}

	return true;
}

void UStatManagerComponent::TickStatusEffects(float DeltaTime)
{
	TArray<UStatusEffect*> StatusEffectToRemove;

	for (auto* StatusEffect : StatusEffects)
	{
		StatusEffect->Tick(DeltaTime);
		if (StatusEffect->HasEnded())
		{
			StatusEffectToRemove.Add(StatusEffect);
		}
	}

	for (auto* StatusEffect : StatusEffectToRemove)
	{
		RemoveStatusEffect(StatusEffect);
	}
}

void UStatManagerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	TickStatusEffects(DeltaTime);
}

void UStatManagerComponent::AddModifier(const UStatModifier* Modifier)
{
	ModifierPriorityMap& PriorityMap = StatModifiers.FindOrAdd(Modifier->StatType);
	ModifierArray& ModifierArray = PriorityMap.FindOrAdd(Modifier->Priority);
	ModifierArray.Add(Modifier);
}

bool UStatManagerComponent::RemoveModifier(const UStatModifier* Modifier)
{
	if (ModifierPriorityMap* PriorityMap = StatModifiers.Find(Modifier->StatType))
	{
		if (ModifierArray* ModifierArrayPtr = PriorityMap->Find(Modifier->Priority))
		{
			ModifierArrayPtr->Remove(Modifier);
		}
	}
	return false;
}
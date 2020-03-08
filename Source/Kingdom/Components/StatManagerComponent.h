// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataTables/StatScaling.h"
#include "Enums/StatTypeEnum.h"
#include "StatModifiers/StatModifier.h"
#include "StatusEffects/StatusEffect.h"
#include "Misc/Constants.h"
#include "Misc/Types.h"

#include "StatManagerComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogStatManagerComponent, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UStatManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatManagerComponent();

	using StatMap = TMap<EStatTypeEnum, float>;
	using ModifierArray = TArray<const UStatModifier*>;
	using ModifierPriorityMap = TMap<int32, ModifierArray>;
	using StatModifierMap = TMap<EStatTypeEnum, ModifierPriorityMap>;

	// Stats:
	UFUNCTION(BlueprintCallable)
	bool AddStat(EStatTypeEnum StatType, float Value);

	UFUNCTION(BlueprintCallable)
	bool SetStat(EStatTypeEnum StatType, float Value);

	UFUNCTION(BlueprintCallable)
	bool IncrementStat(EStatTypeEnum StatType, float Value);

	UFUNCTION(BlueprintCallable)
	bool DecrementStat(EStatTypeEnum StatType, float Value);

	UFUNCTION(BlueprintCallable)
	bool RemoveStat(EStatTypeEnum StatType);

	UFUNCTION(BlueprintCallable)
	bool GetBaseStatValue(EStatTypeEnum StatType, float& OutValue) const;

	UFUNCTION(BlueprintCallable)
	bool GetModifiedStatValue(EStatTypeEnum StatType, float& OutValue) const;

	UFUNCTION(BlueprintCallable)
	bool GetBonusStatValue(EStatTypeEnum StatType, float& OutValue) const;

	UFUNCTION(BlueprintCallable)
	bool GetStatScalingValue(const FStatScaling& Scaling, float& OutValue) const;

	// Status Effects:

	UFUNCTION(BlueprintCallable)
	void AddStatusEffect(UStatusEffect* StatusEffect);

	UFUNCTION(BlueprintCallable)
	bool RemoveStatusEffect(UStatusEffect* StatusEffect);


	// Modifiers:

	UFUNCTION(BlueprintCallable)
	void AddModifier(const UStatModifier* Modifier);

	UFUNCTION(BlueprintCallable)
	bool RemoveModifier(const UStatModifier* Modifier);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	StatMap Stats;
	TArray<UStatusEffect*> StatusEffects;
	StatModifierMap StatModifiers;

private:
	void TickStatusEffects(float DeltaTime);
};
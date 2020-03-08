// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"

#include "Components/StatManagerComponent.h"
#include "DataTables/AbilityData.h"
#include "DataTables/StatScaling.h"
#include "Game/KingdomGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogAbility);

UAbility::UAbility()
	: AbilityType(EAbilityTypeEnum::Simple)
{
}

UAbility::~UAbility()
{
}

bool UAbility::CanExecute_Implementation()
{
	const AActor* Caster = Controller->GetPawn();

	if (!Caster)
	{
		UE_LOG(LogAbility, Error, TEXT("No caster for ability"));
		return false;
	}

	if (!CanPayCosts(AbilityName, Caster, this))
	{
		return false;
	}

	return CanActivate() == EActivateAbilityResultEnum::Success;
}

void UAbility::Execute_Implementation()
{
	EActivateAbilityResultEnum ActivateAbilityResult = CanActivate();
	if (ActivateAbilityResult != EActivateAbilityResultEnum::Success)
	{
		return;
	}

	ActivateAbility();
	ActivateAbilityEvent.Broadcast(AbilityName);
}

 bool UAbility::CanPayCosts(FName AbilityName, const AActor* Actor, const UObject* Caller)
{
	if (Actor == nullptr)
	{
		UE_LOG(LogAbility, Error, TEXT("No owning actor"));
		return false;
	}

	TArray<UStatManagerComponent*> OwnedComponents;
	Actor->GetComponents<UStatManagerComponent>(OwnedComponents);

	if (OwnedComponents.Num() != 1)
	{
		UE_LOG(LogAbility, Error, TEXT("Owning actor does not have the correct number of stat manager components"));
		return false;
	}

	const UStatManagerComponent* StatManagerComponent = OwnedComponents[0];
	if (StatManagerComponent == nullptr)
	{
		return false;
	}

	const FAbilityData* AbilityData = GetAbilityData(AbilityName, Caller);

	if (AbilityData == nullptr)
	{
		return false;
	}

	for (const FStatScaling& Scaling : AbilityData->Cost)
	{
		float StatValue = 0.0f;
		StatManagerComponent->GetModifiedStatValue(Scaling.StatType, StatValue);

		float CostValue = 0.0f;
		StatManagerComponent->GetStatScalingValue(Scaling, CostValue);

		if (StatValue < CostValue)
		{
			return false;
		}
	}

	return true;
}

const FAbilityData* UAbility::GetAbilityData(FName AbilityName, const UObject* Caller)
{
	const UKingdomGameInstance* KingdomGameInstance = Cast<UKingdomGameInstance>(UGameplayStatics::GetGameInstance(Caller));
	if (KingdomGameInstance == nullptr)
	{
		UE_LOG(LogAbility, Error, TEXT("Invalid game instance"));
		return nullptr;
	}

	if (KingdomGameInstance->AbilityDataTable == nullptr)
	{
		UE_LOG(LogAbility, Error, TEXT("Ability data table not setup on kingdom game instance"));
		return nullptr;
	}

	const FAbilityData* AbilitypData = KingdomGameInstance->AbilityDataTable->FindRow<FAbilityData>(AbilityName, TEXT(""));
	if (AbilitypData == nullptr)
	{
		UE_LOG(LogAbility, Error, TEXT("Ability data table does not contain key: %s"), *AbilityName.ToString());
		return nullptr;
	}

	return AbilitypData;
}
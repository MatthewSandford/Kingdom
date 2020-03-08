// Fill out your copyright notice in the Description page of Project Settings.

#include "KingdomCharacter.h"
#include "Components/AbilityManagerComponent.h"
#include "Components/CreatureStatManagerComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/TaskQueueComponent.h"
#include "Components/TeamComponent.h"
#include "DataTables/CreatureSetupData.h"
#include "Enums/StatTypeEnum.h"
#include "KingdomGameInstance.h"

DEFINE_LOG_CATEGORY(LogKingdomCharacter);

AKingdomCharacter::AKingdomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	InitialiseComponents();
}

void AKingdomCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupStatManager();
}

void AKingdomCharacter::InitialiseComponents()
{
	StatManager = CreateDefaultSubobject<UCreatureStatManagerComponent>(TEXT("StatManager"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Team = CreateDefaultSubobject<UTeamComponent>(TEXT("Team"));
	TaskQueue = CreateDefaultSubobject<UTaskQueueComponent>(TEXT("TaskQueue"));
	AbilityMananger = CreateDefaultSubobject<UAbilityManagerComponent>(TEXT("AbilityMananger"));
}

void AKingdomCharacter::SetupStatManager()
{
	const UKingdomGameInstance* KingdomGameInstance = Cast<UKingdomGameInstance>(GetGameInstance());
	if (KingdomGameInstance == nullptr)
	{
		UE_LOG(LogKingdomCharacter, Error, TEXT("Invalid game instance"));
		return;
	}

	if (KingdomGameInstance->CreatureStatsDataTable == nullptr)
	{
		UE_LOG(LogKingdomCharacter, Error, TEXT("Creature stat data table not setup on kingdom game instance"));
		return; 
	}

	const FCreatureSetupData* CreatureSetupData = KingdomGameInstance->CreatureStatsDataTable->FindRow<FCreatureSetupData>(CharacterType, TEXT(""));
	if (CreatureSetupData == nullptr)
	{
		UE_LOG(LogKingdomCharacter, Error, TEXT("Creature stat data table does not contain key: %s"), *CharacterType.ToString());
		return;
	}

	StatManager->SetStat(EStatTypeEnum::MaxHealth, CreatureSetupData->MaxHealth);
	StatManager->SetStat(EStatTypeEnum::Health, CreatureSetupData->MaxHealth);
	StatManager->SetStat(EStatTypeEnum::Damage, CreatureSetupData->Damage);
	StatManager->SetStat(EStatTypeEnum::AutoAttackRange, CreatureSetupData->AutoAttackRange);
}
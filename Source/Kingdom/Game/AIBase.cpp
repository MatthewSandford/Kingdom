// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase.h"

#include "Components/CreatureStatManagerComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/TaskQueueComponent.h"
#include "Components/TeamComponent.h"
#include "DataTables/CreatureSetupData.h"
#include "Enums/StatTypeEnum.h"
#include "KingdomGameInstance.h"

DEFINE_LOG_CATEGORY(LogAIBase);

AAIBase::AAIBase()
{
	PrimaryActorTick.bCanEverTick = true;
	InitialiseComponents();
}

void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	SetupStatManager();
}

void AAIBase::InitialiseComponents()
{
	StatManager = CreateDefaultSubobject<UCreatureStatManagerComponent>(TEXT("StatManager"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Team = CreateDefaultSubobject<UTeamComponent>(TEXT("Team"));
	TaskQueue = CreateDefaultSubobject<UTaskQueueComponent>(TEXT("TaskQueue"));
}

void AAIBase::SetupStatManager()
{
	const UKingdomGameInstance* KingdomGameInstance = Cast<UKingdomGameInstance>(GetGameInstance());
	if (KingdomGameInstance == nullptr)
	{
		UE_LOG(LogAIBase, Error, TEXT("Invalid game instance"));
		return;
	}

	if (KingdomGameInstance->CreatureStatsDataTable == nullptr)
	{
		UE_LOG(LogAIBase, Error, TEXT("Creature stat data table not setup on kingdom game instance"));
		return;
	}

	const FCreatureSetupData* CreatureSetupData = KingdomGameInstance->CreatureStatsDataTable->FindRow<FCreatureSetupData>(CharacterType, TEXT(""));
	if (CreatureSetupData == nullptr)
	{
		UE_LOG(LogAIBase, Error, TEXT("Creature stat data table does not contain key: %s"), *CharacterType.ToString());
		return;
	}

	StatManager->SetStat(EStatTypeEnum::MaxHealth, CreatureSetupData->MaxHealth);
	StatManager->SetStat(EStatTypeEnum::Health, CreatureSetupData->MaxHealth);
	StatManager->SetStat(EStatTypeEnum::Damage, CreatureSetupData->Damage);
	StatManager->SetStat(EStatTypeEnum::AutoAttackRange, CreatureSetupData->AutoAttackRange);
}
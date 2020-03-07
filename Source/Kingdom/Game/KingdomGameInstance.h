// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameStateBase.h"
#include "KingdomGameInstance.generated.h"

UCLASS()
class KINGDOM_API UKingdomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UKingdomGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* AbilityDataTable;
	
};

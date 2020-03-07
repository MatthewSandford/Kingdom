// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

#include "InventoryItem.generated.h"

UCLASS(Blueprintable)
class KINGDOM_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItem();
	~UInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};

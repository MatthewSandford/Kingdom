// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/InventoryItem.h"

#include "InventoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventoryComponent, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventorySlotUpdateEvent, int32, SlotIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	struct InventoryChangeRequest
	{
		InventoryChangeRequest(int32 InSlotIndex, int32 InQuantity)
			: SlotIndex(InSlotIndex)
			, Quantity(InQuantity)
		{
		}

		int32 SlotIndex;
		int32 Quantity;
	};

public:	
	UInventoryComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool AddItem(FName ItemType, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	bool AddItemToSlot(FName ItemType, int32 Quantity, int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	bool RemoveItemFromSlot(int32 SlotIndex, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	bool MoveSlot(int32 SourceSlotIndex, int32 TargetSlotIndex);

	UFUNCTION(BlueprintCallable)
	UInventoryItem* GetInventoryItem(int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	bool CanAddItem(FName ItemType, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	bool IsSlotEmpty(int32 SlotIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UInventoryItem*> InventoryItems;

	UPROPERTY(BlueprintAssignable)
	FInventorySlotUpdateEvent InventorySlotUpdateEvent;

private:

	bool StackSlots(int32 SourceSlotIndex, int32 TargetSlotIndex);

	int32 GetInventoryChangeRequestsForAdd(FName ItemType, int32 Quantity, TArray<InventoryChangeRequest>& OutArray);
	int32 GetInventoryChangeRequestsForStackItem(FName ItemType, int32 Quantity, TArray<InventoryChangeRequest>& OutArray);
	int32 GetInventoryChangeRequestsForAddAddFreshItem(FName ItemType, int32 Quantity, TArray<InventoryChangeRequest>& OutArray);

	void SetInventorySlot(FName ItemType, int32 Quantity, int32 SlotIndex);
};
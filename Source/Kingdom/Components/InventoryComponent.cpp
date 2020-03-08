// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

DEFINE_LOG_CATEGORY(LogInventoryComponent);

UInventoryComponent::UInventoryComponent()
{
}

void UInventoryComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
	InventoryItems.SetNum(NumSlots);
	for (int32 i = 0; i < NumSlots; ++i)
	{
		InventoryItems[i] = NewObject<UInventoryItem>();
	}
}

bool UInventoryComponent::AddItem(FName ItemType, int32 Quantity)
{
	TArray<InventoryChangeRequest> InventoryChangeRequests;
	if (GetInventoryChangeRequestsForAdd(ItemType, Quantity, InventoryChangeRequests) != Quantity)
	{
		UE_LOG(LogInventoryComponent, Warning, TEXT("Could not AddItem - item: %s quantity: %d"), *ItemType.ToString(), Quantity);
		return false;
	}

	for (const InventoryChangeRequest& InventoryChangeRequest : InventoryChangeRequests)
	{
		UInventoryItem* InventoryItem = InventoryItems[InventoryChangeRequest.SlotIndex];
		SetInventorySlot(ItemType, InventoryItem->Quantity + InventoryChangeRequest.Quantity, InventoryChangeRequest.SlotIndex);
	}

	return true;
}

bool UInventoryComponent::AddItemToSlot(FName ItemType, int32 Quantity, int32 SlotIndex)
{
	UInventoryItem* InventoryItem = GetInventoryItem(SlotIndex);
	if (InventoryItem == nullptr)
	{
		return false;
	}

	bool bSlotItemTypeOk = InventoryItem->ItemType == ItemType || InventoryItem->ItemType == NAME_None;
	bool bQuantityOk = InventoryItem->Quantity + Quantity <= StackSize;

	if (!bSlotItemTypeOk || !bQuantityOk)
	{
		UE_LOG(LogInventoryComponent, Warning, TEXT("Could not AddItemToSlot - item: %s quantity: %d slot: %d"), *ItemType.ToString(), Quantity, SlotIndex);
		return false;
	}

	SetInventorySlot(ItemType, InventoryItem->Quantity + Quantity, SlotIndex);
	return true;
}

bool UInventoryComponent::RemoveItemFromSlot(int32 SlotIndex, int32 Quantity)
{
	UInventoryItem* InventoryItem = GetInventoryItem(SlotIndex);
	if (InventoryItem == nullptr)
	{
		return false;
	}

	if (InventoryItem->Quantity - Quantity < 0)
	{
		UE_LOG(LogInventoryComponent, Warning, TEXT("Could not RemoveItemFromSlot - quantity: %d slot: %d"), Quantity, SlotIndex);
		return false;
	}

	FName NewItemType = InventoryItem->Quantity - Quantity == 0 ? NAME_None : InventoryItem->ItemType;
	SetInventorySlot(NewItemType, InventoryItem->Quantity - Quantity, SlotIndex);
	return true;
}

bool UInventoryComponent::MoveSlot(int32 SourceSlotIndex, int32 TargetSlotIndex)
{
	if (SourceSlotIndex == TargetSlotIndex ||
		SourceSlotIndex >= NumSlots ||
		TargetSlotIndex >= NumSlots)
	{
		UE_LOG(LogInventoryComponent, Log, TEXT("Invalid input slots when calling MoveSlot - source: %d target: %d"), SourceSlotIndex, TargetSlotIndex);
		return false;
	}

	UInventoryItem* SourceInventoryItem = InventoryItems[SourceSlotIndex];
	UInventoryItem* TargetInventoryItem = InventoryItems[TargetSlotIndex];

	if (SourceInventoryItem->ItemType == TargetInventoryItem->ItemType)
	{
		StackSlots(SourceSlotIndex, TargetSlotIndex);
	}
	else
	{
		FName SourceItemType = SourceInventoryItem->ItemType;
		int32 SourceQuantity = SourceInventoryItem->Quantity;

		SetInventorySlot(TargetInventoryItem->ItemType, TargetInventoryItem->Quantity, SourceSlotIndex);
		SetInventorySlot(SourceItemType, SourceQuantity, TargetSlotIndex);
	}

	return true;
}

UInventoryItem* UInventoryComponent::GetInventoryItem(int32 SlotIndex)
{
	if (SlotIndex >= NumSlots)
	{
		UE_LOG(LogInventoryComponent, Log, TEXT("Invalid slot when calling GetInventoryItem - slot: %d"), SlotIndex);
		return nullptr;
	}

	return InventoryItems[SlotIndex];
}

bool UInventoryComponent::CanAddItem(FName ItemType, int32 Quantity)
{
	TArray<InventoryChangeRequest> InventoryChangeRequests;
	return GetInventoryChangeRequestsForAdd(ItemType, Quantity, InventoryChangeRequests) == Quantity;
}

bool UInventoryComponent::IsSlotEmpty(int32 SlotIndex)
{
	UInventoryItem* InventoryItem = GetInventoryItem(SlotIndex);
	if (InventoryItem == nullptr)
	{
		return false;
	}

	return InventoryItem->ItemType == NAME_None;
}

bool UInventoryComponent::StackSlots(int32 SourceSlotIndex, int32 TargetSlotIndex)
{
	UInventoryItem* SourceInventoryItem = InventoryItems[SourceSlotIndex];
	UInventoryItem* TargetInventoryItem = InventoryItems[TargetSlotIndex];

	int32 TargetCapacity = StackSize - TargetInventoryItem->Quantity;
	if (TargetCapacity == 0)
	{
		// Bit of a hack to update the UI
		InventorySlotUpdateEvent.Broadcast(SourceSlotIndex);
		return false;
	}

	if (TargetCapacity - SourceInventoryItem->Quantity >= 0)
	{
		SetInventorySlot(TargetInventoryItem->ItemType, TargetInventoryItem->Quantity + SourceInventoryItem->Quantity, TargetSlotIndex);
		SetInventorySlot(NAME_None, 0, SourceSlotIndex);
	}
	else
	{
		SetInventorySlot(SourceInventoryItem->ItemType, SourceInventoryItem->Quantity - TargetCapacity, SourceSlotIndex);
		SetInventorySlot(TargetInventoryItem->ItemType, StackSize, TargetSlotIndex);
	}

	return true;
}

int32 UInventoryComponent::GetInventoryChangeRequestsForAdd(FName ItemType, int32 Quantity, TArray<InventoryChangeRequest>& OutArray)
{
	int32 StackedAmount = GetInventoryChangeRequestsForStackItem(ItemType, Quantity, OutArray);
	if (StackedAmount == Quantity)
	{
		return StackedAmount;
	}

	Quantity -= StackedAmount;
	int32 FreshAmount = GetInventoryChangeRequestsForAddAddFreshItem(ItemType, Quantity, OutArray);
	return FreshAmount + StackedAmount;
}

int32 UInventoryComponent::GetInventoryChangeRequestsForStackItem(FName ItemType, int32 Quantity, TArray<InventoryChangeRequest>& OutArray)
{
	int32 QuantityAdded = 0;
	for (int32 i = 0; i < NumSlots; ++i)
	{
		UInventoryItem* InventoryItem = InventoryItems[i];
		int32 Capaity = StackSize - InventoryItem->Quantity;

		if (Capaity > 0 &&
			ItemType == InventoryItem->ItemType)
		{ 
			int32 QuantityToAdd = Capaity >= Quantity ? Quantity : Capaity;
			OutArray.Add(InventoryChangeRequest(i, QuantityToAdd));
			QuantityAdded += QuantityToAdd;

			if (QuantityAdded == Quantity)
			{
				break;
			}
		}
	}
	return QuantityAdded;
}

int32 UInventoryComponent::GetInventoryChangeRequestsForAddAddFreshItem(FName ItemType, int32 Quantity, TArray<InventoryChangeRequest>& OutArray)
{
	int32 QuantityAdded = 0;
	for (int32 i = 0; i < NumSlots; ++i)
	{
		UInventoryItem* InventoryItem = InventoryItems[i];
		if (InventoryItem->Quantity == 0)
		{
			int32 QuantityToAdd = StackSize >= Quantity ? Quantity : StackSize;
			OutArray.Add(InventoryChangeRequest(i, QuantityToAdd));
			QuantityAdded += QuantityToAdd;

			if (QuantityAdded == Quantity)
			{
				break;
			}
		}
	}
	return QuantityAdded;
}

void UInventoryComponent::SetInventorySlot(FName ItemType, int32 Quantity, int32 SlotIndex)
{
	UInventoryItem* InventoryItem = InventoryItems[SlotIndex];
	InventoryItem->ItemType = ItemType;
	InventoryItem->Quantity = Quantity;
	InventorySlotUpdateEvent.Broadcast(SlotIndex);
}
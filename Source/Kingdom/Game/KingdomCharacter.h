// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "KingdomCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogKingdomCharacter, Log, All);

class UAbilityManagerComponent;
class UStatManagerComponent;
class UInventoryComponent;
class UTaskQueueComponent;
class UTeamComponent;

UCLASS()
class KINGDOM_API AKingdomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKingdomCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStatManagerComponent* StatManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTaskQueueComponent* TaskQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTeamComponent* Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilityManagerComponent* AbilityMananger;

protected:
	virtual void BeginPlay() override;

private:

	void InitialiseComponents();
	void SetupStatManager();

};

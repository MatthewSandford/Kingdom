// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AIBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAIBase, Log, All);

class UCreatureStatManagerComponent;
class UInventoryComponent;
class UTaskQueueComponent;
class UTeamComponent;

UCLASS()
class KINGDOM_API AAIBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAIBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCreatureStatManagerComponent* StatManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTaskQueueComponent* TaskQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTeamComponent* Team;

protected:
	virtual void BeginPlay() override;

private:

	void InitialiseComponents();
	void SetupStatManager();
};

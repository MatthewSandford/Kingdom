// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "Components/ActorComponent.h"
#include "Game/Task.h"

#include "TaskQueueComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTaskQueueComponent, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UTaskQueueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTaskQueueComponent();
	~UTaskQueueComponent();

	UFUNCTION(BlueprintCallable)
	void AddTask(UTask* Task);

	UFUNCTION(BlueprintCallable)
	void QueueTask(UTask* Task);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

	void Clear();
	void RemoveTask(UTask* Task);
	bool TryExecuteTask(UTask* Task);

	TArray<UTask*> Queue;

};
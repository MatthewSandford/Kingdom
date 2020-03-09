// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

#include "Task.generated.h"

class AController;

UCLASS(Blueprintable)
class KINGDOM_API UTask : public UObject
{
	GENERATED_BODY()

public:
	UTask();
	~UTask();

	// Called when the task is added to the task queue
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	// Called before trying to execute the task from the task queue
	// If the task can not execute, it will be removed from the queue
	UFUNCTION(BlueprintNativeEvent)
	bool CanExecute();

	virtual bool CanExecute_Implementation() { return true; };

	// Execute the functionality of the task
	UFUNCTION(BlueprintNativeEvent)
	void Execute();

	virtual void Execute_Implementation() {};

	// If another task is executed whilst this one is executing, the task will be paused
	UFUNCTION(BlueprintImplementableEvent)
	void Pause();

	// When the task has been executed and has finished it will be removed from the queue
	UFUNCTION(BlueprintNativeEvent)
	bool HasFinished();

	virtual bool HasFinished_Implementation() { return true; }

	// If the queue has been cleared, cancel will be called on this task
	UFUNCTION(BlueprintImplementableEvent)
	void Cancel();

	// When adding this task to the task queue should it be executed immediately
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ClearsTaskQueue = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	AController* Controller;
};

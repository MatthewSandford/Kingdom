// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskQueueComponent.h"

DEFINE_LOG_CATEGORY(LogTaskQueueComponent);

UTaskQueueComponent::UTaskQueueComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UTaskQueueComponent::~UTaskQueueComponent()
{
}

void UTaskQueueComponent::AddTask(UTask* Task)
{
	if (!Task)
	{
		UE_LOG(LogTaskQueueComponent, Error, TEXT("Trying to add null task"));
		return;
	}

	Task->Init();

	if (Task->ClearsTaskQueue)
	{
		Clear();
		QueueTask(Task);
	}
	else if (TryExecuteTask(Task))
	{
		if (Queue.Num() != 0)
		{
			Queue[0]->Pause();
		}
		else
		{
			SetComponentTickEnabled(true);
		}

		Queue.Insert(Task, 0);
	}
}

void UTaskQueueComponent::QueueTask(UTask* Task)
{
	if (!Task)
	{
		UE_LOG(LogTaskQueueComponent, Error, TEXT("Trying to queue null task"));
		return;
	}

	Task->Init();

	if (Queue.Num() == 0)
	{
		Task->Execute();
		SetComponentTickEnabled(true);
	}
	Queue.Add(Task);
}

void UTaskQueueComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (Queue.Num() != 0)
	{
		UTask* Task = Queue[0];
		if (Task->HasFinished())
		{
			Queue.Remove(Task);
			if (Queue.Num() != 0)
			{
				TryExecuteTask(Queue[0]);
			}
		}
	}
}

void UTaskQueueComponent::Clear()
{
	for (int32 i = Queue.Num() - 1; i >= 0; --i)
	{
		UTask* Task = Queue[i];
		Task->Cancel();
		Queue.Remove(Task);
	}

	SetComponentTickEnabled(false);
}

void UTaskQueueComponent::RemoveTask(UTask* Task)
{
	Queue.Remove(Task);

	if (Queue.Num() == 0)
	{
		SetComponentTickEnabled(false);
	}
}

bool UTaskQueueComponent::TryExecuteTask(UTask* Task)
{
	if (Task->CanExecute())
	{
		Task->Execute();
		return true;
	}

	RemoveTask(Task);
	return false;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogInteractComponent);

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInteractComponent::IsInRange(FVector Location)
{
	if (!Unbounded)
	{
		AActor* Actor = GetOwner();
		FVector ActorLocation = Actor->GetActorLocation();

		float Distance = (ActorLocation - Location).Size();
		if (Distance > InteractRange)
		{
			return false;
		}
	}
	return true;
}
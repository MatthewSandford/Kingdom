// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "InteractComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInteractComponent, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractEvent, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelledEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();

	UFUNCTION(BlueprintCallable)
	bool IsInRange(FVector Location);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float InteractRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	bool Unbounded;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FInteractEvent InteractEvent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FFinishedEvent FinishedEvent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FCancelledEvent CancelledEvent;
};
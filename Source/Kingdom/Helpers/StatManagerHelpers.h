// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "StatManagerHelpers.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogStatManagerHelpers, Log, All);

class UStatManagerComponent;

UCLASS(Blueprintable)
class KINGDOM_API UStatManagerHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UStatManagerHelpers();
	~UStatManagerHelpers();

	UFUNCTION(BlueprintCallable)
	static float GetHealth(UStatManagerComponent* StatManagerComponent);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputCoreTypes.h"

#include "KeyPressComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UKeyPressComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UKeyPressComponent();
	~UKeyPressComponent();

	UFUNCTION(BlueprintCallable)
	void AddKeyPress(const FKey& Key);

	UFUNCTION(BlueprintCallable)
	bool CheckKeyPress(const FKey& Key);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TSet<FName> KeyPresses;
};

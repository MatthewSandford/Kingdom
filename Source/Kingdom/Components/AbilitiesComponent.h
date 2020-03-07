// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/Abilities/Ability.h"

#include "AbilitiesComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOM_API UAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilitiesComponent();

	UFUNCTION(BlueprintCallable)
	int32 AddAbility(UAbility* Ability);

	UFUNCTION(BlueprintCallable)
	UAbility* GetAbility(int32 Index);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<UAbility*> Abilities;

	void TickAbilities(float DeltaTime);

};

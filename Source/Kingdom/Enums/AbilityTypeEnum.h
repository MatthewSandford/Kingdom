// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)	
enum class EAbilityTypeEnum : uint8
{
	Simple				UMETA(DisplayName = "Simple"),
	ActorTarget 		UMETA(DisplayName = "Actor Target"),
	LocationTarget 		UMETA(DisplayName = "Location Target"),
	SkillShot			UMETA(DisplayName = "Skill Shot"),
};
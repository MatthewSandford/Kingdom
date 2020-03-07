// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)	
enum class ETeamEnum : uint8
{
	Red 		UMETA(DisplayName = "Red"),
	Blue 		UMETA(DisplayName = "Blue"),
	Nature      UMETA(DisplayName = "Nature"),
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

namespace DataTables
{
	ConstructorHelpers::FObjectFinder<UDataTable> AbilityDataTable(TEXT("/Game/TopDownBP/Data/DT_AbilityData.DT_AbilityData"));
} // DataTables
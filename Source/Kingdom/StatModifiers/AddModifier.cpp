// Fill out your copyright notice in the Description page of Project Settings.

#include "AddModifier.h"

UAddModifier::UAddModifier()
{
}

UAddModifier::~UAddModifier()
{
}

float UAddModifier::GetModifiedStatValue(float StatValue) const
{
	StatValue += AddValue;
	return StatValue;
}
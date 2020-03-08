// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyPressComponent.h"

UKeyPressComponent::UKeyPressComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UKeyPressComponent::~UKeyPressComponent()
{
}

void UKeyPressComponent::AddKeyPress(const FKey& Key)
{
	KeyPresses.Add(Key.GetFName());
}

bool UKeyPressComponent::CheckKeyPress(const FKey& Key)
{
	return !KeyPresses.Contains(Key.GetFName());
}

void UKeyPressComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	KeyPresses.Reset();
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAffinity : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal Damage"),
	Bonus = 1 UMETA(DisplayName = "Bonus Damage"),
	Malus = 2 UMETA(DisplayName = "Malus Damage"),
	None = 3 UMETA(DisplayName = "No Damage"),
	MAX
};

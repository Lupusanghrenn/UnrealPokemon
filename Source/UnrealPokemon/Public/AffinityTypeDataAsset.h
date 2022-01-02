// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EAffinity.h"
#include "AffinityTypeDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPOKEMON_API UAffinityTypeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Matrix")
	TArray<EAffinity> damageModifierPerAffinity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UItemDataAsset")
	FPrimaryAssetType    ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int nbType = 5;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const;
	
};

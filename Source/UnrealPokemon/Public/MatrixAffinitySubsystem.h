// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "EAffinity.h"
#include "AffinityTypeDataAsset.h"
#include "ElementalType.h"
#include "MatrixAffinitySubsystem.generated.h"


USTRUCT(BlueprintType)
struct FDamageModifierPerAffinity
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAffinity affinity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float multiplier;
};
/**
 * 
 */
UCLASS()
class UNREALPOKEMON_API UMatrixAffinitySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matrix")
		TArray<EAffinity> affinityMatrix;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Datas")
		TArray<FDamageModifierPerAffinity> damageModifierPerAffinity;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Datas")
		TMap<EAffinity,float> modifierForAffinity;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Datas")
	float samePokemonAndTypeMultiplier = 1.25;
private:
	int nbType = 5;
	UPROPERTY()
	UAffinityTypeDataAsset* matrixData = nullptr;

public:
	//~ Begin USubsystem interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; };
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override {};
	//~ End USubsystem interface

	float GetDamageModifierWhenAttaking(EElementalType atkerType, EElementalType deferType, EElementalType atkType);
	
private:
	float GetDamageModifierFromMatrix(EElementalType atkerType, EElementalType defenderType);
	void CallbackFunction(FPrimaryAssetId idLoaded);
};

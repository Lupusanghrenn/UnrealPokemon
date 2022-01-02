// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixAffinitySubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/ObjectLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"

void UMatrixAffinitySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	EAffinity normal[] = { EAffinity::Normal,EAffinity::Normal,EAffinity::Normal,EAffinity::Normal,EAffinity::Normal };
	EAffinity fire[] = { EAffinity::Normal,EAffinity::Malus,EAffinity::Malus,EAffinity::Bonus,EAffinity::Normal };
	EAffinity water[] = { EAffinity::Normal,EAffinity::Bonus,EAffinity::Malus,EAffinity::Malus,EAffinity::Normal };
	EAffinity plant[] = { EAffinity::Normal,EAffinity::Malus,EAffinity::Bonus,EAffinity::Malus,EAffinity::Normal };
	EAffinity electrik[] = { EAffinity::Normal,EAffinity::Normal,EAffinity::Bonus,EAffinity::Malus,EAffinity::Malus };
	affinityMatrix.Append(normal, UE_ARRAY_COUNT(normal));
	affinityMatrix.Append(fire, UE_ARRAY_COUNT(fire));
	affinityMatrix.Append(water, UE_ARRAY_COUNT(water));
	affinityMatrix.Append(plant, UE_ARRAY_COUNT(plant));
	affinityMatrix.Append(electrik, UE_ARRAY_COUNT(electrik));

	//dictionnary
	modifierForAffinity.Add(EAffinity::Normal, 1);
	modifierForAffinity.Add(EAffinity::Bonus, 2);
	modifierForAffinity.Add(EAffinity::Malus, 0.5);
	modifierForAffinity.Add(EAffinity::None, 0);

	/*UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(BaseClass, false, GIsEditor);
	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/PathWithAllObjectsOfSameType");
	if (bFullyLoad)
	{
		ObjectLibrary->LoadAssetsFromAssetData();
	}*/

	UAssetManager* Manager = UAssetManager::GetIfValid();
	if (Manager)
	{
		/*FPrimaryAssetId matrixId = Manager->GetPrimaryAssetIdForPath(TEXT("/Game/GameData/AffinityType"));*/
		/*FAssetData assetDataToParsde;
		const FSoftObjectPath path = FSoftObjectPath(TEXT("/Game/GameData"));
		bool isDataFound = Manager->GetAssetDataForPath(path, assetDataToParsde);
		FPrimaryAssetId matrixId = Manager->GetPrimaryAssetIdForPath(path);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Init = %d"), matrixId.IsValid()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Init = %d : %s"), isDataFound, *assetDataToParsde.AssetName.ToString()));*/
		/*if (isDataFound) {
			TArray<FName> CurrentLoadState;
			CurrentLoadState.Add(FName("Game"));
			FPrimaryAssetId idMatrix = assetDataToParsde.GetPrimaryAssetId();
			Manager->LoadPrimaryAsset(idMatrix, CurrentLoadState, FStreamableDelegate::CreateUObject(this, &UMatrixAffinitySubsystem::CallbackFunction, idMatrix));
		}*/

		TArray<UObject*> assetsToLoad;
		bool foundAssets = EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/GameData"), assetsToLoad, EngineUtils::ATL_Regular);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Init by find = %d"),foundAssets));
		if (foundAssets) {
			for (auto asset : assetsToLoad)
			{
				UAffinityTypeDataAsset* affinityAsset = Cast<UAffinityTypeDataAsset>(asset);
				if (affinityAsset != nullptr) {
					matrixData = affinityAsset;
					UE_LOG(LogTemp,Warning,TEXT("Asset is not null"));
				}
			}
		}
	}
}

void UMatrixAffinitySubsystem::CallbackFunction(FPrimaryAssetId idLoaded) {
	if (idLoaded.IsValid()) {
		UAssetManager* Manager = UAssetManager::GetIfValid();
		matrixData = Manager->GetPrimaryAssetObject<UAffinityTypeDataAsset>(idLoaded);
		nbType = UKismetMathLibrary::Sqrt(matrixData->damageModifierPerAffinity.Num());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("idLoaded is null"));
	}
}

float UMatrixAffinitySubsystem::GetDamageModifierWhenAttaking(EElementalType atkerType, EElementalType deferType, EElementalType atkType)
{
	float modifier = GetDamageModifierFromMatrix(atkerType,deferType);
	if (atkerType == atkType)
		modifier *= samePokemonAndTypeMultiplier;

	return modifier;
}

float UMatrixAffinitySubsystem::GetDamageModifierFromMatrix(EElementalType atkerType, EElementalType defenderType)
{
	int x = (int)atkerType;
	int y = (int)defenderType;
	EAffinity affinity = affinityMatrix[x * nbType + y];
	if (matrixData != nullptr) {
		affinity = matrixData->damageModifierPerAffinity[x * nbType + y];
		UE_LOG(LogTemp, Warning, TEXT("using asset"));
	}
	float modifier = *modifierForAffinity.Find(affinity);
	return modifier;
}

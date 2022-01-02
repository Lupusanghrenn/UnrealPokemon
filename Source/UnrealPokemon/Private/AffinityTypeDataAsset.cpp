// Fill out your copyright notice in the Description page of Project Settings.


#include "AffinityTypeDataAsset.h"

FPrimaryAssetId UAffinityTypeDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}

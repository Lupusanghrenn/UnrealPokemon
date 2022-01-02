// Copyright Epic Games, Inc. All Rights Reserved.

#include "AffinityMatrixEditor.h"
#include "AffinityMatrixEditorEdMode.h"

#define LOCTEXT_NAMESPACE "FAffinityMatrixEditorModule"

#include "UnrealPokemon/Public/AffinityTypeDataAsset.h"
#include "PropertyEditor/Public/PropertyEditorModule.h"
#include "MatrixEditor.h"

void FAffinityMatrixEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FAffinityMatrixEditorEdMode>(FAffinityMatrixEditorEdMode::EM_AffinityMatrixEditorEdModeId, LOCTEXT("AffinityMatrixEditorEdModeName", "AffinityMatrixEditorEdMode"), FSlateIcon(), true);

	FPropertyEditorModule& PropertyEdModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEdModule.RegisterCustomClassLayout(
		UAffinityTypeDataAsset::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&MatrixEditor::MakeInstance)
	);
	UE_LOG(LogTemp, Warning, TEXT("Affinity matrix Editor loaded."));
}

void FAffinityMatrixEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FAffinityMatrixEditorEdMode::EM_AffinityMatrixEditorEdModeId);
	UE_LOG(LogTemp, Warning, TEXT("Affinity matrix Editor shut down."));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAffinityMatrixEditorModule, AffinityMatrixEditor)
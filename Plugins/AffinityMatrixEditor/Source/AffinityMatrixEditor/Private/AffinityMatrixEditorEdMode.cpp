// Copyright Epic Games, Inc. All Rights Reserved.

#include "AffinityMatrixEditorEdMode.h"
#include "AffinityMatrixEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FAffinityMatrixEditorEdMode::EM_AffinityMatrixEditorEdModeId = TEXT("EM_AffinityMatrixEditorEdMode");

FAffinityMatrixEditorEdMode::FAffinityMatrixEditorEdMode()
{

}

FAffinityMatrixEditorEdMode::~FAffinityMatrixEditorEdMode()
{

}

void FAffinityMatrixEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FAffinityMatrixEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FAffinityMatrixEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FAffinityMatrixEditorEdMode::UsesToolkits() const
{
	return true;
}





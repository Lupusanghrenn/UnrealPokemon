// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixEditor.h"
#include "PropertyEditor/Public/DetailLayoutBuilder.h"
#include "PropertyEditor/Public/DetailCategoryBuilder.h"
#include "PropertyEditor/Public/DetailWidgetRow.h"

#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"

#include "Input/Reply.h"
#include "UnrealPokemon/Public/AffinityTypeDataAsset.h"

#define LOCTEXT_NAMESPACE "MatrixEditor"

TSharedRef<IDetailCustomization> MatrixEditor::MakeInstance()
{
	return MakeShareable(new MatrixEditor);
}


void MatrixEditor::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Matrix"/*, LOCTEXT("CatName", "Affinity Matrix settings"),ECategoryPriority::Important*/);

	Category.AddCustomRow(LOCTEXT("keyword","shuffle"))
		.NameContent()[

			SNew(STextBlock)
				.Text(LOCTEXT("NameText", "ReassignMaterial"))
				//.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()[
			SNew(SButton)
				.Text(LOCTEXT("ButtonText", "Shuffle"))
				.OnClicked_Raw(this, &MatrixEditor::EditObjects)
		];
			UE_LOG(LogTemp, Warning, TEXT("Loaded ?"));
	TSharedRef<IPropertyHandle> prop = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAffinityTypeDataAsset, damageModifierPerAffinity));
	TSharedRef<IPropertyHandle> propType = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAffinityTypeDataAsset, damageModifierPerAffinity[0]));
	//TSharedRef<IPropertyHandle> structHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAffinityTypeDataAsset, damageModifierPerAffinity));
	/*auto defaultProperty = DetailBuilder.EditDefaultProperty(prop);
	auto customWidget = defaultProperty->CustomWidget(true);
	customWidget.ValueContent()[
		SNew(STextBlock).Text(LOCTEXT("ButtontTest", "ValueContent"))
	];*/

	if (ObjectsToEdit.Num() > 0) {
		TWeakObjectPtr<UAffinityTypeDataAsset> propHandle = Cast<UAffinityTypeDataAsset>(ObjectsToEdit[0].Get());
		UE_LOG(LogTemp, Warning, TEXT("objectToEdit > 000 ?"));
		if (propHandle.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast valid"));
			UAffinityTypeDataAsset* asset = propHandle.Get();
			Category.AddCustomRow(LOCTEXT("Ligne1", "ligne 1"))
				.NameContent()[
					SNew(STextBlock).Text(LOCTEXT("name ligne1", "name ligne 1"))
				].ValueContent()[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth()[
							propType->CreatePropertyValueWidget()
							//asset->damageModifierPerAffinity[0]
						]
						+ SHorizontalBox::Slot().AutoWidth()[
							propType->CreatePropertyValueWidget()
								//asset->damageModifierPerAffinity[0]
						]
								+ SHorizontalBox::Slot().AutoWidth()[
									propType->CreatePropertyValueWidget()
										//asset->damageModifierPerAffinity[0]
								]
								+ SHorizontalBox::Slot().AutoWidth()[
									propType->CreatePropertyValueWidget()
										//asset->damageModifierPerAffinity[0]
								]
				];
			UE_LOG(LogTemp, Warning, TEXT("EndDrawer"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Cast not valid"));
		}
	}
}

FReply MatrixEditor::EditObjects()
{
	for (TWeakObjectPtr<UObject> Object : ObjectsToEdit)
	{
		if(!Object.IsValid()) continue;

		UAffinityTypeDataAsset* asset = Cast<UAffinityTypeDataAsset>(Object.Get());

		if(asset == nullptr) continue;
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

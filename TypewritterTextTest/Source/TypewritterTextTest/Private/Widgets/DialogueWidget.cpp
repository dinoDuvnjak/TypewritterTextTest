// Fill out your copyright notice in the Description page of Project Settings.

#include "TypewritterTextTest/Public/Widgets/DialogueWidget.h"

#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "TypewritterTextTest/Public/Data/DialogueDataAsset.h"

void UDialogueWidget::StartDialogue(FDialogueData DialogueData)
 {
	if (CharacterNameText)
	{
		CharacterNameText->SetText(DialogueData.Name);
	}
	if (CharacterImage)
	{
		LoadDialogueImage(DialogueData, [this, DialogueData](UTexture2D* Texture)
		{
			if (Texture)
			{
				CharacterImage->SetBrushFromTexture(Texture);
				CurrentDialogue = DialogueData;
				CurrentCharIndex = 0;
				TypingInterval = DialogueData.TypingInterval;
				bIsAnimating = true;
				if (DialogueRichText)
				{
					DialogueRichText->SetText(FText::GetEmpty());
				}
				if (GetWorld())
				{
					GetWorld()->GetTimerManager().SetTimer(TypingTimerHandle, this, &UDialogueWidget::DisplayNextCharacter, TypingInterval, true);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("dino::Failed to load image."));
			}
		});
	}

}

void UDialogueWidget::LoadDialogueImage(const FDialogueData& DialogueData, TFunction<void(UTexture2D*)> OnLoaded)
{
	if (DialogueData.Image.ToSoftObjectPath().IsValid())
	{
		FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
		Streamable.RequestAsyncLoad(
			DialogueData.Image.ToSoftObjectPath(),
			[OnLoaded, DialogueData]() 
			{
				UTexture2D* LoadedTexture = DialogueData.Image.Get();
				OnLoaded(LoadedTexture);
			},
			FStreamableManager::DefaultAsyncLoadPriority,
			false
		);
	}
	else
	{
		OnLoaded(nullptr);
	}
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UDialogueWidget::Initialize()
{
	return Super::Initialize();
}

void UDialogueWidget::HandleDialogueFinish()
{
	GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
	OnDialogueFinished.Broadcast(CurrentDialogue);
}

FReply UDialogueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::SpaceBar)
	{
		if (bIsAnimating)
		{
			if (GetWorld())
			{
				HandleDialogueFinish();
			}
			UpdateDialogueDisplay(CurrentDialogue.DialogueText.ToString());
			bIsAnimating = false;
			return FReply::Handled();
		}
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UDialogueWidget::DisplayNextCharacter()
{
	FString FullDialogueString = CurrentDialogue.DialogueText.ToString();
	if (CurrentCharIndex < FullDialogueString.Len())
	{
		CurrentCharIndex++;
		FString PartialDialogue = FullDialogueString.Left(CurrentCharIndex);
		UpdateDialogueDisplay(PartialDialogue);
	}
	else
	{
		bIsAnimating = false;
		if (GetWorld())
		{
			HandleDialogueFinish();
		}
	}
}

void UDialogueWidget::UpdateDialogueDisplay(const FString& NewDisplayString)
{
	if (DialogueRichText)
	{
		DialogueRichText->SetText(FText::FromString(NewDisplayString));
	}
	if (DialogueScrollBox)
	{
		DialogueScrollBox->ScrollToEnd();
	}
}
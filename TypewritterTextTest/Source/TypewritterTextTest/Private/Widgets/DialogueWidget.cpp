// Fill out your copyright notice in the Description page of Project Settings.


#include "TypewritterTextTest/Public/Widgets/DialogueWidget.h"

#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "TypewritterTextTest/Public/Data/DialogueDataAsset.h"

void UDialogueWidget::StartDialogue(FDialogueData DialogueData, float InTypingInterval)
 {
	if (CharacterNameText)
	{
		CharacterNameText->SetText(DialogueData.Name);
	}
	if (CharacterImage && DialogueData.Image.IsValid())
	{
		// If already loaded, use it immediately
		UTexture2D* LoadedTexture = DialogueData.Image.Get();
		if (LoadedTexture)
		{
			if (CharacterImage)
			{
				FSlateBrush Brush;
				Brush.SetResourceObject(LoadedTexture);
				Brush.ImageSize = FVector2D(LoadedTexture->GetSizeX(), LoadedTexture->GetSizeY());
				CharacterImage->SetBrush(Brush);
			}
			return;
		}

		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		StreamableManager.RequestAsyncLoad(DialogueData.Image.ToSoftObjectPath(), [this, DialogueData]()
		{
			UTexture2D* LoadedTexture = Cast<UTexture2D>(DialogueData.Image.ToSoftObjectPath().ResolveObject());
			if (!LoadedTexture)
			{
				UE_LOG(LogTemp, Error, TEXT("Loaded object is not a texture!"));
				return;
			}
			// Convert Texture2D to Brush
			FSlateBrush Brush;
			Brush.SetResourceObject(LoadedTexture);
			Brush.ImageSize = FVector2D(LoadedTexture->GetSizeX(), LoadedTexture->GetSizeY());

			// Set to UImage
			if (CharacterImage)
			{
				CharacterImage->SetBrush(Brush);
			}
		});
	}

	CurrentDialogue = DialogueData;
	CurrentCharIndex = 0;
	TypingInterval = InTypingInterval;
	bIsAnimating = true;

	if (DialogueRichText)
	{
		DialogueRichText->SetText(FText::GetEmpty());
	}

	// Start a timer using the Timer Manager (this is real-time based, not frame-dependent).
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TypingTimerHandle, this, &UDialogueWidget::DisplayNextCharacter, TypingInterval, true);
	}
}

bool UDialogueWidget::Initialize()
{
	return Super::Initialize();
}

FReply UDialogueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::SpaceBar)
	{
		if (bIsAnimating)
		{
			if (GetWorld())
			{
				GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
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
			GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		}
	}
}

void UDialogueWidget::UpdateDialogueDisplay(const FString& NewDisplayString)
{
	// If using URichTextBlock, you might need to preserve markup for special words.
	// For simplicity, we assume NewDisplayString contains the proper markup already.
	if (DialogueRichText)
	{
		DialogueRichText->SetText(FText::FromString(NewDisplayString));
	}

	// Optionally, if the dialogue is inside a scroll box, auto-scroll to the bottom.
	if (DialogueScrollBox)
	{
		DialogueScrollBox->ScrollToEnd();
	}
}
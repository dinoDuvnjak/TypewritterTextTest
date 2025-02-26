// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TypewritterTextTest/Public/Data/DialogueDataAsset.h"
#include "DialogueWidget.generated.h"

class UImage;
class UTextBlock;
class UScrollBox;
class URichTextBlock;
struct FDialogueData;
/**
 * 
 */
UCLASS()
class TYPEWRITTERTEXTTEST_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartDialogue(FDialogueData DialogueData, float InTypingInterval);
protected:
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* DialogueRichText;
	UPROPERTY(meta = (BindWidget))
	UScrollBox* DialogueScrollBox;
	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterNameText;
protected:
	void DisplayNextCharacter();
	void UpdateDialogueDisplay(const FString& NewDisplayString);
protected:	
	// UUserWidget interface
	virtual bool Initialize() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	// End of UUserWidget interface
private:
	bool bIsAnimating = false;
	FTimerHandle TypingTimerHandle = FTimerHandle();
	FDialogueData CurrentDialogue = FDialogueData();
	/** Current length of text revealed (in characters). */
	int32 CurrentCharIndex;

	/** How often (in seconds) to reveal the next character. */
	float TypingInterval;
};

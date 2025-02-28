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
	void StartDialogue(FDialogueData DialogueData);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueFinished, FDialogueData, FinishedDialogue);
	UPROPERTY(BlueprintAssignable)
	FOnDialogueFinished OnDialogueFinished;
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
	void LoadDialogueImage(const FDialogueData& DialogueData, TFunction<void(UTexture2D*)> OnLoaded);
protected:	
	// UUserWidget interface
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	void OnDialogueFinish();
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	// End of UUserWidget interface
private:
	bool bIsAnimating = false;
	FTimerHandle TypingTimerHandle = FTimerHandle();
	FDialogueData CurrentDialogue = FDialogueData();
	int32 CurrentCharIndex;
	float TypingInterval;
};

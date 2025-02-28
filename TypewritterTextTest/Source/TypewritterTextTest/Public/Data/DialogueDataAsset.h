// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "DialogueDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D>  Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TypingInterval = 0.1f;

	FDialogueData()
	: Name(FText::GetEmpty())
	, Image(nullptr)
	, DialogueText(FText::GetEmpty())
	, TypingInterval(0.1f)
	{}
};

UCLASS(BlueprintType)
class TYPEWRITTERTEXTTEST_API UDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FDialogueData> DialogueSequence = TArray<FDialogueData>();
};

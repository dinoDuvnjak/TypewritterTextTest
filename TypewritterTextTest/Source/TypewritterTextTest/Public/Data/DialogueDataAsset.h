// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueDataAsset.generated.h"

//create struct exposed to blueprints
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

	FDialogueData()
	: Name(FText::GetEmpty())
	, Image(nullptr)
	, DialogueText(FText::GetEmpty())
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "KeywordBlockDecorator.generated.h"

/**
 * 
 */
UCLASS()
class TYPEWRITTERTEXTTEST_API UKeywordBlockDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
protected:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;	
};

class FKeywordDecorator : public FRichTextDecorator
{
public:
	FKeywordDecorator(URichTextBlock* InOwner);

protected:
	bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override;
	TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& DefaultTextStyle) const override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/KeywordBlockDecorator.h"

TSharedPtr<ITextDecorator> UKeywordBlockDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FKeywordDecorator(InOwner));
}

FKeywordDecorator::FKeywordDecorator(URichTextBlock* InOwner) 
	: FRichTextDecorator(InOwner)
{}

bool FKeywordDecorator::Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const
{
	return RunParseResult.Name == TEXT("keyword");
}

TSharedPtr<SWidget> FKeywordDecorator::CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& DefaultTextStyle) const
{
	FString KeywordText = RunInfo.Content.ToString();
	TSharedRef<STextBlock> TextBlock = SNew(STextBlock)
		.Text(FText::FromString(KeywordText)) 
		.ColorAndOpacity(FSlateColor(FLinearColor::Yellow)) 
		.Font(DefaultTextStyle.Font)
		.ToolTip(SNew(SToolTip) 
			.Text(FText::FromString(FString::Printf(TEXT("Explanation about: %s"), *KeywordText)))
		);
	
	return TextBlock;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"

#include "InspectWidget.generated.h"

/**
 * 
 */
UCLASS()
class REALHORROR_API UInspectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItemName(FText ItemName);
	void SetItemDiscription(FText ItemDiscription);

	void ScrollUp();
	void ScrollDown();
private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadOnly, EditDefaultsOnly)
	UTextBlock* TB_ItemName;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadOnly, EditDefaultsOnly)
	UTextBlock* TB_ItemDiscription;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadOnly, EditDefaultsOnly)
	UScrollBox* SB_ItemDiscription;

	float ScrollOffset = 0.0f;
};

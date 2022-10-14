// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class REALHORROR_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetIsFocused(bool value);
private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Interact;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UImage* I_Interact;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REALHORROR_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact() = 0;
	virtual void Focus(bool Value) {}
	virtual FText GetItemName() { return FText(); }
	virtual FText GetItemDiscription() { return FText(); }
	
	virtual void SetInput(bool Value) {}
	// Inspect Widget
	virtual USceneComponent* GetInspectLocation() { return nullptr; }
	virtual void ScrollUp() {}
	virtual void ScrollDown() {}
	virtual void ShowInspectWidget(FText ItemName, FText ItemDiscription) {};
	virtual void HideInspectWidget() {}

	// Hidable Object
	virtual void Hide() {}
	virtual void UnHide(float Time = -1.0f) {}
};

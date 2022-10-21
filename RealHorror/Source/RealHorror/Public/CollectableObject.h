// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"

#include "CollectableObject.generated.h"

/**
 * 
 */
UCLASS()
class REALHORROR_API ACollectableObject : public AInteractObject
{
	GENERATED_BODY()
	
public:
	ACollectableObject();
	
protected:
	virtual void BeginPlay() override;
	virtual void Interact() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual FText GetItemName() override { return ItemName; }
	virtual FText GetItemDiscription() override { return ItemDiscription; }
private:
	void Inspect();
	void DropDown();
	void RotateMesh();
protected:
	FText ItemName;
	FText ItemDiscription;
private:
	FTransform OriginTransform;
	FVector RelativeScale;
	int ZoomLevel = 0;
	float ZoomSize = 0.02f;
};

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
	
protected:
	virtual void BeginPlay() override;
	virtual void Interact() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Inspect();
	void DropDown();
	void RotateMesh();
private:
	FTransform OriginTransform;
	FVector RelativeScale;
	APlayerController* PC = nullptr;
	class AHorrorCharacter* Player = nullptr;
	int ZoomLevel = 0;
	float ZoomSize = 0.05f;
};

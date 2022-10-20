// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

#include "HidableObject.generated.h"

/**
 * 
 */
UCLASS()
class REALHORROR_API AHidableObject : public AInteractObject
{
	GENERATED_BODY()
	
public:
	AHidableObject();
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	UBoxComponent* BoxComponent;
};

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
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual void Hide() override;
	virtual void UnHide(float Time = -1.0f) override;

private:
	void MoveCamera();
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	float CameraBlendTime = 0.4f;

	// Camera Move
	float Pitch = 0;
	float Yaw = 0;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	float MaxPitch = 10;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere)
	float MaxYaw = 60;
	FRotator OriginRelativeRoation;
};

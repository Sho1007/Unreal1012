// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Public/InspectWidget.h"

#include "Components/SceneCaptureComponent2D.h"

#include "HorrorCharacter.generated.h"

UCLASS()
class REALHORROR_API AHorrorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorrorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTransform GetCameraTransform() { return CameraComponent->GetComponentTransform(); }

	// Inspecting
	void ShowInspectWidget(FText ItemName, FText ItemDiscription);
	void HideInspectWidget();
	void ScrollUp() { InspectWidget->ScrollUp(); }
	void ScrollDown() { InspectWidget->ScrollDown(); }
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void Interact();
private:
	void FindFocusTarget();
	

private:
	bool bIsCanMove = true;
	bool bIsCameraCanMove = true;

	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	class IInteractInterface* FocusActor = nullptr;
	UInspectWidget* InspectWidget = nullptr;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditDefaultsOnly)
	TSubclassOf<UInspectWidget> InspectWidgetClass;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* InspectingLocation = nullptr;
};

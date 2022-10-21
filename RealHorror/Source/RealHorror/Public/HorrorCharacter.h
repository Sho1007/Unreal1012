// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Public/InspectWidget.h"
#include "Components/SceneCaptureComponent2D.h"

#include "../Public/InteractInterface.h"

#include "HorrorCharacter.generated.h"

UCLASS()
class REALHORROR_API AHorrorCharacter : public ACharacter, public IInteractInterface
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
protected:
	// Interact Interface
	virtual void Interact() override;
	virtual USceneComponent* GetInspectLocation() override { return InspectingLocation; }
	virtual void SetInput(bool Value) override;
	virtual void ScrollUp() override { InspectWidget->ScrollUp(); }
	virtual void ScrollDown() override { InspectWidget->ScrollDown(); }
	virtual void ShowInspectWidget(FText ItemName, FText ItemDiscription) override;
	virtual void HideInspectWidget() override;
	// Hidable Object
	virtual void Hide() override;
	virtual void UnHide(float Time = -1.0f) override;
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	
private:
	void FindFocusTarget();
	

private:
	bool bIsHide = false;

	bool bIsCanMove = true;
	bool bIsCameraCanMove = true;

	APlayerController* PC = nullptr;

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

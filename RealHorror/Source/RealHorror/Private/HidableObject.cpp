// Fill out your copyright notice in the Description page of Project Settings.


#include "HidableObject.h"

AHidableObject::AHidableObject() : Super()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(RootComponent);
}

void AHidableObject::BeginPlay()
{
	Super::BeginPlay();
	OriginRelativeRoation = CameraComponent->GetRelativeRotation();
}

void AHidableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PC->WasInputKeyJustPressed(EKeys::E))
		UnHide();

	MoveCamera();
}

void AHidableObject::Interact()
{
	Hide();
}

void AHidableObject::Hide()
{
	Player->Hide();
	EnableInput(PC);
	Pitch = Yaw = 0;
	CameraComponent->SetRelativeRotation(OriginRelativeRoation);
	PC->SetViewTargetWithBlend(this, CameraBlendTime);
	
	FTimerHandle WaitTimer;
	GetWorld()->GetTimerManager().SetTimer(WaitTimer, FTimerDelegate::CreateLambda([&]()
		{
			SetActorTickEnabled(true);
		}), CameraBlendTime, false);
}

void AHidableObject::UnHide(float Time)
{
	//PC->SetViewTargetWithBlend(Cast<AActor>(Player), CameraBlendTime);
	SetActorTickEnabled(false);
	DisableInput(PC);
	Player->UnHide(CameraBlendTime);
}

void AHidableObject::MoveCamera()
{
	float MouseX, MouseY;
	PC->GetInputMouseDelta(MouseX, MouseY);
	if (!MouseX && !MouseY) return;

	

	if (MouseY > 0)
	{
		if (Pitch < MaxPitch)
		{
			Pitch += MouseY;
			if (Pitch > MaxPitch) Pitch = MaxPitch;
		}
	}
	else
	{
		if (-MaxPitch < Pitch)
		{
			Pitch += MouseY;
			if (Pitch < -MaxPitch) Pitch = -MaxPitch;
		}
	}

	if (MouseX > 0)
	{
		if (Yaw < MaxYaw)
		{
			Yaw += MouseX;
			if (Yaw > MaxYaw) Yaw = MaxYaw;
		}
	}
	else
	{
		if (-MaxYaw < Yaw)
		{
			Yaw += MouseX;
			if (Yaw < -MaxYaw) Yaw = -MaxYaw;
		}
	}

	CameraComponent->SetRelativeRotation(OriginRelativeRoation + FRotator(Pitch, Yaw, 0));
}

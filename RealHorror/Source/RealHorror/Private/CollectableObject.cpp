// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableObject.h"
#include "../Public/HorrorCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void ACollectableObject::BeginPlay()
{
	Super::BeginPlay();

	OriginTransform = GetActorTransform();
	PC = GetWorld()->GetFirstPlayerController();
	Player = Cast<AHorrorCharacter>(PC->GetCharacter());
}

void ACollectableObject::Interact()
{
	if (Player && Player->IsValidLowLevelFast())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Cast Successed"));
		Focus(false);
		WidgetComponent->SetVisibility(false, false);
		
		FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		AttachToComponent(Player->InspectingLocation, Rules);

		StaticMeshComponent->SetSimulatePhysics(false);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Player->DisableInput(PC);
		this->EnableInput(PC);
		FTimerHandle WaitTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, FTimerDelegate::CreateLambda([&]() {
			SetActorTickEnabled(true);
		}), 0.5f, false);
	}
}

void ACollectableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PC->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		float MouseX, MouseY;
		PC->GetInputMouseDelta(MouseX, MouseY);

		FTransform Transform = StaticMeshComponent->GetRelativeTransform();
		Transform.ConcatenateRotation(FRotator(0, -MouseX * 2, 0).Quaternion());
		Transform.ConcatenateRotation(FRotator(-MouseY * 2, 0, 0).Quaternion());
		StaticMeshComponent->SetRelativeTransform(Transform);
	}
	if (PC->WasInputKeyJustPressed(EKeys::E))
	{
		SetActorTickEnabled(false);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		this->DisableInput(PC);
		Player->EnableInput(PC);
		DetachRootComponentFromParent(false);
		WidgetComponent->SetVisibility(true, false);
		SetActorTransform(OriginTransform);
		Focus(true);
	}
}

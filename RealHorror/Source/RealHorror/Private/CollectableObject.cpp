// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableObject.h"
#include "Kismet/KismetMathLibrary.h"

ACollectableObject::ACollectableObject() : Super()
{
	ItemName = FText::FromName("CollectableObject");
	ItemDiscription = FText::FromName("DiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTestDiscriptionTest");
}

void ACollectableObject::BeginPlay()
{
	Super::BeginPlay();

	OriginTransform = GetActorTransform();
}

void ACollectableObject::Interact()
{
	Inspect();
}

void ACollectableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PC->WasInputKeyJustPressed(EKeys::E))
		DropDown();
	else
		RotateMesh();
}

void ACollectableObject::Inspect()
{
	if (Player)
	{
		Focus(false);
		WidgetComponent->SetVisibility(false);
		FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
		AttachToComponent(Player->GetInspectLocation(), Rules);

		RelativeScale = GetActorRelativeScale3D();

		StaticMeshComponent->SetSimulatePhysics(false);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Player->SetInput(false);
		this->EnableInput(PC);

		// Input Switch
		FTimerHandle WaitTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, FTimerDelegate::CreateLambda([&]() {
			SetActorTickEnabled(true);
			}), 0.5f, false);

		Player->ShowInspectWidget(ItemName, ItemDiscription);
	}
}

void ACollectableObject::DropDown()
{
	Player->HideInspectWidget();
	SetActorTickEnabled(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->DisableInput(PC);
	Player->SetInput(true);
	FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
	DetachFromActor(Rules);
	WidgetComponent->SetVisibility(true);
	SetActorTransform(OriginTransform);
	Focus(true);
}

void ACollectableObject::RotateMesh()
{
	if (PC->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		float MouseX, MouseY;
		PC->GetInputMouseDelta(MouseX, MouseY);

		SetActorRotation(UKismetMathLibrary::ComposeRotators(GetActorRotation(), FRotator(0, MouseX * -2.0f, 0)));
		SetActorRotation(UKismetMathLibrary::ComposeRotators(GetActorRotation(), FRotator(0, 0, MouseY * 2.0f)));
	}

	if (PC->IsInputKeyDown(EKeys::Up))
	{
		Player->ScrollUp();
	}
	else if (PC->IsInputKeyDown(EKeys::Down))
	{
		Player->ScrollDown();
	}

	if (PC->WasInputKeyJustPressed(EKeys::MouseScrollDown))
	{
		if (ZoomLevel > 0)
		{
			ZoomLevel -= 1;
			SetActorScale3D(RelativeScale + (ZoomLevel * ZoomSize));
		}
	}

	if (PC->WasInputKeyJustPressed(EKeys::MouseScrollUp))
	{
		if (ZoomLevel < 10)
		{
			ZoomLevel += 1;
			SetActorScale3D(RelativeScale + (ZoomLevel * ZoomSize));
		}
	}
}

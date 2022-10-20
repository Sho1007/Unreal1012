// Fill out your copyright notice in the Description page of Project Settings.


#include "HidableObject.h"

AHidableObject::AHidableObject() : Super()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	CameraComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

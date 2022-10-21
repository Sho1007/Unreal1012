// Fill out your copyright notice in the Description page of Project Settings.


#include "Locker.h"

ALocker::ALocker() : Super()
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(StaticMeshComponent);
}

void ALocker::BeginPlay()
{
	Super::BeginPlay();
}

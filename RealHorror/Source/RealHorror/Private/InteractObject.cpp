// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "../Public/InteractWidget.h"

// Sets default values
AInteractObject::AInteractObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetRenderCustomDepth(true);
	SetRootComponent(StaticMeshComponent);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractObject::Interact()
{
	Destroy();
}

void AInteractObject::Focus(bool value)
{
	StaticMeshComponent->bRenderCustomDepth = true;
	StaticMeshComponent->CustomDepthStencilValue = 1;

	StaticMeshComponent->SetCustomDepthStencilValue((int)value);
	UInteractWidget* Widget = Cast<UInteractWidget>(WidgetComponent->GetWidget());
	if (Widget)
	{
		Widget->SetIsFocused(value);
	}
}

// Called every frame
void AInteractObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


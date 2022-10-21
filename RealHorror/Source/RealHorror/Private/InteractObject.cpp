// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "../Public/InteractWidget.h"
#include "../Public/HorrorCharacter.h"

// Sets default values
AInteractObject::AInteractObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(Root);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetRenderCustomDepth(true);
	StaticMeshComponent->SetupAttachment(RootComponent);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	PC = GetWorld()->GetFirstPlayerController();
	Player = Cast<IInteractInterface>(PC->GetCharacter());
}

void AInteractObject::Interact()
{
	Destroy();
}

void AInteractObject::Focus(bool value)
{
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


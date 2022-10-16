// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "../Public/InteractInterface.h"

#include "InteractObject.generated.h"

UCLASS()
class REALHORROR_API AInteractObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact() override;
	virtual void Focus(bool value) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite, EditAnywhere)
	UWidgetComponent* WidgetComponent = nullptr;
};

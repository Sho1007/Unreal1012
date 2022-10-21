// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HidableObject.h"
#include "Locker.generated.h"

/**
 * 
 */
UCLASS()
class REALHORROR_API ALocker : public AHidableObject
{
	GENERATED_BODY()
	
public:
	ALocker();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorMesh;
};

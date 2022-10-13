// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorCharacter.h"

// Sets default values
AHorrorCharacter::AHorrorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHorrorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHorrorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHorrorCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AHorrorCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AHorrorCharacter::LookRight);

}

void AHorrorCharacter::MoveForward(float AxisValue)
{
	if ((Controller == nullptr) || (AxisValue == 0.0)) return;

	// Find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotaion(0, Rotation.Yaw, 0);

	// Get Forward Vector
	const FVector Direction = FRotationMatrix(YawRotaion).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AHorrorCharacter::MoveRight(float AxisValue)
{
	if ((Controller == nullptr) || (AxisValue == 0.0)) return;

	// Find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotaion(0, Rotation.Yaw, 0);

	// Get Forward Vector
	const FVector Direction = FRotationMatrix(YawRotaion).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AHorrorCharacter::LookUp(float AxisValue)
{
	if (!Controller || !AxisValue) return;
	if (bIsCameraCanMove)
		AddControllerPitchInput(AxisValue);
}

void AHorrorCharacter::LookRight(float AxisValue)
{
	if (!Controller || !AxisValue) return;
	if (bIsCameraCanMove)
		AddControllerYawInput(AxisValue);
}


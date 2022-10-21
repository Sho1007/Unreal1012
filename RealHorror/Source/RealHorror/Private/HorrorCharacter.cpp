// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Public/InteractInterface.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AHorrorCharacter::AHorrorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 10.0f;
	SpringArmComponent->SetRelativeLocation(FVector(20, 0, 70));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InspectingLocation = CreateDefaultSubobject<USceneComponent>("InspectingLocation");
	InspectingLocation->SetupAttachment(CameraComponent);
	InspectingLocation->SetRelativeLocation(FVector(100, -10, 0));
}

// Called when the game starts or when spawned
void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();

	InspectWidget = CreateWidget<UInspectWidget>(Cast<APlayerController>(GetController()), InspectWidgetClass);
	InspectWidget->AddToViewport();
	InspectWidget->SetVisibility(ESlateVisibility::Hidden);

	PC = Cast<APlayerController>(GetController());
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHorrorCharacter::Interact);
}

void AHorrorCharacter::ShowInspectWidget(FText ItemName, FText ItemDiscription)
{
	InspectWidget->SetItemName(ItemName);
	InspectWidget->SetItemDiscription(ItemDiscription);
	InspectWidget->SetVisibility(ESlateVisibility::Visible);
}

void AHorrorCharacter::HideInspectWidget()
{
	InspectWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AHorrorCharacter::Hide()
{
	bIsHide = true;
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
}

void AHorrorCharacter::UnHide(float Time)
{
	
	PC->SetViewTargetWithBlend(this, Time);
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			SetActorHiddenInGame(false);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			EnableInput(PC);
		}
	), Time, false);
	bIsHide = false;
}

void AHorrorCharacter::SetInput(bool Value)
{
	if (Value) EnableInput(GetWorld()->GetFirstPlayerController());
	else DisableInput(GetWorld()->GetFirstPlayerController());
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

	FindFocusTarget();
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

	FindFocusTarget();
}

void AHorrorCharacter::LookUp(float AxisValue)
{
	if (!Controller || !AxisValue) return;
	if (bIsCameraCanMove)
	{
		AddControllerPitchInput(AxisValue);
		FindFocusTarget();
	}
		
}

void AHorrorCharacter::LookRight(float AxisValue)
{
	if (!Controller || !AxisValue) return;
	if (bIsCameraCanMove)
	{
		AddControllerYawInput(AxisValue);
		FindFocusTarget();
	}
}

void AHorrorCharacter::Interact()
{
	if (FocusActor)
	{
		FocusActor->Interact();
	}
}

void AHorrorCharacter::FindFocusTarget()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * 300.0f;
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, { this }, EDrawDebugTrace::None, HitResult, true))
	{
		IInteractInterface* Object = Cast<IInteractInterface>(HitResult.GetActor());
		if (Object)
		{
			if (FocusActor)
			{
				if (FocusActor == Object) return;
				else FocusActor->Focus(false);
			}
			FocusActor = Object;
			FocusActor->Focus(true);
			
			return;
		}
	}

	if (FocusActor)
	{
		FocusActor->Focus(false);
		FocusActor = nullptr;
	}
}


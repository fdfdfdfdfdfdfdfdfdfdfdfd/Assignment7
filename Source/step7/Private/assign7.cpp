#include "assign7.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "SpartaControll.h"


Aassign7::Aassign7()
{
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	SetRootComponent(Body);
	Body->SetSimulatePhysics(false);
	Body->SetCollisionProfileName(TEXT("OverlapAll"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	// SpringArm->TargetArmLength = 300.f; 이거 안해도 기본값이 300.0f로 적용되어 있음

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void Aassign7::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector StartLocation = GetActorLocation();
	StartLocation += FVector(0.0f, 0.0f, 50.0f); // 높이를 조금 올려줌.

	FVector EndLocationWithLocalForwardVector = StartLocation + (GetActorForwardVector() * 100.0f);
	FVector EndLocationWorldForwardVector = StartLocation + (FVector::ForwardVector * 100.0f);

	DrawDebugDirectionalArrow(GetWorld(), StartLocation, EndLocationWithLocalForwardVector, 50.0f, FColor::Red, false, 0.f, 0, 2.0f);
	DrawDebugDirectionalArrow(GetWorld(), StartLocation, EndLocationWorldForwardVector, 50.0f, FColor::Green, false, 0.f, 0, 2.0f);
}

void Aassign7::UE4UpDown(float InAxisValue)
{
	UE_LOG(LogTemp, Log, TEXT("Aassign7::UE4UpDown(%f)"), InAxisValue);
}

void Aassign7::UE4LeftRight(float InAxisValue)
{
	UE_LOG(LogTemp, Log, TEXT("Aassign7::UE4LeftRight(%f)"), InAxisValue);
}

void Aassign7::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UE4UpDown"), this, &ThisClass::UE4UpDown);
	PlayerInputComponent->BindAxis(TEXT("UE4LeftRight"), this, &ThisClass::UE4LeftRight);

	if (UEnhancedInputComponent* EnhancedInPut = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaControll* PlayerController = Cast<ASpartaControll>(GetController()))
		{
			if (PlayerController->MoveForwardAction)
			{
				EnhancedInPut->BindAction(PlayerController->MoveForwardAction, ETriggerEvent::Triggered, this, &ThisClass::MoveForward);
			}

			if (PlayerController->MoveRightAction)
			{
				EnhancedInPut->BindAction(PlayerController->MoveRightAction, ETriggerEvent::Triggered, this, &ThisClass::MoveRight);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInPut->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
			}
		}
	}
}

void Aassign7::MoveForward(const FInputActionValue& InValue)
{
	float ForwardInput = InValue.Get<float>();
	// UE_LOG(LogTemp, Log, TEXT("ForwardInput: %.1f"), ForwardInput);
	AddActorLocalOffset(FVector(ForwardInput, 0.f, 0.f));
}

void Aassign7::MoveRight(const FInputActionValue& InValue)
{
	float RightInput = InValue.Get<float>();
	// UE_LOG(LogTemp, Log, TEXT("RightInput: %.1f"), RightInput);
	AddActorLocalOffset(FVector(0.f, RightInput, 0.f));
}

void Aassign7::Look(const FInputActionValue& InValue)
{
	float LookInput = InValue.Get<float>();
	// UE_LOG(LogTemp, Log, TEXT("Look: %.1f"), LookInput);
	AddActorLocalRotation(FRotator(0.f, LookInput, 0.f));
}

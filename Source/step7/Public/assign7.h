#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "assign7.generated.h"


// 1d로 단순 동작만 하는거면 애로우 유무는 필요 없는건가요? 앞으로 간다고 해도 어디가 앞인지는 알아야 할 것 같은데
class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class STEP7_API Aassign7 : public APawn
{
	GENERATED_BODY()

private:
	void UE4UpDown(float InAxisValue);
	void UE4LeftRight(float InAxisValue);

	void MoveForward(const FInputActionValue& InValue);

	void MoveRight(const FInputActionValue& InValue);

	void Look(const FInputActionValue& InValue);

public:
	Aassign7();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "assign7|Components")
	UCapsuleComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "assign7|Components")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "assign7|Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "assign7|Components")
	UCameraComponent* Camera;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};

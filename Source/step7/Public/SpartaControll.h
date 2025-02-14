#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaControll.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class STEP7_API ASpartaControll : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASpartaControll|Properties")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASpartaControll|Properties")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASpartaControll|Properties")
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASpartaControll|Properties")
	UInputAction* LookAction;

};

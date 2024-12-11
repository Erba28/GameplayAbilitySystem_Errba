// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Character/ErrbaEnemy.h>
#include "ErrbaPlayerControllerBase.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class GASTEST_API AErrbaPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	AErrbaPlayerControllerBase();
	virtual void PlayerTick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext>ErrbaContext;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction>MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();
protected:
	virtual void BeginPlay()override;
	virtual void SetupInputComponent()override;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};

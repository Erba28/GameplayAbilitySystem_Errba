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
//class IEnemyInterface;

UCLASS()
class GASTEST_API AErrbaPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	AErrbaPlayerControllerBase();
	//仅在悬停不同Actor时检查
	virtual void PlayerTick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere,Category = "Input")//在蓝图中可编辑
	TObjectPtr<UInputMappingContext>ErrbaContext;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction>MoveAction;
	//引用FInputActionValue结构体做Move函数变量
	void Move(const FInputActionValue& InputActionValue);
	
	void CursorTrace();
	//指向IEnemyInterface的指针
protected:
	virtual void BeginPlay()override;
	virtual void SetupInputComponent()override;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};

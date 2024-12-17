 // Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ErrbaPlayerControllerBase.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>


AErrbaPlayerControllerBase::AErrbaPlayerControllerBase()
{
	bReplicates = true;
}

void AErrbaPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AErrbaPlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector InputAxisVector = InputActionValue.Get<FVector>();
	//获得摄像机相对Pawn方向为正方向
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	//e枚举
	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis:: Y);

	if (APawn* ControllerPawn = GetPawn())
	{
		//用Scale
		ControllerPawn->AddMovementInput(ForwardDir, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDir, InputAxisVector.X);
		//ControllerPawn->AddMovementInput(FVector(0,0,1), InputAxisVector.Z*100);

	}
}

void AErrbaPlayerControllerBase::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit); 
	if (!CursorHit.GetActor())return;
	//两个指针，一个正在悬停的Actor,一个为记录上一个悬停的Actor
	LastActor = ThisActor;

	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor ());
	/*
	Line trace from cursor, There are several scenarios : 
	A.LastActor is null && ThisActor is null
		- Do nothing
	B.LastActor is null && ThisActor is valid
		- heighlight ThisActor
	C.LastActor is valid && ThisActor is null
		- UnHighlight LastActor
	D.Both actors are valid, but lastActor != ThisActor 
		- UnHighiight LastActor, and Highlight ThisActor
	E.Both actors are valid, and are the same actor
		- Do nothing
	*/
	if(LastActor == nullptr)
		if (ThisActor != nullptr)
		{	
			//B
			ThisActor->HightLightActor();
		}
		else
		{
			//A
		}
	else
		if (ThisActor == nullptr)
		{
			//C
			LastActor->UnHightLightActor();
		}
		else
		{
			//E
			LastActor->UnHightLightActor();
			ThisActor->HightLightActor();
		}
}

void AErrbaPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	//断言
	  check(ErrbaContext);

	//创建一个指向增强输入子系统指针 Subsystem 通过本地玩家类静态函数获取 GetSubsystem是一个需要类型的模板（方法），方法需要一个类型为本地玩家的参数 
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//断言
		check(Subsystem);
	//调用AddMappingContext函数调用Input Mapping Context，优先级
	Subsystem->AddMappingContext(ErrbaContext, 0);
	//显示鼠标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}

void AErrbaPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	//转换+断言CastChecked
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked < UEnhancedInputComponent>(InputComponent);
	//绑定Move,MoveAction,最后操作方法地址，完全限定函数名
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AErrbaPlayerControllerBase::Move);

}
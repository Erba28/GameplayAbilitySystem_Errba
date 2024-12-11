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
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis:: Y);

	if (APawn* ControllerPawn = GetPawn())//��������������ִ��playercontroller������pawn��Move��������ÿ֡���ã������ö���
	{
		ControllerPawn->AddMovementInput(ForwardDir, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDir, InputAxisVector.X);
		//ControllerPawn->AddMovementInput(FVector(0,0,1), InputAxisVector.Z*100);

	}
}

void AErrbaPlayerControllerBase::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit); 
	if (!CursorHit.GetActor())return;//��һ��
	LastActor = ThisActor;
	//���ڸոջ��еĿ�����û��ʵ������ӿ�
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor ());

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
}

void AErrbaPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	//����
	  check(ErrbaContext);

	//�õ����������ǿ������ϵͳ
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		check(Subsystem);
	//���������龰
	Subsystem->AddMappingContext(ErrbaContext, 0);
	//��ʾ���
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
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked < UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AErrbaPlayerControllerBase::Move);

}
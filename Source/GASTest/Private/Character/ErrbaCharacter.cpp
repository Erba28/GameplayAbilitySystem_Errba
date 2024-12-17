// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ErrbaCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AErrbaCharacter::AErrbaCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ErrbaCharacterBase.h"

AErrbaCharacterBase::AErrbaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//绑定武器到插槽
	Weapon->SetupAttachment(GetMesh(), FName("WeaponSocket")); 
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AErrbaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}




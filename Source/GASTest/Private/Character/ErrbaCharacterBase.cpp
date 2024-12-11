// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ErrbaCharacterBase.h"

// Sets default values
AErrbaCharacterBase::AErrbaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponSocket")); 
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AErrbaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}




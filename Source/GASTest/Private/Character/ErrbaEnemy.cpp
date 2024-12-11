// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ErrbaEnemy.h"
#include "GASTest/GASTest.h"

void AErrbaEnemy::HightLightActor()
{
	//bHightLightActor = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AErrbaEnemy::UnHightLightActor()
{
	//bHightLightActor = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

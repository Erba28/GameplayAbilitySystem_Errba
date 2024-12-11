// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ErrbaCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "ErrbaEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GASTEST_API AErrbaEnemy : public AErrbaCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	bool bHightLightActor = false;	
	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;
};

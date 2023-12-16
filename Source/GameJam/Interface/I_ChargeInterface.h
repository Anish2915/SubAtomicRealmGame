// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_ChargeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_ChargeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEJAM_API II_ChargeInterface
{
	GENERATED_BODY()

public:
	virtual void apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle) = 0;
	virtual void GripInterface(FVector &vec) = 0;
	virtual void SlugDestroy(int SlugParticle,FVector ProjectilePosition) = 0;
};

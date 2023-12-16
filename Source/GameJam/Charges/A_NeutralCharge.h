// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_ChargeBase.h"
#include "A_NeutralCharge.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AA_NeutralCharge : public AA_ChargeBase
{
	GENERATED_BODY()
public:
	virtual void apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle) override;
	virtual void GripInterface(FVector& vec) override;
	virtual void SlugDestroy(int SlugParticle, FVector ProjectilePosition) override;
};

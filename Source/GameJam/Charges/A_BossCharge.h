// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_ChargeBase.h"
#include "A_BossCharge.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AA_BossCharge : public AA_ChargeBase
{
	GENERATED_BODY()
public:
	AA_BossCharge();
	virtual void apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle) override;
	virtual void GripInterface(FVector& vec) override;
	virtual void SlugDestroy(int SlugParticle, FVector ProjectilePosition) override;

	float health = 100;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UWidgetComponent* Widget;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealth(float a);

};

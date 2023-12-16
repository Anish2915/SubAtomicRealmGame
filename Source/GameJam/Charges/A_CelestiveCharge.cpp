// Fill out your copyright notice in the Description page of Project Settings.


#include "A_CelestiveCharge.h"

void AA_CelestiveCharge::apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle)
{

}

void AA_CelestiveCharge::GripInterface(FVector& vec)
{
	if (anti) return;
	FVector Temp = GetActorLocation();
	SetActorLocation(vec);
	Temp = Temp - vec;
	if (OppChargeRef) {
		OppChargeRef->SetActorLocation(OppChargeRef->GetActorLocation() + Temp);
	}
}

void AA_CelestiveCharge::SlugDestroy(int SlugParticle, FVector ProjectilePosition)
{
	if (SlugParticle == 0 || SlugParticle==2) {
		Destroy();
	}
}

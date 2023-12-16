// Fill out your copyright notice in the Description page of Project Settings.


#include "A_NeutralCharge.h"

void AA_NeutralCharge::apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle)
{
}

void AA_NeutralCharge::GripInterface(FVector& vec)
{
	FVector Temp = GetActorLocation();
	SetActorLocation(vec);
	Temp = Temp - vec;
	if (OppChargeRef) {
		OppChargeRef->SetActorLocation(OppChargeRef->GetActorLocation() + Temp);
	}
}

void AA_NeutralCharge::SlugDestroy(int SlugParticle, FVector ProjectilePosition)
{
	if (SlugParticle == 1 || SlugParticle == 2) {
		Destroy();
	}
}



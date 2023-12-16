// Fill out your copyright notice in the Description page of Project Settings.


#include "A_NegativeCharge.h"
#include "A_PositiveCharge.h"
void AA_NegativeCharge::apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle)
{
	if (particleIndex == 4) {
		this->SetActorEnableCollision(false);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (PositiveBP)
		GetWorld()->SpawnActor<AA_PositiveCharge>(PositiveBP, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 200), GetActorRotation(), SpawnInfo)->Excited = Excited;
		this->Destroy();
	}
}

void AA_NegativeCharge::GripInterface(FVector& vec)
{
	FVector Temp = GetActorLocation();
	SetActorLocation(vec);
	Temp = Temp - vec;
	if (OppChargeRef) {
		OppChargeRef->SetActorLocation(OppChargeRef->GetActorLocation() + Temp);
	}
}

void AA_NegativeCharge::SlugDestroy(int SlugParticle, FVector ProjectilePosition)
{
	if (SlugParticle==1 || SlugParticle==2) {
		Destroy();
	}
	else if (SlugParticle == 4) {
		SpawnNiag(ProjectilePosition, GetActorLocation());
	}
}

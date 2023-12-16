// Fill out your copyright notice in the Description page of Project Settings.


#include "A_PositiveCharge.h"
#include "A_NegativeCharge.h"
#include "A_CelestiveCharge.h"
#include "Kismet/GameplayStatics.h"
void AA_PositiveCharge::apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle)
{
	if (particleIndex == 3) {
		this->SetActorEnableCollision(false);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (NegativeBP) 
		GetWorld()->SpawnActor<AA_NegativeCharge>(NegativeBP, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100), GetActorRotation(), SpawnInfo)->Excited = Excited;
		this->Destroy();
	}
	else if (particleIndex == 0) {
		this->SetActorEnableCollision(false);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		if (CelestiveBP)
		{
			AA_CelestiveCharge* temp1 =  GetWorld()->SpawnActor<AA_CelestiveCharge>(CelestiveBP, FVector(GetActorLocation().X + 200, GetActorLocation().Y, GetActorLocation().Z + 200), GetActorRotation(), SpawnInfo);
			
			AA_CelestiveCharge* temp2 = GetWorld()->SpawnActor<AA_CelestiveCharge>(CelestiveBP, FVector(GetActorLocation().X - 200, GetActorLocation().Y, GetActorLocation().Z + 200), GetActorRotation(), SpawnInfo);
			if (temp1 && temp2) {
				temp1->anti = false;
				temp2->anti = true;
				temp1->OppChargeRef = temp2;
				temp2->OppChargeRef = temp1;
				temp1->Excited = Excited;
				temp2->Excited = Excited;
			}
		}
		this->Destroy();

	}
}

void AA_PositiveCharge::GripInterface(FVector& vec)
{
	FVector Temp = GetActorLocation();
	SetActorLocation(vec);
	Temp = Temp - vec;
	if (OppChargeRef) {
		OppChargeRef->SetActorLocation(OppChargeRef->GetActorLocation() + Temp);
	}
}

void AA_PositiveCharge::SlugDestroy(int SlugParticle, FVector ProjectilePosition)
{
	if (SlugParticle == 1 || SlugParticle == 2) {
		Destroy();
	}
	else if (SlugParticle == 3) {
		SpawnNiag(ProjectilePosition, GetActorLocation());
	}
}



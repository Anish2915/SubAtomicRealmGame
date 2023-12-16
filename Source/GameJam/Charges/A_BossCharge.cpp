// Fill out your copyright notice in the Description page of Project Settings.


#include "A_BossCharge.h"
#include "Components/WidgetComponent.h"
#include "Misc/MessageDialog.h"
#include "Kismet/KismetSystemLibrary.h"
AA_BossCharge::AA_BossCharge()
{
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Wid"));
	Widget->SetupAttachment(RootComponent);
}

void AA_BossCharge::apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle)
{
	if(particleIndex==0 || particleIndex==2)
	health = health - 1;
	UpdateHealth(health);
	
}

void AA_BossCharge::GripInterface(FVector& vec)
{
}

void AA_BossCharge::SlugDestroy(int SlugParticle, FVector ProjectilePosition)
{
	if (SlugParticle <= 2) {
		health = health - 2;
		UpdateHealth(health);
	}
}



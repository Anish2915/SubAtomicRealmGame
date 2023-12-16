// Fill out your copyright notice in the Description page of Project Settings.


#include "Blaster_CPP.h"
#include "TP_WeaponComponent.h"

// Sets default values
ABlaster_CPP::ABlaster_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlaster_CPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlaster_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlaster_CPP::Set(UTP_WeaponComponent* compo)
{
	comp = compo;
}





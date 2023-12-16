// Fill out your copyright notice in the Description page of Project Settings.


#include "A_ChargeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Blaster_CPP.h"
#include "../GameJamCharacter.h"
#include "../GameJamPlayerController.h"
#include "Camera/CameraShakeBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"
// Sets default values
AA_ChargeBase::AA_ChargeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2 , ECollisionResponse::ECR_Block);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AA_ChargeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
	if(FoundActors.Num()>=1)
    blaster = Cast<ABlaster_CPP>(FoundActors[0]);
}

// Called every frame
void AA_ChargeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Excited && blaster) {
		FVector temp1 = GetActorLocation();
		FVector temp2 = blaster->GetActorLocation();
		FVector Forward = temp2 - temp1;
		if (blaster->DoesHasShield && Forward.Length() <= 400) {
			Destroy();
		}
		if (Forward.Length() >= 250) {
			FVector Normalised = Forward / Forward.Length();
			SetActorLocation(GetActorLocation() + Normalised * speed);
		}
		else {
			AGameJamCharacter* GameCharacter =  Cast<AGameJamCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (GameCharacter) {
				//GameCharacter->LaunchCharacter(FVector(Forward.X*100, Forward.Y*100,10.f), false, false);
				AGameJamPlayerController* Contr = Cast<AGameJamPlayerController>(GetWorld()->GetFirstPlayerController());
				if (Contr) {
					Contr->ClientStartCameraShake(ShakeBase, 5, ECameraShakePlaySpace::CameraLocal);
				}
			}
			Destroy();
		}
	}
}

void AA_ChargeBase::SpawnNiag(FVector First, FVector Second)
{
	
	Spaw = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, First);
	if (Spaw) {
		Spaw->SetVectorParameter("beamstart", First);
		Spaw->SetVectorParameter("beamend", Second);
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this,&AA_ChargeBase::DestroyNiag,0.45f, false);
}

void AA_ChargeBase::DestroyNiag()
{
	if (Spaw) Spaw->DestroyComponent();
	Destroy();
}






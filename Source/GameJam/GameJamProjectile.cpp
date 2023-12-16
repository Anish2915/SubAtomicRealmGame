// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJamProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Charges/A_ChargeBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AGameJamProjectile::AGameJamProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGameJamProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	DamageCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphereComp"));
	DamageCollision->SetupAttachment(RootComponent);
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AGameJamProjectile::OnOverlap);
	DamageCollision->OnComponentEndOverlap.AddDynamic(this, &AGameJamProjectile::OnOverlapEnd);

	DamageCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	DamageCollision->CanCharacterStepUpOn = ECB_No;
	
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	//ParticleIndex = -1;
}

void AGameJamProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		II_ChargeInterface* ChargeInterface = Cast<II_ChargeInterface>(OtherActor);
		if (ChargeInterface) {
			if (DoesSlug) {
				DestroyBeforeDie();
			}
			else {
				ChargeInterface->apk(ParticleIndex, DoesSlug, SlugIndex, SlugParticle);
				Destroy();
				if (DestroySound)
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroySound, GetActorLocation(), 1.0f);
			}
		}
	}
	
	
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	//{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//Destroy();
	//}
}

void AGameJamProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* OA = Cast<AA_ChargeBase>(OtherActor))
    ChargeArray.AddUnique(OA);
}

void AGameJamProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	if (auto* OA = Cast<AA_ChargeBase>(OtherActor))
	ChargeArray.Remove(OA);
}

void AGameJamProjectile::DestroyBeforeDie()
{
	for (int i = 0; i < ChargeArray.Num(); i++) {
		II_ChargeInterface* ChargeInterface = Cast<II_ChargeInterface>(ChargeArray[i]);
		if (ChargeInterface) {
			ChargeInterface->SlugDestroy(SlugParticle,GetActorLocation());
		}

	}
	Destroy();
	if (DestroySound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroySound, GetActorLocation(), 1.0f);
}


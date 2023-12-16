// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameJamProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AGameJamProjectile : public AActor
{
	GENERATED_BODY()
public:

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* DamageCollision;
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AGameJamProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	int ParticleIndex;

	UPROPERTY(BlueprintReadWrite)
	bool DoesSlug;
	int SlugIndex;
	int SlugParticle;

	UPROPERTY(EditAnywhere)
	class USoundBase* DestroySound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara")
	class UNiagaraSystem* DestroyNiagara;

	TArray<class AA_ChargeBase*> ChargeArray;

	UFUNCTION(BlueprintCallable)
	void DestroyBeforeDie();
};


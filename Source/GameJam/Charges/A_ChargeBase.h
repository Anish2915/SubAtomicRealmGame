// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/I_ChargeInterface.h"
#include "A_ChargeBase.generated.h"

UCLASS()
class GAMEJAM_API AA_ChargeBase : public AActor , public II_ChargeInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_ChargeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* Sphere;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void apk(int particleIndex, bool DoesSlug, int SlugIndex, int SlugParticle) override {};
	virtual void GripInterface(FVector& vec) override {};
	virtual void SlugDestroy(int SlugParticle, FVector ProjectilePosition) {};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool anti = false;

	UPROPERTY(EditAnywhere)
	AA_ChargeBase* OppChargeRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Excited = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ClassToFind;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> ShakeBase;

	class ABlaster_CPP* blaster;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float speed=10;

	UPROPERTY(BlueprintReadWrite)
	AA_ChargeBase* Next;

	UPROPERTY(BlueprintReadWrite)
	AA_ChargeBase* Back;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	class UNiagaraSystem* HitParticles;

	void SpawnNiag(FVector First,FVector Second);
	void DestroyNiag();
	FTimerHandle TimerHandle;
	class UNiagaraComponent* Spaw;
};

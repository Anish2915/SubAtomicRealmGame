// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_WeaponComponent.h"
#include "Blaster_CPP.generated.h"

UCLASS()
class GAMEJAM_API ABlaster_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlaster_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTP_WeaponComponent* comp;
	void Set(UTP_WeaponComponent* compo);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool DoesHasShield = false;

	UFUNCTION(BlueprintImplementableEvent)
	void FireBP_B();

};

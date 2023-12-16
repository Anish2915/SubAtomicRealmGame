// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "GameJamCharacter.h"
#include "GameJamProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blaster_CPP.h"
#include "Charges/A_ChargeBase.h"
#include "GameJamPlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(1000.0f, 0.0f, 10.0f);
	ParticleIndex = -1;
	DoesSlug = false;
	SlugIndex = -1;
	SlugParticle = -1;
	
}


void UTP_WeaponComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("%d , %d , %d "),ParticleIndex,DoesSlug , SlugParticle );
	if (ParticleIndex == -1 && !DoesSlug) return;
	
	
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(FVector(100.0f, 0.0f, 10.0f));
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			// Spawn the projectile at the muzzle
			UE_LOG(LogTemp, Warning, TEXT("%d"), DoesSlug);
			if (DoesSlug) {
				
				if (SlugParticle == 5) {
					blaster->DoesHasShield = true;
					
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Projecting SLug"));
					AGameJamProjectile* Proj = World->SpawnActor<AGameJamProjectile>(SlugProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					if (Proj) {
						Proj->ParticleIndex = ParticleIndex;
						Proj->DoesSlug = DoesSlug;
						Proj->SlugIndex = SlugIndex;
						Proj->SlugParticle = SlugParticle;
						Proj->ProjectileMovement->InitialSpeed = 1000.f;
						Proj->ProjectileMovement->MaxSpeed = 1000.f;
						Proj->DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					}
					
				}
			}
			
			else {
				UE_LOG(LogTemp, Warning, TEXT("Projecting Simple"));

				AGameJamProjectile* Proj = World->SpawnActor<AGameJamProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				if (Proj) {
					Proj->ParticleIndex = ParticleIndex;
					Proj->DoesSlug = DoesSlug;
					Proj->SlugIndex = SlugIndex;
					Proj->SlugParticle = SlugParticle;
					Proj->DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				}
				
			}
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
	if (blaster) {
		blaster->FireBP_B();
	}
}

void UTP_WeaponComponent::Grip()
{
	FHitResult Hit;

	

	//PlayerController1 = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController1->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(FVector(100.0f, 0.0f, 10.0f));
	FVector TraceStart = SpawnLocation;
	FVector TraceEnd = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	if (Spaw) {
		Spaw->SetVectorParameter("beamstart", TraceStart);
		Spaw->SetVectorParameter("beamend", TraceEnd);
	}
	FCollisionQueryParams QueryParams;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel2, QueryParams);

	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0.05f, 0, 10.0f);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		II_ChargeInterface* ChargeInterface = Cast<II_ChargeInterface>(Hit.GetActor());
		if (ChargeInterface) {
			ChargeInterface->GripInterface(TraceEnd);
		}
		//Hit.GetActor()->SetActorLocation(TraceEnd);
	}
	
}

void UTP_WeaponComponent::GripCancled()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancled"));
	if (Spaw) Spaw->DestroyComponent();
}

void UTP_WeaponComponent::AttachWeapon(AGameJamCharacter* TargetCharacter)
{
	//APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	blaster = Cast<ABlaster_CPP>(GetOwner());
	blaster->Set(this);
	Character = TargetCharacter;

	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
			EnhancedInputComponent->BindAction(GripAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Grip);
			EnhancedInputComponent->BindAction(GripAction, ETriggerEvent::Started, this, &UTP_WeaponComponent::GripStarted);
			EnhancedInputComponent->BindAction(GripAction, ETriggerEvent::Completed, this, &UTP_WeaponComponent::GripCancled);
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}

void UTP_WeaponComponent::GripStarted()
{
	PlayerController1 = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController1->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(FVector(100.0f, 0.0f, 10.0f));
	FVector TraceStart = SpawnLocation;
	FVector TraceEnd = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	Spaw =  UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, TraceStart);
	//UNiagaraFunctionLibrary::SpawnSystemAttached(HitParticles, this, FName(TEXT("GripPoint")),TraceStart,FRotator(0,0,0),);
	if (Spaw) { 
		Spaw->SetVectorParameter("beamstart", TraceStart);
		Spaw->SetVectorParameter("beamend", TraceEnd); 
	}
}

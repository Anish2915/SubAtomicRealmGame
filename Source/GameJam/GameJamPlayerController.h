// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameJamPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class GAMEJAM_API AGameJamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

protected:
	virtual void BeginPlay() override;
public:

};

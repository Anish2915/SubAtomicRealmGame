// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "A_HUDcpp.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AA_HUDcpp : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	class AGameJamPlayerController* PC_ref;

	UPROPERTY(BlueprintReadWrite)
	class UBasicWidget* WidRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBasicWidget> SelectedWid;
};

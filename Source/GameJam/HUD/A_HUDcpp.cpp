// Fill out your copyright notice in the Description page of Project Settings.


#include "A_HUDcpp.h"
#include "../GameJamPlayerController.h"
#include "../Widgets/BasicWidget.h"
void AA_HUDcpp::BeginPlay()
{
	PC_ref = Cast<AGameJamPlayerController>(GetOwningPlayerController());
	if (PC_ref && SelectedWid) {
		WidRef = CreateWidget<UBasicWidget>(PC_ref,SelectedWid);
		WidRef->AddToViewport();
		WidRef->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV_LAB1_API AAHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
};

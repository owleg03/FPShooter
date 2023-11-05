// Fill out your copyright notice in the Description page of Project Settings.


#include "AHUD.h"

#include "Engine/Canvas.h"

void AAHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		const FVector2D CrossHairDrawPosition(
			Center.X - CrosshairTexture->GetSurfaceWidth() * 0.5f,
			Center.Y - CrosshairTexture->GetSurfaceHeight() * 0.5f
		);

		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}

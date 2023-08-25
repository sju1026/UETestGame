// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"
#include <Engine/Canvas.h>

void AFPSHUD::DrawHUD() {
	Super::DrawHUD();

	if (Crosshairtexture) {
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CrosshairDrawPosition(Center.X - (Crosshairtexture->GetSurfaceWidth() * 0.5f), Center.Y - (Crosshairtexture->GetSurfaceHeight() * 0.5f));

		FCanvasTileItem TileItem(CrosshairDrawPosition, Crosshairtexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}
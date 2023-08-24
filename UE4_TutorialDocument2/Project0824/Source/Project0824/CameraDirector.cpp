// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f) {

		FChangeCameraData NowCamera = Cameras[NowCameraIndex];
		
		TimeToNextCameraChange += NowCamera.TimeBetweenCameraChanges;

		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
		if (controller) {
			if ((controller->GetViewTarget() != NowCamera.Camera) && (NowCamera.Camera != nullptr)) {
				if (NowCamera.SmoothBlendTime <= 0.0f) {
					controller->SetViewTarget(NowCamera.Camera);
				}
				else {
					controller->SetViewTargetWithBlend(NowCamera.Camera, NowCamera.SmoothBlendTime);
				}
				
			}

			/*if ((controller->GetViewTarget() != CameraOne) && (CameraOne != nullptr)) {
				controller->SetViewTarget(CameraOne);
			}
			else if ((controller->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr)) {
				controller->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}*/
		}

		NowCameraIndex++;

		if (NowCameraIndex >= Cameras.Num()) {
			NowCameraIndex = 0;
		}
	}
}


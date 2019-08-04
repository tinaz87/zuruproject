// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnUser.generated.h"
UCLASS()
class ZURUPROJECT_API APawnUser : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnUser();
	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();

	void LeftClick();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mStaticSphere;
	UCameraComponent* mOurCamera;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
};

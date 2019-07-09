// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Box/Box.h"
#include "MyVertex.generated.h"

UCLASS()
class ZURUPROJECT_API AMyVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyVertex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CreateShape();
private:

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* mMesh;

	
	void AddTriangle(int32 V1, int32 V2, int32 V3);

private:
	Box* mBox;
};

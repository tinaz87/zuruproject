// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MyVertex.h"
#include "Box/Box.h"
#include "Cube.generated.h"

UCLASS()
class ZURUPROJECT_API ACube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* mMesh;

	void CreateTriangle();

	UFUNCTION(Category = Default)
		void OnClick(UPrimitiveComponent* pComponent, FKey iKey);

private:
	AMyVertex* mVertex;
	TArray<AMyVertex*> mVericesCubes;
	Box* mBox;

};

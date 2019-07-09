// Fill out your copyright notice in the Description page of Project Settings.

#include "MyVertex.h"

// Sets default values
AMyVertex::AMyVertex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->mMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Vertex"));
	RootComponent = this->mMesh;
	//this->SetRootComponent(this->mMesh);
	this->mMesh->bUseAsyncCooking = true;
	this->mBox = new Box(10, 10, 10);
	
}

// Called when the game starts or when spawned
void AMyVertex::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyVertex::CreateShape() {

	TArray<FLinearColor> VertexColors;
	VertexColors.Add(FLinearColor(0.f, 0.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.5f, 1.f, 0.5f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 1.f));

	this->mMesh->CreateMeshSection_LinearColor(0, this->mBox->mVerices, this->mBox->mTriangles, this->mBox->mNormals, TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);


}

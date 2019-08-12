// Fill out your copyright notice in the Description page of Project Settings.

#include "Cube.h"
#include "MessageDialog.h"

static float scaleX = 1;
// Sets default values
ACube::ACube() :mMesh(nullptr),mVertex(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->mMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("MyCUBE"));
	this->mMesh->bUseAsyncCooking = true;	
	
	//this->mMesh->SetupAttachment(RootComponent);
	this->SetRootComponent(RootComponent);

	this->mBox = new Box(50, 50, 50);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay\n"));
	Super::BeginPlay();
	this->CreateTriangle();
	scaleX = 1;

	/*FVector pLocation = this->GetActorLocation();
	FRotator pRotation = this->GetActorRotation();
	FString a = pLocation.ToString();
	FString b = pRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *a);
	UE_LOG(LogTemp, Warning, TEXT("ROTATION: %s"), *b);*/


}


float pTime = 0;
// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FRotator pRotation = this->GetActorRotation() + FRotator(0, 0, DeltaTime);
	this->SetActorRotation(pRotation);
	FRotator pRotation1 = this->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("ROTATION: %s"), *pRotation1.ToString());*/
}
bool ACube::IsNearVertices(const FVector& iWorldHitPosition) {

	for (auto& pVertice : this->mBox->mTopFaceVertices) {

		FVector pLocalPos = iWorldHitPosition - this->GetActorLocation();
		float a = FVector::Distance(pVertice, pLocalPos);
		if (a < 10) {
			
			
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s (world: %s), Vertex: %s, Distance: %f"),*pLocalPos.ToString(),*iWorldHitPosition.ToString(),
				*pVertice.ToString(),a);
			return true;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("FAR --- Hit: %s (world: %s), Vertex: %s, Distance: %f"), *pLocalPos.ToString(), *iWorldHitPosition.ToString(),
				*pVertice.ToString(), a);
		}
	}

	return false;
}

void ACube::OnClick(UPrimitiveComponent* pComponent, FKey iKey)
{
	UE_LOG(LogTemp, Warning, TEXT("\n-----------------------------\n"));
	//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Clicked")));
	
	//UProceduralMeshComponent* pMesh = NewObject<UProceduralMeshComponent>(this, TEXT("MuVertices"));
	//pMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules

	//(
	//	EAttachmentRule::KeepRelative,
	//	false
	//),"MMM");
	//build_cube(pMesh, 180);

	////FTransform a(FRotator(0,0,0),, FVector(1, 1, 1));
	//pMesh->SetRelativeLocation(FVector(200, 200, 150));

	/**/


	/*float pXPoint = (this->mLengthX) / 2;
	float pYPoint = (this->mLengthY) / 2;
	float pZPoint = (this->mLengthZ) / 2;

	*/
	if (0) {
		scaleX += 0.5;


		FVector pLastPosition = this->mMesh->RelativeLocation;
		FVector pPrevScale = this->mMesh->RelativeScale3D;
		auto pVertexBuffer = this->mMesh->GetProcMeshSection(0)->ProcVertexBuffer;
		auto pPoint = pVertexBuffer[0].Position;
		auto pLastPositionPoint0 = pPrevScale * pPoint;
		UE_LOG(LogTemp, Warning, TEXT("\nPRIMA\n-LastPosition: %s,\n-LastPositionPoint0: %s (prev-scale: %s,pos: %s)\n"), *pLastPosition.ToString(), *pLastPositionPoint0.ToString(), *pPrevScale.ToString(), *pPoint.ToString());



		FVector pScale = FVector(scaleX, 1, 1);
		auto pNewPoint = pScale * pPoint;

		auto pDistance = FVector::Distance(pNewPoint, pLastPositionPoint0);
		auto pNewPosition = pNewPoint - pLastPositionPoint0;
		pNewPosition.X += pLastPosition.X;
		pNewPosition.Y = pLastPosition.Y;
		pNewPosition.Z = pLastPosition.Z;

		this->mMesh->SetRelativeScale3D(pScale);
		//this->mMesh->SetWorldScale3D(pScale);

		UE_LOG(LogTemp, Warning, TEXT("\nDOPO\n-After: %s (scale: %s),\n-New Position: %s\n\n"), *pNewPoint.ToString(), *pScale.ToString(), *pNewPosition.ToString());

		this->mMesh->SetRelativeLocation(pNewPosition);
		UE_LOG(LogTemp, Warning, TEXT("\n-----------------------------\n"));

		if (!this->mVertex)
		{
			UE_LOG(LogTemp, Warning, TEXT("\nCREO VERTEX"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;




			this->mVertex = (AMyVertex*)GetWorld()->SpawnActor<AMyVertex>(AMyVertex::StaticClass(), FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);


			mVertex->CreateShape();



		}
		FVector pMyPOsition = this->GetActorLocation() + pNewPoint;
		UE_LOG(LogTemp, Warning, TEXT("\nPosizione vertice: %s\n\n"), *pMyPOsition.ToString());
		mVertex->SetActorRelativeLocation(pMyPOsition);

	}

}


void ACube::CreateTriangle() {

	//SetActorRelativeLocation(FVector(200, 200, 200));
	/*this->mMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules
	(
		EAttachmentRule::KeepRelative,
		false
	));*/

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

	this->mMesh->OnClicked.AddDynamic(this, &ACube::OnClick);

	//mMesh->SetRelativeLocation(FVector(10, 10, 10));

	//UProceduralMeshComponent* pMesh = NewObject<UProceduralMeshComponent>(this,TEXT("MuVert12ices"));
	//pMesh->SetupAttachment(this->RootComponent);
	//build_cube(pMesh, 80);

	this->SetActorLocation(FVector(0, 0, 50));
}
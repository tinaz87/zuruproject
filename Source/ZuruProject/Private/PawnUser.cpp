// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnUser.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

#include "ConstructorHelpers.h"

#include "Cube.h"
// Sets default values
APawnUser::APawnUser()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Take control of the default playe
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	mStaticSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		mStaticSphere->SetStaticMesh(SphereVisualAsset.Object);
		mStaticSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		mStaticSphere->SetWorldScale3D(FVector(0.8f));
	}
		
	// Create a camera and attach to our spring arm
	mOurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	mOurCamera->SetupAttachment(RootComponent);
	mStaticSphere->SetupAttachment(RootComponent);
	
	
}

void APawnUser::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnUser::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnUser::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APawnUser::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APawnUser::ZoomIn()
{
	bZoomingIn = true;
}

void APawnUser::ZoomOut()
{
	bZoomingIn = false;
}

// Called when the game starts or when spawned
void APawnUser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		/*FRotator NewRotation = mStaticSphere->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -90.0f, 90.0f);
		mStaticSphere->SetWorldRotation(NewRotation);*/

		FRotator NewRotation = GetActorRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -90.0f, 90.0f);
		SetActorRotation(NewRotation);

	}

	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 100 units per second
			MovementInput = MovementInput.GetSafeNormal() * 500.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += mOurCamera->GetForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += mOurCamera->GetRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}

	//
	//FHitResult OutHit;
	//FVector Start = this->GetActorLocation();// ->GetComponentLocation();

	//// alternatively you can get the camera location
	//// FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	//FVector ForwardVector = mOurCamera->GetForwardVector();
	//FVector End = ((ForwardVector * 1000.f) + Start);
	//FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	//if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	//{
	//	if (OutHit.bBlockingHit)
	//	{
	//		if (GEngine) {

	//			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
	//			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
	//			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

	//		}
	//	}
	//}
	
}
void  APawnUser::LeftClick() {
	// Get the camera transform.
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	UE_LOG(LogTemp, Warning, TEXT("CLICK"));
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		FHitResult TraceResult(ForceInit);
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, TraceResult);
		FString TraceString;
		if (TraceResult.GetActor() != nullptr)
		{
			TraceString += FString::Printf(TEXT("Trace Actor %s."), *TraceResult.GetActor()->GetName());
			TraceString += FString::Printf(TEXT("HIT %s."), *TraceResult.ImpactPoint.ToString());

			ACube* pCube = Cast<ACube>(TraceResult.GetActor());
			if (pCube)
			{				
				pCube->IsNearVertices(TraceResult.ImpactPoint);
			}
		}
		if (TraceResult.GetComponent() != nullptr)
		{
			TraceString += FString::Printf(TEXT("Trace Comp %s."), *TraceResult.GetComponent()->GetName());
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *TraceString));
	}
	////UWorld* World = GetWorld();
	////if (World)
	////{
	////	UE_LOG(LogTemp, Warning, TEXT("WORLD"));
	////}
	//float LineTraceDistance = 600.f;
	//FVector Start;
	//FVector End;
	//// get the camera view
	//FVector CameraLoc = mOurCamera->GetComponentLocation();
	//FRotator CameraRot = mOurCamera->GetComponentRotation();
	//Start = CameraLoc;
	//End = CameraLoc + (CameraRot.Vector() * LineTraceDistance);

	//// additional trace parameters
	//FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
	//TraceParams.bTraceComplex = true;
	//TraceParams.bReturnPhysicalMaterial = true;
	////Re-initialize hit info
	//FHitResult HitDetails = FHitResult(ForceInit);
	//bool bIsHit = GetWorld()->LineTraceSingleByChannel(
	//	HitDetails,      // FHitResult object that will be populated with hit info
	//	Start,      // starting position
	//	End,        // end position
	//	ECC_GameTraceChannel3,  // collision channel - 3rd custom one
	//	TraceParams      // additional trace settings
	//);
	//if (bIsHit)
	//{
	//	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);
	//	// something was hit
	//	UE_LOG(LogTemp, Warning, TEXT("We hit something") );
	//	UE_LOG(LogTemp, Warning, TEXT("%s"),*HitDetails.Actor->GetName());
	//	UE_LOG(LogTemp, Warning, TEXT("distance: %s"),*FString::SanitizeFloat(HitDetails.Distance));
	//	DrawDebugBox(GetWorld(), HitDetails.ImpactPoint, FVector(2.f, 2.f, 2.f), FColor::Blue, false, 5.f, ECC_WorldStatic, 1.f);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("miss"));
	//	DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 5.f, ECC_WorldStatic, 1.f);
	//	// we missed
	//}

}


// Called to bind functionality to input
void APawnUser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//Hook up every-frame handling for our four axes
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnUser::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnUser::MoveRight);
	PlayerInputComponent->BindAxis("Pitch", this, &APawnUser::PitchCamera);
	PlayerInputComponent->BindAxis("Yaw", this, &APawnUser::YawCamera);


	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APawnUser::LeftClick);
}


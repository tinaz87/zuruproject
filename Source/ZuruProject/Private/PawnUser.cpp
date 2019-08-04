// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnUser.h"

// Sets default values
APawnUser::APawnUser()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	mStaticSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	mStaticSphere->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		mStaticSphere->SetStaticMesh(SphereVisualAsset.Object);
		mStaticSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		mStaticSphere->SetWorldScale3D(FVector(0.8f));
	}
		
	// Create a camera and attach to our spring arm
	mOurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	mOurCamera->SetupAttachment(mStaticSphere);

	
	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

//Input functions
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
		FRotator NewRotation = mStaticSphere->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -90.0f, 90.0f);
		mStaticSphere->SetWorldRotation(NewRotation);
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

	
}
void  APawnUser::LeftClick() {
	// Get the camera transform.
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	UE_LOG(LogTemp, Warning, TEXT("CLICK"));
	

	UWorld* World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("WORLD"));
	}
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


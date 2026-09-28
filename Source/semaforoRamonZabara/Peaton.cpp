// Fill out your copyright notice in the Description page of Project Settings.


#include "Peaton.h"

// Sets default values
APeaton::APeaton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a child component of mesh and sets the root
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// Creates a child component of box collider and sets the root
	BoxColision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColision"));
	RootComponent = BoxColision;
}

// Called when the game starts or when spawned
void APeaton::BeginPlay()
{
	Super::BeginPlay();
	
	if (Mesh)
	{
		//Mesh->SetRelativeTransform(Transform);
	}

	/*if (Mesh && Material)
	{
		Mesh->SetMaterial(0, Material);
	}*/

	if (PatrolPoints.Num() > 0)
	{
		FVector FirstLocation = PatrolPoints[0]->GetActorLocation();
		SetActorLocation(FirstLocation);
	}
}

// Called every frame
void APeaton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canMove)
		MoveToTarget(DeltaTime);
}

void APeaton::MoveToTarget(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = PatrolPoints[targetPointIndex]->GetActorLocation();
	
	// Dirección normalizada hacia el objetivo
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

	// Movimiento en línea recta
	FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	// Si está lo suficientemente cerca, detenerse
	float Distance = FVector::Dist(NewLocation, TargetLocation);
	if (Distance < 10.f)
	{
		targetPointIndex ++;

		if (targetPointIndex >= PatrolPoints.Num())
		{
			targetPointIndex = 0;
		}
	}
}

void APeaton::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	canMove = false;
}

void APeaton::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	canMove = true;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLight.h"

// Sets default values
ATrafficLight::ATrafficLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates the light component and attach it to the root
    LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
    RootComponent = LightComponent;

    // Creates the sphere collision component and attach it to the root
	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	RootComponent = SphereCollisionComponent;
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

    SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLight::OverlapBegin);
    SphereCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATrafficLight::OverlapEnd);

    LightComponent->SetLightColor(FLinearColor::Green);
}

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrafficLight::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    // Intentamos hacer un cast de AActor* a AMiObjeto*
    APeaton* Actor = Cast<APeaton>(OtherActor);

    if (Actor)
    {
        // El cast fue correcto
        Peatons.Add(Actor);

        ATrafficLight::ControlTraffic();
        ATrafficLight::ChangeTrafficLightColor();
    }
}

void ATrafficLight::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    APeaton* Actor = Cast<APeaton>(OtherActor);

    if (Actor)
    {
        // El cast fue correcto
        Peatons.Remove(Actor);

        ATrafficLight::ControlTraffic();
        ATrafficLight::ChangeTrafficLightColor();
    }
}

void ATrafficLight::ControlTraffic()
{
    for (int i = 0; i < Peatons.Num(); i++)
    {
        if (i == 0)
            Peatons[i]->canMove = true;

        else
            Peatons[i]->canMove = false;
    }
}

void ATrafficLight::ChangeTrafficLightColor()
{
    if (Peatons.Num() == 0)
        LightComponent->SetLightColor(FLinearColor::Green);

    else
        LightComponent->SetLightColor(FLinearColor::Red);
}
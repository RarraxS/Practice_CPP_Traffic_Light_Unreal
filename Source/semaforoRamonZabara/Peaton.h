// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Components/BoxComponent.h"
#include "Peaton.generated.h"

UCLASS()
class SEMAFORORAMONZABARA_API APeaton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeaton();

	// El transform
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
		FTransform Transform;*/

	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	// Material
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UMaterialInterface* Material;*/

	// Componente de colisión caja, visible en el editor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Colision")
		UBoxComponent* BoxColision;

	// Array de puntos de patrulla
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<ATargetPoint*> PatrolPoints;

	// Velocidad del peaton
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float MoveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool canMove = true;

	int targetPointIndex = 0;

	// Función de movimiento
	void MoveToTarget(float DeltaTime);
};

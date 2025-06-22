// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMeshComponent.h"

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldActor.generated.h"

UCLASS()
class AWorldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldActor();

	
	UPROPERTY(EditAnywhere)
	int XVertexCount= 20;

	UPROPERTY(EditAnywhere)
	int YVertexCount = 20;

	UPROPERTY(EditAnywhere)
	int CellCount = 100;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateTerrain();

	UPROPERTY()
	UProceduralMeshComponent* TerrainMesh;

	UPROPERTY()
	TArray<FVector> TerrainVertices;

	UPROPERTY()
	TArray<int> TerrainTriangles;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActor.h"

// Sets default values
AWorldActor::AWorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TerrainMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TerrainMesh"));
	TerrainMesh->SetupAttachment(RootComponent);
	TerrainMesh->RegisterComponent();
}

// Called when the game starts or when spawned
void AWorldActor::BeginPlay()
{
	Super::BeginPlay();

	GenerateTerrain();
}

// Called every frame
void AWorldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldActor::GenerateTerrain()
{
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	// Generate vertices
	for (int y = 0; y < YVertexCount; y++)
	{
		for (int x = 0; x < XVertexCount; x++)
		{
			FVector Vertex = FVector(CellCount * x, CellCount * y, 0.0f);
			TerrainVertices.Add(Vertex);
			DrawDebugBox(GetWorld(), Vertex, FVector(2.0, 2.0f, 2.0f), FColor::Red, true);

			Normals.Add(FVector(0, 0, 1)); // Up
			UV0.Add(FVector2D((float)x / XVertexCount, (float)y / YVertexCount));
			VertexColors.Add(FColor::White);
			Tangents.Add(FProcMeshTangent(1, 0, 0));
		}
	}

	// Generate triangles
	for (int y = 0; y < YVertexCount - 1; y++)
	{
		for (int x = 0; x < XVertexCount - 1; x++)
		{
			int i0 = (y * XVertexCount) + x;
			int i1 = i0 + 1;
			int i2 = i0 + XVertexCount;
			int i3 = i2 + 1;

			// First triangle
			TerrainTriangles.Add(i0);
			TerrainTriangles.Add(i2);
			TerrainTriangles.Add(i1);

			// Second triangle
			TerrainTriangles.Add(i1);
			TerrainTriangles.Add(i2);
			TerrainTriangles.Add(i3);
		}
	}
	// Create mesh
	check(TerrainMesh != nullptr);
	TerrainMesh->CreateMeshSection(0, TerrainVertices, TerrainTriangles, Normals, UV0, VertexColors, Tangents, true);
}


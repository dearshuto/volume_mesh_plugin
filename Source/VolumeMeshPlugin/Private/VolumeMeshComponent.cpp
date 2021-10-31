// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeMeshComponent.h"
#include <mc_Ffi.h>



UVolumeMeshComponent::UVolumeMeshComponent(const FObjectInitializer& objectInitializer)
    : Super(objectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PostPhysics;

    m_pVolumeDataInstance = create_volume_data_16();
    m_pMeshDataInstance = create_mesh_data();
}

UVolumeMeshComponent::~UVolumeMeshComponent()
{
    if (m_pMeshDataInstance != nullptr)
    {
        destroy_mesh_data(m_pMeshDataInstance);
    }

    if (m_pVolumeDataInstance != nullptr)
    {
        destroy_volume_data_16(m_pVolumeDataInstance);
    }
}

void UVolumeMeshComponent::InitializeComponent()
{
    Super::InitializeComponent();

    PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UVolumeMeshComponent::TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction* pThisFunction)
{
    if (GetNumSections() == 0)
    {
        // 頂点群
        TArray<FVector> vertices;
        // インデックス群
        TArray<int32> indices;
        // 法線群（今回は空っぽのまま）
        TArray<FVector> normals;
        // テクスチャー座標群
        TArray<FVector2D> texcoords0;
        // 頂点カラー群（今回は空っぽのまま）
        TArray<FLinearColor> vertex_colors;
        // 接線群（今回は空っぽのまま）
        TArray<FProcMeshTangent> tangents;

        build_16_with_marching_cubes(m_pMeshDataInstance, m_pVolumeDataInstance, Threshold);

        vertices.Emplace(FVector{0.0, 0.0, 0.0});
        vertices.Emplace(FVector{60.0, 0.0, 0.0});
        vertices.Emplace(FVector{0.0, 60.0, 0.0});

        normals.Emplace(FVector{0.0, 0.0, 1.0});
        normals.Emplace(FVector{0.0, 0.0, 1.0});
        normals.Emplace(FVector{0.0, 0.0, 1.0});

        indices.Emplace(0);
        indices.Emplace(2);
        indices.Emplace(1);

        // for (auto i = 0; i < get_vertex_count(m_pInstance); ++i)
        // {
        //     const auto actualIndex = i;//get_vertex_count(m_pInstance) - i - 1;
        //     FVector position;
        //     get_position(m_pInstance, &position.X, &position.Y, &position.Z, actualIndex);
        //     vertices.Emplace(position);

        //     FVector normal;
        //     get_normal(m_pInstance, &normal.X, &normal.Y, &normal.Z, actualIndex);
        //     normals.Emplace(normal);
        // }

        // for (auto i = 0; i < get_index_count(m_pInstance); ++i)
        // {
        //     const auto index = get_index( m_pInstance ,i);
        //     indices.Emplace(index);
        // }
        CreateMeshSection_LinearColor(0, vertices, indices, normals, texcoords0, vertex_colors, tangents, true);
    }
}
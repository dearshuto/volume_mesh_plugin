// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "VolumeMeshComponent.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup=Rendering)
class VOLUMEMESHPLUGIN_API UVolumeMeshComponent : public UProceduralMeshComponent
{
	GENERATED_UCLASS_BODY()
	
	
public:
	~UVolumeMeshComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	class UMaterialInterface* pMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	float Threshold;
	
private:
	virtual void InitializeComponent() override;

	virtual void TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction* pThisFunction) override;

	virtual class UMaterialInterface* GetMaterial(int32 ElementIndex) const override
	{
		return pMaterial;
	}

	virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* Material) override
	{
		pMaterial = Material;
	}

	void SetupMesh();

private:
	void* m_pVolumeDataInstance = nullptr;
	void* m_pMeshDataInstance = nullptr;
};

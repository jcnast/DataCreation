
#pragma once

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/StaticModelData.h"
#include "Data/Rendering/Headers/TextureData.h"

namespace Data
{
	/*
		This file has been auto-generated

		DO NOT CHANGE
	*/
	struct Assets
	{
		struct StaticModels
		{
			const AssetName<Rendering::StaticModelData> MI_0 = AssetName<Rendering::StaticModelData>(3880192898);
		};
		const StaticModels smdl;
		struct AnimatedModels
		{
			const AssetName<Rendering::AnimatedModelData> Woman_0 = AssetName<Rendering::AnimatedModelData>(1603614241);
		};
		const AnimatedModels amdl;
		struct StaticMeshes
		{
			const AssetName<Rendering::StaticMeshData> MI_0 = AssetName<Rendering::StaticMeshData>(1740916818);
		};
		const StaticMeshes msh;
		struct AnimatedMeshes
		{
			const AssetName<Rendering::AnimatedMeshData> Woman_0 = AssetName<Rendering::AnimatedMeshData>(3593970672);
		};
		const AnimatedMeshes msh;
		struct Materials
		{
			const AssetName<Rendering::MaterialData> MI_0 = AssetName<Rendering::MaterialData>(1740916818);
			const AssetName<Rendering::MaterialData> Woman_0 = AssetName<Rendering::MaterialData>(3593970672);
		};
		const Materials mat;
		struct Skeletons
		{
			const AssetName<Rendering::SkeletonData> Woman_0 = AssetName<Rendering::SkeletonData>(3593970672);
		};
		const Skeletons skl;
		struct SkeletonAnimations
		{
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Death = AssetName<Rendering::SkeletonAnimationData>(4259411171);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Idle = AssetName<Rendering::SkeletonAnimationData>(4140853032);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Jump = AssetName<Rendering::SkeletonAnimationData>(2420364265);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Jump2 = AssetName<Rendering::SkeletonAnimationData>(2348057118);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_PickUp = AssetName<Rendering::SkeletonAnimationData>(2634831132);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Punch = AssetName<Rendering::SkeletonAnimationData>(2816760887);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Running = AssetName<Rendering::SkeletonAnimationData>(127888874);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_SitIdle = AssetName<Rendering::SkeletonAnimationData>(2289128976);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Sitting = AssetName<Rendering::SkeletonAnimationData>(437013649);
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Walking = AssetName<Rendering::SkeletonAnimationData>(460649925);
		};
		const SkeletonAnimations sanim;

	};
	const Assets Ast;
	}

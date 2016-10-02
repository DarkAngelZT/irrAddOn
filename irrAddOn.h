// Copyright (C) 2012 Neo
// This file is part of the Neo's game.
// Free to distribute and use.
//irrAddOn 的dll总输出函数文件
#ifndef __IRR_ADD_ON_H_INCLUDED__
#define __IRR_ADD_ON_H_INCLUDED__
#include "CSceneNodeAnimatorSprite.h"
#include "ParticleAffactor.h"

#ifdef _WINDOWS
#define IRR_ADDON_API __declspec(dllexport)
#endif

#ifdef _LINUX
#define IRR_ADDON_API
#endif

namespace irr
{
	namespace scene
	{
		IRR_ADDON_API ISceneNodeAnimator* createSpriteAnimator(video::ITexture*texture, 
			const core::array<core::vector2df>&translations,
			core::vector2df& scale,
			s32 timePerFrame, bool loop,ITimer*timer);
		IRR_ADDON_API IParticleSphereExplosionEmitter*CreateExplosionSphereEmitter(
			const core::vector3df& center, f32 radius,
			const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
			u32 minParticlesPerSecond = 5,
			u32 maxParticlesPerSecond = 10,
			const video::SColor& minStartColor = video::SColor(255,0,0,0),
			const video::SColor& maxStartColor = video::SColor(255,255,255,255),
			u32 lifeTimeMin=2000, u32 lifeTimeMax=4000,
			s32 maxAngleDegrees=0,
			const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
			const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f),
			const u32& maxEmit=100);
		IRR_ADDON_API IParticleColorAffectorQ*CreateColourAffactorQ(const irr::video::SColor& targetColor0, const irr::video::SColor& targetColor1);

	} // end namespace scene
} // end namespace irr
#endif

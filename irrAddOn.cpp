// Copyright (C) 2012 Neo
// This file is part of the Neo's game.
// Free to distribute and use.
//irrAddOn 的dll总输出函数文件的实现文件
#include "irrAddOn.h"

namespace irr
{
	namespace scene
	{
		ISceneNodeAnimator* createSpriteAnimator(video::ITexture* texture,
			const core::array<core::vector2df>&translations,
			core::vector2df& scale,
			s32 timePerFrame, bool loop,ITimer*timer)
		{
			ISceneNodeAnimator* anim = new CSceneNodeAnimatorSprite(texture,translations,scale,
				timePerFrame, loop, timer->getTime());

			return anim;
		}
		IParticleSphereExplosionEmitter*CreateExplosionSphereEmitter(
			const core::vector3df& center, f32 radius, const core::vector3df& direction,
			u32 minParticlesPerSecond, u32 maxParticlesPerSecond,
			const video::SColor& minStartColor, const video::SColor& maxStartColor,
			u32 lifeTimeMin, u32 lifeTimeMax,
			s32 maxAngleDegrees, const core::dimension2df& minStartSize,
			const core::dimension2df& maxStartSize,
			const u32& maxEmit)
		{
			return new IParticleSphereExplosionEmitter(center, radius, direction,
				minParticlesPerSecond, maxParticlesPerSecond,
				minStartColor, maxStartColor,
				lifeTimeMin, lifeTimeMax, maxAngleDegrees,
				minStartSize, maxStartSize,
				maxEmit);
		}

		IRR_ADDON_API IParticleColorAffectorQ*CreateColourAffactorQ( const irr::video::SColor& targetColor0, const irr::video::SColor& targetColor1 )
		{
			return new IParticleColorAffectorQ(targetColor0,targetColor1);
		}

	} // end namespace scene
} // end namespace irr

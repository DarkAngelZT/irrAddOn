#include "ParticleAffactor.h"

namespace irr
{
	namespace scene
	{
		s32 IParticleSphereExplosionEmitter::emitt( u32 now, u32 timeSinceLastCall, SParticle*& outArray )
		{
			if (Emitted<=_max_emit)
			{
				u32 em=emitt_standard(now,timeSinceLastCall,outArray);
				Emitted+=em;
				return em;
			}
			return 0;
		}
		//! constructor
		IParticleSphereExplosionEmitter::IParticleSphereExplosionEmitter(
			const core::vector3df& center, f32 radius,
			const core::vector3df& direction, u32 minParticlesPerSecond,
			u32 maxParticlesPerSecond, const video::SColor& minStartColor,
			const video::SColor& maxStartColor, u32 lifeTimeMin, u32 lifeTimeMax,
			s32 maxAngleDegrees,
			const core::dimension2df& minStartSize,
			const core::dimension2df& maxStartSize,
			const u32& maxEmit)
			:Center(center), Radius(radius), Direction(direction),
			MinStartSize(minStartSize), MaxStartSize(maxStartSize),
			MinParticlesPerSecond(minParticlesPerSecond),
			MaxParticlesPerSecond(maxParticlesPerSecond),
			MinStartColor(minStartColor), MaxStartColor(maxStartColor),
			MinLifeTime(lifeTimeMin), MaxLifeTime(lifeTimeMax),
			Time(0), Emitted(0), MaxAngleDegrees(maxAngleDegrees),
			_max_emit(maxEmit)
		{
#ifdef _DEBUG
			setDebugName("CParticleSphereExplosionEmitter");
#endif
		}
		//标准粒子释放过程，搬运自内核
		irr::u32 IParticleSphereExplosionEmitter::emitt_standard(u32 now, u32 timeSinceLastCall, SParticle*& outArray)
		{
			Time += timeSinceLastCall;

			const u32 pps = (MaxParticlesPerSecond - MinParticlesPerSecond);
			const f32 perSecond = pps ? ((f32)MinParticlesPerSecond + RandGen->frand() * pps) : MinParticlesPerSecond;
			const f32 everyWhatMillisecond = 1000.0f / perSecond;

			if(Time > everyWhatMillisecond)
			{
				Particles.set_used(0);
				u32 amount = (u32)((Time / everyWhatMillisecond) + 0.5f);
				Time = 0;
				SParticle p;

				if(amount > MaxParticlesPerSecond*2)
					amount = MaxParticlesPerSecond * 2;

				for(u32 i=0; i<amount; ++i)
				{
					// Random distance from center
					const f32 distance = RandGen->frand() * Radius;

					// Random direction from center
					p.pos.set(Center + distance);
					p.pos.rotateXYBy(RandGen->frand() * 360.f, Center );
					p.pos.rotateYZBy(RandGen->frand() * 360.f, Center );
					p.pos.rotateXZBy(RandGen->frand() * 360.f, Center );

					p.startTime = now;
					p.vector = Direction;

					if(MaxAngleDegrees)
					{
						core::vector3df tgt = Direction;
						tgt.rotateXYBy(RandGen->frand() * MaxAngleDegrees);
						tgt.rotateYZBy(RandGen->frand() * MaxAngleDegrees);
						tgt.rotateXZBy(RandGen->frand() * MaxAngleDegrees);
						p.vector = tgt;
					}

					p.endTime = now + MinLifeTime;
					if (MaxLifeTime != MinLifeTime)
						p.endTime += RandGen->rand() % (MaxLifeTime - MinLifeTime);

					if (MinStartColor==MaxStartColor)
						p.color=MinStartColor;
					else
						p.color = MinStartColor.getInterpolated(MaxStartColor, RandGen->frand());

					p.startColor = p.color;
					p.startVector = p.vector;

					if (MinStartSize==MaxStartSize)
						p.startSize = MinStartSize;
					else
						p.startSize = MinStartSize.getInterpolated(MaxStartSize, RandGen->frand());
					p.size = p.startSize;

					Particles.push_back(p);
				}

				outArray = Particles.pointer();

				return Particles.size();
			}

			return 0;
		}

		void IParticleSphereExplosionEmitter::Configure( IrrlichtDevice*device )
		{
			RandGen=device->getRandomizer();
		}



	} // end namespace scene
} // end namespace irr

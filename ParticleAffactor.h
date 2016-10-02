// Copyright (C) 2012 Neo
// This file is part of the Neo's game.
// Free to distribute and use.
//粒子系统特效器
#ifndef __PARTICLE_AFFACTOR_H_INCLUDED__
#define __PARTICLE_AFFACTOR_H_INCLUDED__
#include<irrlicht.h>

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
		//用法：
		//create
		//Configure
		class IParticleSphereExplosionEmitter:public IParticleEmitter
		{
		protected:
			u32 _max_emit;
			u32 emitt_standard(u32 now, u32 timeSinceLastCall, SParticle*& outArray);
			IRandomizer*RandGen;
		public:
			//返回已发射的粒子数量
			virtual s32 emitt(u32 now, u32 timeSinceLastCall, SParticle*& outArray);
			irr::u32 GetEmittedAmount() const { return Emitted; }
			void SetEmittedAmount(irr::u32 val) { Emitted = val; }
			//! constructor
			IParticleSphereExplosionEmitter(
				const core::vector3df& center, f32 radius,
				const core::vector3df& direction = core::vector3df(0.0f,0.03f,0.0f),
				u32 minParticlesPerSecond = 20,
				u32 maxParticlesPerSecond = 40,
				const video::SColor& minStartColor = video::SColor(255,0,0,0),
				const video::SColor& maxStartColor = video::SColor(255,255,255,255),
				u32 lifeTimeMin=2000,
				u32 lifeTimeMax=4000,
				s32 maxAngleDegrees=0,
				const core::dimension2df& minStartSize = core::dimension2df(5.0f,5.0f),
				const core::dimension2df& maxStartSize = core::dimension2df(5.0f,5.0f),
				const u32& maxEmit=100);

			//这个函数是被逼无奈搞的，因为irr没有将os类导出来
			IRR_ADDON_API void Configure(IrrlichtDevice*device);
			//重载函数,从内核搬运至此（照抄的）
			//! Set direction the emitter emits particles
			virtual void setDirection( const core::vector3df& newDirection ) { Direction = newDirection; }

			//! Set minimum number of particles per second.
			virtual void setMinParticlesPerSecond( u32 minPPS ) { MinParticlesPerSecond = minPPS; }

			//! Set maximum number of particles per second.
			virtual void setMaxParticlesPerSecond( u32 maxPPS ) { MaxParticlesPerSecond = maxPPS; }

			//! Set minimum start color
			virtual void setMinStartColor( const video::SColor& color ) { MinStartColor = color; }

			//! Set maximum start color
			virtual void setMaxStartColor( const video::SColor& color ) { MaxStartColor = color; }

			//! Set the maximum starting size for particles
			virtual void setMaxStartSize( const core::dimension2df& size ) { MaxStartSize = size; }

			//! Set the minimum starting size for particles
			virtual void setMinStartSize( const core::dimension2df& size ) { MinStartSize = size; }

			//! Set the minimum particle life-time in milliseconds
			virtual void setMinLifeTime( u32 lifeTimeMin ) { MinLifeTime = lifeTimeMin; }

			//! Set the maximum particle life-time in milliseconds
			virtual void setMaxLifeTime( u32 lifeTimeMax ) { MaxLifeTime = lifeTimeMax; }

			//!	Set maximal random derivation from the direction
			virtual void setMaxAngleDegrees( s32 maxAngleDegrees ) { MaxAngleDegrees = maxAngleDegrees; }

			//! Set the center of the sphere for particle emissions
			virtual void setCenter( const core::vector3df& center ) { Center = center; }

			//! Set the radius of the sphere for particle emissions
			virtual void setRadius( f32 radius ) { Radius = radius; }

			//! Gets direction the emitter emits particles
			virtual const core::vector3df& getDirection() const { return Direction; }

			//! Get minimum number of particles per second.
			virtual u32 getMinParticlesPerSecond() const { return MinParticlesPerSecond; }

			//! Get maximum number of particles per second.
			virtual u32 getMaxParticlesPerSecond() const { return MaxParticlesPerSecond; }

			//! Get minimum start color
			virtual const video::SColor& getMinStartColor() const { return MinStartColor; }

			//! Get maximum start color
			virtual const video::SColor& getMaxStartColor() const { return MaxStartColor; }

			//! Gets the maximum starting size for particles
			virtual const core::dimension2df& getMaxStartSize() const { return MaxStartSize; }

			//! Gets the minimum starting size for particles
			virtual const core::dimension2df& getMinStartSize() const { return MinStartSize; }

			//! Get the minimum particle life-time in milliseconds
			virtual u32 getMinLifeTime() const { return MinLifeTime; }

			//! Get the maximum particle life-time in milliseconds
			virtual u32 getMaxLifeTime() const { return MaxLifeTime; }

			//!	Get maximal random derivation from the direction
			virtual s32 getMaxAngleDegrees() const { return MaxAngleDegrees; }

			//! Get the center of the sphere for particle emissions
			virtual const core::vector3df& getCenter() const { return Center; }

			//! Get the radius of the sphere for particle emissions
			virtual f32 getRadius() const { return Radius; }
		private:

			core::array<SParticle> Particles;

			core::vector3df	Center;
			f32 Radius;
			core::vector3df Direction;

			core::dimension2df MinStartSize, MaxStartSize;
			u32 MinParticlesPerSecond, MaxParticlesPerSecond;
			video::SColor MinStartColor, MaxStartColor;
			u32 MinLifeTime, MaxLifeTime;

			u32 Time;
			u32 Emitted;
			s32 MaxAngleDegrees;
		};
		class IParticleColorAffectorQ : public IParticleAffector
		{
		public:
			IParticleColorAffectorQ(const irr::video::SColor& targetColor0, const irr::video::SColor& targetColor1)
			{
				Target0 = targetColor0;
				Target1 = targetColor1;
			}
			virtual void affect(u32 now, SParticle* particlearray, u32 count)
			{
				if (!Enabled)
					return;
				f32 d;

				for (u32 i=0; i<count; ++i)
				{
					d = (particlearray[i].endTime - now) / (particlearray[i].endTime-particlearray[i].startTime);
					particlearray[i].color = particlearray[i].startColor.getInterpolated_quadratic(
							Target0,Target1, d);
				}
			}
			virtual E_PARTICLE_AFFECTOR_TYPE getType()const
			{
				return EPAT_FADE_OUT;
			}
			irr::video::SColor Target0;
			irr::video::SColor Target1;

		};
	}
}

#endif

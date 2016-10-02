// Copyright (C) 2012 Neo
// This file is part of the Neo's game.
// Free to distribute and use.

#ifndef __C_SCENE_NODE_ANIMATOR_SPRITE_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_SPRITE_H_INCLUDED__

#include "irrArray.h"
#include "vector2d.h"
#include <irrlicht.h>

namespace irr
{
	namespace scene
	{
		class CSceneNodeAnimatorSprite : public ISceneNodeAnimator
		{
		public:

			//! constructor
			CSceneNodeAnimatorSprite(video::ITexture* texture,const core::array<core::vector2df>&translations,core::vector2df& scale,
				s32 timePerFrame, bool loop, u32 now);

			//! destructor
			virtual ~CSceneNodeAnimatorSprite();

			//! animates a scene node
			virtual void animateNode(ISceneNode* node, u32 timeMs);

			//! Writes attributes of the scene node animator.
			virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

			//! Reads attributes of the scene node animator.
			virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

			//! Returns type of the scene node animator
			virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_UNKNOWN; }

			//! Creates a clone of this animator.
			/** Please note that you will have to drop
			(IReferenceCounted::drop()) the returned pointer after calling
			this. */
			virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);

		private:

			void clearSprites();

			video::ITexture* Texture;
			core::array<core::vector2df>Translations;
			core::vector2df Scale;
			u32 TimePerFrame;
			u32 StartTime;
			u32 FinishTime;
			bool HasFinished;
			bool Loop;
		};


	} // end namespace scene
} // end namespace irr


#endif
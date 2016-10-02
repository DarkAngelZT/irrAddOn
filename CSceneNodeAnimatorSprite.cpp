// Copyright (C) 2012 Neo
// This file is part of the Neo's game.
// Free to distribute and use.
#include "CSceneNodeAnimatorSprite.h"
#include "ITexture.h"

namespace irr
{
	namespace scene
	{
		//! constructor
		CSceneNodeAnimatorSprite::CSceneNodeAnimatorSprite(video::ITexture* texture, 
			const core::array<core::vector2df>&translations,	core::vector2df& scale,
			s32 timePerFrame, bool loop, u32 now):
			TimePerFrame(timePerFrame), StartTime(now), Loop(loop),Scale(scale)
		{


				if (texture)
					texture->grab();
				Translations=translations;
				Texture=texture;

			FinishTime = now + (timePerFrame * translations.size());
		}


		//! destructor
		CSceneNodeAnimatorSprite::~CSceneNodeAnimatorSprite()
		{
			clearSprites();
		}


		void CSceneNodeAnimatorSprite::clearSprites()
		{
			/*for (u32 i=0; i<Translations.size(); ++i)
			{
				if (Translations[i])
					delete Translations[i];
			}*/
			Translations.clear();
			if(Texture)
			{
				Texture->drop();
			}
		}


		//! animates a scene node
		void CSceneNodeAnimatorSprite::animateNode(ISceneNode* node, u32 timeMs)
		{
			if(!node)
				return;

			if (Translations.size())
			{
				const u32 t = (timeMs-StartTime);

				u32 idx = 0;
				if (!Loop && timeMs >= FinishTime)
				{
					idx = Translations.size() - 1;
					HasFinished = true;
				}
				else
				{
					idx = (t/TimePerFrame) % Translations.size();
				}

				if (idx < Translations.size())
				{
					core::vector2df tran=Translations[idx];
					core::matrix4 mat;
					mat.buildTextureTransform(0,core::vector2df(0.0f),tran,Scale);
					node->setMaterialTexture(0, Texture);
					node->getMaterial(0).setTextureMatrix(0,mat);
				}
			}
		}


		//! Writes attributes of the scene node animator.
		void CSceneNodeAnimatorSprite::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
		{
			out->addInt("TimePerFrame", TimePerFrame);
			out->addBool("Loop", Loop);
			// add texture in addition when serializing for editors
			out->addTexture("Texture",Texture);
			// add one translation in addition when serializing for editors
			// to make it easier to add translations quickly

			u32 count = Translations.size();
			if ( options && (options->Flags & io::EARWF_FOR_EDITOR))
				count += 1;

			for (u32 i=0; i<count; ++i)
			{
				core::stringc tname = "Translation";
				tname += (int)(i+1);
				out->addVector2d(tname.c_str(), i<Translations.size() ? Translations[i] : core::vector2df(0.0f));
				
			}
		}


		//! Reads attributes of the scene node animator.
		void CSceneNodeAnimatorSprite::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
		{
			TimePerFrame = in->getAttributeAsInt("TimePerFrame");
			Loop = in->getAttributeAsBool("Loop");
			Texture=in->getAttributeAsTexture("Texture");
			Texture->grab();
			clearSprites();

			for(u32 i=1; true; ++i)
			{
				core::stringc tname = "Translation";
				tname += (int)i;

				if (in->existsAttribute(tname.c_str()))
				{
					core::vector2df trans = in->getAttributeAsVector2d(tname.c_str());
					//if (trans)
					//{
						Translations.push_back(trans);
					//}
				}
				else
					break;
			}
		}


		ISceneNodeAnimator* CSceneNodeAnimatorSprite::createClone(ISceneNode* node, ISceneManager* newManager)
		{
			CSceneNodeAnimatorSprite * newAnimator = 
				new CSceneNodeAnimatorSprite(Texture, Translations, Scale, TimePerFrame, Loop, StartTime);

			return newAnimator;
		}


	} // end namespace scene
} // end namespace irr


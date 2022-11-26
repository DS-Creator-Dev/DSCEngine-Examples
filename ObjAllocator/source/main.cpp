#include <nds.h>
#include <stdio.h>

#include <DSC>

#include "cat_sprite8.h"

using namespace DSC;

class MyScene : public Scene
{		
private:
	Allocator allocator = Allocator::defaultMainSpriteVram();
	PaletteManager sprite_palette = PaletteManager(Hardware::MainEngine::ObjPalette);
	PaletteLoader palette_loader = PaletteLoader(&sprite_palette);
	
	ObjAllocator obj_alloc = ObjAllocator(allocator, palette_loader);
		
public:
	void init() override
	{				
		consoleDemoInit();
		iprintf("Hello world!");	

		palette_loader.set_default_allocation_mode(PaletteLoader::ALLOC_MODE_STANDARD_PALETTE);

		Hardware::VramBank('E').main().sprite().vram().config();
		Debug::log("Set banks");			
		key_down += key_down_hanlder;		
		
		VramLoader::clear(allocator.reserve(64), 64); // transparent tile				
		
		Vector<ObjFrame*> frames;
		
		for(int r=0;r<3;r++)
		{
			for(int c=0;c<4;c++)
			{
				frames.push_back(new ObjFrame(&ROA_cat_sprite88, r,c));				
				
				if(!obj_alloc.allocate(frames.back()))
				{
					Debug::log("Failed allocation");
				}
			}
		}
		
		for(int i=0;i<frames.size();i+=3) 
		{
			delete frames[i];
			frames[i]=nullptr;
		}
	}	
	
	void frame() override
	{
		//Debug::log("frame");
	}
	
private:	
	
	static void key_down_hanlder(void* sender, void* _keys)
	{		
		Debug::log("Key pressed");
	}
		
};


dsc_launch(MyScene);

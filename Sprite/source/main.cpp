#include <nds.h>
#include <stdio.h>

#include <DSC>

#include "cat_sprite8.h"

using namespace DSC;

class MyScene : public Scene
{		
private:
	Allocator allocator = Allocator::defaultSubSpriteVram();
	PaletteManager* sprite_palette;
	PaletteLoader* palette_loader;
	
	ObjAllocator* obj_alloc;
	
	Sprite* cat = new Sprite(SIZE_32x32, Engine::Sub);
		
public:
	void init() override
	{					
		// playground
		// trying to figure out the best way to connect components to each other
		
		// everything works as long as a cat appears on the screen
		
		
		Hardware::VramBank('E').main().sprite().vram().config();		
		Hardware::VramBank('D').sub().sprite().vram().config();		
		Hardware::VramBank('I').sub().sprite().ext_palette().config();				
		key_down += key_down_hanlder;		
								
		Debug::log("Ext pal = %x", Hardware::SubEngine::ObjExtendedPalette(0));
				
		sprite_palette = new PaletteManager(Hardware::SubEngine::ObjExtendedPalette(0));	
		palette_loader = new PaletteLoader(nullptr, {sprite_palette});
		
		obj_alloc = new ObjAllocator(&allocator, palette_loader);
	
		consoleDemoInit();
		iprintf("Hello world!");	
		
		videoSetMode(MODE_0_2D);
		Hardware::MainEngine::objEnable(true);
		Hardware::SubEngine::objEnable(true);		

		palette_loader->set_default_allocation_mode(PaletteLoader::ALLOC_MODE_EXTENDED_PALETTES);
				
		Hardware::VramBank('I').lcd().config();						
		
		cat->set_default_allocator(obj_alloc);		
		cat->add_frame(new ObjFrame(&ROA_cat_sprite88, 0,0));
		
		Hardware::VramBank('I').sub().sprite().ext_palette().config();		
		
		cat->update_position();
		cat->update_visual();
	}	
	
	void frame() override
	{		
		Sprite::oam_deploy_main();
		Sprite::oam_deploy_sub();
	}
	
private:	
	
	static void key_down_hanlder(void* sender, void* _keys)
	{		
		Debug::log("Key pressed");
	}
		
};


dsc_launch(MyScene);

#include <DSC>
#include <nds.h>
#include "cat_sprite8.h"

using namespace DSC;

class Scene1 : public GenericScene256
{
private:
	Sprite* cat;
	Sprite* cat2;
public:
	void init() override
	{
		GenericScene256::init();
		
		cat = create_sprite(new Sprite(SIZE_32x32, Engine::Main));
		
		cat2 = create_sprite(new Sprite(SIZE_32x32, Engine::Sub));
		
		begin_sprites_init();
		
		cat->add_frame(new ObjFrame(&ROA_cat_sprite88, 0,0));		
		cat->add_frame(new ObjFrame(&ROA_cat_sprite88, 0,1));
		
		cat2->add_frame(new ObjFrame(&ROA_cat_sprite88, 0,2));
		
		end_sprites_init();				
		
		cat->update_visual();
		cat->update_position();		
		
		cat2->update_visual();
		cat2->update_position();		
	}		
	
	void frame() override
	{					
		Sprite::oam_deploy_main();		
		Sprite::oam_deploy_sub();		
	}		
};

dsc_launch(Scene1);

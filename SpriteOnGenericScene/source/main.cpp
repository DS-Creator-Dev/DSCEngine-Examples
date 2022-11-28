#include <DSC>
#include <nds.h>
#include "red_cat.h"
#include "blue_cat.h"
#include "bitmap.h"

using namespace DSC;

class Scene1 : public GenericScene256
{
private:
	Sprite* red_cat;
	Sprite* blue_cat;	
	
	int cat_front_anim;
	int cat_back_anim;
	int cat_left_anim;
	int cat_right_anim;
	
	void init_cat(Sprite* cat, const AssetData* cat_asset)
	{		
		int cat_front_0 = cat->add_frame(new ObjFrame(cat_asset, 0,0));
		int cat_front_1 = cat->add_frame(new ObjFrame(cat_asset, 1,0));
		int cat_front_2 = cat->add_frame(new ObjFrame(cat_asset, 2,0));
		
		int cat_back_0 = cat->add_frame(new ObjFrame(cat_asset, 0,1));
		int cat_back_1 = cat->add_frame(new ObjFrame(cat_asset, 1,1));
		int cat_back_2 = cat->add_frame(new ObjFrame(cat_asset, 2,1));
		
		int cat_left_0 = cat->add_frame(new ObjFrame(cat_asset, 0,2));
		int cat_left_1 = cat->add_frame(new ObjFrame(cat_asset, 1,2));
		int cat_left_2 = cat->add_frame(new ObjFrame(cat_asset, 2,2));
		
		int cat_right_0 = cat->add_frame(new ObjFrame(cat_asset, 0,3));
		int cat_right_1 = cat->add_frame(new ObjFrame(cat_asset, 1,3));
		int cat_right_2 = cat->add_frame(new ObjFrame(cat_asset, 2,3));
		
		cat_front_anim = cat->get_visual()->add_frameset(cat_front_0, cat_front_1, cat_front_2, ObjVisual::FRAMESET_END);
		cat_back_anim  = cat->get_visual()->add_frameset(cat_back_0, cat_back_1, cat_back_2, ObjVisual::FRAMESET_END);
		cat_left_anim  = cat->get_visual()->add_frameset(cat_left_0, cat_left_1, cat_left_2, ObjVisual::FRAMESET_END);
		cat_right_anim = cat->get_visual()->add_frameset(cat_right_0, cat_right_1, cat_right_2, ObjVisual::FRAMESET_END);
		cat->get_visual()->set_animation_ticks(10);
		cat->get_visual()->set_animation(cat_front_anim);						
		
		cat->set_position(128-16, 96-16);
	}
public:
	void init() override
	{
		GenericScene256::init();
		
		require_bitmap(MAIN_BG3, &ROA_bitmap8);
		require_bitmap(SUB_BG3, &ROA_bitmap8);
		
		red_cat = create_sprite(new Sprite(SIZE_32x32, Engine::Main));
		
		blue_cat = create_sprite(new Sprite(SIZE_32x32, Engine::Sub));
		
		begin_sprites_init();
		
		init_cat(red_cat, &ROA_red_cat8);
		init_cat(blue_cat, &ROA_blue_cat8);		
		
		end_sprites_init();	

		key_held.add_event(&Scene1::on_key_held, this);
	}		
	
	void frame() override
	{					
		GenericScene256::frame();				
	}		
	
	void on_key_held(void* sender, void* args)
	{
		int keys = (int)args;
		if(keys & KEY_RIGHT)
		{
			red_cat->move(1,0);
			blue_cat->move(-1,0);
			
			red_cat->get_visual()->set_animation(cat_right_anim);						
			blue_cat->get_visual()->set_animation(cat_left_anim);						
		}
		else if(keys & KEY_LEFT)
		{
			red_cat->move(-1,0);
			blue_cat->move(1,0);
			
			red_cat->get_visual()->set_animation(cat_left_anim);						
			blue_cat->get_visual()->set_animation(cat_right_anim);						
		}
		else if(keys & KEY_UP)
		{
			red_cat->move(0,-1);
			blue_cat->move(0,1);
			
			red_cat->get_visual()->set_animation(cat_back_anim);						
			blue_cat->get_visual()->set_animation(cat_front_anim);						
		}
		else if(keys & KEY_DOWN)
		{
			red_cat->move(0,1);
			blue_cat->move(0,-1);
			
			red_cat->get_visual()->set_animation(cat_front_anim);						
			blue_cat->get_visual()->set_animation(cat_back_anim);						
		}
	}
};

dsc_launch(Scene1);

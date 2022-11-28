/************************************************************************

	Changing Scenes example
	
	There are two scenes, each one displaying a bitmap. Pressing any key 
	causes each scene to close and launch the other scene.	

************************************************************************/
#include <DSC>

// assets data
#include "Scene1bmp.h"
#include "Scene2bmp.h"
#include "Bottom.h"

using namespace DSC;

class Scene1 : public GenericScene256
{
public:
	void init() override
	{
		GenericScene256::init();
		require_bitmap(MAIN_BG3, &ROA_Scene1bmp8);
		require_bitmap(SUB_BG3, &ROA_Bottom8);
		key_down.add_event(&Scene1::key_down_hanlder, this);
	}
	
	void key_down_hanlder(void* sender, void* _keys);
};

class Scene2 : public GenericScene256
{
public:
	void init() override
	{
		GenericScene256::init();
		require_bitmap(MAIN_BG3, &ROA_Scene2bmp8);
		require_bitmap(SUB_BG3, &ROA_Bottom8);
		key_down.add_event(&Scene2::key_down_hanlder, this);
	}
	
	void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{	
	// press any key to go to the next scene
	close()->next(new Scene2());
}

void Scene2::key_down_hanlder(void* sender, void* _keys)
{	
	// press any key to return to the previous scene
	close()->next(new Scene1());
}


// specify the launch scene
dsc_launch(Scene1);

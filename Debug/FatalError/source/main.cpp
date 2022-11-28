#include <nds.h>
#include <stdio.h>
#include <DSC>

// asset data
#include "info.h"

using namespace DSC;

class Scene1 : public GenericScene256
{
public:
	void init() override
	{	
		GenericScene256::init();
		require_bitmap(SUB_BG3, &ROA_info8);						
		
		key_down += key_down_hanlder;
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{
	Debug::log("Key down detected");
	switch((const int)_keys)
	{
		case KEY_A: nds_assert(1<2); break;		
		case KEY_B: nds_assert(2+2==5); break;		
		default: break;
	}	
}

dsc_launch(Scene1);

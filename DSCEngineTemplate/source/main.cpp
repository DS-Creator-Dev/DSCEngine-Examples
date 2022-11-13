#include <nds.h>
#include <stdio.h>

#include <DSC>

using namespace DSC;

class MyScene : public Scene
{		
public:
	void init() override
	{		
		consoleDemoInit();
		iprintf("Hello world!");
		
		key_down += key_down_hanlder;		
	}	
	
private:	
	
	static void key_down_hanlder(void* sender, void* _keys)
	{		
	}
		
};


dsc_launch(MyScene);

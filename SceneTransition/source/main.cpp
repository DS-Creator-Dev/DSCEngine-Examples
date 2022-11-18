#include <DSC>
#include <nds.h>
#include <stdio.h>

using namespace DSC;

class Scene1 : public Scene
{
public:
	void init() override
	{		
		consoleDemoInit();		
	
		iprintf("This is Scene 1\n\n");
		
		// the address should remain constant if there are no memory leaks
		iprintf("Offset = %08X\n", (int)this); 
		
		key_down.add_event(&Scene1::key_down_hanlder, this);		
	}
	
	void key_down_hanlder(void* sender, void* _keys);	
};

class Scene2 : public Scene
{
public:
	void init() override
	{
		consoleDemoInit();		
	
		iprintf("This is Scene 2\n\n");
		
		iprintf("Offset = %08X\n", (int)this);
		
		key_down.add_event(&Scene2::key_down_hanlder, this);
	}
	
	void key_down_hanlder(void* sender, void* _keys);	
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{	
	close()->next(new Scene2());
}

void Scene2::key_down_hanlder(void* sender, void* _keys)
{	
	close()->next(new Scene1());
}

dsc_launch(Scene1);

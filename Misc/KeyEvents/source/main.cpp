#include <DSC>
#include <nds.h>
#include <stdio.h>

using namespace DSC;

class TestScene : public Scene
{		
public:
	void init() override
	{
		consoleDemoInit();		
	
		iprintf("Press keys to trigger events...\n");
		
		// example of static event handler
		// alternative: 
		// key_up.add_event(key_down_hanlder);
		key_down += key_down_hanlder;
		
		// example of class member event handler
		// we need to also specify the instance that 
		// runs the non-static event handler
		key_up.add_event(&TestScene::key_up_hanlder, this);
	}

	int events_count = 0;
	
private:
	static constexpr int KEYS_COUNT = 14;
	static const int keyIds[KEYS_COUNT];
	static const char* keyNames[KEYS_COUNT];
	
	static void key_down_hanlder(void* sender, void* _keys)
	{
		// the key_* events send the keys bits directly as an int through the event args
		// so we need to dispatch it before usage:
		const int& keys = (int)_keys; 
		TestScene*& scene = (TestScene*&)sender;
		
		scene->events_count++;
		
		iprintf("Key pressed  : %08X\n", keys);
		for(int i=0;i<KEYS_COUNT;i++)
		{
			if(keys & keyIds[i]) iprintf("%s ",keyNames[i]);
		}	
		iprintf("Events count: %i\n\n", scene->events_count);
				
		if(keys & KEY_TOUCH)
		{
			scene->key_up.remove_event(&TestScene::key_up_hanlder, scene);
			iprintf("Removed keys up handler\n\n");
		}
	}
	
	void key_up_hanlder(void* sender, void* _keys)
	{
		const int& keys = (int)_keys;
		TestScene*& scene = (TestScene*&)sender;
		
		scene->events_count++;
		
		iprintf("Key released : %08X\n", keys);
		for(int i=0;i<KEYS_COUNT;i++)
		{
			if(keys & keyIds[i]) iprintf("%s ",keyNames[i]);
		}
		iprintf("Events count: %i\n\n", scene->events_count);
	}
};


dsc_launch(TestScene);


const int TestScene::keyIds[TestScene::KEYS_COUNT] = {KEY_A, KEY_B, KEY_SELECT, KEY_START, KEY_RIGHT, KEY_LEFT,
          KEY_UP, KEY_DOWN, KEY_R, KEY_L, KEY_X, KEY_Y, KEY_TOUCH, KEY_LID};
const char* TestScene::keyNames[TestScene::KEYS_COUNT] = {"A", "B", "Select", "Start", "Right", "Left",
          "Up", "Down", "R", "L", "X", "Y", "Touch", "Lid"};
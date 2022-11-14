#include <DSC>
#include "rainbow8.h"
#include "face8.h"

using namespace DSC;

int face_x(float t);
int face_y(float t);

class Scene1 : public GenericScene256
{
public:
	void init() override
	{				
		GenericScene256::init();				
		require_bitmap(MAIN_BG2, &ROA_face8);
		require_bitmap(MAIN_BG3, &ROA_rainbow8);
	}	
	
	float t=0;
	
	void frame() override
	{		
		// scroll to highlight the fact there are different backgrounds
		bgSetScroll(2, face_x(t), face_y(t));
		bgUpdate();		
		t+=0.2;
	}	
};

dsc_launch(Scene1);

#include <math.h>

int face_x(float t) { return 10*sin(t); }
int face_y(float t) { return 10*sin(t/2); }

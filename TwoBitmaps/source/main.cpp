#include <DSC>
#include "rainbow.h"
#include "face.h"
#include "sub.h"

using namespace DSC;

int face_x(float t);
int face_y(float t);
int buzz(float t);

class Scene1 : public GenericScene256
{
public:
	void init() override
	{
		GenericScene256::init();
		require_bitmap(MAIN_BG2, &ROA_face8);
		require_bitmap(MAIN_BG3, &ROA_rainbow8);
		
		require_bitmap(SUB_BG2, &ROA_sub8);
		require_bitmap(SUB_BG3, &ROA_rainbow8);
	}	
	
	float t=0;
	
	void frame() override
	{		
		// scroll to highlight the fact there are different backgrounds
		bgSetScroll(MAIN_BG2, face_x(t), face_y(t));						
		bgSetScroll(SUB_BG2, buzz(t), 0);
		bgUpdate();		
		t+=0.2;				
	}	
};

dsc_launch(Scene1);

#include <math.h>

int face_x(float t) { return -72 + 10*sin(t); }
int face_y(float t) { return -40 + 10*sin(t/2); }
int buzz(float t)   { return 3*sin(5*t);}

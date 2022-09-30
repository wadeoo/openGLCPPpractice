#include "Light.h"

static float lightPositionMoon[] = {0,500,500,0};
static float diffuseLightMoon[] = { 1, 1, 1, 1 };
static float specularLightMoon[] = { 1, 1, 1, 1 };
//static float ambientLightMoon[] = { 1, 1, 1, 0.3 };
//static float moonlightDirection[] = { 0, -1, -1 };




Light::Light()
{
}


Light::~Light()
{
}

void Light::setLight(){
	glEnable(GL_LIGHTING);

	//…Ë÷√‘¬π‚
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightMoon);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightMoon);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionMoon);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightMoon);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, moonlightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.f);



	glEnable(GL_LIGHT0);
}

void Light::Update(){

}
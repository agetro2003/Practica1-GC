#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;



void
Scene0::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	//Heptagono negro
	//gObjects.push_back(new RegularPolygon(7, 200.0, glm::dvec4(0.0, 0.0, 0.0, 1.0)));

	//Triangulo verde
	//gObjects.push_back(new RegularPolygon(3, 200.0, glm::dvec4(0.0, 1.0, 0.0, 1.0)));
	//Circunferencia magenta
	//gObjects.push_back(new RegularPolygon(360, 200.0, glm::dvec4(1.0, 0.0, 1.0, 1.0)));

	//RGB Triangle
	//gObjects.push_back(new RGBTriangle(200));
	//RGB Rectangle
	//gObjects.push_back(new RGBRectangle(500, 200));

	//apartado 10 
	gObjects.push_back(new RegularPolygon(360, 200.0, glm::dvec4(1.0, 1.0, 1.0, 1.0)));
	gObjects.push_back(new RGBTriangle(40));
	gObjects.push_back(new RGBRectangle(400, 200));
	gObjects.push_back(new Cube(250));
	
}


void
Scene1::init()
{
	setGL();
	//gObjects.push_back(new RGBAxes(400.0));
	//gObjects.push_back(new Cube(250));

}

Scene::~Scene()
{
	destroy();
	resetGL();
}

 

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects)
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque) 
	glClearColor(0.6, 0.7, 0.8, 1.0); // New background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
}

void 
Scene::update()
{
	//update gObjects
	for (Abs_Entity* el : gObjects)
		el->update();

	}
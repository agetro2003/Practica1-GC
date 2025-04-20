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
	//gObjects.push_back(new RegularPolygon(360, 200.0, glm::dvec4(1.0, 1.0, 1.0, 1.0)));
	//gObjects.push_back(new RGBTriangle(40));
	//gObjects.push_back(new RGBRectangle(400, 200));
	
	//Cubo Apartado 15
	//gObjects.push_back(new Cube(250));
	
}

void
Scene1::init()
{
	setGL();
	gObjects.push_back(new RGBAxes(400.0));
	//Triangulo cian
	gObjects.push_back(new RegularPolygon(3, 200.0, glm::dvec4(0.0, 1.0, 1.0, 1.0)));
	//Circunferencia magenta
	gObjects.push_back(new RegularPolygon(360, 200.0, glm::dvec4(1.0, 0.0, 1.0, 1.0)));

}

void
Scene2::init()
{
	setGL();
	gObjects.push_back(new RGBAxes(400.0));
	//apartado 10 
	// declarar triangulo en una variable
	RGBTriangle* t = new RGBTriangle(40);
	// setear la posicion del triangulo
	t->setPos(glm::vec3(200, 0, 0));
	gObjects.push_back(t);
	gObjects.push_back(new RegularPolygon(360, 200.0, glm::dvec4(1.0, 1.0, 1.0, 1.0)));
	gObjects.push_back(new RGBRectangle(400, 200));

}

void
Scene3::init()
{
	setGL();
	gObjects.push_back(new RGBAxes(400.0));
	//cubo del apartado 15
	//gObjects.push_back(new Cube(250));
	//cubo del apartado 16/17
	GLdouble lenght = 250;
	GLdouble l = lenght / 2;
	RGBCube* c = new RGBCube(lenght);
	c->setPos(glm::vec3(l, l, -l));
	gObjects.push_back(c);

}

void
Scene4::init()
{
	setGL(); // OpenGL settings
	gObjects.push_back(new RGBAxes(400.0));

	//Ground* ground = new Ground(300.0);  //Ap20
	
	//Ap21, suelo con baldosas
	Ground2* ground = new Ground2(400.0, 400.0, 4,4); 
	//Rotar el Ground para que descanse sobre el plano Y = 0
	ground->rotate();
	gObjects.push_back(ground);
	
	//Ap22-25, caja sin tapas con texturas distintas por fuera y dentro
	//BoxOutline* box = new BoxOutline(250.0);
	BoxOutline* boxOut = new BoxOutline(50.0);
	boxOut->rearrange(glm::vec3(100, 30, 100));
	gObjects.push_back(boxOut);
	
	//Ap 30-31, caja con tapa que se abre y cierra
	Box* box = new Box(50.0);
	box->rearrange(glm::vec3(-100, 30, -100));
	gObjects.push_back(box);
	
	//Ap26-29, estrella doble de 8 puntas que rota
	//Star3D* star = new Star3D(180, 8, 175);
	Star3D* star = new Star3D(36, 8, 35);
	star->rearrange(glm::vec3(100, 110, 100));
	gObjects.push_back(star);

	//Ap35, foto de la escena
	Photo* photo = new Photo(75);
	photo->rotate(glm::vec3(0, 10, 0));
	gObjects.push_back(photo);

	//Ap33, hierba
	Grass* grass = new Grass(50.0);
	grass->rearrange(glm::vec3(-120, 25, 120));
	gObjects.push_back(grass);
	
	//Ap32, caja sin tapas con textura translúcida
	//GlassParapet* glass = new GlassParapet(250.0);
	GlassParapet* glass = new GlassParapet(420.0, 105.0);
	/*
	glass->mTexture = new Texture(); 
	glass->mTexture->load("../assets/images/windowV.jpg", 100);
	gTextures.push_back(glass->mTexture);

	Texture* mTexture_glass = new Texture();
	mTexture_glass->load("../assets/images/windowV.jpg", 100);
	glass->mTexture = mTexture_glass;
	gTextures.push_back(mTexture_glass);
	*/
	gObjects.push_back(glass);

}

void
Scene5::init()
{
	setGL(); // OpenGL settings
	gObjects.push_back(new RGBAxes(400.0));

	Torus* torus = new Torus(100, 50);
	torus->setColor(glm::dvec4(0.0, 1.0, 0.0, 1.0));
	gObjects.push_back(torus);
}

void
Scene6::init()
{
	setGL(); // OpenGL settings
	gObjects.push_back(new RGBAxes(400.0));

	IndexedBox* box = new IndexedBox(200);
	box->setColor(glm::dvec4(0.0, 1.0, 0.0, 1.0));
	gObjects.push_back(box);
}

void
Scene7::init()
{
	setGL(); // OpenGL settings
	
	gObjects.push_back(new RGBAxes(400.0));

	
	Sphere* sphere = new Sphere(100, 360, 360);
	sphere->setColor(glm::dvec4(0.0, 1.0, 0.0, 1.0));

	Disk* disk = new Disk(100, 200, 200, 360);
	disk->setColor(glm::dvec4(0.0, 0.0, 1.0, 1.0));

	Cone* cone = new Cone(160, 10, 20, 200, 200);
	cone->setColor(glm::dvec4(0.0, 0.0, 1.0, 1.0));
	
	//gObjects.push_back(disk);
	//gObjects.push_back(sphere);
	//gObjects.push_back(cone);
	
	
	AdvancedTIE* adv_tie = new AdvancedTIE();
	gObjects.push_back(adv_tie);

}


void
Scene8::init()
{
	setGL(); // OpenGL settings

	gObjects.push_back(new RGBAxes(400.0));

	Sphere* tatooine = new Sphere(200, 360, 360);
	tatooine->setColor(glm::dvec4(1.0, 233.0/255.0, 0.0, 1.0));
	gObjects.push_back(tatooine);

	AdvancedTIE* adv_tie = new AdvancedTIE();
	adv_tie->scale(glm::vec3(0.25f, 0.25f, 0.25f));
	adv_tie->move(glm::vec3(0.0f, 225.0f, 0.0f));
	gObjects.push_back(adv_tie);


}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {	/*
		auto* objWithTexture = dynamic_cast<EntityWithTexture*>(el);
		if (objWithTexture) {
			delete objWithTexture->mTexture;
			auto* objWithInsideTexture = dynamic_cast<BoxOutline*>(el);
			if (objWithInsideTexture) {
				delete objWithInsideTexture->mInsideTexture;
			}
		}*/
		delete el;
	}
		

	gObjects.clear();

	for (Texture* el : gTextures)
		delete el;

	gTextures.clear();
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
//	glEnable(GL_TEXTURE_2D);
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	//glDisable(GL_TEXTURE_2D);
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

void
Scene::setNormals()
{
	for (Abs_Entity* el : gObjects) {
		auto* objWithNormals = dynamic_cast<ColorMaterialEntity*>(el);
		if (objWithNormals) {
			objWithNormals->toggleShowNormals();	
		}
}
	}
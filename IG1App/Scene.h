#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init() = 0;
	//update gObjects 
	virtual void update();
	void render(Camera const& cam) const;

	// load or unload scene data into the GPU
	void load();
	void unload();

	

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
};

//scene0
class Scene0 : public Scene
{
public:
	Scene0() = default;
	~Scene0() = default;

	void init() override; 
};


//scene1
class Scene1 : public Scene {
public:
	Scene1() = default;
	~Scene1() = default;

	void init() override;
};

//scene2
class Scene2 : public Scene {
public:
	Scene2() = default;
	~Scene2() = default;

	void init() override;
};

//scene3
class Scene3 : public Scene {
public:
	Scene3() = default;
	~Scene3() = default;

	void init() override;
};

//scene4
class Scene4 : public Scene {
public:
	Scene4() = default;
	~Scene4() = default;

	void init() override;
};

//scene5
class Scene5 : public Scene {
public:
	Scene5() = default;
	~Scene5() = default;
	
	void init() override;
};

#endif //_H_Scene_H_

#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(const mat4& modelViewMat) const
{
	mShader->setUniform("modelView", modelViewMat);
}

Abs_Entity::~Abs_Entity()
{
	delete mMesh;
	mMesh = nullptr;
}

void
Abs_Entity::load()
{
	mMesh->load();
}

void
Abs_Entity::unload()
{
	mMesh->unload();
}

EntityWithColors::EntityWithColors()
{
	mShader = Shader::get("vcolors");
}

void
EntityWithColors::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mMesh->render();
	}
}

RGBAxes::RGBAxes(GLdouble l)
{
	mShader = Shader::get("vcolors");
	mMesh = Mesh::createRGBAxes(l);
	load();
}

// Constructor with a color.
SingleColorEntity::SingleColorEntity(glm::dvec4 mColor)
{
	mShader = Shader::get("simple");
}

// Get the color of the entity.
glm::dvec4 SingleColorEntity::color() const { return mColor; }

// Set the color of the entity.
void SingleColorEntity::setColor(glm::dvec4 color) { mColor = color; }

// Render with mShader->setUniform("color", mColor).
void SingleColorEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("color", glm::vec4(mColor));
		//mShader->setUniform("color", mColor);

		mMesh->render();
	}
}
// Create a regular polygon with num vertices, radius r and color mColor.
RegularPolygon::RegularPolygon(GLuint num, GLdouble r, glm::dvec4 mColor)
{
	RegularPolygon::setColor(mColor);
	mShader = Shader::get("simple");
	mMesh = Mesh::generateRegularPolygon(num, r);
	load();
}



// Constructor
RGBTriangle::RGBTriangle(GLdouble l)
{
	
	mShader = Shader::get("vcolors");
	//rellenar el triangulo
	mMesh = Mesh::generateRGBTriangle(l);

	

	load();

}

//render the RGBTriangle
void RGBTriangle::render(const glm::mat4& modelViewMat) const
{
	
	
		if (mMesh != nullptr) {
			//translate the triangle 200 units in the x axis
		mat4 translateMatrix = glm::translate(mModelMat, glm::vec3(-200.0f, 0.0f, 0.0f));
		mat4 aMat = modelViewMat * translateMatrix; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		glDisable(GL_CULL_FACE);



	}
}

//update the RGBTriangle
void RGBTriangle::update()
{
	glm::mat4 orbitMat = glm::rotate(glm::mat4(1.0), glm::radians(9.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	glm::mat4 orbited = orbitMat * mModelMat;

	glm::vec3 initialPos = glm::vec3(orbited[3]);

	glm::mat4 toOrigin = glm::translate(glm::mat4(1.0), -initialPos);
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(18.0f),  glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 toPos = glm::translate(glm::mat4(1.0), initialPos);

	mModelMat = toPos * rotateMat * toOrigin * orbited;




	
}

// Constructor
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
{
	mShader = Shader::get("vcolors");
	mMesh = Mesh::generateRGBRectangle(w, h);
	load();
}

void RGBRectangle::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
		mMesh->render();
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
		mMesh->render();
		glDisable(GL_CULL_FACE);
	}
}


//Constructor
Cube::Cube(GLdouble lenght, glm::dvec4 mColor)
{

	mShader = Shader::get("vcolors");
	//create cube
	mMesh = Mesh::generateCube(lenght);


	load();

}

void Cube::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("color", glm::vec4(mColor));
		//mShader->setUniform("color", mColor);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//mMesh->render();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT );
		mMesh->render();
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		glDisable(GL_CULL_FACE);

	}

}


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
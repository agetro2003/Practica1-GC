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
	//load();
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
	//load();
}



// Constructor
RGBTriangle::RGBTriangle(GLdouble l)
{
	
	mShader = Shader::get("vcolors");
	//rellenar el triangulo
	mMesh = Mesh::generateRGBTriangle(l);

//	load();

}


void RGBTriangle::setPos(glm::vec3 pos)
{
	mModelMat = glm::translate(mModelMat, pos);
}

void RGBTriangle::rotate()
{
	//Move to the origin
	glm::vec3 initialPos = glm::vec3(mModelMat[3]);
	glm::mat4 toOrigin = glm::translate(glm::mat4(1.0), -initialPos);
	//Rotate clockwise
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(18.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	//Move back to the initial position
	glm::mat4 toPos = glm::translate(glm::mat4(1.0), initialPos);

	mModelMat = toPos * rotateMat * toOrigin * mModelMat;

}

void RGBTriangle::orbit()
{
	// orbit the triangle around the origin counterclockwise
	glm::mat4 orbitMat = glm::rotate(glm::mat4(1.0), glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	mModelMat = orbitMat * mModelMat;
}

//render the RGBTriangle
void RGBTriangle::render(const glm::mat4& modelViewMat) const
{
	
	
		if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
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
	rotate();
	orbit();
}

// Constructor
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
{
	mShader = Shader::get("vcolors");
	mMesh = Mesh::generateRGBRectangle(w, h);
	//load();
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
	mMesh = Mesh::generateCube(lenght);	//Cubo generado con 14 v�rtices y GL_TRIANGLE_STRIP como primitiva, usado en el apartado 15 de la pr�ctica 1
	//mMesh = Mesh::generateCube2(lenght);	//Cubo generado con 36 v�rtices GL_TRIANGLES como primitiva, usado en el apartado 16 de la pr�ctica 1

	//load();

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


// Constructor
RGBCube::RGBCube(GLdouble l)
{

	mShader = Shader::get("vcolors");
	//create RGB Cube
	mMesh = Mesh::generateRGBCubeTriangles(l);

	//load();

}

void RGBCube::render(const glm::mat4& modelViewMat) const {

	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();
		glCullFace(GL_FRONT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		mMesh->render();
		glDisable(GL_CULL_FACE);

	}


}

//Funciones para rotaci�n del apartado 17 �8pr�ctica 1)

void RGBCube::setPos(glm::vec3 pos)
{
	mModelMat = glm::translate(mModelMat, pos);
}

//Rotar en x
void RGBCube::rotatex( )
{
	glm::vec3 Pos = glm::vec3(mModelMat[3]);
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mModelMat = rotateMat * mModelMat;
}

//Rotar en y
void RGBCube::rotatey()
{
	glm::vec3 Pos = glm::vec3(mModelMat[3]);
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mModelMat = rotateMat * mModelMat;
}

//Rotar en z
void RGBCube::rotatez()
{
	glm::vec3 Pos = glm::vec3(mModelMat[3]);
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	mModelMat = rotateMat * mModelMat;
}

//Rota en x 180 grados, luego en y 180 grados en y, luego 180 grados en z y vuelve a empezar2
void RGBCube::update() {
	if (alpha < 180)
	{
		rotatex();
		alpha += 2;
	}
	else if (alpha < 360)
	{
		rotatez();
		alpha += 2;
	}
	else if (alpha < 540)
	{
		rotatey();
		alpha += 2;
	} 
	else 
	{
		alpha = 0;
		rotatex();
		alpha += 2;
	}
}


EntityWithTexture::EntityWithTexture()
{
	mShader = Shader::get("texture");
}

void EntityWithTexture::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("modulate", mModulate);
		if (mTexture != nullptr) {
			mTexture->bind();
			mMesh->render();
			mTexture->unbind();
		}
		else {
			mMesh->render();
		}

	}
}

void EntityWithTexture::rearrange(glm::vec3 pos) {
	glm::mat4 translateMat = glm::translate(mModelMat, pos);
	mModelMat = translateMat * mModelMat;
}

// Constructor de la clase Ground para el apartado 20
Ground::Ground(GLdouble lenght) {

	mShader = Shader::get("texture");
	//create Ground
	mMesh = Mesh::generateRectangleTexCor(lenght, lenght);
	mTexture=new Texture();
	//ruta relativa de la imagen
	mTexture->load("../assets/images/baldosaC.png");

}


void Ground::render(const glm::mat4& modelViewMat) const {

	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("modulate", mModulate);
		glEnable(GL_CULL_FACE);
		
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Condicional para verificar si hay textura
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glDisable(GL_CULL_FACE);
	}
	
	
}

void Ground::rotate() {

	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mModelMat = rotateMat * mModelMat;
}


// Constructor de la clase Ground para el apartado 21
Ground2::Ground2(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {

	mShader = Shader::get("texture");
	//create Ground
	mMesh = Mesh::generaRectangleTexCor(w, h, rw, rh);
	mTexture = new Texture();
	//ruta relativa de la imagen
	mTexture->load("../assets/images/baldosaC.png");

}

void Ground2::render(const glm::mat4& modelViewMat) const {

	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("modulate", mModulate);
		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Condicional para verificar si hay textura
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glDisable(GL_CULL_FACE);
	}


}

void Ground2::rotate() {

	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mModelMat = rotateMat * mModelMat;
}

//Constructor caja sin tapa apartados 22-25
BoxOutline::BoxOutline(GLdouble lenght, glm::dvec4 mColor)
{

	mShader = Shader::get("texture");
	//create cubo sin tapas
	mMesh = Mesh::generateBoxOutlineTexCor(lenght, lenght);
	mTexture = new Texture();
	mInsideTexture = new Texture();

	//ruta relativa de la imagen
	mTexture->load("../assets/images/container.jpg");
	mInsideTexture->load("../assets/images/papelE.png");

}

void BoxOutline::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("modulate", mModulate);
	

		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Condicional para verificar si hay textura
		if (mInsideTexture != nullptr) {
			mInsideTexture->bind();
		}
		mMesh->render();
		if (mInsideTexture != nullptr) {
			mInsideTexture->unbind();
		}
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glDisable(GL_CULL_FACE);

	}

}

//Constructor estrella apartado 26-29
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h) {
	mShader = Shader::get("texture");
	//create 3DStar
	//mMesh = Mesh::generateStar3D(re, np, h);
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
	mTexture = new Texture();

	//ruta relativa de la imagen
	mTexture->load("../assets/images/baldosaP.png");


} 


void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		if (mTexture != nullptr) {
			mTexture->unbind();
		}

		
		aMat = modelViewMat * mModelMat * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//aMat = modelViewMat * glm::translate(glm::mat4(1.0), -glm::vec3(mModelMat[3])) * mModelMat;
		upload(aMat);

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		

		glDisable(GL_CULL_FACE);
	}
}

//update the Stars
void Star3D::update()
{
	//Move to the origin
	glm::vec3 initialPos = glm::vec3(mModelMat[3]);
	glm::mat4 toOrigin = glm::translate(glm::mat4(1.0), -initialPos);
	glm::mat4 rotateMatY = glm::rotate(glm::mat4(1.0), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Move back to the initial position
	glm::mat4 toPos = glm::translate(glm::mat4(1.0), initialPos);
	
	glm::mat4 rotateMatZ = glm::rotate(glm::mat4(1.0), glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	mModelMat = toPos * rotateMatY * toOrigin * mModelMat *rotateMatZ;
}


//Constructor caja sin tapa apartados 32
GlassParapet::GlassParapet(GLdouble width, GLdouble height, glm::dvec4 mColor)
{

	mShader = Shader::get("texture:texture_alpha");
	//create cubo sin tapas
	mMesh = Mesh::generateGlassParapet(width, height);
	mTexture = new Texture();

	//ruta relativa de la imagen
	mTexture->load("../assets/images/windowV.jpg", 100);

}

void GlassParapet::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("modulate", mModulate);

		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		glEnable(GL_CULL_FACE);
		
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Condicional para verificar si hay textura
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glDisable(GL_CULL_FACE);


		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}

//Ap-35, foto
Photo::Photo(GLdouble lenght)
{
	mShader = Shader::get("texture");
	//create foto
	mMesh = Mesh::generateRectangleTexCor(lenght, lenght);
	mTexture = new Texture();
	l = 600;

}


void Photo::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);
		mShader->setUniform("modulate", mModulate);
		mTexture->loadColorBuffer(l, l);
		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Condicional para verificar si hay textura
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mTexture != nullptr) {
			mTexture->bind();
		}
		mMesh->render();
		if (mTexture != nullptr) {
			mTexture->unbind();
		}
		glDisable(GL_CULL_FACE);
	}
}



void Photo::update() {
	mTexture->loadColorBuffer(l, l);
	
}

void Photo::rotate(glm::vec3 pos) {

	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 translateMat= glm::translate(mModelMat, pos);
	mModelMat = translateMat * rotateMat * mModelMat;
}


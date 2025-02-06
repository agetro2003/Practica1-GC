#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	//assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
// Create a regular polygon with num vertices and radius r
Mesh *	
Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	float alpha = 90;
	float step = 360 / num;
	for (int i = 0; i < num; i++) {
		double x = r * cos(radians(alpha));
		double y = r * sin(radians(alpha));
		mesh->vVertices.emplace_back(x, y, 0.0);
		alpha += step;
	}


	return mesh;

}

// Create a RGB triangle with radius r
Mesh*
Mesh::generateRGBTriangle(GLdouble r)
{
	Mesh* mesh = generateRegularPolygon(3, r);
	mesh->mPrimitive = GL_TRIANGLES;	
	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // red
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // green
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); // blue

	return mesh;
}

// Create a rectangle with width w and height h
Mesh*
Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(w * 0.5, h * 0.5, 0.0);
	mesh->vVertices.emplace_back(-w * 0.5, h * 0.5, 0.0);
	mesh->vVertices.emplace_back(w * 0.5, -h * 0.5, 0.0);
	mesh->vVertices.emplace_back(-w * 0.5, -h * 0.5, 0.0);
	
	return mesh;
}

// Create a RGB rectangle with width w, height h, one vertex red, one blue and two green
Mesh*
Mesh::generateRGBRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = generateRectangle(w, h);
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); 

	return mesh;
}

//P1-Apartado 15 -> Cubo gnerado con 14 vértices y GL_TRIANGLE_STRIP como primitiva
Mesh*
Mesh::generateCube(GLdouble length) 
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 14;
	mesh->vVertices.reserve(mesh->mNumVertices);
	GLdouble l = length * 0.5;

	//Cara z+ (0-1-2 + 1-2-3)
	mesh->vVertices.emplace_back(-l, l, l);	//0
	mesh->vVertices.emplace_back(l, l, l);	//1
	mesh->vVertices.emplace_back(-l, -l, l);//2
	mesh->vVertices.emplace_back(l, -l, l);	//3

	//Cara y- (2-3-4)
	//Cara x+ (3-4-1 + 4-1-5)
	mesh->vVertices.emplace_back(l, -l, -l);//4
	mesh->vVertices.emplace_back(l, l, l);	//1
	mesh->vVertices.emplace_back(l, l, -l);	//5

	//Cara y+ (1-5-0 + 5-0-6)
	mesh->vVertices.emplace_back(-l, l, l);	//0
	mesh->vVertices.emplace_back(-l, l, -l);//6
	
	//Cara x- (0-6-2 + 6-2-7)
	mesh->vVertices.emplace_back(-l, -l, l);//2
	mesh->vVertices.emplace_back(-l, -l, -l);//7

	//Cara y- (2-7-4)
	//Cara z- (7-4-6 + 4-6-5)
	mesh->vVertices.emplace_back(l, -l, -l);//4
	mesh->vVertices.emplace_back(-l, l, -l);//6
	mesh->vVertices.emplace_back(l, l, -l);	//5

	return mesh;
}


//P1-Apartado 16 -> Cubo con 64 vértices y GL_TRIANGLES como primitiva para poder asignar colores a vértices (y no queden caras de colores mezclados)
Mesh*
Mesh::generateCube2(GLdouble length)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);
	GLdouble l = length * 0.5;

	//Cara z+ (0-1-2 + 1-2-3)
	mesh->vVertices.emplace_back(-l, l, l);	//0
	mesh->vVertices.emplace_back(l, l, l);	//1
	mesh->vVertices.emplace_back(-l, -l, l);//2

	mesh->vVertices.emplace_back(-l, -l, l);//2
	mesh->vVertices.emplace_back(l, l, l);	//1
	mesh->vVertices.emplace_back(l, -l, l);	//3

	//Cara y- (2-3-4 + 2-7-4)
	mesh->vVertices.emplace_back(-l, -l, l);//2
	mesh->vVertices.emplace_back(l, -l, l);	//3
	mesh->vVertices.emplace_back(l, -l, -l);//4

	mesh->vVertices.emplace_back(-l, -l, -l);//7
	mesh->vVertices.emplace_back(-l, -l, l);//2
	mesh->vVertices.emplace_back(l, -l, -l);//4
	
	//Cara x+ (3-4-1 + 4-1-5)
	mesh->vVertices.emplace_back(l, -l, -l);//4
	mesh->vVertices.emplace_back(l, -l, l);	//3
	mesh->vVertices.emplace_back(l, l, l);	//1

	mesh->vVertices.emplace_back(l, -l, -l);//4
	mesh->vVertices.emplace_back(l, l, l);	//1
	mesh->vVertices.emplace_back(l, l, -l);	//5
	
	//Cara y+ (1-5-0 + 5-0-6)
	mesh->vVertices.emplace_back(l, l, -l);	//5
	mesh->vVertices.emplace_back(l, l, l);	//1
	mesh->vVertices.emplace_back(-l, l, l);	//0

	mesh->vVertices.emplace_back(l, l, -l);	//5
	mesh->vVertices.emplace_back(-l, l, l);	//0
	mesh->vVertices.emplace_back(-l, l, -l);//6
	
	//Cara x- (0-6-2 + 6-2-7)
	mesh->vVertices.emplace_back(-l, l, -l);//6
	mesh->vVertices.emplace_back(-l, l, l);	//0
	mesh->vVertices.emplace_back(-l, -l, l);//2
	
	mesh->vVertices.emplace_back(-l, l, -l);//6
	mesh->vVertices.emplace_back(-l, -l, l);//2
	mesh->vVertices.emplace_back(-l, -l, -l);//7
	
	//Cara z- (7-4-6 + 4-6-5)
	mesh->vVertices.emplace_back(-l, -l, -l);//7
	mesh->vVertices.emplace_back(l, -l, -l);//4
	mesh->vVertices.emplace_back(-l, l, -l);//6

	mesh->vVertices.emplace_back(-l, l, -l);//6
	mesh->vVertices.emplace_back(l, -l, -l);//4
	mesh->vVertices.emplace_back(l, l, -l);	//5
	
	return mesh;
}

Mesh*
Mesh::generateRGBCubeTriangles(GLdouble length) {

	Mesh* mesh = generateCube(length);
	mesh->vColors.reserve(mesh->mNumVertices);

	//Cara z+ (0-1-2 + 1-2-3) (roja)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//0
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//1
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//2

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//2
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//1
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//3

	
	//Cara y- (2-3-4 + 2-7-4) (azul)
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//2
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//3
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//4

	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//7
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//4
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//2
	
	//Cara x+ (3-4-1 + 4-1-5) (verde)
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//4
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//3
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//1

	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//4
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//1
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//5

	//Cara y+ (1-5-0 + 5-0-6) (azul)
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//5
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//1
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//0

	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//5
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//0
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);//6

	//Cara x- (0-6-2 + 6-2-7) (verde)
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//6
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//0
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//2

	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//6
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//2
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//7

	//Cara z- (7-4-6 + 4-6-5) (roja)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//7
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//4
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//6

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//6
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//4
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);//5
	
	return mesh;

}

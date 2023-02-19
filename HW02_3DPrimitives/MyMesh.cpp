#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	
	// 2 circles with opposite normals
	// Top circle has center at (0, 0, height) instead of (0, 0, 0)
	float triRadians = (2 * PI) / a_nSubdivisions;
	float currentTriRad = 0;

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 pointOne = vector3(cos(currentTriRad) * a_fRadius, sin(currentTriRad) * a_fRadius, 0.0f);
		currentTriRad += triRadians;
		vector3 pointTwo = vector3(cos(currentTriRad) * a_fRadius, sin(currentTriRad) * a_fRadius, 0.0f);

		// Top part of cone
		AddTri(vector3(0.0f, 0.0f, a_fHeight), pointOne, pointTwo);
		// Underside of cone
		AddTri(vector3(0.0f, 0.0f, 0.0f), pointTwo, pointOne);
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	
	// 2 completely separate circles with opposing normals
	// Squares should join the two sides
	float triRadians = (2 * PI) / a_nSubdivisions;
	float currentTriRad = 0;

	for (int i = 0; i < a_nSubdivisions; i++) {
		// One > Two > Three > Four
		// A > B > C > D
		vector3 pointOne = vector3(cos(currentTriRad) * a_fRadius, sin(currentTriRad) * a_fRadius, 0.0f);
		currentTriRad += triRadians;
		vector3 pointTwo = vector3(cos(currentTriRad) * a_fRadius, sin(currentTriRad) * a_fRadius, 0.0f);
		vector3 pointThree = pointOne + vector3(0.0f, 0.0f, a_fHeight);
		vector3 pointFour = pointTwo + vector3(0.0f, 0.0f, a_fHeight);

		// Ceiling of cylinder
		AddTri(vector3(0.0f, 0.0f, a_fHeight), pointThree, pointFour);
		// Floor of cylinder
		AddTri(vector3(0.0f, 0.0f, 0.0f), pointTwo, pointOne);
		// Wall of cylinder
		AddQuad(pointOne, pointTwo, pointThree, pointFour);
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	
	// Cylinder - thinner cylinder
	// Ceiling and floor will need squares to fill in
	// Inner wall with flipped normals will also be needed
	float triRadians = (2 * PI) / a_nSubdivisions;
	float currentTriRad = 0;

	for (int i = 0; i < a_nSubdivisions; i++) {
		// Two circles to keep track of
		// Outer: 1, 2, 3, 4
		// Inner: 5, 6, 7, 8
		vector3 pointOne = vector3(cos(currentTriRad) * a_fOuterRadius, sin(currentTriRad) * a_fOuterRadius, 0.0f);
		// Have to do this now since currentTriRad will increment soon, even though it's numerically out of order
		vector3 pointFive = vector3(cos(currentTriRad) * a_fInnerRadius, sin(currentTriRad) * a_fInnerRadius, 0.0f);
		currentTriRad += triRadians;
		vector3 pointTwo = vector3(cos(currentTriRad) * a_fOuterRadius, sin(currentTriRad) * a_fOuterRadius, 0.0f);
		vector3 pointSix = vector3(cos(currentTriRad) * a_fInnerRadius, sin(currentTriRad) * a_fInnerRadius, 0.0f);
		// Outer upper circle
		vector3 pointThree = pointOne + vector3(0.0f, 0.0f, a_fHeight);
		vector3 pointFour = pointTwo + vector3(0.0f, 0.0f, a_fHeight);
		// Inner upper circle
		vector3 pointSeven = pointFive + vector3(0.0f, 0.0f, a_fHeight);
		vector3 pointEight = pointSix + vector3(0.0f, 0.0f, a_fHeight);

		// Tube's outer wall
		AddQuad(pointOne, pointTwo, pointThree, pointFour);
		// Tube's inner wall
		AddQuad(pointFive, pointSeven, pointSix, pointEight);	// Need to flip the normals, 6 and 7 need to be in reverse order
		// Tube's ceiling
		AddQuad(pointThree, pointFour, pointSeven, pointEight);
		// Tube's floor
		AddQuad(pointOne, pointFive, pointTwo, pointSix);
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	
	// Outer Radius - Inner Radius = Radius of torus
	// Probably only quads as the whole thing is walls
	// Circle formula still relevant
	float offsetTriRadians = (2 * PI) / a_nSubdivisionsB;
	float offsetCurrentRads = 0;

	for (int i = 0; i < a_nSubdivisionsB; i++) {
		// Calculate offset for this ring
		matrix4 coordTransform = IDENTITY_M4;
		coordTransform = glm::rotate(coordTransform, offsetCurrentRads, vector3(0.0f, 1.0f, 0.0f));
		coordTransform = glm::translate(coordTransform, vector3(a_fInnerRadius + ((a_fOuterRadius - a_fInnerRadius) / 2), 0.0f, 0.0f));
		matrix4 futureTransform = IDENTITY_M4;
		futureTransform = glm::rotate(futureTransform, offsetCurrentRads + offsetTriRadians, vector3(0.0f, 1.0f, 0.0f));
		futureTransform = glm::translate(futureTransform, vector3(a_fInnerRadius + ((a_fOuterRadius - a_fInnerRadius) / 2), 0.0f, 0.0f));

		float triRadians = (2 * PI) / a_nSubdivisionsA;
		float currentTriRad = 0;

		for (int j = 0; j < a_nSubdivisionsA; j++) {
			vector3 pointOne = vector3(cos(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), sin(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), 0.0f);
			vector3 pointThree = vector3(cos(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), sin(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), 0.0f);
			currentTriRad += triRadians;
			vector3 pointTwo = vector3(cos(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), sin(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), 0.0f);
			vector3 pointFour = vector3(cos(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), sin(currentTriRad) * (a_fOuterRadius - a_fInnerRadius), 0.0f);

			// Translate the four points
			pointOne = coordTransform * vector4(pointOne, 1.0f);
			pointTwo = coordTransform * vector4(pointTwo, 1.0f);
			pointThree = futureTransform * vector4(pointThree, 1.0f);
			pointFour = futureTransform * vector4(pointFour, 1.0f);
			AddQuad(pointOne, pointThree, pointTwo, pointFour);
		}
		offsetCurrentRads += offsetTriRadians;
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	
	// Top and bottom should be circles
	// Everything inbetween should be square walls
	float triRadians = (2 * PI) / a_nSubdivisions;
	float currentTriRad = 0;
	float subDivHeight = a_fRadius / a_nSubdivisions;

	for (int i = 0; i < a_nSubdivisions; i++) {
		float currentSphereRad = triRadians / 2;
		vector3 pointOne = vector3(sin(currentSphereRad) * cos(currentTriRad) * a_fRadius, sin(currentSphereRad) * sin(currentTriRad) * a_fRadius,
			cos(currentSphereRad) * a_fRadius);
		currentTriRad += triRadians;
		vector3 pointTwo = vector3(sin(currentSphereRad) * cos(currentTriRad) * a_fRadius, sin(currentSphereRad) * sin(currentTriRad) * a_fRadius,
			cos(currentSphereRad) * a_fRadius);

		for (int j = 1; j < a_nSubdivisions - 1; j++) {
			vector3 sqPointOne = vector3(sin(currentSphereRad) * cos(currentTriRad - triRadians) * a_fRadius, sin(currentSphereRad) * sin(currentTriRad - triRadians) * a_fRadius,
				cos(currentSphereRad) * a_fRadius);
			vector3 sqPointTwo = vector3(sin(currentSphereRad) * cos(currentTriRad) * a_fRadius, sin(currentSphereRad) * sin(currentTriRad) * a_fRadius,
				cos(currentSphereRad) * a_fRadius);
			vector3 sqPointThree = vector3(sin(currentSphereRad + (triRadians / 2)) * cos(currentTriRad - triRadians) * a_fRadius,
				sin(currentSphereRad + (triRadians / 2)) * sin(currentTriRad - triRadians) * a_fRadius,
				cos(currentSphereRad + (triRadians / 2)) * a_fRadius);
			vector3 sqPointFour = vector3(sin(currentSphereRad + (triRadians / 2)) * cos(currentTriRad) * a_fRadius,
				sin(currentSphereRad + (triRadians / 2)) * sin(currentTriRad) * a_fRadius,
				cos(currentSphereRad + (triRadians / 2)) * a_fRadius);

			AddQuad(sqPointOne, sqPointThree, sqPointTwo, sqPointFour);

			currentSphereRad += triRadians / 2;
		}

		// Top of sphere
		AddTri(vector3(0.0f, 0.0f, a_fRadius), pointOne, pointTwo);
		// Move points one and two to the top of the sphere
		pointOne = vector3(pointOne.x, pointOne.y, cos(currentSphereRad) * a_fRadius);
		pointTwo = vector3(pointTwo.x, pointTwo.y, cos(currentSphereRad) * a_fRadius);
		// Bottom of sphere
		AddTri(vector3(0.0f, 0.0f, 0.0f - a_fRadius), pointTwo, pointOne);
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
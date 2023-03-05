#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Tyler Grant - tjg2610@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	for (int i = 0; i < 46; i++) {
		m_pMeshArr[i] = new MyMesh();
		m_pMeshArr[i]->GenerateCube(1.0f, C_BLACK);
	}
		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	matrix4 m4Position = glm::translate(IDENTITY_M4, vector3(distToMove, 0.0f, 0.0f));
	distToMove += .05f;

	//First (top) row
	m_pMeshArr[0]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-3.0f, 4.0f, 0.0f)));
	m_pMeshArr[1]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, 4.0f, 0.0f)));

	//Second
	m_pMeshArr[2]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-2.0f, 3.0f, 0.0f)));
	m_pMeshArr[3]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, 3.0f, 0.0f)));

	//Third
	for (int i = 4; i < 11; i++) {
		m_pMeshArr[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-3.0f + (i - 4), 2.0f, 0.0f)));
	}

	//Fourth
	m_pMeshArr[11]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-4.0f, 1.0f, 0.0f)));
	m_pMeshArr[12]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-3.0f, 1.0f, 0.0f)));
	m_pMeshArr[13]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-1.0f, 1.0f, 0.0f)));
	m_pMeshArr[14]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, 1.0f, 0.0f)));
	m_pMeshArr[15]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, 1.0f, 0.0f)));
	m_pMeshArr[16]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, 1.0f, 0.0f)));
	m_pMeshArr[17]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, 1.0f, 0.0f)));

	//Fifth
	for (int i = 18; i < 29; i++) {
		m_pMeshArr[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-5.0f + (i - 18), 0.0f, 0.0f)));
	}

	//Sixth
	m_pMeshArr[29]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-5.0f, -1.0f, 0.0f)));
	for (int i = 30; i < 37; i++) {
		m_pMeshArr[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-3.0f + (i - 30), -1.0f, 0.0f)));
	}
	m_pMeshArr[37]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -1.0f, 0.0f)));

	//Seventh
	m_pMeshArr[38]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-5.0f, -2.0f, 0.0f)));
	m_pMeshArr[39]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-3.0f, -2.0f, 0.0f)));
	m_pMeshArr[40]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, -2.0f, 0.0f)));
	m_pMeshArr[41]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -2.0f, 0.0f)));

	//Eighth
	m_pMeshArr[42]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-2.0f, -3.0f, 0.0f)));
	m_pMeshArr[43]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-1.0f, -3.0f, 0.0f)));
	m_pMeshArr[44]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, -3.0f, 0.0f)));
	m_pMeshArr[45]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, -3.0f, 0.0f)));

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes
	for (int i = 0; i < 46; i++) {
		SafeDelete(m_pMeshArr[i]);
	}

	//release GUI
	ShutdownGUI();
}
#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint depthmapShader, shadowmapShader, depthMap, depthMapFBO;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint VBOlangit, VAOlangit, EBOlangit, textureLangit; // Buat langit
	GLuint VBO, VAO, EBO, texture, VBO0, VAO0, EBO0, texture0; // Buat Plane
	GLuint VBO1, VAO1, EBO1, texture1, VBO2, VAO2, EBO2, texture2; // Buat Jembatan dan jalan
	GLuint VBO3, VAO3, EBO3, texture3, VBO4, VAO4, EBO4, texture4; // Buat Tiang
	GLuint VBO5, VAO5, EBO5, texture5, VBO6, VAO6, EBO6, texture6; // Buat Tiang
	GLuint VBO7, VAO7, EBO7, texture7, VBO8, VAO8, EBO8, texture8; // Buat Tiang
	GLuint VBO9, VAO9, EBO9, texture9, VBO10, VAO10, EBO10, texture10, VBO12, VAO12, EBO12, texture12,
		VBO13, VAO13, EBO13, texture13, VBO14, VAO14, EBO14, VBO15, VAO15, EBO15, VBO16, VAO16, EBO16, VBO17, VAO17, EBO17; // Buat Pagar
	GLuint VBO11, VAO11, EBO11, texture11; // Buat Lampu
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildShaders();
	void BuildDepthMap();
	// KERJAAN PANDU
	void BuildColoredJembatan();
	void BuildColoredJalan();
	void BuildColoredPlane();
	void BuildColoredLowerPlane();
	void BuildColoredLangit();
	void DrawColoredJembatan(GLuint shader);
	void DrawColoredJalan(GLuint shader);
	void DrawColoredPlane(GLuint shader);
	void DrawColoredLowerPlane(GLuint shader);
	void DrawColoredLangit(GLuint shader);
	// KERJAAN WAHYU
	void BuildColoredPole1();
	void BuildColoredMidPole1();
	void BuildColoredTipPole1();
	void BuildColoredPole2();
	void BuildColoredMidPole2();
	void BuildColoredTipPole2();
	void DrawColoredPole1(GLuint shader);
	void DrawColoredMidPole1(GLuint shader);
	void DrawColoredTipPole1(GLuint shader);
	void DrawColoredPole2(GLuint shader);
	void DrawColoredMidPole2(GLuint shader);
	void DrawColoredTipPole2(GLuint shader);
	// KERJAAN IRSYAD
	void BuildColoredTiang1();
	void BuildColoredAtap1();
	void DrawColoredTiang1(GLuint shader);
	void DrawColoredAtap1(GLuint shader);
	void BuildColoredTiang2();
	void BuildColoredAtap2();
	void DrawColoredTiang2(GLuint shader);
	void DrawColoredAtap2(GLuint shader);
	void BuildColoredTiang1Kanan();
	void BuildColoredAtap1Kanan();
	void DrawColoredTiang1Kanan(GLuint shader);
	void DrawColoredAtap1Kanan(GLuint shader);
	void BuildColoredTiang2Kanan();
	void BuildColoredAtap2Kanan();
	void DrawColoredTiang2Kanan(GLuint shader);
	void DrawColoredAtap2Kanan(GLuint shader);
	// KERJAAN WAWAN
	void BuildColoredCube();
	void DrawColoredCube(GLuint shader);
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void FlyCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};


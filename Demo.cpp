#include "Demo.h"

Demo::Demo() {

}


Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	//shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	BuildShaders();
	BuildDepthMap();

	// KERJAAN PANDU
	BuildColoredJembatan();
	BuildColoredJalan();
	BuildColoredPlane();
	BuildColoredLowerPlane();
	BuildColoredLangit();

	// KERJAAN WAHYU
	BuildColoredPole1();
	BuildColoredMidPole1();
	BuildColoredTipPole1();
	BuildColoredPole2();
	BuildColoredMidPole2();
	BuildColoredTipPole2();

	// KERJAAN IRSYAD
	BuildColoredTiang1();
	BuildColoredAtap1();
	BuildColoredTiang2();
	BuildColoredAtap2();
	BuildColoredTiang1Kanan();
	BuildColoredAtap1Kanan();
	BuildColoredTiang2Kanan();
	BuildColoredAtap2Kanan();
	BuildColoredPlane();

	// KERJAAN WAWAN
	BuildColoredCube();

	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO0);
	glDeleteBuffers(1, &VBO0);
	glDeleteBuffers(1, &EBO0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		FlyCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		FlyCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Demo::Update(double deltaTime) {
	
}

void Demo::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Step 1 Render depth of scene to texture
	// ----------------------------------------
	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 150.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(-30.0f, 30.0f, -90.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	// render scene from light's point of view
	UseShader(this->depthmapShader);
	glUniformMatrix4fv(glGetUniformLocation(this->depthmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	// KERJAAN PANDU
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawColoredLowerPlane(this->depthmapShader);
	DrawColoredPlane(this->depthmapShader);
	glDisable(GL_BLEND);
	DrawColoredJembatan(this->depthmapShader);
	DrawColoredJalan(this->depthmapShader);
	DrawColoredLangit(this->depthmapShader);
	// KERJAAN WAHYU
	DrawColoredPole1(this->depthmapShader);
	DrawColoredMidPole1(this->depthmapShader);
	DrawColoredTipPole1(this->depthmapShader);
	DrawColoredPole2(this->depthmapShader);
	DrawColoredMidPole2(this->depthmapShader);
	DrawColoredTipPole2(this->depthmapShader);
	//KERJAAN IRSYAD
	DrawColoredTiang1(this->depthmapShader);
	DrawColoredAtap1(this->depthmapShader);
	DrawColoredTiang2(this->depthmapShader);
	DrawColoredAtap2(this->depthmapShader);
	DrawColoredTiang1Kanan(this->depthmapShader);
	DrawColoredAtap1Kanan(this->depthmapShader);
	DrawColoredTiang2Kanan(this->depthmapShader);
	DrawColoredAtap2Kanan(this->depthmapShader);
	// KERJAAN WAWAN
	DrawColoredCube(this->depthmapShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	// Step 2 Render scene normally using generated depth map
	// ------------------------------------------------------
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Pass perspective projection matrix
	UseShader(this->shadowmapShader);
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shadowmapShader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// LookAt camera (position, target/direction, up)
	glm::vec3 cameraPos = glm::vec3(0, 5, 2);
	glm::vec3 cameraFront = glm::vec3(0, 0, 0);
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shadowmapShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Setting Light Attributes
	glUniformMatrix4fv(glGetUniformLocation(this->shadowmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glUniform3f(glGetUniformLocation(this->shadowmapShader, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);
	glUniform3f(glGetUniformLocation(this->shadowmapShader, "lightPos"), -30.0f, 30.0f, -90.0f);

	// Configure Shaders
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "shadowMap"), 1);

	/////// KERJAAN PANDU //////////
	// Render lower floor
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredLowerPlane(this->shadowmapShader);
	// Render floor
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredPlane(this->shadowmapShader);
	glDisable(GL_BLEND);
	// Render jembatan
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredJembatan(this->shadowmapShader);
	// Render jembatan
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredJalan(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLangit);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredLangit(this->shadowmapShader);
	///////// KERJAAN WAHYU ///////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredPole1(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredMidPole1(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredTipPole1(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredPole2(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredMidPole2(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredTipPole2(this->shadowmapShader);
	///////// KERJAAN IRSYAD //////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredTiang1(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredAtap1(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredTiang2(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredAtap2(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredTiang1Kanan(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredAtap1Kanan(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredTiang2Kanan(this->shadowmapShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredAtap2Kanan(this->shadowmapShader);
	////// KERJAAN WAWAN ////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	DrawColoredCube(this->shadowmapShader);

	glDisable(GL_DEPTH_TEST);
}

///////////////////////////////////
////// INI KERJAANNYA PANDU ///////
//////////////////////////////////
void Demo::BuildColoredJembatan() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("aspal.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

		0.5, 1.5, 100.0, 0, 0, 0.0f, 0.0f, 1.0f, // 0
		4.5, 1.5, 100.0, 1, 0, 0.0f, 0.0f, 1.0f, // 1
		4.5, 2.5, 100.0, 1, 1, 0.0f, 0.0f, 1.0f, // 2
		0.5, 2.5, 100.0, 0, 1, 0.0f, 0.0f, 1.0f, // 3

		4.5, 1.5, 100.0, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		4.5, 1.5, 32.0, 1, 0, 1.0f, 0.0f, 0.0f, // 5
		4.5, 2.5, 32.0, 1, 1, 1.0f, 0.0f, 0.0f, // 6
		4.5, 2.5, 100.0, 0, 1, 1.0f, 0.0f, 0.0f, // 7

		0.5, 1.5, 100.0, 0, 0, -1.0f, 0.0f, 0.0f, // 8
		0.5, 1.5, 32.0, 1, 0, -1.0f, 0.0f, 0.0f, // 9
		0.5, 2.5, 32.0, 1, 1, -1.0f, 0.0f, 0.0f, // 10
		0.5, 2.5, 100.0, 0, 1, -1.0f, 0.0f, 0.0f, // 11

		4.5, 2.5, 32.0, 0, 0, 1.0f, 0.0f, 0.0f, // 20
		4.5, 2.5, 24.0, 1, 0, 1.0f, 0.0f, 0.0f, // 21
		4.5, 3.5, 24.0, 1, 1, 1.0f, 0.0f, 0.0f, //22
		4.5, 3.5, 32.0, 0, 1, 1.0f, 0.0f, 0.0f, //23

		0.5, 2.5, 32.0, 0, 0, -1.0f, 0.0f, 0.0f, // 24
		0.5, 2.5, 24.0, 1, 0, -1.0f, 0.0f, 0.0f, // 25
		0.5, 3.5, 24.0, 1, 1, -1.0f, 0.0f, 0.0f, //26
		0.5, 3.5, 32.0, 0, 1, -1.0f, 0.0f, 0.0f, //27

		4.5, 3.5, 24.0, 0, 0, 1.0f, 0.0f, 0.0f, // 28
		4.5, 3.5, 16.0, 1, 0, 1.0f, 0.0f, 0.0f, // 29
		4.5, 4.5, 16.0, 1, 1, 1.0f, 0.0f, 0.0f, //30
		4.5, 4.5, 24.0, 0, 1, 1.0f, 0.0f, 0.0f, //31

		0.5, 3.5, 24.0, 0, 0, -1.0f, 0.0f, 0.0f, // 32
		0.5, 3.5, 16.0, 1, 0, -1.0f, 0.0f, 0.0f, // 33
		0.5, 4.5, 16.0, 1, 1, -1.0f, 0.0f, 0.0f, //34
		0.5, 4.5, 24.0, 0, 1, -1.0f, 0.0f, 0.0f, //35

		4.5, 4.5, 16.0, 0, 0, 1.0f, 0.0f, 0.0f, // 36
		4.5, 4.5, 12.0, 1, 0, 1.0f, 0.0f, 0.0f, // 37
		4.5, 5.5, 12.0, 1, 1, 1.0f, 0.0f, 0.0f, //38
		4.5, 5.5, 16.0, 0, 1, 1.0f, 0.0f, 0.0f, //39

		0.5, 4.5, 16.0, 0, 0, -1.0f, 0.0f, 0.0f, // 40
		0.5, 4.5, 12.0, 1, 0, -1.0f, 0.0f, 0.0f, // 41
		0.5, 5.5, 12.0, 1, 1, -1.0f, 0.0f, 0.0f, //42
		0.5, 5.5, 16.0, 0, 1, -1.0f, 0.0f, 0.0f, //43

		4.5, 5.5, 12.0, 0, 0, 1.0f, 0.0f, 0.0f, // 44
		4.5, 5.5, 8.0, 1, 0, 1.0f, 0.0f, 0.0f, // 45
		4.5, 6.5, 8.0, 1, 1, 1.0f, 0.0f, 0.0f, //46
		4.5, 6.5, 12.0, 0, 1, 1.0f, 0.0f, 0.0f, //47

		0.5, 5.5, 12.0, 0, 0, -1.0f, 0.0f, 0.0f, // 48
		0.5, 5.5, 8.0, 1, 0, -1.0f, 0.0f, 0.0f, // 49
		0.5, 6.5, 8.0, 1, 1, -1.0f, 0.0f, 0.0f, //50
		0.5, 6.5, 12.0, 0, 1, -1.0f, 0.0f, 0.0f, //51

		4.5, 6.5, 8.0, 0, 0, 1.0f, 0.0f, 0.0f, // 52
		4.5, 6.5, 4.0, 1, 0, 1.0f, 0.0f, 0.0f, // 53
		4.5, 7.5, 4.0, 1, 1, 1.0f, 0.0f, 0.0f, //54
		4.5, 7.5, 8.0, 0, 1, 1.0f, 0.0f, 0.0f, //55

		0.5, 6.5, 8.0, 0, 0, -1.0f, 0.0f, 0.0f, // 56
		0.5, 6.5, 4.0, 1, 0, -1.0f, 0.0f, 0.0f, // 57
		0.5, 7.5, 4.0, 1, 1, -1.0f, 0.0f, 0.0f, //58
		0.5, 7.5, 8.0, 0, 1, -1.0f, 0.0f, 0.0f, //59

		4.5, 7.5, 4.0, 0, 0, 1.0f, 0.0f, 0.0f, // 60
		4.5, 7.5, 0.0, 1, 0, 1.0f, 0.0f, 0.0f, // 61
		4.5, 8.5, 0.0, 1, 1, 1.0f, 0.0f, 0.0f, //62
		4.5, 8.5, 4.0, 0, 1, 1.0f, 0.0f, 0.0f, //63

		0.5, 7.5, 4.0, 0, 0, -1.0f, 0.0f, 0.0f, // 64
		0.5, 7.5, 0.0, 1, 0, -1.0f, 0.0f, 0.0f, // 65
		0.5, 8.5, 0.0, 1, 1, -1.0f, 0.0f, 0.0f, //66
		0.5, 8.5, 4.0, 0, 1, -1.0f, 0.0f, 0.0f, //67

		/// SETENGAHNYA LAGI ///
		0.5, 1.5, -100.0, 0, 0, 0.0f, 0.0f, -1.0f, // 0
		4.5, 1.5, -100.0, 1, 0, 0.0f, 0.0f, -1.0f, // 1
		4.5, 2.5, -100.0, 1, 1, 0.0f, 0.0f, -1.0f, // 2
		0.5, 2.5, -100.0, 0, 1, 0.0f, 0.0f, -1.0f, // 3

		4.5, 1.5, -100.0, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		4.5, 1.5, -32.0, 1, 0, 1.0f, 0.0f, 0.0f, // 5
		4.5, 2.5, -32.0, 1, 1, 1.0f, 0.0f, 0.0f, // 6
		4.5, 2.5, -100.0, 0, 1, 1.0f, 0.0f, 0.0f, // 7

		0.5, 1.5, -100.0, 0, 0, -1.0f, 0.0f, 0.0f, // 8
		0.5, 1.5, -32.0, 1, 0, -1.0f, 0.0f, 0.0f, // 9
		0.5, 2.5, -32.0, 1, 1, -1.0f, 0.0f, 0.0f, // 10
		0.5, 2.5, -100.0, 0, 1, -1.0f, 0.0f, 0.0f, // 11

		4.5, 2.5, -32.0, 0, 0, 1.0f, 0.0f, 0.0f, // 20
		4.5, 2.5, -24.0, 1, 0, 1.0f, 0.0f, 0.0f, // 21
		4.5, 3.5, -24.0, 1, 1, 1.0f, 0.0f, 0.0f, //22
		4.5, 3.5, -32.0, 0, 1, 1.0f, 0.0f, 0.0f, //23

		0.5, 2.5, -32.0, 0, 0, -1.0f, 0.0f, 0.0f, // 24
		0.5, 2.5, -24.0, 1, 0, -1.0f, 0.0f, 0.0f, // 25
		0.5, 3.5, -24.0, 1, 1, -1.0f, 0.0f, 0.0f, //26
		0.5, 3.5, -32.0, 0, 1, -1.0f, 0.0f, 0.0f, //27

		4.5, 3.5, -24.0, 0, 0, 1.0f, 0.0f, 0.0f, // 28
		4.5, 3.5, -16.0, 1, 0, 1.0f, 0.0f, 0.0f, // 29
		4.5, 4.5, -16.0, 1, 1, 1.0f, 0.0f, 0.0f, //30
		4.5, 4.5, -24.0, 0, 1, 1.0f, 0.0f, 0.0f, //31

		0.5, 3.5, -24.0, 0, 0, -1.0f, 0.0f, 0.0f, // 32
		0.5, 3.5, -16.0, 1, 0, -1.0f, 0.0f, 0.0f, // 33
		0.5, 4.5, -16.0, 1, 1, -1.0f, 0.0f, 0.0f, //34
		0.5, 4.5, -24.0, 0, 1, -1.0f, 0.0f, 0.0f, //35

		4.5, 4.5, -16.0, 0, 0, 1.0f, 0.0f, 0.0f, // 36
		4.5, 4.5, -12.0, 1, 0, 1.0f, 0.0f, 0.0f, // 37
		4.5, 5.5, -12.0, 1, 1, 1.0f, 0.0f, 0.0f, //38
		4.5, 5.5, -16.0, 0, 1, 1.0f, 0.0f, 0.0f, //39

		0.5, 4.5, -16.0, 0, 0, -1.0f, 0.0f, 0.0f, // 40
		0.5, 4.5, -12.0, 1, 0, -1.0f, 0.0f, 0.0f, // 41
		0.5, 5.5, -12.0, 1, 1, -1.0f, 0.0f, 0.0f, //42
		0.5, 5.5, -16.0, 0, 1, -1.0f, 0.0f, 0.0f, //43

		4.5, 5.5, -12.0, 0, 0, 1.0f, 0.0f, 0.0f, // 44
		4.5, 5.5, -8.0, 1, 0, 1.0f, 0.0f, 0.0f, // 45
		4.5, 6.5, -8.0, 1, 1, 1.0f, 0.0f, 0.0f, //46
		4.5, 6.5, -12.0, 0, 1, 1.0f, 0.0f, 0.0f, //47

		0.5, 5.5, -12.0, 0, 0, -1.0f, 0.0f, 0.0f, // 48
		0.5, 5.5, -8.0, 1, 0, -1.0f, 0.0f, 0.0f, // 49
		0.5, 6.5, -8.0, 1, 1, -1.0f, 0.0f, 0.0f, //50
		0.5, 6.5, -12.0, 0, 1, -1.0f, 0.0f, 0.0f, //51

		4.5, 6.5, -8.0, 0, 0, 1.0f, 0.0f, 0.0f, // 52
		4.5, 6.5, -4.0, 1, 0, 1.0f, 0.0f, 0.0f, // 53
		4.5, 7.5, -4.0, 1, 1, 1.0f, 0.0f, 0.0f, //54
		4.5, 7.5, -8.0, 0, 1, 1.0f, 0.0f, 0.0f, //55

		0.5, 6.5, -8.0, 0, 0, -1.0f, 0.0f, 0.0f, // 56
		0.5, 6.5, -4.0, 1, 0, -1.0f, 0.0f, 0.0f, // 57
		0.5, 7.5, -4.0, 1, 1, -1.0f, 0.0f, 0.0f, //58
		0.5, 7.5, -8.0, 0, 1, -1.0f, 0.0f, 0.0f, //59

		4.5, 7.5, -4.0, 0, 0, 1.0f, 0.0f, 0.0f, // 60
		4.5, 7.5, 0.0, 1, 0, 1.0f, 0.0f, 0.0f, // 61
		4.5, 8.5, 0.0, 1, 1, 1.0f, 0.0f, 0.0f, //62
		4.5, 8.5, -4.0, 0, 1, 1.0f, 0.0f, 0.0f, //63

		0.5, 7.5, -4.0, 0, 0, -1.0f, 0.0f, 0.0f, // 64
		0.5, 7.5, 0.0, 1, 0, -1.0f, 0.0f, 0.0f, // 65
		0.5, 8.5, 0.0, 1, 1, -1.0f, 0.0f, 0.0f, //66
		0.5, 8.5, -4.0, 0, 1, -1.0f, 0.0f, 0.0f, //67
	};

	unsigned int indices[] = {

		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
		24, 25, 26, 24, 26, 27,
		28, 29, 30, 28, 30, 31,
		32, 33, 34, 32, 34, 35,
		36, 37, 38, 36, 38, 39,
		40, 41, 42, 40, 42, 43,
		44, 45, 46, 44, 46, 47,
		48, 49, 50, 48, 50, 51,
		52, 53, 54, 52, 54, 55,
		56, 57, 58, 56, 58, 59,
		60, 61, 62, 60, 62, 63,
		64, 65, 66, 64, 66, 67,

		/// PONDASI ///
		68, 69, 70, 68, 70, 71,
		72, 73, 74, 72, 74, 75,
		76, 77, 78, 76, 78, 79,
		80, 81, 82, 80, 82, 83,
		84, 85, 86, 84, 86, 87,
		88, 89, 90, 88, 90, 91,
		92, 93, 94, 92, 94, 95,
		96, 97, 98, 96, 98, 99,
		100, 101, 102, 100, 102, 103,
		104, 105, 106, 104, 106, 107,

		/// STENGAHNYA LAGI ///
		108, 109, 110, 108, 110, 111,
		112, 113, 114, 112, 114, 115,
		116, 117, 118, 116, 118, 119,
		120, 121, 122, 120, 122, 123,
		124, 125, 126, 124, 126, 127,
		128, 129, 130, 128, 130, 131,
		132, 133, 134, 132, 134, 135,
		136, 137, 138, 136, 138, 139,
		140, 141, 142, 140, 142, 143,
		144, 145, 146, 144, 146, 147,
		148, 149, 150, 148, 150, 151,
		152, 153, 154, 152, 154, 155,
		156, 157, 158, 156, 158, 159,
		160, 161, 162, 160, 162, 163,
		164, 165, 166, 164, 166, 167,
		168, 169, 170, 168, 170, 171,
		172, 173, 174, 172, 174, 175,
		176, 177, 178, 176, 178, 179,
		180, 181, 182, 180, 182, 183,
		184, 185, 186, 184, 186, 187,
		188, 189, 190, 188, 190, 191,
		192, 193, 194, 192, 194, 195,
		196, 197, 198, 196, 198, 199,
		200, 201, 202, 200, 202, 203,
		204, 205, 206, 204, 206, 207,
		208, 209, 210, 208, 210, 211,
		212, 213, 214, 212, 214, 215,
	};

	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredJembatan(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO1);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 321, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredJalan()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("jalan.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	float vertices[] = {
		// format position, tex coords

		0.5, 2.5, 100.0, 0, 0, 0.0f, 1.0f, 0.0f, // 1
		4.5, 2.5, 100.0, 2, 0, 0.0f, 1.0f, 0.0f, // 2
		4.5, 2.5, 32.0, 2, 10, 0.0f, 1.0f, 0.0f, // 3
		0.5, 2.5, 32.0, 0, 10, 0.0f, 1.0f, 0.0f, // 4

		0.5, 3.5, 32.0, 0, 0, 0.0f, 1.0f, 0.0f, // 9
		4.5, 3.5, 32.0, 2, 0, 0.0f, 1.0f, 0.0f, // 10
		4.5, 3.5, 24.0, 2, 1.33, 0.0f, 1.0f, 0.0f, //11
		0.5, 3.5, 24.0, 0, 1.33, 0.0f, 1.0f, 0.0f, //12

		0.5, 4.5, 24.0, 0, 0, 0.0f, 1.0f, 0.0f, // 13
		4.5, 4.5, 24.0, 2, 0, 0.0f, 1.0f, 0.0f, // 14
		4.5, 4.5, 16.0, 2, 1.33, 0.0f, 1.0f, 0.0f, //15
		0.5, 4.5, 16.0, 0, 1.33, 0.0f, 1.0f, 0.0f, //16

		0.5, 5.5, 16.0, 0, 0, 0.0f, 1.0f, 0.0f, // 17
		4.5, 5.5, 16.0, 2, 0, 0.0f, 1.0f, 0.0f, // 18
		4.5, 5.5, 12.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //19
		0.5, 5.5, 12.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //20

		0.5, 6.5, 12.0, 0, 0, 0.0f, 1.0f, 0.0f, // 21
		4.5, 6.5, 12.0, 2, 0, 0.0f, 1.0f, 0.0f, // 22
		4.5, 6.5, 8.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //23
		0.5, 6.5, 8.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //24

		0.5, 7.5, 8.0, 0, 0, 0.0f, 1.0f, 0.0f, // 25
		4.5, 7.5, 8.0, 2, 0, 0.0f, 1.0f, 0.0f, // 26
		4.5, 7.5, 4.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //27
		0.5, 7.5, 4.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //28

		0.5, 8.5, 4.0, 0, 0, 0.0f, 1.0f, 0.0f, // 29
		4.5, 8.5, 4.0, 2, 0, 0.0f, 1.0f, 0.0f, // 30
		4.5, 8.5, 0.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //31
		0.5, 8.5, 0.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //32

		0.5, 2.5, 32.0, 0, 0, 0.0f, 0.0f, 1.0f, // 9
		4.5, 2.5, 32.0, 2, 0, 0.0f, 0.0f, 1.0f, // 10
		4.5, 3.5, 32.0, 2, 0.67, 0.0f, 0.0f, 1.0f, //11
		0.5, 3.5, 32.0, 0, 0.67, 0.0f, 0.0f, 1.0f, //12

		0.5, 3.5, 24.0, 0, 0, 0.0f, 0.0f, 1.0f, // 13
		4.5, 3.5, 24.0, 2, 0, 0.0f, 0.0f, 1.0f, // 14
		4.5, 4.5, 24.0, 2, 0.67, 0.0f, 0.0f, 1.0f, //15
		0.5, 4.5, 24.0, 0, 0.67, 0.0f, 0.0f, 1.0f, //16

		0.5, 4.5, 16.0, 0, 0, 0.0f, 0.0f, 1.0f, // 17
		4.5, 4.5, 16.0, 2, 0, 0.0f, 0.0f, 1.0f, // 18
		4.5, 5.5, 16.0, 2, 0.67, 0.0f, 0.0f, 1.0f, //19
		0.5, 5.5, 16.0, 0, 0.67, 0.0f, 0.0f, 1.0f, //20

		0.5, 5.5, 12.0, 0, 0, 0.0f, 0.0f, 1.0f, // 21
		4.5, 5.5, 12.0, 2, 0, 0.0f, 0.0f, 1.0f, // 22
		4.5, 6.5, 12.0, 2, 0.67, 0.0f, 0.0f, 1.0f, //23
		0.5, 6.5, 12.0, 0, 0.67, 0.0f, 0.0f, 1.0f, //24

		0.5, 6.5, 8.0, 0, 0, 0.0f, 0.0f, 1.0f, // 25
		4.5, 6.5, 8.0, 2, 0, 0.0f, 0.0f, 1.0f, // 26
		4.5, 7.5, 8.0, 2, 0.67, 0.0f, 0.0f, 1.0f, //27
		0.5, 7.5, 8.0, 0, 0.67, 0.0f, 0.0f, 1.0f, //28

		0.5, 7.5, 4.0, 0, 0, 0.0f, 0.0f, 1.0f, // 29
		4.5, 7.5, 4.0, 2, 0, 0.0f, 0.0f, 1.0f, // 30
		4.5, 8.5, 4.0, 2, 0.67, 0.0f, 0.0f, 1.0f, //31
		0.5, 8.5, 4.0, 0, 0.67, 0.0f, 0.0f, 1.0f, //32

		/// SETENGAHNYA LAGI
		0.5, 2.5, -100.0, 0, 0, 0.0f, 1.0f, 0.0f, // 1
		4.5, 2.5, -100.0, 2, 0, 0.0f, 1.0f, 0.0f, // 2
		4.5, 2.5, -32.0, 2, 10, 0.0f, 1.0f, 0.0f, // 3
		0.5, 2.5, -32.0, 0, 10, 0.0f, 1.0f, 0.0f, // 4

		0.5, 3.5, -32.0, 0, 0, 0.0f, 1.0f, 0.0f, // 9
		4.5, 3.5, -32.0, 2, 0, 0.0f, 1.0f, 0.0f, // 10
		4.5, 3.5, -24.0, 2, 1.33, 0.0f, 1.0f, 0.0f, //11
		0.5, 3.5, -24.0, 0, 1.33, 0.0f, 1.0f, 0.0f, //12

		0.5, 4.5, -24.0, 0, 0, 0.0f, 1.0f, 0.0f, // 13
		4.5, 4.5, -24.0, 2, 0, 0.0f, 1.0f, 0.0f, // 14
		4.5, 4.5, -16.0, 2, 1.33, 0.0f, 1.0f, 0.0f, //15
		0.5, 4.5, -16.0, 0, 1.33, 0.0f, 1.0f, 0.0f, //16

		0.5, 5.5, -16.0, 0, 0, 0.0f, 1.0f, 0.0f, // 17
		4.5, 5.5, -16.0, 2, 0, 0.0f, 1.0f, 0.0f, // 18
		4.5, 5.5, -12.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //19
		0.5, 5.5, -12.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //20

		0.5, 6.5, -12.0, 0, 0, 0.0f, 1.0f, 0.0f, // 21
		4.5, 6.5, -12.0, 2, 0, 0.0f, 1.0f, 0.0f, // 22
		4.5, 6.5, -8.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //23
		0.5, 6.5, -8.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //24

		0.5, 7.5, -8.0, 0, 0, 0.0f, 1.0f, 0.0f, // 25
		4.5, 7.5, -8.0, 2, 0, 0.0f, 1.0f, 0.0f, // 26
		4.5, 7.5, -4.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //27
		0.5, 7.5, -4.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //28

		0.5, 8.5, -4.0, 0, 0, 0.0f, 1.0f, 0.0f, // 29
		4.5, 8.5, -4.0, 2, 0, 0.0f, 1.0f, 0.0f, // 30
		4.5, 8.5, 0.0, 2, 0.67, 0.0f, 1.0f, 0.0f, //31
		0.5, 8.5, 0.0, 0, 0.67, 0.0f, 1.0f, 0.0f, //32

		0.5, 2.5, -32.0, 0, 0, 0.0f, 0.0f, -1.0f, // 9
		4.5, 2.5, -32.0, 2, 0, 0.0f, 0.0f, -1.0f, // 10
		4.5, 3.5, -32.0, 2, 0.67, 0.0f, 0.0f, -1.0f, //11
		0.5, 3.5, -32.0, 0, 0.67, 0.0f, 0.0f, -1.0f, //12

		0.5, 3.5, -24.0, 0, 0, 0.0f, 0.0f, -1.0f, // 13
		4.5, 3.5, -24.0, 2, 0, 0.0f, 0.0f, -1.0f, // 14
		4.5, 4.5, -24.0, 2, 0.67, 0.0f, 0.0f, -1.0f, //15
		0.5, 4.5, -24.0, 0, 0.67, 0.0f, 0.0f, -1.0f, //16

		0.5, 4.5, -16.0, 0, 0, 0.0f, 0.0f, -1.0f, // 17
		4.5, 4.5, -16.0, 2, 0, 0.0f, 0.0f, -1.0f, // 18
		4.5, 5.5, -16.0, 2, 0.67, 0.0f, 0.0f, -1.0f, //19
		0.5, 5.5, -16.0, 0, 0.67, 0.0f, 0.0f, -1.0f, //20

		0.5, 5.5, -12.0, 0, 0, 0.0f, 0.0f, -1.0f, // 21
		4.5, 5.5, -12.0, 2, 0, 0.0f, 0.0f, -1.0f, // 22
		4.5, 6.5, -12.0, 2, 0.67, 0.0f, 0.0f, -1.0f, //23
		0.5, 6.5, -12.0, 0, 0.67, 0.0f, 0.0f, -1.0f, //24

		0.5, 6.5, -8.0, 0, 0, 0.0f, 0.0f, -1.0f, // 25
		4.5, 6.5, -8.0, 2, 0, 0.0f, 0.0f, -1.0f, // 26
		4.5, 7.5, -8.0, 2, 0.67, 0.0f, 0.0f, -1.0f, //27
		0.5, 7.5, -8.0, 0, 0.67, 0.0f, 0.0f, -1.0f, //28

		0.5, 7.5, -4.0, 0, 0, 0.0f, 0.0f, -1.0f, // 29
		4.5, 7.5, -4.0, 2, 0, 0.0f, 0.0f, -1.0f, // 30
		4.5, 8.5, -4.0, 2, 0.67, 0.0f, 0.0f, -1.0f, //31
		0.5, 8.5, -4.0, 0, 0.67, 0.0f, 0.0f, -1.0f, //32
	};

	unsigned int indices[] = {

		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
		24, 25, 26, 24, 26, 27,
		28, 29, 30, 28, 30, 31,
		32, 33, 34, 32, 34, 35,
		36, 37, 38, 36, 38, 39,
		40, 41, 42, 40, 42, 43,
		44, 45, 46, 44, 46, 47,
		48, 49, 50, 48, 50, 51,
		52, 53, 54, 52, 54, 55,
		56, 57, 58, 56, 58, 59,
		///SETENGAHNYA LAGI ///
		60, 61, 62, 60, 62, 63,
		64, 65, 66, 64, 66, 67,
		68, 69, 70, 68, 70, 71,
		72, 73, 74, 72, 74, 75,
		76, 77, 78, 76, 78, 79,
		80, 81, 82, 80, 82, 83,
		84, 85, 86, 84, 86, 87,
		88, 89, 90, 88, 90, 91,
		92, 93, 94, 92, 94, 95,
		96, 97, 98, 96, 98, 99,
		100, 101, 102, 100, 102, 103,
		104, 105, 106, 104, 106, 107,
		108, 109, 110, 108, 110, 111,
		112, 113, 114, 112, 114, 115,
		116, 117, 118, 116, 118, 119,
	};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredJalan(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO2);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 180, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("air.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, 0.5, -100.0,  0,  0, 0.0f, 1.0f, 0.0f,
		 50.0, 0.5, -100.0, 50,  0, 0.0f, 1.0f, 0.0f,
		 50.0, 0.5,  100.0, 50, 50, 0.0f, 1.0f, 0.0f,
		-50.0, 0.5,  100.0,  0, 50, 0.0f, 1.0f, 0.0f,

	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO0);
	glGenBuffers(1, &VBO0);
	glGenBuffers(1, &EBO0);

	glBindVertexArray(VAO0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredPlane(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO0);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLowerPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("lowerPlane.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -100.0,  0,  0, 0.0f, 1.0f, 0.0f,
		 50.0, -0.5, -100.0, 1,  0, 0.0f, 1.0f, 0.0f,
		 50.0, -0.5,  100.0, 1, 1, 0.0f, 1.0f, 0.0f,
		-50.0, -0.5,  100.0,  0, 1, 0.0f, 1.0f, 0.0f,

	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredLowerPlane(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLangit()
{
	// Load and create a texture 
	glGenTextures(1, &textureLangit);
	glBindTexture(GL_TEXTURE_2D, textureLangit);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("langit.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5,  100.0,  0,  0, 0.0f, 1.0f, 0.0f,
		 50.0, -0.5,  100.0, 1,  0, 0.0f, 1.0f, 0.0f,
		 50.0, 50.0,  100.0, 1, 1, 0.0f, 1.0f, 0.0f,
		-50.0, 50.0,  100.0,  0, 1, 0.0f, 1.0f, 0.0f,

		-50.0, -0.5,  -100.0,  0,  0, 0.0f, 1.0f, 0.0f,
		 50.0, -0.5,  -100.0, 1,  0, 0.0f, 1.0f, 0.0f,
		 50.0, 50.0,  -100.0, 1, 1, 0.0f, 1.0f, 0.0f,
		-50.0, 50.0,  -100.0,  0, 1, 0.0f, 1.0f, 0.0f,

		 50.0, -0.5,  -100.0,  0,  0, 0.0f, 1.0f, 0.0f,
		 50.0, -0.5,  100.0, 1,  0, 0.0f, 1.0f, 0.0f,
		 50.0, 50.0,  100.0, 1, 1, 0.0f, 1.0f, 0.0f,
		 50.0, 50.0,  -100.0,  0, 1, 0.0f, 1.0f, 0.0f,

		 -50.0, -0.5,  -100.0,  0,  0, 0.0f, 1.0f, 0.0f,
		 -50.0, -0.5,  100.0, 1,  0, 0.0f, 1.0f, 0.0f,
		 -50.0, 50.0,  100.0, 1, 1, 0.0f, 1.0f, 0.0f,
		 -50.0, 50.0,  -100.0,  0, 1, 0.0f, 1.0f, 0.0f,
	};

	GLuint indices[] = { 
		0,  2, 1,  0,  3,  2,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
	};

	glGenVertexArrays(1, &VAOlangit);
	glGenBuffers(1, &VBOlangit);
	glGenBuffers(1, &EBOlangit);

	glBindVertexArray(VAOlangit);

	glBindBuffer(GL_ARRAY_BUFFER, VBOlangit);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOlangit);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredLangit(GLuint shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLangit);
	UseShader(shader);
	glBindVertexArray(VAOlangit);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//////////////////////////////////
///// INI KERJAANNYA WAHYU //////
/////////////////////////////////
void Demo::BuildColoredPole1() {
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pondasi_tiang_besar.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices1[] = {
		// TIANG KIRI
		//front
		-0.5, -0.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0 KABA
		0.5, -0.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1 KIBA
		0.5,  5.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2 KITA
		-0.5,  5.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3 KATA
		// right
		0.5,  5.5,  -10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4 KITA
		0.5,  5.5, -9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5 KATA
		0.5, -0.5, -9.5, 1, 1, 1.0f,  0.0f,  0.0f,// 6 KABA
		0.5, -0.5,  -10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7 KIBA
		// back
		-0.5, -0.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8  KABA
		0.5,  -0.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9  KIBA
		0.5,   5.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10 KITA
		-0.5,  5.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11 KATA
		// left
		-0.5, -0.5, -9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 12 KIBA
		-0.5, -0.5,  -10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 13 KABA
		-0.5,  5.5,  -10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 14 KATA
		-0.5,  5.5, -9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 15 KITA
		// upper
		0.5, 5.5,  -10.5, 0, 0,  0.0f,  1.0f,  0.0f,   // 16 
		-0.5, 5.5,  -10.5, 1, 0,  0.0f,  1.0f,  0.0f,  // 17
		-0.5, 5.5, -9.5, 1, 1,  0.0f,  1.0f,  0.0f,  // 18
		0.5, 5.5, -9.5, 0, 1,  0.0f,  1.0f,  0.0f,   // 19
		// bottom
		-0.5, -0.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		0.5, -0.5, -9.5, 1, 0, 0.0f,  -1.0f,  0.0f,  // 21
		0.5, -0.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f,  // 22
		-0.5, -0.5,  -10.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
		//TIANG KANAN
		// front
		4.5, -0.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 24 KIBA
		5.5, -0.5, -10.5, 1, 0,  0.0f,  0.0f,  1.0f,// 25 KABA
		5.5,  5.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f, // 26 KATA
		4.5,  5.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 27 KITA
		// right
		5.5,  5.5,  -10.5, 0, 0,  1.0f,  0.0f,  0.0f,// 28 KITA
		5.5,  5.5, -9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 29 KATA
		5.5, -0.5, -9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 30 KABA
		5.5, -0.5,  -10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 31 KIBA
		// back
		4.5, -0.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 32  KABA
		5.5,  -0.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 33 KIBA
		5.5,   5.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 34 KITA
		4.5,  5.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 35  KATA
		// left
		4.5, -0.5, -9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 36 KIBA
		4.5, -0.5,  -10.5, 1, 0, -1.0f,  0.0f,  0.0f, // 37 KABA
		4.5,  4.5,  -10.5, 1, 1, -1.0f,  0.0f,  0.0f, // 38 KATA
		4.5,  4.5, -9.5, 0, 1, -1.0f,  0.0f,  0.0f, // 39 KITA
		// upper
		5.5, 5.5,  -10.5, 0, 0,  0.0f,  1.0f,  0.0f,  // 40
		4.5, 5.5, -10.5, 1, 0,   0.0f,  1.0f,  0.0f,// 41
		4.5, 5.5, -9.5, 1, 1,  0.0f,  1.0f,  0.0f, // 42
		5.5, 5.5, -9.5, 0, 1,   0.0f,  1.0f,  0.0f, // 43
		// bottom
		4.5, -0.5, -9.5, 0, 0,  0.0f,  -1.0f,  0.0f,// 44
		5.5, -0.5, -9.5, 1, 0,  0.0f,  -1.0f,  0.0f, // 45
		5.5, -0.5,  -10.5, 1, 1,  0.0f,  -1.0f,  0.0f,  // 46
		4.5, -0.5,  -10.5, 0, 1,  0.0f,  -1.0f,  0.0f, // 47
		//TIANG ATAP 
		// upper
		4.5, 5.5,  -10.5, 0, 0,   0.0f,  1.0f,  0.0f, // 48
		0.5, 5.5, -10.5, 1, 0,  0.0f,  1.0f,  0.0f, // 49
		0.5, 5.5, -9.5, 1, 1,  0.0f,  1.0f,  0.0f, // 50
		4.5, 5.5, -9.5, 0, 1,  0.0f,  1.0f,  0.0f,  // 51
		// bottom
		0.5, 4.5, -9.5, 0, 0,  0.0f,  -1.0f,  0.0f, // 52
		4.5, 4.5, -9.5, 1, 0,  0.0f,  -1.0f,  0.0f, // 53
		4.5, 4.5,  -10.5, 1, 1,  0.0f,  -1.0f,  0.0f, // 54
		0.5, 4.5,  -10.5, 0, 1,  0.0f,  -1.0f,  0.0f, // 55
		// front
		0.5, 4.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 56		KIBA
		4.5, 4.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 57	KABA
		4.5,  5.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 58	KATA
		0.5,  5.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 59	KITA
		// back
		0.5, 4.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f,  // 60
		4.5,  4.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 61
		4.5,   5.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 62
		0.5,  5.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 63
	};

	// buat gabungin vertex
	unsigned int indices1[] = {
		//tiang kiri
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang kanan
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//atap tiang
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63 // back
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredPole1(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO3);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredMidPole1()
{
	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tiang_besar.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices1[] = {
		// TIANG KIRI
		//front
		0.5, 5.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0 KANAN BAWAH
		-0.5, 5.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1 KIRI BAWAH
		0.5,  15.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f, // 2 KIRI ATAS
		1.5,  15.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3 KANAN ATAS
		// right
		1.5,  15.5,  -10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4 KIRI ATAS
		1.5,  15.5, -9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5 KANAN ATAS
		0.5, 5.5, -9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6 KANAN BAWAH
		0.5, 5.5,  -10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7 KIRI BAWAH
		// back
		-0.5, 5.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 KANAN BAWAH
		0.5,  5.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 9 KIRI BAWAH
		1.5,   15.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10 KIRI ATAS
		0.5,  15.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 11 KANAN ATAS
		// left X, Y, Z
		-0.5, 5.5, -9.5, 0, 0, -1.0f,  0.0f,  0.0f,  // 12 KIRI BAWAH,	
		-0.5, 5.5,  -10.5, 1, 0, -1.0f,  0.0f,  0.0f,	 // 13 KANAN BAWAH,	
		0.5,  15.5,  -10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 14 KANAN ATAS, 
		0.5,  15.5, -9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 15 KIRI ATAS,	
		// upper
		1.5, 15.5,  -10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16
		0.5, 15.5,  -10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		0.5, 15.5, -9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		1.5, 15.5, -9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19
		// bottom
		-0.5, 5.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		0.5, 5.5, -9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		0.5, 5.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, 5.5,  -10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
		//TIANG KANAN
		// front
		4.5, 5.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 24 KIBA
		5.5, 5.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f, // 25 KABA
		4.5,  15.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 26 KATA
		3.5,  15.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 27 KITA
		// right
		4.5,  15.5,  -10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 28 KITA
		4.5,  15.5, -9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 29 KATA
		5.5, 5.5, -9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 30 KABA
		5.5, 5.5,  -10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 31 KIBA
		// back
		4.5, 5.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 32		KABA
		5.5,  5.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 33	KIBA
		4.5,   15.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 34	KITA
		3.5,  15.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 35	KATA
		// left
		4.5, 5.5, -9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 36		KIBA
		4.5, 5.5,  -10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 37		KABA
		3.5,  15.5,  -10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 38	KATA
		3.5,  15.5, -9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 39	KITA
		// upper
		3.5, 15.5,  -10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 40
		4.5, 15.5, -10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 41
		4.5, 15.5, -9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 42
		3.5, 15.5, -9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 43
		// bottom
		5.5, 5.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 44
		4.5, 5.5, -9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 45
		4.5, 5.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 46
		5.5, 5.5,  -10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 47
		//TIANG ATAP 
		// upper
		3.5, 15.5,  -10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 48
		1.5, 15.5, -10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 49
		1.5, 15.5, -9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 50
		3.5, 15.5, -9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 51
		// bottom
		1, 14.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 52
		4, 14.5, -9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 53
		4, 14.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 54
		1, 14.5,  -10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 55
		// front
		1.4, 14.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 56	KIBA
		3.6, 14.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 57	KABA
		3.5,  15.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 58	KATA
		1.5,  15.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f,  // 59	KITA
		// back
		1.4, 14.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 60
		3.6,  14.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 61
		3.5,   15.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 62
		1.5,  15.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 63
	};

	// buat gabungin vertex
	unsigned int indices1[] = {
		//tiang kiri
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang kanan
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//atap tiang
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63 // back
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);

	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredMidPole1(GLuint shader) {
	UseShader(shader);
	glBindVertexArray(VAO4);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTipPole1() {
	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tiang_besar.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices1[] = {
		// TIANG KIRI
		//front
		0.5, 15.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0 KABA
		1.5, 15.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1 KIBA
		1.5,  23.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2 KITA
		0.5,  23.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3 KATA
		// right
		1.5,  23.5, -10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4 KITA
		1.5,  23.5, -9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5 KATA
		1.5, 15.5, -9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6 KABA
		1.5, 15.5,  -10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7 KIBA
		// back
		0.5, 15.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8  KABA
		1.5,  15.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 9  KIBA
		1.5,   23.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 10 KITA
		0.5,  23.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 11 KATA
		// left
		0.5, 15.5, -9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 12 KIBA
		0.5, 15.5,  -10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 13 KABA
		0.5,  23.5,  -10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 14 KATA
		0.5,  23.5, -9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 15 KITA
		// upper
		1.5, 23.5,  -10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16 
		0.5, 23.5,  -10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		0.5, 23.5, -9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		1.5, 23.5, -9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19
		// bottom
		0.5, 15.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		1.5, 15.5, -9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		1.5, 15.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		0.5, 15.5,  -10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
		//TIANG KANAN
		// front
		3.5, 15.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 24 KIBA
		4.5, 15.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f, // 25 KABA
		4.5,  23.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f, // 26 KATA
		3.5,  23.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 27 KITA
		// right
		4.5,  23.5,  -10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 28 KITA
		4.5,  23.5, -9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 29 KATA
		4.5, 15.5, -9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 30 KABA
		4.5, 15.5,  -10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 31 KIBA
		// back
		3.5, 15.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 32  KABA
		4.5,  15.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 33 KIBA
		4.5,   23.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 34 KITA
		3.5,  23.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 35  KATA
		// left
		3.5, 15.5, -9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 36 KIBA
		3.5, 15.5,  -10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 37 KABA
		3.5, 23.5,  -10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 38 KATA
		3.5,  23.5, -9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 39 KITA
		// upper
		4.5, 23.5,  -10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 40
		3.5, 23.5, -10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 41
		3.5, 23.5, -9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 42
		4.5, 23.5, -9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 43
		// bottom
		3.5, 22.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 44
		4.5, 22.5, -9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 45
		4.5, 22.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 46
		3.5, 22.5,  -10.5, 0, 1,0.0f,  -1.0f,  0.0f, // 47
		//TIANG ATAP 
		// upper
		3.5, 23.5,  -10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 48
		1.5, 23.5, -10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 49
		1.5, 23.5, -9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 50
		3.5, 23.5, -9.5, 0, 1,  0.0f,  1.0f,  0.0f, // 51
		// bottom
		1.5, 22.5, -9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 52
		3.5, 22.5, -9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 53
		3.5, 22.5,  -10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 54
		1.5, 22.5,  -10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 55
		// front
		1.5, 22.5, -10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 56	KIBA
		3.5, 22.5, -10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 57	KABA
		3.5,  23.5, -10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 58	KATA
		1.5,  23.5, -10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 59	KITA
		// back
		1.5, 22.5, -9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 60
		3.5,  22.5, -9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 61
		3.5,   23.5, -9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 62
		1.5,  23.5, -9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 63
	};

	// buat gabungin vertex
	unsigned int indices1[] = {
		//tiang kiri
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang kanan
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//atap tiang
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63 // back
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);

	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredTipPole1(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO5);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

/////////////////// TIANG 2 ///////////////
void Demo::BuildColoredPole2() {
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pondasi_tiang_besar.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices1[] = {
		// TIANG KIRI
		//front
		-0.5, -0.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0 KABA
		0.5, -0.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1 KIBA
		0.5,  5.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 2 KITA
		-0.5,  5.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f,  // 3 KATA
		// right
		0.5,  5.5,  10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4 KITA
		0.5,  5.5, 9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5 KATA
		0.5, -0.5, 9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6 KABA
		0.5, -0.5,  10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7 KIBA
		// back
		-0.5, -0.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 8  KABA
		0.5,  -0.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 9  KIBA
		0.5,   5.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 10 KITA
		-0.5,  5.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 11 KATA
		// left
		-0.5, -0.5, 9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 12 KIBA
		-0.5, -0.5,  10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 13 KABA
		-0.5,  5.5,  10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 14 KATA
		-0.5,  5.5, 9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 15 KITA
		// upper
		0.5, 5.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16 
		-0.5, 5.5,  10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		-0.5, 5.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		0.5, 5.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19
		// bottom
		-0.5, -0.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		0.5, -0.5, 9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		0.5, -0.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f,// 22
		-0.5, -0.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
		//TIANG KANAN
		// front
		4.5, -0.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 24 KIBA
		5.5, -0.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f, // 25 KABA
		5.5,  5.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f, // 26 KATA
		4.5,  5.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 27 KITA
		// right
		5.5,  5.5,  10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 28 KITA
		5.5,  5.5, 9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 29 KATA
		5.5, -0.5, 9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 30 KABA
		5.5, -0.5,  10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 31 KIBA
		// back
		4.5, -0.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 32  KABA
		5.5,  -0.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 33 KIBA
		5.5,   5.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 34 KITA
		4.5,  5.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 35  KATA
		// left
		4.5, -0.5, 9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 36 KIBA
		4.5, -0.5,  10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 37 KABA
		4.5,  4.5,  10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 38 KATA
		4.5,  4.5, 9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 39 KITA
		// upper
		5.5, 5.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 40
		4.5, 5.5, 10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 41
		4.5, 5.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 42
		5.5, 5.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 43
		// bottom
		4.5, -0.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 44
		5.5, -0.5, 9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 45
		5.5, -0.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 46
		4.5, -0.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 47
		//TIANG ATAP 
		// upper
		4.5, 5.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 48
		0.5, 5.5, 10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 49
		0.5, 5.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 50
		4.5, 5.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 51
		// bottom
		0.5, 4.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 52
		4.5, 4.5, 9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 53
		4.5, 4.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 54
		0.5, 4.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 55
		// front
		0.5, 4.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 56		KIBA
		4.5, 4.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 57	KABA
		4.5,  5.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 58	KATA
		0.5,  5.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 59	KITA
		// back
		0.5, 4.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 60
		4.5,  4.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 61
		4.5,   5.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 62
		0.5,  5.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 63
	};

	// buat gabungin vertex
	unsigned int indices1[] = {
		//tiang kiri
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang kanan
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//atap tiang
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63 // back
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);

	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredPole2(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO6);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredMidPole2()
{
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tiang_besar.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices1[] = {
		// TIANG KIRI
		//front
		0.5, 5.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f,  // 0 KANAN BAWAH
		-0.5, 5.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 1 KIRI BAWAH
		0.5,  15.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f,// 2 KIRI ATAS
		1.5,  15.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3 KANAN ATAS
		// right
		1.5,  15.5,  10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4 KIRI ATAS
		1.5,  15.5, 9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5 KANAN ATAS
		0.5, 5.5, 9.5, 1, 1, 1.0f,  0.0f,  0.0f,  // 6 KANAN BAWAH
		0.5, 5.5,  10.5, 0, 1, 1.0f,  0.0f,  0.0f,  // 7 KIRI BAWAH
		// back
		-0.5, 5.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 8 KANAN BAWAH
		0.5,  5.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 9 KIRI BAWAH
		1.5,   15.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10 KIRI ATAS
		0.5,  15.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 11 KANAN ATAS
		// left X, Y, Z
		-0.5, 5.5, 9.5, 0, 0, -1.0f,  0.0f,  0.0f,  // 12 KIRI BAWAH,	
		-0.5, 5.5,  10.5, 1, 0,	-1.0f,  0.0f,  0.0f, // 13 KANAN BAWAH,	
		0.5,  15.5,  10.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14 KANAN ATAS, 
		0.5,  15.5, 9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 15 KIRI ATAS,	
		// upper
		1.5, 15.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16
		0.5, 15.5,  10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		0.5, 15.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		1.5, 15.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19
		// bottom
		-0.5, 5.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		0.5, 5.5, 9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 21
		0.5, 5.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		-0.5, 5.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
		//TIANG KANAN
		// front
		4.5, 5.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 24 KIBA
		5.5, 5.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f, // 25 KABA
		4.5,  15.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f, // 26 KATA
		3.5,  15.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 27 KITA
		// right
		4.5,  15.5,  10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 28 KITA
		4.5,  15.5, 9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 29 KATA
		5.5, 5.5, 9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 30 KABA
		5.5, 5.5,  10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 31 KIBA
		// back
		4.5, 5.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 32		KABA
		5.5,  5.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 33	KIBA
		4.5,   15.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 34	KITA
		3.5,  15.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 35	KATA
		// left
		4.5, 5.5, 9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 36		KIBA
		4.5, 5.5,  10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 37		KABA
		3.5,  15.5,  10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 38	KATA
		3.5,  15.5, 9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 39	KITA
		// upper
		3.5, 15.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 40
		4.5, 15.5, 10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 41
		4.5, 15.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 42
		3.5, 15.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 43
		// bottom
		5.5, 5.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 44
		4.5, 5.5, 9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 45
		4.5, 5.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 46
		5.5, 5.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 47
		//TIANG ATAP 
		// upper
		3.5, 15.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 48
		1.5, 15.5, 10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 49
		1.5, 15.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f,  // 50
		3.5, 15.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 51
		// bottom
		1, 14.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 52
		4, 14.5, 9.5, 1, 0, 0.0f,  -1.0f,  0.0f, // 53
		4, 14.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 54
		1, 14.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 55
		// front
		1.4, 14.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 56	KIBA
		3.6, 14.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f,  // 57	KABA
		3.5,  15.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 58	KATA
		1.5,  15.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 59	KITA
		// back
		1.4, 14.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 60
		3.6,  14.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 61
		3.5,   15.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 62
		1.5,  15.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 63
	};

	// buat gabungin vertex
	unsigned int indices1[] = {
		//tiang kiri
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang kanan
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//atap tiang
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63 // back
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);

	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredMidPole2(GLuint shader) {
	UseShader(shader);
	glBindVertexArray(VAO7);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTipPole2() {
	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tiang_besar.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices1[] = {
		// TIANG KIRI
		//front
		0.5, 15.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0 KABA
		1.5, 15.5, 10.5, 1, 0,  0.0f,  0.0f,  1.0f, // 1 KIBA
		1.5,  23.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f,   // 2 KITA
		0.5,  23.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3 KATA
		// right
		1.5,  23.5, 10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4 KITA
		1.5,  23.5, 9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5 KATA
		1.5, 15.5, 9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6 KABA
		1.5, 15.5,  10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7 KIBA
		// back
		0.5, 15.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 8  KABA
		1.5,  15.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 9  KIBA
		1.5,   23.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 10 KITA
		0.5,  23.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 11 KATA
		// left
		0.5, 15.5, 9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 12 KIBA
		0.5, 15.5,  10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 13 KABA
		0.5,  23.5,  10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 14 KATA
		0.5,  23.5, 9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 15 KITA
		// upper
		1.5, 23.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 16 
		0.5, 23.5,  10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 17
		0.5, 23.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 18
		1.5, 23.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 19
		// bottom
		0.5, 15.5, 9.5, 0, 0,0.0f,  -1.0f,  0.0f, // 20
		1.5, 15.5, 9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 21
		1.5, 15.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 22
		0.5, 15.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
		//TIANG KANAN
		// front
		3.5, 15.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 24 KIBA
		4.5, 15.5, 10.5, 1, 0, 0.0f,  0.0f,  1.0f, // 25 KABA
		4.5,  23.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f, // 26 KATA
		3.5,  23.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 27 KITA
		// right
		4.5,  23.5,  10.5, 0, 0, 1.0f,  0.0f,  0.0f, // 28 KITA
		4.5,  23.5, 9.5, 1, 0, 1.0f,  0.0f,  0.0f, // 29 KATA
		4.5, 15.5, 9.5, 1, 1, 1.0f,  0.0f,  0.0f, // 30 KABA
		4.5, 15.5,  10.5, 0, 1, 1.0f,  0.0f,  0.0f, // 31 KIBA
		// back
		3.5, 15.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 32  KABA
		4.5,  15.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 33 KIBA
		4.5,   23.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 34 KITA
		3.5,  23.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 35  KATA
		// left
		3.5, 15.5, 9.5, 0, 0, -1.0f,  0.0f,  0.0f,// 36 KIBA
		3.5, 15.5,  10.5, 1, 0, -1.0f,  0.0f,  0.0f,// 37 KABA
		3.5, 23.5,  10.5, 1, 1, -1.0f,  0.0f,  0.0f,// 38 KATA
		3.5,  23.5, 9.5, 0, 1, -1.0f,  0.0f,  0.0f,// 39 KITA
		// upper
		4.5, 23.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 40
		3.5, 23.5, 10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 41
		3.5, 23.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 42
		4.5, 23.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 43
		// bottom
		3.5, 22.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f,// 44
		4.5, 22.5, 9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 45
		4.5, 22.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 46
		3.5, 22.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 47
		//TIANG ATAP 
		// upper
		3.5, 23.5,  10.5, 0, 0, 0.0f,  1.0f,  0.0f,  // 48
		1.5, 23.5, 10.5, 1, 0, 0.0f,  1.0f,  0.0f, // 49
		1.5, 23.5, 9.5, 1, 1, 0.0f,  1.0f,  0.0f, // 50
		3.5, 23.5, 9.5, 0, 1, 0.0f,  1.0f,  0.0f,  // 51
		// bottom
		1.5, 22.5, 9.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 52
		3.5, 22.5, 9.5, 1, 0,  0.0f,  -1.0f,  0.0f,// 53
		3.5, 22.5,  10.5, 1, 1, 0.0f,  -1.0f,  0.0f, // 54
		1.5, 22.5,  10.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 55
		// front
		1.5, 22.5, 10.5, 0, 0, 0.0f,  0.0f,  1.0f, // 56	KIBA
		3.5, 22.5, 10.5, 1, 0,  0.0f,  0.0f,  1.0f, // 57	KABA
		3.5,  23.5, 10.5, 1, 1, 0.0f,  0.0f,  1.0f,  // 58	KATA
		1.5,  23.5, 10.5, 0, 1, 0.0f,  0.0f,  1.0f, // 59	KITA
		// back
		1.5, 22.5, 9.5, 0, 0, 0.0f,  0.0f,  -1.0f,// 60
		3.5,  22.5, 9.5, 1, 0, 0.0f,  0.0f,  -1.0f,// 61
		3.5,   23.5, 9.5, 1, 1, 0.0f,  0.0f,  -1.0f,// 62
		1.5,  23.5, 9.5, 0, 1, 0.0f,  0.0f,  -1.0f,// 63
	};

	// buat gabungin vertex
	unsigned int indices1[] = {
		//tiang kiri
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang kanan
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//atap tiang
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63 // back
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);

	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredTipPole2(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO8);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//////////////////////////////////////
////// INI KERJAANNYA IRSYAD ////////
/////////////////////////////////////
//Sebelah Kiri//
void Demo::BuildColoredTiang1() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices1[] = {
		// format position, tex coords
		// TIANG 1
		 //front
		0.7, 8.5, 2.5, 0, 0,  // 0
		0.5, 8.5, 2.5, 1, 0,   // 1
		0.5, 10.5, 2.5, 1, 1,   // 2
		0.7, 10.5, 2.5, 0, 1,  // 3
		// right
		0.5,  10.5,  2.5, 0, 0,  // 4
		0.5,  10.5, -2.0, 1, 0,  // 5
		0.5, 8.5, -2.0, 1, 1,  // 6
		0.5, 8.5,  2.5, 0, 1,  // 7
		// back
		0.7, 8.5, -2.0, 0, 0, // 8 
		0.5, 8.5, -2.0, 1, 0, // 9
		0.5, 10.5, -2.0, 1, 1, // 10
		0.7, 10.5, -2.0, 0, 1, // 11
		// left
		0.7, 8.5, -2.0, 0, 0, // 12
		0.7, 8.5,  2.5, 1, 0, // 13
		0.7, 10.5, 2.5, 1, 1, // 14
		0.7, 10.5, -2.0, 0, 1, // 15
		// upper
		0.5, 10.5, 2.5, 0, 0,   // 16
		0.7, 10.5, 2.5, 1, 0,  // 17
		0.7, 10.5, -2.0, 1, 1,  // 18
		0.5, 10.5, -2.0, 0, 1,   // 19
		// bottom
		0.7, 8.5, -2.0, 0, 0, // 20
		0.5, 8.5, -2.0, 1, 0,  // 21
		0.5, 8.5,  2.5, 1, 1,  // 22
		0.7, 8.5,  2.5, 0, 1, // 23
		//TIANG 2
		// front
		0.7, 8.5, 3.5, 0, 0,  // 24 ,,kiba,
		0.5, 8.5, 3.5, 1, 0,  // 25 ,,kaba,
		0.5, 10.5, 3.5, 1, 1,  // 26 ,,kaat,
		0.7, 10.5, 3.5, 0, 1,  // 27 ,,kiat
		// right
		0.5,  10.5, 3.5, 0, 0,  // 28
		0.5,  10.5, 4.0, 1, 0,  // 29
		0.5, 8.5, 4.0, 1, 1,  // 30
		0.5, 8.5, 3.5, 0, 1,  // 31
		// back
		0.7, 8.5, 4.0, 0, 0, // 32
		0.5, 8.5, 4.0, 1, 0, // 33
		0.5, 10.5, 4.0, 1, 1, // 34
		0.7, 10.5, 4.0, 0, 1, // 35
		// left
		0.7, 8.5, 4.0, 0, 0, // 36
		0.7, 8.5, 3.5, 1, 0, // 37
		0.7, 10.5,3.5, 1, 1, // 38
		0.7, 10.5,4.0, 0, 1, // 39
		// upper
		0.5, 10.5, 3.5, 0, 0,   // 40
		0.7, 10.5, 3.5, 1, 0,  // 41
		0.7, 10.5, 4.0, 1, 1,  // 42
		0.5, 10.5, 4.0, 0, 1,   // 43
		// bottom
		0.7, 8.5, 4.0, 0, 0, // 44
		0.5, 8.5, 4.0, 1, 0,  // 45
		0.5, 8.5, 3.5, 1, 1,  // 46
		0.7, 8.5, 3.5, 0, 1, // 47
		//TIANG 3
		// front
		0.7, 7.5, 5.0, 0, 0,  // 48 ,,kiba,
		0.5, 7.5, 5.0, 1, 0,  // 49 ,,kaba,
		0.5, 9.5, 5.0, 1, 1,  // 50 ,,kaat,
		0.7, 9.5, 5.0, 0, 1,  // 51 ,,kiat
		// right
		0.5,  9.5, 5.0, 0, 0,  // 52
		0.5,  9.5, 5.5, 1, 0,  // 53
		0.5, 7.5, 5.5, 1, 1,  // 54
		0.5, 7.5,  5.0, 0, 1,  // 55
		// back
		0.7, 7.5, 5.5, 0, 0, // 56
		0.5, 7.5, 5.5, 1, 0, // 57
		0.5,  9.5, 5.5, 1, 1, // 58
		0.7,  9.5, 5.5, 0, 1, // 59
		// left
		0.7, 7.5, 5.5, 0, 0, // 60
		0.7, 7.5, 5.0, 1, 0, // 61
		0.7, 9.5, 5.0, 1, 1, // 62
		0.7, 9.5, 5.5, 0, 1, // 63
		// upper
		0.5, 9.5,  5.0, 0, 0,   // 64
		0.7, 9.5, 5.0, 1, 0,  // 65
		0.7, 9.5, 5.5, 1, 1,  // 66
		0.5,9.5, 5.5, 0, 1,   // 67
		// bottom
		0.7, 7.5, 5.5, 0, 0, // 68
		0.5, 7.5, 5.5, 1, 0,  // 69
		0.5, 7.5, 5.0, 1, 1,  // 70
		0.7, 7.5, 5.0, 0, 1, // 71
		//TIANG 4
		// front
		0.7, 7.5, 6.5, 0, 0,  // 72 ,,kiba,
		0.5, 7.5, 6.5, 1, 0,  // 73 ,,kaba,
		0.5, 9.5, 6.5, 1, 1,  // 74 ,,kaat,
		0.7, 9.5, 6.5, 0, 1,  // 75 ,,kiat
		// right
		0.5,  9.5, 6.5, 0, 0,  // 76
		0.5,  9.5, 7.0, 1, 0,  // 77
		0.5, 7.5, 7.0, 1, 1,  // 78
		0.5, 7.5, 6.5, 0, 1,  // 79
		// back
		0.7, 7.5, 7.0, 0, 0, // 80
		0.5, 7.5, 7.0, 1, 0, // 81
		0.5, 9.5,7.0, 1, 1, // 82
		0.7, 9.5,7.0, 0, 1, // 83
		// left
		0.7, 7.5, 7.0, 0, 0, // 84
		0.7, 7.5, 6.5, 1, 0, // 85
		0.7, 9.5, 6.5, 1, 1, // 86
		0.7, 9.5, 7.0, 0, 1, // 87
		// upper
		0.5, 9.5, 6.5, 0, 0,   // 88
		0.7, 9.5, 6.5, 1, 0,  // 89
		0.7, 9.5, 7.0, 1, 1,  // 90
		0.5, 9.5,7.0, 0, 1,   // 91
		// bottom
		0.7, 7.5, 7.0, 0, 0, // 92
		0.5, 7.5, 7.0, 1, 0,  // 93
		0.5, 7.5, 6.5, 1, 1,  // 94
		0.7, 7.5, 6.5, 0, 1, // 95
		//TIANG 5
		// front
		0.7, 6.5, 8.0, 0, 0,  // 96 ,,kiba,
		0.5, 6.5, 8.0, 1, 0,  // 97 ,,kaba,
		0.5, 9.5, 8.0, 1, 1,  // 98 ,,kaat,
		0.7, 9.5, 8.0, 0, 1,  // 99 ,,kiat
		// right
		0.5,  9.5, 8.0, 0, 0,  // 100
		0.5,  9.5, 8.5, 1, 0,  // 101
		0.5, 6.5, 8.5, 1, 1,  // 102
		0.5, 6.5, 8.0, 0, 1,  // 103
		// back
		0.7, 6.5, 8.5, 0, 0, // 104
		0.5, 6.5, 8.5, 1, 0, // 105
		0.5,  9.5, 8.5, 1, 1, // 106
		0.7,  9.5, 8.5, 0, 1, // 107
		// left
		0.7, 6.5, 8.5, 0, 0, // 108
		0.7, 6.5, 8.0, 1, 0, // 109
		0.7,  9.5,8.0, 1, 1, // 110
		0.7,  9.5, 8.5, 0, 1, // 111
		// upper
		0.5, 9.5,  8.0, 0, 0,   // 112
		0.7, 9.5, 8.0, 1, 0,  // 113
		0.7, 9.5, 8.5, 1, 1,  // 114
		0.5, 9.5, 8.5, 0, 1,   // 115
		// bottom
		0.7, 6.5, 8.5, 0, 0, // 116
		0.5, 6.5,8.5, 1, 0,  // 117
		0.5, 6.5, 8.0, 1, 1,  // 118
		0.7, 6.5, 8.0, 0, 1, // 119
		//TIANG 6
		// front
		0.7, 6.5, 11.5, 0, 0,  // 96 ,,kiba,
		0.5, 6.5, 11.5, 1, 0,  // 97 ,,kaba,
		0.5, 8.5, 11.5, 1, 1,  // 98 ,,kaat,
		0.7, 8.5, 11.5, 0, 1,  // 99 ,,kiat
		// right
		0.5,  8.5, 11.5, 0, 0,  // 100
		0.5,  8.5, 12.0, 1, 0,  // 101
		0.5, 6.5, 12.0, 1, 1,  // 102
		0.5, 6.5, 11.5, 0, 1,  // 103
		// back
		0.7, 6.5, 12.0, 0, 0, // 104
		0.5, 6.5, 12.0, 1, 0, // 105
		0.5, 8.5, 12.0, 1, 1, // 106
		0.7, 8.5, 12.0, 0, 1, // 107
		// left
		0.7, 6.5, 12.0, 0, 0, // 108
		0.7, 6.5, 11.5, 1, 0, // 109
		0.7, 8.5, 11.5, 1, 1, // 110
		0.7, 8.5, 12.0, 0, 1, // 111
		// upper
		0.5, 8.5, 11.5, 0, 0,   // 112
		0.7, 8.5, 11.5, 1, 0,  // 113
		0.7, 8.5, 12.0, 1, 1,  // 114
		0.5, 8.5, 12.0, 0, 1,   // 115
		// bottom
		0.7, 6.5, 12.0, 0, 0, // 116
		0.5, 6.5, 12.0, 1, 0,  // 117
		0.5, 6.5, 11.5, 1, 1,  // 118
		0.7, 6.5, 11.5, 0, 1, // 119
		//TIANG 7
		// front
		0.7, 5.5, 12.0, 0, 0,  // 96 ,,kiba,
		0.5, 5.5, 12.0, 1, 0,  // 97 ,,kaba,
		0.5, 7.5, 12.0, 1, 1,  // 98 ,,kaat,
		0.7, 7.5, 12.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 7.5, 12.0, 0, 0,  // 100
		0.5, 7.5, 12.5, 1, 0,  // 101
		0.5, 5.5, 12.5, 1, 1,  // 102
		0.5, 5.5, 12.0, 0, 1,  // 103
		// back
		0.7, 5.5, 12.5, 0, 0, // 104
		0.5, 5.5, 12.5, 1, 0, // 105
		0.5, 7.5, 12.5, 1, 1, // 106
		0.7, 7.5, 12.5, 0, 1, // 107
		// left
		0.7, 5.5, 12.5, 0, 0, // 108
		0.7, 5.5, 12.0, 1, 0, // 109
		0.7, 7.5, 12.0, 1, 1, // 110
		0.7, 7.5, 12.5, 0, 1, // 111
		// upper
		0.5, 7.5, 12.0, 0, 0,   // 112
		0.7, 7.5, 12.0, 1, 0,  // 113
		0.7, 7.5, 12.5, 1, 1,  // 114
		0.5, 7.5, 12.5, 0, 1,   // 115
		// bottom
		0.7, 5.5, 12.5, 0, 0, // 116
		0.5, 5.5, 12.5, 1, 0,  // 117
		0.5, 5.5, 12.0, 1, 1,  // 118
		0.7, 5.5, 12.0, 0, 1, // 119
		//TIANG 8
		// front
		0.7, 5.5, 13.5, 0, 0,  // 96 ,,kiba,
		0.5, 5.5, 13.5, 1, 0,  // 97 ,,kaba,
		0.5, 7.5, 13.5, 1, 1,  // 98 ,,kaat,
		0.7, 7.5, 13.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 7.5, 13.5, 0, 0,  // 100
		0.5, 7.5, 14.0, 1, 0,  // 101
		0.5, 5.5, 14.0, 1, 1,  // 102
		0.5, 5.5, 13.5, 0, 1,  // 103
		// back
		0.7, 5.5, 14.0, 0, 0, // 104
		0.5, 5.5, 14.0, 1, 0, // 105
		0.5, 7.5, 14.0, 1, 1, // 106
		0.7, 7.5, 14.0, 0, 1, // 107
		// left
		0.7, 5.5, 14.0, 0, 0, // 108
		0.7, 5.5, 13.5, 1, 0, // 109
		0.7, 7.5, 13.5, 1, 1, // 110
		0.7, 7.5, 14.0, 0, 1, // 111
		// upper
		0.5, 7.5, 13.5, 0, 0,   // 112
		0.7, 7.5, 13.5, 1, 0,  // 113
		0.7, 7.5, 14.0, 1, 1,  // 114
		0.5, 7.5, 14.0, 0, 1,   // 115
		// bottom
		0.7, 5.5, 14.0, 0, 0, // 116
		0.5, 5.5, 14.0, 1, 0,  // 117
		0.5, 5.5, 13.5, 1, 1,  // 118
		0.7, 5.5, 13.5, 0, 1, // 119
		//TIANG 9
		// front
		0.7, 5.5, 15.0, 0, 0,  // 96 ,,kiba,
		0.5, 5.5, 15.0, 1, 0,  // 97 ,,kaba,
		0.5, 7.5, 15.0, 1, 1,  // 98 ,,kaat,
		0.7, 7.5, 15.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 7.5, 15.0, 0, 0,  // 100
		0.5, 7.5, 15.5, 1, 0,  // 101
		0.5, 5.5, 15.5, 1, 1,  // 102
		0.5, 5.5, 15.0, 0, 1,  // 103
		// back
		0.7, 5.5, 15.5, 0, 0, // 104
		0.5, 5.5, 15.5, 1, 0, // 105
		0.5, 7.5, 15.5, 1, 1, // 106
		0.7, 7.5, 15.5, 0, 1, // 107
		// left
		0.7, 5.5, 15.5, 0, 0, // 108
		0.7, 5.5, 15.0, 1, 0, // 109
		0.7, 7.5, 15.0, 1, 1, // 110
		0.7, 7.5, 15.5, 0, 1, // 111
		// upper
		0.5, 7.5, 15.0, 0, 0,   // 112
		0.7, 7.5, 15.0, 1, 0,  // 113
		0.7, 7.5, 15.5, 1, 1,  // 114
		0.5, 7.5, 15.5, 0, 1,   // 115
		// bottom
		0.7, 5.5, 15.5, 0, 0, // 116
		0.5, 5.5, 15.5, 1, 0,  // 117
		0.5, 5.5, 15.0, 1, 1,  // 118
		0.7, 5.5, 15.0, 0, 1, // 119
		//TIANG 10
		// front
		0.7, 4.5, 16.5, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, 16.5, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, 16.5, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, 16.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, 16.5, 0, 0,  // 100
		0.5, 6.5, 17.0, 1, 0,  // 101
		0.5, 4.5, 17.0, 1, 1,  // 102
		0.5, 4.5, 16.5, 0, 1,  // 103
		// back
		0.7, 4.5, 17.0, 0, 0, // 104
		0.5, 4.5, 17.0, 1, 0, // 105
		0.5, 6.5, 17.0, 1, 1, // 106
		0.7, 6.5, 17.0, 0, 1, // 107
		// left
		0.7, 4.5, 17.0, 0, 0, // 108
		0.7, 4.5, 16.5, 1, 0, // 109
		0.7, 6.5, 16.5, 1, 1, // 110
		0.7, 6.5, 17.0, 0, 1, // 111
		// upper
		0.5, 6.5, 16.5, 0, 0,   // 112
		0.7, 6.5, 16.5, 1, 0,  // 113
		0.7, 6.5, 17.0, 1, 1,  // 114
		0.5, 6.5, 17.0, 0, 1,   // 115
		// bottom
		0.7, 4.5, 17.0, 0, 0, // 116
		0.5, 4.5, 17.0, 1, 0,  // 117
		0.5, 4.5, 16.5, 1, 1,  // 118
		0.7, 4.5, 16.5, 0, 1, // 119
		//TIANG 11
		// front
		0.7, 4.5, 18.0, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, 18.0, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, 18.0, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, 18.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, 18.0, 0, 0,  // 100
		0.5, 6.5, 18.5, 1, 0,  // 101
		0.5, 4.5, 18.5, 1, 1,  // 102
		0.5, 4.5, 18.0, 0, 1,  // 103
		// back
		0.7, 4.5, 18.5, 0, 0, // 104
		0.5, 4.5, 18.5, 1, 0, // 105
		0.5, 6.5, 18.5, 1, 1, // 106
		0.7, 6.5, 18.5, 0, 1, // 107
		// left
		0.7, 4.5, 18.5, 0, 0, // 108
		0.7, 4.5, 18.0, 1, 0, // 109
		0.7, 6.5, 18.0, 1, 1, // 110
		0.7, 6.5, 18.5, 0, 1, // 111
		// upper
		0.5, 6.5, 18.0, 0, 0,   // 112
		0.7, 6.5, 18.0, 1, 0,  // 113
		0.7, 6.5, 18.5, 1, 1,  // 114
		0.5, 6.5, 18.5, 0, 1,   // 115
		// bottom
		0.7, 4.5, 18.5, 0, 0, // 116
		0.5, 4.5, 18.5, 1, 0,  // 117
		0.5, 4.5, 18.0, 1, 1,  // 118
		0.7, 4.5, 18.0, 0, 1, // 119
		//TIANG 12
		// front
		0.7, 4.5, 19.5, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, 19.5, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, 19.5, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, 19.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, 19.5, 0, 0,  // 100
		0.5, 6.5, 20.0, 1, 0,  // 101
		0.5, 4.5, 20.0, 1, 1,  // 102
		0.5, 4.5, 19.5, 0, 1,  // 103
		// back
		0.7, 4.5, 20.0, 0, 0, // 104
		0.5, 4.5, 20.0, 1, 0, // 105
		0.5, 6.5, 20.0, 1, 1, // 106
		0.7, 6.5, 20.0, 0, 1, // 107
		// left
		0.7, 4.5, 20.0, 0, 0, // 108
		0.7, 4.5, 19.5, 1, 0, // 109
		0.7, 6.5, 19.5, 1, 1, // 110
		0.7, 6.5, 20.0, 0, 1, // 111
		// upper
		0.5, 6.5, 19.5, 0, 0,   // 112
		0.7, 6.5, 19.5, 1, 0,  // 113
		0.7, 6.5, 20.0, 1, 1,  // 114
		0.5, 6.5, 20.0, 0, 1,   // 115
		// bottom
		0.7, 4.5, 20.0, 0, 0, // 116
		0.5, 4.5, 20.0, 1, 0,  // 117
		0.5, 4.5, 19.5, 1, 1,  // 118
		0.7, 4.5, 19.5, 0, 1, // 119
		//TIANG 13
		// front
		0.7, 4.5, 21.0, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, 21.0, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, 21.0, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, 21.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, 21.0, 0, 0,  // 100
		0.5, 6.5, 21.5, 1, 0,  // 101
		0.5, 4.5, 21.5, 1, 1,  // 102
		0.5, 4.5, 21.0, 0, 1,  // 103
		// back
		0.7, 4.5, 21.5, 0, 0, // 104
		0.5, 4.5, 21.5, 1, 0, // 105
		0.5, 6.5, 21.5, 1, 1, // 106
		0.7, 6.5, 21.5, 0, 1, // 107
		// left
		0.7, 4.5, 21.5, 0, 0, // 108
		0.7, 4.5, 21.0, 1, 0, // 109
		0.7, 6.5, 21.0, 1, 1, // 110
		0.7, 6.5, 21.5, 0, 1, // 111
		// upper
		0.5, 6.5, 21.0, 0, 0,   // 112
		0.7, 6.5, 21.0, 1, 0,  // 113
		0.7, 6.5, 21.5, 1, 1,  // 114
		0.5, 6.5, 21.5, 0, 1,   // 115
		// bottom
		0.7, 4.5, 21.5, 0, 0, // 116
		0.5, 4.5, 21.5, 1, 0,  // 117
		0.5, 4.5, 21.0, 1, 1,  // 118
		0.7, 4.5, 21.0, 0, 1, // 119
		//TIANG 14
		// front
		0.7, 4.5, 22.5, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, 22.5, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, 22.5, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, 22.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, 22.5, 0, 0,  // 100
		0.5, 6.5, 23.0, 1, 0,  // 101
		0.5, 4.5, 23.0, 1, 1,  // 102
		0.5, 4.5, 22.5, 0, 1,  // 103
		// back
		0.7, 4.5, 23.0, 0, 0, // 104
		0.5, 4.5, 23.0, 1, 0, // 105
		0.5, 6.5, 23.0, 1, 1, // 106
		0.7, 6.5, 23.0, 0, 1, // 107
		// left
		0.7, 4.5, 23.0, 0, 0, // 108
		0.7, 4.5, 22.5, 1, 0, // 109
		0.7, 6.5, 22.5, 1, 1, // 110
		0.7, 6.5, 23.0, 0, 1, // 111
		// upper
		0.5, 6.5, 22.5, 0, 0,   // 112
		0.7, 6.5, 22.5, 1, 0,  // 113
		0.7, 6.5, 23.0, 1, 1,  // 114
		0.5, 6.5, 23.0, 0, 1,   // 115
		// bottom
		0.7, 4.5, 23.0, 0, 0, // 116
		0.5, 4.5, 23.0, 1, 0,  // 117
		0.5, 4.5, 22.5, 1, 1,  // 118
		0.7, 4.5, 22.5, 0, 1, // 119
		//TIANG 15
		// front
		0.7, 3.5, 24.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 24.0, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, 24.0, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, 24.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, 24.0, 0, 0,  // 100
		0.5, 5.5, 24.5, 1, 0,  // 101
		0.5, 3.5, 24.5, 1, 1,  // 102
		0.5, 3.5, 24.0, 0, 1,  // 103
		// back
		0.7, 3.5, 24.5, 0, 0, // 104
		0.5, 3.5, 24.5, 1, 0, // 105
		0.5, 5.5, 24.5, 1, 1, // 106
		0.7, 5.5, 24.5, 0, 1, // 107
		// left
		0.7, 3.5, 24.5, 0, 0, // 108
		0.7, 3.5, 24.0, 1, 0, // 109
		0.7, 5.5, 24.0, 1, 1, // 110
		0.7, 5.5, 24.5, 0, 1, // 111
		// upper
		0.5, 5.5, 24.0, 0, 0,   // 112
		0.7, 5.5, 24.0, 1, 0,  // 113
		0.7, 5.5, 24.5, 1, 1,  // 114
		0.5, 5.5, 24.5, 0, 1,   // 115
		// bottom
		0.7, 3.5, 24.5, 0, 0, // 116
		0.5, 3.5, 24.5, 1, 0,  // 117
		0.5, 3.5, 24.0, 1, 1,  // 118
		0.7, 3.5, 24.0, 0, 1, // 119
		//TIANG 16
		// front
		0.7, 3.5, 25.5, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 25.5, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, 25.5, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, 25.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, 25.5, 0, 0,  // 100
		0.5, 5.5, 26.0, 1, 0,  // 101
		0.5, 3.5, 26.0, 1, 1,  // 102
		0.5, 3.5, 25.5, 0, 1,  // 103
		// back
		0.7, 3.5, 26.0, 0, 0, // 104
		0.5, 3.5, 25.5, 1, 0, // 105
		0.5, 5.5, 25.5, 1, 1, // 106
		0.7, 5.5, 26.0, 0, 1, // 107
		// left
		0.7, 3.5, 26.0, 0, 0, // 108
		0.7, 3.5, 25.5, 1, 0, // 109
		0.7, 5.5, 25.5, 1, 1, // 110
		0.7, 5.5, 26.0, 0, 1, // 111
		// upper
		0.5, 5.5, 25.5, 0, 0,   // 112
		0.7, 5.5, 25.5, 1, 0,  // 113
		0.7, 5.5, 26.0, 1, 1,  // 114
		0.5, 5.5, 26.0, 0, 1,   // 115
		// bottom
		0.7, 3.5, 26.0, 0, 0, // 116
		0.5, 3.5, 26.0, 1, 0,  // 117
		0.5, 3.5, 25.5, 1, 1,  // 118
		0.7, 3.5, 25.5, 0, 1, // 119
		//TIANG 17
		// front
		0.7, 3.5, 27.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 27.0, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, 27.0, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, 27.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, 27.0, 0, 0,  // 100
		0.5, 5.5, 27.5, 1, 0,  // 101
		0.5, 3.5, 27.5, 1, 1,  // 102
		0.5, 3.5, 27.0, 0, 1,  // 103
		// back
		0.7, 3.5, 27.5, 0, 0, // 104
		0.5, 3.5, 27.5, 1, 0, // 105
		0.5, 5.5, 27.5, 1, 1, // 106
		0.7, 5.5, 27.5, 0, 1, // 107
		// left
		0.7, 3.5, 27.5, 0, 0, // 108
		0.7, 3.5, 27.0, 1, 0, // 109
		0.7, 5.5, 27.0, 1, 1, // 110
		0.7, 5.5, 27.5, 0, 1, // 111
		// upper
		0.5, 5.5, 27.0, 0, 0,   // 112
		0.7, 5.5, 27.0, 1, 0,  // 113
		0.7, 5.5, 27.5, 1, 1,  // 114
		0.5, 5.5, 27.5, 0, 1,   // 115
		// bottom
		0.7, 3.5, 27.5, 0, 0, // 116
		0.5, 3.5, 27.5, 1, 0,  // 117
		0.5, 3.5, 27.0, 1, 1,  // 118
		0.7, 3.5, 27.0, 0, 1, // 119
		//TIANG 18
		// front
		0.7, 3.5, 28.5, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 28.5, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, 28.5, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, 28.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, 28.5, 0, 0,  // 100
		0.5, 5.5, 29.0, 1, 0,  // 101
		0.5, 3.5, 29.0, 1, 1,  // 102
		0.5, 3.5, 28.5, 0, 1,  // 103
		// back
		0.7, 3.5, 29.0, 0, 0, // 104
		0.5, 3.5, 29.0, 1, 0, // 105
		0.5, 5.5, 29.0, 1, 1, // 106
		0.7, 5.5, 29.0, 0, 1, // 107
		// left
		0.7, 3.5, 29.0, 0, 0, // 108
		0.7, 3.5, 28.5, 1, 0, // 109
		0.7, 5.5, 28.5, 1, 1, // 110
		0.7, 5.5, 29.0, 0, 1, // 111
		// upper
		0.5, 5.5, 28.5, 0, 0,   // 112
		0.7, 5.5, 28.5, 1, 0,  // 113
		0.7, 5.5, 29.0, 1, 1,  // 114
		0.5, 5.5, 29.0, 0, 1,   // 115
		// bottom
		0.7, 3.5, 29.0, 0, 0, // 116
		0.5, 3.5, 29.0, 1, 0,  // 117
		0.5, 3.5, 28.5, 1, 1,  // 118
		0.7, 3.5, 28.5, 0, 1, // 119
		//TIANG 19
		// front
		0.7, 3.5, 30.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 30.0, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, 30.0, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, 30.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, 30.0, 0, 0,  // 100
		0.5, 5.5, 30.5, 1, 0,  // 101
		0.5, 3.5, 30.5, 1, 1,  // 102
		0.5, 3.5, 30.0, 0, 1,  // 103
		// back
		0.7, 3.5, 30.5, 0, 0, // 104
		0.5, 3.5, 30.5, 1, 0, // 105
		0.5, 5.5, 30.5, 1, 1, // 106
		0.7, 5.5, 30.5, 0, 1, // 107
		// left
		0.7, 3.5, 30.5, 0, 0, // 108
		0.7, 3.5, 30.0, 1, 0, // 109
		0.7, 5.5, 30.0, 1, 1, // 110
		0.7, 5.5, 30.5, 0, 1, // 111
		// upper
		0.5, 5.5, 30.0, 0, 0,   // 112
		0.7, 5.5, 30.0, 1, 0,  // 113
		0.7, 5.5, 30.5, 1, 1,  // 114
		0.5, 5.5, 30.5, 0, 1,   // 115
		// bottom
		0.7, 3.5, 30.5, 0, 0, // 116
		0.5, 3.5, 30.5, 1, 0,  // 117
		0.5, 3.5, 30.0, 1, 1,  // 118
		0.7, 3.5, 30.0, 0, 1, // 119
		//TIANG 20
		// front
		0.7, 3.5, 31.5, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 31.5, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, 31.5, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, 31.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, 31.5, 0, 0,  // 100
		0.5, 5.5, 32.0, 1, 0,  // 101
		0.5, 3.5, 32.0, 1, 1,  // 102
		0.5, 3.5, 31.5, 0, 1,  // 103
		// back
		0.7, 3.5, 32.0, 0, 0, // 104
		0.5, 3.5, 32.0, 1, 0, // 105
		0.5, 5.5, 32.0, 1, 1, // 106
		0.7, 5.5, 32.0, 0, 1, // 107
		// left
		0.7, 3.5, 32.0, 0, 0, // 108
		0.7, 3.5, 31.5, 1, 0, // 109
		0.7, 5.5, 31.5, 1, 1, // 110
		0.7, 5.5, 32.0, 0, 1, // 111
		// upper
		0.5, 5.5, 31.5, 0, 0,   // 112
		0.7, 5.5, 31.5, 1, 0,  // 113
		0.7, 5.5, 32.0, 1, 1,  // 114
		0.5, 5.5, 32.0, 0, 1,   // 115
		// bottom
		0.7, 3.5, 32.0, 0, 0, // 116
		0.5, 3.5, 32.0, 1, 0,  // 117
		0.5, 3.5, 31.5, 1, 1,  // 118
		0.7, 3.5, 31.5, 0, 1, // 119
		//TIANG 21
		// front
		0.7, 3.5, 33.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, 33.0, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, 33.0, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, 33.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, 33.0, 0, 0,  // 100
		0.5, 4.5, 33.5, 1, 0,  // 101
		0.5, 2.5, 33.5, 1, 1,  // 102
		0.5, 2.5, 33.0, 0, 1,  // 103
		// back
		0.7, 2.5, 33.5, 0, 0, // 104
		0.5, 2.5, 33.5, 1, 0, // 105
		0.5, 4.5, 33.5, 1, 1, // 106
		0.7, 4.5, 33.5, 0, 1, // 107
		// left
		0.7, 2.5, 33.5, 0, 0, // 108
		0.7, 2.5, 33.0, 1, 0, // 109
		0.7, 4.5, 33.0, 1, 1, // 110
		0.7, 4.5, 33.5, 0, 1, // 111
		// upper
		0.5, 4.5, 33.0, 0, 0,   // 112
		0.7, 4.5, 33.0, 1, 0,  // 113
		0.7, 4.5, 33.5, 1, 1,  // 114
		0.5, 4.5, 33.5, 0, 1,   // 115
		// bottom
		0.7, 2.5, 33.5, 0, 0, // 116
		0.5, 2.5, 33.5, 1, 0,  // 117
		0.5, 2.5, 33.0, 1, 1,  // 118
		0.7, 2.5, 33.0, 0, 1, // 119
		//TIANG 22
		// front
		0.7, 2.5, 34.5, 0, 0,  // 96 ,,kiba,
		0.5, 2.5, 34.5, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, 34.5, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, 34.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, 34.5, 0, 0,  // 100
		0.5, 4.5, 35.0, 1, 0,  // 101
		0.5, 2.5, 35.0, 1, 1,  // 102
		0.5, 2.5, 34.5, 0, 1,  // 103
		// back
		0.7, 2.5, 35.0, 0, 0, // 104
		0.5, 2.5, 35.0, 1, 0, // 105
		0.5, 4.5, 35.0, 1, 1, // 106
		0.7, 4.5, 35.0, 0, 1, // 107
		// left
		0.7, 2.5, 35.0, 0, 0, // 108
		0.7, 2.5, 34.5, 1, 0, // 109
		0.7, 4.5, 34.5, 1, 1, // 110
		0.7, 4.5, 35.0, 0, 1, // 111
		// upper
		0.5, 4.5, 34.5, 0, 0,   // 112
		0.7, 4.5, 34.5, 1, 0,  // 113
		0.7, 4.5, 35.0, 1, 1,  // 114
		0.5, 4.5, 35.0, 0, 1,   // 115
		// bottom
		0.7, 2.5, 35.0, 0, 0, // 116
		0.5, 2.5, 35.0, 1, 0,  // 117
		0.5, 2.5, 34.5, 1, 1,  // 118
		0.7, 2.5, 34.5, 0, 1, // 119
		//TIANG 23
		// front
		0.7, 2.5, 36.0, 0, 0,  // 96 ,,kiba,
		0.5, 2.5, 36.0, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, 36.0, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, 36.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, 36.0, 0, 0,  // 100
		0.5, 4.5, 36.5, 1, 0,  // 101
		0.5, 2.5, 36.5, 1, 1,  // 102
		0.5, 2.5, 36.0, 0, 1,  // 103
		// back
		0.7, 2.5, 36.5, 0, 0, // 104
		0.5, 2.5, 36.5, 1, 0, // 105
		0.5, 4.5, 36.5, 1, 1, // 106
		0.7, 4.5, 36.5, 0, 1, // 107
		// left
		0.7, 2.5, 36.5, 0, 0, // 108
		0.7, 2.5, 36.0, 1, 0, // 109
		0.7, 4.5, 36.0, 1, 1, // 110
		0.7, 4.5, 36.5, 0, 1, // 111
		// upper
		0.5, 4.5, 36.0, 0, 0,   // 112
		0.7, 4.5, 36.0, 1, 0,  // 113
		0.7, 4.5, 36.5, 1, 1,  // 114
		0.5, 4.5, 36.5, 0, 1,   // 115
		// bottom
		0.7, 2.5, 36.5, 0, 0, // 116
		0.5, 2.5, 36.5, 1, 0,  // 117
		0.5, 2.5, 36.0, 1, 1,  // 118
		0.7, 2.5, 36.0, 0, 1, // 119
		//TIANG 24
		// front
		0.7, 2.5, 37.5, 0, 0,  // 96 ,,kiba,
		0.5, 2.5, 37.5, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, 37.5, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, 37.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, 37.5, 0, 0,  // 100
		0.5, 4.5, 38.0, 1, 0,  // 101
		0.5, 2.5, 38.0, 1, 1,  // 102
		0.5, 2.5, 37.5, 0, 1,  // 103
		// back
		0.7, 2.5, 38.0, 0, 0, // 104
		0.5, 2.5, 38.0, 1, 0, // 105
		0.5, 4.5, 38.0, 1, 1, // 106
		0.7, 4.5, 38.0, 0, 1, // 107
		// left
		0.7, 2.5, 38.0, 0, 0, // 108
		0.7, 2.5, 37.5, 1, 0, // 109
		0.7, 4.5, 37.5, 1, 1, // 110
		0.7, 4.5, 38.0, 0, 1, // 111
		// upper
		0.5, 4.5, 37.5, 0, 0,   // 112
		0.7, 4.5, 37.5, 1, 0,  // 113
		0.7, 4.5, 38.0, 1, 1,  // 114
		0.5, 4.5, 38.0, 0, 1,   // 115
		// bottom
		0.7, 2.5, 38.0, 0, 0, // 116
		0.5, 2.5, 38.0, 1, 0,  // 117
		0.5, 2.5, 37.5, 1, 1,  // 118
		0.7, 2.5, 37.5, 0, 1, // 119
	};

	unsigned int indices1[] = {
		//tiang 1
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang 2
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//tiang 3
		48, 49, 50, 48, 50, 51,   // front
		52, 53, 54, 52, 54, 55,   // right
		56, 57, 58, 56, 58, 59,  // back
		60, 62, 61, 60, 63, 62,  // left
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		//tiang 4
		72, 73, 74, 72, 74, 75,   // front
		76, 77, 78, 76, 78, 79,   // right
		80, 81, 82, 80, 82, 83,  // back
		84, 86, 85, 84, 87, 86,  // left
		88, 90, 89, 88, 91, 90,  // upper
		92, 94, 93, 92, 95, 94,   // bottom
		//tiang 5
		96, 97, 98, 96, 98, 99,   // front
		100, 101, 102, 100, 102, 103,   // right
		104, 105, 106, 104, 106, 107,  // back
		108, 110, 109, 108, 111, 110,  // left
		112, 114, 113, 112, 115, 114,  // upper
		116, 118, 117, 116, 119, 118,   // bottom
		//tiang 6
		120, 121, 122, 120, 122, 123,   // front
		124, 125, 126, 124, 126, 127,   // right
		128, 129, 130, 128, 130, 131,  // back
		132, 134, 133, 132, 135, 134,  // left
		136, 138, 137, 136, 139, 138,  // upper
		140, 142, 141, 140, 143, 142,   // bottom
		//tiang 7
		144, 145, 146, 144, 146, 147,   // front
		148, 149, 150, 148, 150, 151,   // right
		152, 153, 154, 152, 154, 155,  // back
		156, 158, 157, 156, 159, 158,  // left
		160, 162, 161, 160, 163, 162,  // upper
		164, 166, 165, 164, 167, 166,   // bottom
		//tiang 8
		168, 169, 170, 168, 170, 171,   // front
		172, 173, 174, 172, 174, 175,   // right
		176, 177, 178, 176, 178, 179,  // back
		180, 182, 181, 180, 183, 182,  // left
		184, 186, 185, 184, 187, 186,  // upper
		188, 190, 189, 188, 191, 190,   // bottom
		//tiang 9
		192, 193, 194, 192, 194, 195,   // front
		196, 197, 198, 196, 198, 199,   // right
		200, 201, 202, 200, 202, 203,  // back
		204, 206, 205, 204, 207, 206,  // left
		208, 210, 209, 208, 211, 211,  // upper
		212, 214, 213, 212, 215, 214,   // bottom
		//tiang 10
		216, 217, 218, 216, 218, 219,   // front
		220, 221, 222, 220, 222, 223,   // right
		224, 225, 226, 224, 226, 227,  // back
		228, 230, 229, 228, 231, 230,  // left
		232, 234, 233, 232, 235, 234,  // upper
		236, 238, 237, 236, 239, 238,   // bottom
		//tiang 11
		240, 241, 242, 240, 242, 243,   // front
		244, 245, 246, 244, 246, 247,   // right
		248, 249, 250, 248, 250, 251,  // back
		252, 254, 253, 252, 255, 254,  // left
		256, 258, 257, 256, 259, 258,  // upper
		260, 262, 261, 260, 263, 262,   // bottom
		//tiang 12
		264, 265, 266, 264, 266, 267,   // front
		268, 269, 270, 268, 270, 271,   // right
		272, 273, 274, 272, 274, 275,  // back
		276, 278, 277, 276, 279, 278,  // left
		280, 282, 281, 280, 283, 282,  // upper
		284, 286, 285, 284, 287, 286,   // bottom
		//tiang 13
		288, 289, 290, 288, 290, 291,   // front
		292, 293, 294, 292, 294, 295,   // right
		296, 297, 298, 296, 298, 299,  // back
		300, 302, 301, 300, 303, 302,  // left
		304, 306, 305, 304, 307, 306,  // upper
		308, 310, 309, 308, 311, 310,   // bottom
		//tiang 14
		312, 313, 314, 312, 314, 315,   // front
		316, 317, 318, 316, 318, 319,   // right
		320, 321, 322, 320, 322, 323,  // back
		324, 326, 325, 324, 327, 326,  // left
		328, 330, 329, 328, 331, 330,  // upper
		332, 334, 333, 332, 335, 334,   // bottom
		//tiang 15
		336, 337, 338, 336, 338, 339,   // front
		340, 341, 342, 340, 342, 343,   // right
		344, 345, 346, 344, 346, 347,  // back
		348, 350, 349, 348, 351, 350,  // left
		352, 354, 353, 352, 355, 354,  // upper
		356, 358, 357, 356, 359, 358,   // bottom
		//tiang 16
		360, 361, 362, 360, 362, 363,   // front
		364, 365, 366, 364, 366, 367,   // right
		368, 369, 370, 368, 370, 371,  // back
		372, 374, 373, 372, 375, 374,  // left
		376, 378, 377, 376, 379, 378,  // upper
		380, 382, 381, 380, 383, 382,   // bottom
		//tiang 17
		384, 385, 386, 384, 386, 387,   // front
		388, 389, 390, 388, 390, 391,   // right
		392, 393, 394, 392, 394, 395,  // back
		396, 398, 397, 396, 399, 398,  // left
		400, 402, 401, 400, 403, 402,  // upper
		404, 406, 405, 404, 407, 406,   // bottom
		//tiang 18
		408, 409, 410, 408, 409, 410,   // front
		412, 413, 414, 412, 414, 415,   // right
		416, 417, 418, 416, 418, 419,  // back
		420, 422, 421, 420, 423, 422,  // left
		424, 426, 425, 424, 427, 426,  // upper
		428, 430, 429, 428, 431, 430,   // bottom
		//tiang 19
		432, 433, 434, 432, 434, 435,   // front
		436, 437, 438, 436, 438, 439,   // right
		440, 441, 442, 440, 442, 443,  // back
		444, 446, 445, 444, 447, 446,  // left
		448, 450, 449, 448, 451, 450,  // upper
		452, 454, 453, 452, 455, 454,   // bottom
		//tiang 20
		456, 457, 458, 456, 458, 459,   // front
		460, 461, 462, 460, 462, 463,   // right
		464, 465, 466, 464, 466, 467,  // back
		468, 470, 469, 468, 471, 470,  // left
		472, 474, 473, 472, 475, 474,  // upper
		476, 478, 477, 476, 479, 478,   // bottom
		//tiang 21
		480, 481, 482, 480, 482, 483,   // front
		484, 485, 486, 484, 486, 487,   // right
		488, 489, 490, 488, 490, 491,  // back
		492, 494, 493, 492, 495, 494,  // left
		496, 498, 497, 496, 499, 498,  // upper
		500, 502, 501, 500, 503, 502,   // bottom
		//tiang 22
		504, 505, 506, 504, 506, 507,   // front
		508, 509, 510, 508, 510, 511,   // right
		512, 513, 514, 512, 514, 515,  // back
		516, 518, 517, 516, 519, 518,  // left
		520, 522, 521, 520, 523, 522,  // upper
		524, 526, 525, 524, 527, 526,   // bottom
		//tiang 23
		528, 529, 530, 528, 530, 531,   // front
		532, 533, 534, 532, 534, 535,   // right
		536, 537, 538, 536, 538, 539,  // back
		540, 542, 541, 540, 543, 542,  // left
		544, 546, 545, 544, 547, 546,  // upper
		548, 550, 549, 548, 551, 550,   // bottom
		//tiang 24
		552, 553, 554, 552, 554, 555,   // front
		556, 557, 558, 556, 558, 559,   // right
		560, 561, 562, 560, 562, 563,  // back
		564, 566, 565, 564, 567, 566,  // left
		568, 570, 569, 568, 571, 570,  // upper
		572, 574, 573, 572, 575, 574,   // bottom
	};


	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTiang1(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO9);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 864, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredAtap1() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices2[] = {
		// format position, tex coords
		//TIANG ATAP 0
		// upper
		0.7, 11.0, -4.0, 0, 0,   // 112 kiba
		0.5, 11.0, -4.0, 1, 0,  // 113 kaba
		0.5, 11.0, 4.0, 1, 1,  // 114 kaat
		0.7, 11.0, 4.0, 0, 1,   // 115 kiat
		// bottom
		0.5, 10.5, 4.0, 0, 0, // 116
		0.7, 10.5, 4.0, 1, 0,  // 117
		0.7, 10.5, -4.0, 1, 1,  // 118
		0.5, 10.5, -4.0, 0, 1, // 119
		// front
		0.5, 10.5, 4.0, 0, 0,  // 120
		0.5, 10.5, -4.0, 1, 0,  // 121
		0.5, 11.0, -4.0, 1, 1, // 122
		0.5, 11.0, 4.0, 0, 1, // 123
		// back
		0.7, 10.5, 4.0, 0, 0, // 124
		0.7, 10.5, -4.0, 1, 0, // 125
		0.7, 11.0, -4.0, 1, 1, // 126
		0.7, 11.0, 4.0, 0, 1, // 127
		//TIANG ATAP 1
		// upper
		0.7, 10.0, 4.0, 0, 0,   // 128 kiba
		0.5, 10.0, 4.0, 1, 0,  // 129 kaba
		0.5, 10.0, 8.5, 1, 1,  // 130 kaat
		0.7, 10.0, 8.5, 0, 1,   // 131 kiat
		// bottom
		0.5, 9.5, 8.5, 0, 0, // 132
		0.7, 9.5, 8.5, 1, 0,  // 133
		0.7, 9.5, 4.0, 1, 1,  // 134
		0.5, 9.5, 4.0, 0, 1, // 135
		// front
		0.5, 9.5, 8.5, 0, 0,  // 136
		0.5, 9.5, 4.0, 1, 0,  // 137
		0.5, 10.0,4.0, 1, 1, // 138
		0.5, 10.0,8.5, 0, 1, // 139
		// back
		0.7, 9.5, 8.5, 0, 0, // 140
		0.7, 9.5, 4.0, 1, 0, // 141
		0.7, 10.0,4.0, 1, 1, // 142
		0.7, 10.0,8.5, 0, 1, // 143
		//TIANG ATAP 2
		// upper
		0.7, 9.0, 8.0, 0, 0,   // 144
		0.5, 9.0, 8.0, 1, 0,  // 145
		0.5, 9.0, 12.0, 1, 1,  // 146
		0.7, 9.0, 12.0, 0, 1,   // 147
		// bottom
		0.5, 8.5, 12.0, 0, 0, // 148
		0.7, 8.5, 12.0, 1, 0,  // 149
		0.7, 8.5, 8.0, 1, 1,  // 150
		0.5, 8.5, 8.0, 0, 1, // 151
		// front
		0.5, 8.5, 12.0, 0, 0,  // 152
		0.5, 8.5, 8.0, 1, 0,  // 153
		0.5, 9.0,8.0, 1, 1, // 154
		0.5, 9.0,12.0, 0, 1, // 155
		// back
		0.7, 8.5, 12.0, 0, 0, // 156
		0.7, 8.5, 8.0, 1, 0, // 157
		0.7, 9.0,8.0, 1, 1, // 158
		0.7, 9.0, 12.0, 0, 1, // 159
		//TIANG ATAP 3
		// upper
		0.7, 8.0, 12.0, 0, 0,   // 160
		0.5, 8.0, 12.0, 1, 0,  // 161
		0.5, 8.0, 15.5, 1, 1,  // 162
		0.7, 8.0, 15.5, 0, 1,   // 163
		// bottom
		0.5, 7.5, 15.5, 0, 0, // 164
		0.7, 7.5, 15.5, 1, 0,  //165
		0.7, 7.5, 12.0, 1, 1,  // 166
		0.5, 7.5, 12.0, 0, 1, // 167
		// front
		0.5, 7.5, 15.5, 0, 0,  // 168
		0.5, 7.5, 12.0, 1, 0,  // 169
		0.5, 8.0, 12.0, 1, 1, // 170
		0.5, 8.0, 15.5, 0, 1, // 171
		// back
		0.7, 8.0, 15.5, 0, 0, // 172
		0.7, 8.0, 12.0, 1, 0, // 173
		0.7, 7.5, 12.0, 1, 1, // 174
		0.7, 7.5, 15.5, 0, 1, // 175
		//TIANG ATAP 4
		// upper
		0.7, 7.0, 15.5, 0, 0,   // 176
		0.5, 7.0, 15.5, 1, 0,  // 177
		0.5, 7.0, 23.0, 1, 1,  // 178
		0.7, 7.0, 23.0, 0, 1,   // 179
		// bottom
		0.5, 6.5, 23.0, 0, 0, // 180
		0.7, 6.5, 23.0, 1, 0,  // 181
		0.7, 6.5, 15.5, 1, 1,  // 182
		0.5, 6.5, 15.5, 0, 1, // 183
		// front
		0.5, 6.5, 23.0, 0, 0,  // 184
		0.5, 6.5, 15.5, 1, 0,  // 185
		0.5, 7.0, 15.5, 1, 1, // 186
		0.5, 7.0, 23.0, 0, 1, // 187
		// back
		0.7, 6.5, 23.0, 0, 0, // 188
		0.7, 6.5, 15.5, 1, 0, // 189
		0.7, 7.0, 15.5, 1, 1, // 190
		0.7, 7.0, 23.0, 0, 1, // 191
		//TIANG ATAP 5
		// upper
		0.7, 6.0, 23.0, 0, 0,   // 192
		0.5, 6.0, 23.0, 1, 0,  // 193
		0.5, 6.0, 32.0, 1, 1,  // 194
		0.7, 6.0, 32.0, 0, 1,   // 195
		// bottom
		0.5, 5.5, 32.0, 0, 0, // 196
		0.7, 5.5, 32.0, 1, 0,  // 197
		0.7, 5.5, 23.0, 1, 1,  // 198
		0.5, 5.5, 23.0, 0, 1, // 199
		// front
		0.5, 5.5, 32.0, 0, 0,  // 200
		0.5, 5.5, 23.0, 1, 0,  // 201
		0.5, 6.0, 23.0, 1, 1, // 202
		0.5, 6.0, 32.0, 0, 1, // 203
		// back
		0.7, 5.5, 32.0, 0, 0, // 204
		0.7, 5.5, 23.0, 1, 0, // 205
		0.7, 6.0, 23.0, 1, 1, // 206
		0.7, 6.0, 32.0, 0, 1, // 207
		//TIANG ATAP 6
		// upper
		0.5, 4.5, 32.0, 0, 0,   // 208
		0.7, 4.5, 32.0, 1, 0,  // 209
		0.7, 4.5, 38.0, 1, 1,  // 210
		0.5, 4.5, 38.0, 0, 1,   // 211
		// bottom
		0.7, 5.0, 38.0, 0, 0, // 212
		0.5, 5.0, 38.0, 1, 0,  // 213
		0.5, 5.0, 32.0, 1, 1,  // 214
		0.7, 5.0, 32.0, 0, 1, // 215
		// front
		0.7, 4.5, 38.0, 0, 0,  // 216
		0.7, 4.5, 32.0, 1, 0,  // 217
		0.7, 5.0, 32.0, 1, 1, // 218
		0.7, 5.0, 38.0, 0, 1, // 219
		// back
		0.5, 4.5, 38.0, 0, 0, // 220
		0.5, 4.5, 32.0, 1, 0, // 221
		0.5, 5.0, 32.0, 1, 1, // 222
		0.5, 5.0, 38.0, 0, 1, // 223
	};

	unsigned int indices2[] = {
		//atap tiang -1
		0, 2, 1, 0, 3, 2,  // upper
		4, 6, 5, 4, 7, 6,   // bottom
		8, 9, 10, 8, 11, 10, // front
		12, 13, 14, 12, 15, 14, // back
		//atap tiang -2
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom
		24, 25, 26, 24, 27, 26, // front
		28, 29, 30, 28, 31, 30, // back
		//atap tiang -3
		32, 34, 33, 32, 35, 34,  // upper
		36, 38, 37, 36, 39, 38,   // bottom
		40, 41, 42, 40, 42, 43, // front
		44, 45, 46, 44, 46, 47, // back
		//atap tiang -4
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63, // back
		//atap tiang -5
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		72, 73, 74, 72, 74, 75, // front
		76, 77, 78, 76, 78, 79, // back
		//atap tiang -6
		80, 82, 81, 80, 83, 82,  // upper
		84, 86, 85, 84, 87, 86,   // bottom
		88, 89, 90, 88, 90, 91, // front
		92, 93, 94, 92, 94, 95, // back
		//atap tiang -7
		96, 98, 97, 96, 99, 98,  // upper
		100, 102, 101, 100, 103, 102,   // bottom
		104, 105, 106, 104, 106, 107, // front
		108, 109, 110, 108, 110, 111, // back
	};


	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredAtap1(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO10);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 168, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTiang2() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices1[] = {
		// format position, tex coords
		// TIANG 1
		 //front
		0.7, 8.5, -2.5, 0, 0,  // 0
		0.5, 8.5, -2.5, 1, 0,   // 1
		0.5, 10.5, -2.5, 1, 1,   // 2
		0.7, 10.5, -2.5, 0, 1,  // 3
		// right
		0.5,  10.5,  -2.5, 0, 0,  // 4
		0.5,  10.5, -2.0, 1, 0,  // 5
		0.5, 8.5, -2.0, 1, 1,  // 6
		0.5, 8.5,  -2.5, 0, 1,  // 7
		// back
		0.7, 8.5, -2.0, 0, 0, // 8 
		0.5, 8.5, -2.0, 1, 0, // 9
		0.5, 10.5, -2.0, 1, 1, // 10
		0.7, 10.5, -2.0, 0, 1, // 11
		// left
		0.7, 8.5, -2.0, 0, 0, // 12
		0.7, 8.5,  -2.5, 1, 0, // 13
		0.7, 10.5, -2.5, 1, 1, // 14
		0.7, 10.5, -2.0, 0, 1, // 15
		// upper
		0.5, 10.5, -2.5, 0, 0,   // 16
		0.7, 10.5, -2.5, 1, 0,  // 17
		0.7, 10.5, -2.0, 1, 1,  // 18
		0.5, 10.5, -2.0, 0, 1,   // 19
		// bottom
		0.7, 8.5, -2.0, 0, 0, // 20
		0.5, 8.5, -2.0, 1, 0,  // 21
		0.5, 8.5,  -2.5, 1, 1,  // 22
		0.7, 8.5,  -2.5, 0, 1, // 23
		//TIANG 2
		// front
		0.7, 8.5, -3.5, 0, 0,  // 24 ,,kiba,
		0.5, 8.5, -3.5, 1, 0,  // 25 ,,kaba,
		0.5, 10.5, -3.5, 1, 1,  // 26 ,,kaat,
		0.7, 10.5, -3.5, 0, 1,  // 27 ,,kiat
		// right
		0.5,  10.5, -3.5, 0, 0,  // 28
		0.5,  10.5, -4.0, 1, 0,  // 29
		0.5, 8.5, -4.0, 1, 1,  // 30
		0.5, 8.5, -3.5, 0, 1,  // 31
		// back
		0.7, 8.5, -4.0, 0, 0, // 32
		0.5, 8.5, -4.0, 1, 0, // 33
		0.5, 10.5, -4.0, 1, 1, // 34
		0.7, 10.5, -4.0, 0, 1, // 35
		// left
		0.7, 8.5, -4.0, 0, 0, // 36
		0.7, 8.5, -3.5, 1, 0, // 37
		0.7, 10.5,-3.5, 1, 1, // 38
		0.7, 10.5,-4.0, 0, 1, // 39
		// upper
		0.5, 10.5, -3.5, 0, 0,   // 40
		0.7, 10.5, -3.5, 1, 0,  // 41
		0.7, 10.5, -4.0, 1, 1,  // 42
		0.5, 10.5, -4.0, 0, 1,   // 43
		// bottom
		0.7, 8.5, -4.0, 0, 0, // 44
		0.5, 8.5, -4.0, 1, 0,  // 45
		0.5, 8.5, -3.5, 1, 1,  // 46
		0.7, 8.5, -3.5, 0, 1, // 47
		//TIANG 3
		// front
		0.7, 7.5, -5.0, 0, 0,  // 48 ,,kiba,
		0.5, 7.5, -5.0, 1, 0,  // 49 ,,kaba,
		0.5, 9.5, -5.0, 1, 1,  // 50 ,,kaat,
		0.7, 9.5, -5.0, 0, 1,  // 51 ,,kiat
		// right
		0.5,  9.5, -5.0, 0, 0,  // 52
		0.5,  9.5, -5.5, 1, 0,  // 53
		0.5, 7.5, -5.5, 1, 1,  // 54
		0.5, 7.5,  -5.0, 0, 1,  // 55
		// back
		0.7, 7.5, -5.5, 0, 0, // 56
		0.5, 7.5, -5.5, 1, 0, // 57
		0.5,  9.5, -5.5, 1, 1, // 58
		0.7,  9.5, -5.5, 0, 1, // 59
		// left
		0.7, 7.5, -5.5, 0, 0, // 60
		0.7, 7.5, -5.0, 1, 0, // 61
		0.7, 9.5, -5.0, 1, 1, // 62
		0.7, 9.5, -5.5, 0, 1, // 63
		// upper
		0.5, 9.5,  -5.0, 0, 0,   // 64
		0.7, 9.5, -5.0, 1, 0,  // 65
		0.7, 9.5, -5.5, 1, 1,  // 66
		0.5,9.5, -5.5, 0, 1,   // 67
		// bottom
		0.7, 7.5, -5.5, 0, 0, // 68
		0.5, 7.5, -5.5, 1, 0,  // 69
		0.5, 7.5, -5.0, 1, 1,  // 70
		0.7, 7.5, -5.0, 0, 1, // 71
		//TIANG 4
		// front
		0.7, 7.5, -6.5, 0, 0,  // 72 ,,kiba,
		0.5, 7.5, -6.5, 1, 0,  // 73 ,,kaba,
		0.5, 9.5, -6.5, 1, 1,  // 74 ,,kaat,
		0.7, 9.5, -6.5, 0, 1,  // 75 ,,kiat
		// right
		0.5,  9.5, -6.5, 0, 0,  // 76
		0.5,  9.5, -7.0, 1, 0,  // 77
		0.5, 7.5, -7.0, 1, 1,  // 78
		0.5, 7.5, -6.5, 0, 1,  // 79
		// back
		0.7, 7.5, -7.0, 0, 0, // 80
		0.5, 7.5, -7.0, 1, 0, // 81
		0.5, 9.5,-7.0, 1, 1, // 82
		0.7, 9.5,-7.0, 0, 1, // 83
		// left
		0.7, 7.5, -7.0, 0, 0, // 84
		0.7, 7.5, -6.5, 1, 0, // 85
		0.7, 9.5, -6.5, 1, 1, // 86
		0.7, 9.5, -7.0, 0, 1, // 87
		// upper
		0.5, 9.5, -6.5, 0, 0,   // 88
		0.7, 9.5, -6.5, 1, 0,  // 89
		0.7, 9.5, -7.0, 1, 1,  // 90
		0.5, 9.5,-7.0, 0, 1,   // 91
		// bottom
		0.7, 7.5, -7.0, 0, 0, // 92
		0.5, 7.5, -7.0, 1, 0,  // 93
		0.5, 7.5, -6.5, 1, 1,  // 94
		0.7, 7.5, -6.5, 0, 1, // 95
		//TIANG 5
		// front
		0.7, 6.5, -8.0, 0, 0,  // 96 ,,kiba,
		0.5, 6.5, -8.0, 1, 0,  // 97 ,,kaba,
		0.5, 9.5, -8.0, 1, 1,  // 98 ,,kaat,
		0.7, 9.5, -8.0, 0, 1,  // 99 ,,kiat
		// right
		0.5,  9.5, -8.0, 0, 0,  // 100
		0.5,  9.5, -8.5, 1, 0,  // 101
		0.5, 6.5, -8.5, 1, 1,  // 102
		0.5, 6.5, -8.0, 0, 1,  // 103
		// back
		0.7, 6.5, -8.5, 0, 0, // 104
		0.5, 6.5, -8.5, 1, 0, // 105
		0.5,  9.5, -8.5, 1, 1, // 106
		0.7,  9.5, -8.5, 0, 1, // 107
		// left
		0.7, 6.5, -8.5, 0, 0, // 108
		0.7, 6.5, -8.0, 1, 0, // 109
		0.7,  9.5,-8.0, 1, 1, // 110
		0.7,  9.5, -8.5, 0, 1, // 111
		// upper
		0.5, 9.5,  -8.0, 0, 0,   // 112
		0.7, 9.5, -8.0, 1, 0,  // 113
		0.7, 9.5, -8.5, 1, 1,  // 114
		0.5, 9.5, -8.5, 0, 1,   // 115
		// bottom
		0.7, 6.5, -8.5, 0, 0, // 116
		0.5, 6.5,-8.5, 1, 0,  // 117
		0.5, 6.5, -8.0, 1, 1,  // 118
		0.7, 6.5, -8.0, 0, 1, // 119
		//TIANG 6
		// front
		0.7, 6.5, -11.5, 0, 0,  // 96 ,,kiba,
		0.5, 6.5, -11.5, 1, 0,  // 97 ,,kaba,
		0.5, 8.5, -11.5, 1, 1,  // 98 ,,kaat,
		0.7, 8.5, -11.5, 0, 1,  // 99 ,,kiat
		// right
		0.5,  8.5, -11.5, 0, 0,  // 100
		0.5,  8.5, -12.0, 1, 0,  // 101
		0.5, 6.5, -12.0, 1, 1,  // 102
		0.5, 6.5, -11.5, 0, 1,  // 103
		// back
		0.7, 6.5, -12.0, 0, 0, // 104
		0.5, 6.5, -12.0, 1, 0, // 105
		0.5, 8.5, -12.0, 1, 1, // 106
		0.7, 8.5, -12.0, 0, 1, // 107
		// left
		0.7, 6.5, -12.0, 0, 0, // 108
		0.7, 6.5, -11.5, 1, 0, // 109
		0.7, 8.5, -11.5, 1, 1, // 110
		0.7, 8.5, -12.0, 0, 1, // 111
		// upper
		0.5, 8.5, -11.5, 0, 0,   // 112
		0.7, 8.5, -11.5, 1, 0,  // 113
		0.7, 8.5, -12.0, 1, 1,  // 114
		0.5, 8.5, -12.0, 0, 1,   // 115
		// bottom
		0.7, 6.5, -12.0, 0, 0, // 116
		0.5, 6.5, -12.0, 1, 0,  // 117
		0.5, 6.5, -11.5, 1, 1,  // 118
		0.7, 6.5, -11.5, 0, 1, // 119
		//TIANG 7
		// front
		0.7, 5.5, -12.0, 0, 0,  // 96 ,,kiba,
		0.5, 5.5, -12.0, 1, 0,  // 97 ,,kaba,
		0.5, 7.5, -12.0, 1, 1,  // 98 ,,kaat,
		0.7, 7.5, -12.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 7.5, -12.0, 0, 0,  // 100
		0.5, 7.5, -12.5, 1, 0,  // 101
		0.5, 5.5, -12.5, 1, 1,  // 102
		0.5, 5.5, -12.0, 0, 1,  // 103
		// back
		0.7, 5.5, -12.5, 0, 0, // 104
		0.5, 5.5, -12.5, 1, 0, // 105
		0.5, 7.5, -12.5, 1, 1, // 106
		0.7, 7.5, -12.5, 0, 1, // 107
		// left
		0.7, 5.5, -12.5, 0, 0, // 108
		0.7, 5.5, -12.0, 1, 0, // 109
		0.7, 7.5, -12.0, 1, 1, // 110
		0.7, 7.5, -12.5, 0, 1, // 111
		// upper
		0.5, 7.5, -12.0, 0, 0,   // 112
		0.7, 7.5, -12.0, 1, 0,  // 113
		0.7, 7.5, -12.5, 1, 1,  // 114
		0.5, 7.5, -12.5, 0, 1,   // 115
		// bottom
		0.7, 5.5, -12.5, 0, 0, // 116
		0.5, 5.5, -12.5, 1, 0,  // 117
		0.5, 5.5, -12.0, 1, 1,  // 118
		0.7, 5.5, -12.0, 0, 1, // 119
		//TIANG 8
		// front
		0.7, 5.5, -13.5, 0, 0,  // 96 ,,kiba,
		0.5, 5.5, -13.5, 1, 0,  // 97 ,,kaba,
		0.5, 7.5, -13.5, 1, 1,  // 98 ,,kaat,
		0.7, 7.5, -13.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 7.5, -13.5, 0, 0,  // 100
		0.5, 7.5, -14.0, 1, 0,  // 101
		0.5, 5.5, -14.0, 1, 1,  // 102
		0.5, 5.5, -13.5, 0, 1,  // 103
		// back
		0.7, 5.5, -14.0, 0, 0, // 104
		0.5, 5.5, -14.0, 1, 0, // 105
		0.5, 7.5, -14.0, 1, 1, // 106
		0.7, 7.5, -14.0, 0, 1, // 107
		// left
		0.7, 5.5, -14.0, 0, 0, // 108
		0.7, 5.5, -13.5, 1, 0, // 109
		0.7, 7.5, -13.5, 1, 1, // 110
		0.7, 7.5, -14.0, 0, 1, // 111
		// upper
		0.5, 7.5, -13.5, 0, 0,   // 112
		0.7, 7.5, -13.5, 1, 0,  // 113
		0.7, 7.5, -14.0, 1, 1,  // 114
		0.5, 7.5, -14.0, 0, 1,   // 115
		// bottom
		0.7, 5.5, -14.0, 0, 0, // 116
		0.5, 5.5, -14.0, 1, 0,  // 117
		0.5, 5.5, -13.5, 1, 1,  // 118
		0.7, 5.5, -13.5, 0, 1, // 119
		//TIANG 9
		// front
		0.7, 5.5, -15.0, 0, 0,  // 96 ,,kiba,
		0.5, 5.5, -15.0, 1, 0,  // 97 ,,kaba,
		0.5, 7.5, -15.0, 1, 1,  // 98 ,,kaat,
		0.7, 7.5, -15.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 7.5, -15.0, 0, 0,  // 100
		0.5, 7.5, -15.5, 1, 0,  // 101
		0.5, 5.5, -15.5, 1, 1,  // 102
		0.5, 5.5, -15.0, 0, 1,  // 103
		// back
		0.7, 5.5, -15.5, 0, 0, // 104
		0.5, 5.5, -15.5, 1, 0, // 105
		0.5, 7.5, -15.5, 1, 1, // 106
		0.7, 7.5, -15.5, 0, 1, // 107
		// left
		0.7, 5.5, -15.5, 0, 0, // 108
		0.7, 5.5, -15.0, 1, 0, // 109
		0.7, 7.5, -15.0, 1, 1, // 110
		0.7, 7.5, -15.5, 0, 1, // 111
		// upper
		0.5, 7.5, -15.0, 0, 0,   // 112
		0.7, 7.5, -15.0, 1, 0,  // 113
		0.7, 7.5, -15.5, 1, 1,  // 114
		0.5, 7.5, -15.5, 0, 1,   // 115
		// bottom
		0.7, 5.5, -15.5, 0, 0, // 116
		0.5, 5.5, -15.5, 1, 0,  // 117
		0.5, 5.5, -15.0, 1, 1,  // 118
		0.7, 5.5, -15.0, 0, 1, // 119
		//TIANG 10
		// front
		0.7, 4.5, -16.5, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, -16.5, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, -16.5, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, -16.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, -16.5, 0, 0,  // 100
		0.5, 6.5, -17.0, 1, 0,  // 101
		0.5, 4.5, -17.0, 1, 1,  // 102
		0.5, 4.5, -16.5, 0, 1,  // 103
		// back
		0.7, 4.5, -17.0, 0, 0, // 104
		0.5, 4.5, -17.0, 1, 0, // 105
		0.5, 6.5, -17.0, 1, 1, // 106
		0.7, 6.5, -17.0, 0, 1, // 107
		// left
		0.7, 4.5, -17.0, 0, 0, // 108
		0.7, 4.5, -16.5, 1, 0, // 109
		0.7, 6.5, -16.5, 1, 1, // 110
		0.7, 6.5, -17.0, 0, 1, // 111
		// upper
		0.5, 6.5, -16.5, 0, 0,   // 112
		0.7, 6.5, -16.5, 1, 0,  // 113
		0.7, 6.5, -17.0, 1, 1,  // 114
		0.5, 6.5, -17.0, 0, 1,   // 115
		// bottom
		0.7, 4.5, -17.0, 0, 0, // 116
		0.5, 4.5, -17.0, 1, 0,  // 117
		0.5, 4.5, -16.5, 1, 1,  // 118
		0.7, 4.5, -16.5, 0, 1, // 119
		//TIANG 11
		// front
		0.7, 4.5, -18.0, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, -18.0, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, -18.0, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, -18.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, -18.0, 0, 0,  // 100
		0.5, 6.5, -18.5, 1, 0,  // 101
		0.5, 4.5, -18.5, 1, 1,  // 102
		0.5, 4.5, -18.0, 0, 1,  // 103
		// back
		0.7, 4.5, -18.5, 0, 0, // 104
		0.5, 4.5, -18.5, 1, 0, // 105
		0.5, 6.5, -18.5, 1, 1, // 106
		0.7, 6.5, -18.5, 0, 1, // 107
		// left
		0.7, 4.5, -18.5, 0, 0, // 108
		0.7, 4.5, -18.0, 1, 0, // 109
		0.7, 6.5, -18.0, 1, 1, // 110
		0.7, 6.5, -18.5, 0, 1, // 111
		// upper
		0.5, 6.5, -18.0, 0, 0,   // 112
		0.7, 6.5, -18.0, 1, 0,  // 113
		0.7, 6.5, -18.5, 1, 1,  // 114
		0.5, 6.5, -18.5, 0, 1,   // 115
		// bottom
		0.7, 4.5, -18.5, 0, 0, // 116
		0.5, 4.5, -18.5, 1, 0,  // 117
		0.5, 4.5, -18.0, 1, 1,  // 118
		0.7, 4.5, -18.0, 0, 1, // 119
		//TIANG 12
		// front
		0.7, 4.5, -19.5, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, -19.5, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, -19.5, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, -19.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, -19.5, 0, 0,  // 100
		0.5, 6.5, -20.0, 1, 0,  // 101
		0.5, 4.5, -20.0, 1, 1,  // 102
		0.5, 4.5, -19.5, 0, 1,  // 103
		// back
		0.7, 4.5, -20.0, 0, 0, // 104
		0.5, 4.5, -20.0, 1, 0, // 105
		0.5, 6.5, -20.0, 1, 1, // 106
		0.7, 6.5, -20.0, 0, 1, // 107
		// left
		0.7, 4.5, -20.0, 0, 0, // 108
		0.7, 4.5, -19.5, 1, 0, // 109
		0.7, 6.5, -19.5, 1, 1, // 110
		0.7, 6.5, -20.0, 0, 1, // 111
		// upper
		0.5, 6.5, -19.5, 0, 0,   // 112
		0.7, 6.5, -19.5, 1, 0,  // 113
		0.7, 6.5, -20.0, 1, 1,  // 114
		0.5, 6.5, -20.0, 0, 1,   // 115
		// bottom
		0.7, 4.5, -20.0, 0, 0, // 116
		0.5, 4.5, -20.0, 1, 0,  // 117
		0.5, 4.5, -19.5, 1, 1,  // 118
		0.7, 4.5, -19.5, 0, 1, // 119
		//TIANG 13
		// front
		0.7, 4.5, -21.0, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, -21.0, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, -21.0, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, -21.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, -21.0, 0, 0,  // 100
		0.5, 6.5, -21.5, 1, 0,  // 101
		0.5, 4.5, -21.5, 1, 1,  // 102
		0.5, 4.5, -21.0, 0, 1,  // 103
		// back
		0.7, 4.5, -21.5, 0, 0, // 104
		0.5, 4.5, -21.5, 1, 0, // 105
		0.5, 6.5, -21.5, 1, 1, // 106
		0.7, 6.5, -21.5, 0, 1, // 107
		// left
		0.7, 4.5, -21.5, 0, 0, // 108
		0.7, 4.5, -21.0, 1, 0, // 109
		0.7, 6.5, -21.0, 1, 1, // 110
		0.7, 6.5, -21.5, 0, 1, // 111
		// upper
		0.5, 6.5, -21.0, 0, 0,   // 112
		0.7, 6.5, -21.0, 1, 0,  // 113
		0.7, 6.5, -21.5, 1, 1,  // 114
		0.5, 6.5, -21.5, 0, 1,   // 115
		// bottom
		0.7, 4.5, -21.5, 0, 0, // 116
		0.5, 4.5, -21.5, 1, 0,  // 117
		0.5, 4.5, -21.0, 1, 1,  // 118
		0.7, 4.5, -21.0, 0, 1, // 119
		//TIANG 14
		// front
		0.7, 4.5, -22.5, 0, 0,  // 96 ,,kiba,
		0.5, 4.5, -22.5, 1, 0,  // 97 ,,kaba,
		0.5, 6.5, -22.5, 1, 1,  // 98 ,,kaat,
		0.7, 6.5, -22.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 6.5, -22.5, 0, 0,  // 100
		0.5, 6.5, -23.0, 1, 0,  // 101
		0.5, 4.5, -23.0, 1, 1,  // 102
		0.5, 4.5, -22.5, 0, 1,  // 103
		// back
		0.7, 4.5, -23.0, 0, 0, // 104
		0.5, 4.5, -23.0, 1, 0, // 105
		0.5, 6.5, -23.0, 1, 1, // 106
		0.7, 6.5, -23.0, 0, 1, // 107
		// left
		0.7, 4.5, -23.0, 0, 0, // 108
		0.7, 4.5, -22.5, 1, 0, // 109
		0.7, 6.5, -22.5, 1, 1, // 110
		0.7, 6.5, -23.0, 0, 1, // 111
		// upper
		0.5, 6.5, -22.5, 0, 0,   // 112
		0.7, 6.5, -22.5, 1, 0,  // 113
		0.7, 6.5, -23.0, 1, 1,  // 114
		0.5, 6.5, -23.0, 0, 1,   // 115
		// bottom
		0.7, 4.5, -23.0, 0, 0, // 116
		0.5, 4.5, -23.0, 1, 0,  // 117
		0.5, 4.5, -22.5, 1, 1,  // 118
		0.7, 4.5, -22.5, 0, 1, // 119
		//TIANG 15
		// front
		0.7, 3.5, -24.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -24.0, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, -24.0, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, -24.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, -24.0, 0, 0,  // 100
		0.5, 5.5, -24.5, 1, 0,  // 101
		0.5, 3.5, -24.5, 1, 1,  // 102
		0.5, 3.5, -24.0, 0, 1,  // 103
		// back
		0.7, 3.5, -24.5, 0, 0, // 104
		0.5, 3.5, -24.5, 1, 0, // 105
		0.5, 5.5, -24.5, 1, 1, // 106
		0.7, 5.5, -24.5, 0, 1, // 107
		// left
		0.7, 3.5, -24.5, 0, 0, // 108
		0.7, 3.5, -24.0, 1, 0, // 109
		0.7, 5.5, -24.0, 1, 1, // 110
		0.7, 5.5, -24.5, 0, 1, // 111
		// upper
		0.5, 5.5, -24.0, 0, 0,   // 112
		0.7, 5.5, -24.0, 1, 0,  // 113
		0.7, 5.5, -24.5, 1, 1,  // 114
		0.5, 5.5, -24.5, 0, 1,   // 115
		// bottom
		0.7, 3.5, -24.5, 0, 0, // 116
		0.5, 3.5, -24.5, 1, 0,  // 117
		0.5, 3.5, -24.0, 1, 1,  // 118
		0.7, 3.5, -24.0, 0, 1, // 119
		//TIANG 16
		// front
		0.7, 3.5, -25.5, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -25.5, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, -25.5, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, -25.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, -25.5, 0, 0,  // 100
		0.5, 5.5, -26.0, 1, 0,  // 101
		0.5, 3.5, -26.0, 1, 1,  // 102
		0.5, 3.5, -25.5, 0, 1,  // 103
		// back
		0.7, 3.5, -26.0, 0, 0, // 104
		0.5, 3.5, -25.5, 1, 0, // 105
		0.5, 5.5, -25.5, 1, 1, // 106
		0.7, 5.5, -26.0, 0, 1, // 107
		// left
		0.7, 3.5, -26.0, 0, 0, // 108
		0.7, 3.5, -25.5, 1, 0, // 109
		0.7, 5.5, -25.5, 1, 1, // 110
		0.7, 5.5, -26.0, 0, 1, // 111
		// upper
		0.5, 5.5, -25.5, 0, 0,   // 112
		0.7, 5.5, -25.5, 1, 0,  // 113
		0.7, 5.5, -26.0, 1, 1,  // 114
		0.5, 5.5, -26.0, 0, 1,   // 115
		// bottom
		0.7, 3.5, -26.0, 0, 0, // 116
		0.5, 3.5, -26.0, 1, 0,  // 117
		0.5, 3.5, -25.5, 1, 1,  // 118
		0.7, 3.5, -25.5, 0, 1, // 119
		//TIANG 17
		// front
		0.7, 3.5, -27.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -27.0, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, -27.0, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, -27.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, -27.0, 0, 0,  // 100
		0.5, 5.5, -27.5, 1, 0,  // 101
		0.5, 3.5, -27.5, 1, 1,  // 102
		0.5, 3.5, -27.0, 0, 1,  // 103
		// back
		0.7, 3.5, -27.5, 0, 0, // 104
		0.5, 3.5, -27.5, 1, 0, // 105
		0.5, 5.5, -27.5, 1, 1, // 106
		0.7, 5.5, -27.5, 0, 1, // 107
		// left
		0.7, 3.5, -27.5, 0, 0, // 108
		0.7, 3.5, -27.0, 1, 0, // 109
		0.7, 5.5, -27.0, 1, 1, // 110
		0.7, 5.5, -27.5, 0, 1, // 111
		// upper
		0.5, 5.5, -27.0, 0, 0,   // 112
		0.7, 5.5, -27.0, 1, 0,  // 113
		0.7, 5.5, -27.5, 1, 1,  // 114
		0.5, 5.5, -27.5, 0, 1,   // 115
		// bottom
		0.7, 3.5, -27.5, 0, 0, // 116
		0.5, 3.5, -27.5, 1, 0,  // 117
		0.5, 3.5, -27.0, 1, 1,  // 118
		0.7, 3.5, -27.0, 0, 1, // 119
		//TIANG 18
		// front
		0.7, 3.5, -28.5, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -28.5, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, -28.5, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, -28.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, -28.5, 0, 0,  // 100
		0.5, 5.5, -29.0, 1, 0,  // 101
		0.5, 3.5, -29.0, 1, 1,  // 102
		0.5, 3.5, -28.5, 0, 1,  // 103
		// back
		0.7, 3.5, -29.0, 0, 0, // 104
		0.5, 3.5, -29.0, 1, 0, // 105
		0.5, 5.5, -29.0, 1, 1, // 106
		0.7, 5.5, -29.0, 0, 1, // 107
		// left
		0.7, 3.5, -29.0, 0, 0, // 108
		0.7, 3.5, -28.5, 1, 0, // 109
		0.7, 5.5, -28.5, 1, 1, // 110
		0.7, 5.5, -29.0, 0, 1, // 111
		// upper
		0.5, 5.5, -28.5, 0, 0,   // 112
		0.7, 5.5, -28.5, 1, 0,  // 113
		0.7, 5.5, -29.0, 1, 1,  // 114
		0.5, 5.5, -29.0, 0, 1,   // 115
		// bottom
		0.7, 3.5, -29.0, 0, 0, // 116
		0.5, 3.5, -29.0, 1, 0,  // 117
		0.5, 3.5, -28.5, 1, 1,  // 118
		0.7, 3.5, -28.5, 0, 1, // 119
		//TIANG 19
		// front
		0.7, 3.5, -30.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -30.0, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, -30.0, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, -30.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, -30.0, 0, 0,  // 100
		0.5, 5.5, -30.5, 1, 0,  // 101
		0.5, 3.5, -30.5, 1, 1,  // 102
		0.5, 3.5, -30.0, 0, 1,  // 103
		// back
		0.7, 3.5, -30.5, 0, 0, // 104
		0.5, 3.5, -30.5, 1, 0, // 105
		0.5, 5.5, -30.5, 1, 1, // 106
		0.7, 5.5, -30.5, 0, 1, // 107
		// left
		0.7, 3.5, -30.5, 0, 0, // 108
		0.7, 3.5, -30.0, 1, 0, // 109
		0.7, 5.5, -30.0, 1, 1, // 110
		0.7, 5.5, -30.5, 0, 1, // 111
		// upper
		0.5, 5.5, -30.0, 0, 0,   // 112
		0.7, 5.5, -30.0, 1, 0,  // 113
		0.7, 5.5, -30.5, 1, 1,  // 114
		0.5, 5.5, -30.5, 0, 1,   // 115
		// bottom
		0.7, 3.5, -30.5, 0, 0, // 116
		0.5, 3.5, -30.5, 1, 0,  // 117
		0.5, 3.5, -30.0, 1, 1,  // 118
		0.7, 3.5, -30.0, 0, 1, // 119
		//TIANG 20
		// front
		0.7, 3.5, -31.5, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -31.5, 1, 0,  // 97 ,,kaba,
		0.5, 5.5, -31.5, 1, 1,  // 98 ,,kaat,
		0.7, 5.5, -31.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 5.5, -31.5, 0, 0,  // 100
		0.5, 5.5, -32.0, 1, 0,  // 101
		0.5, 3.5, -32.0, 1, 1,  // 102
		0.5, 3.5, -31.5, 0, 1,  // 103
		// back
		0.7, 3.5, -32.0, 0, 0, // 104
		0.5, 3.5, -32.0, 1, 0, // 105
		0.5, 5.5, -32.0, 1, 1, // 106
		0.7, 5.5, -32.0, 0, 1, // 107
		// left
		0.7, 3.5, -32.0, 0, 0, // 108
		0.7, 3.5, -31.5, 1, 0, // 109
		0.7, 5.5, -31.5, 1, 1, // 110
		0.7, 5.5, -32.0, 0, 1, // 111
		// upper
		0.5, 5.5, -31.5, 0, 0,   // 112
		0.7, 5.5, -31.5, 1, 0,  // 113
		0.7, 5.5, -32.0, 1, 1,  // 114
		0.5, 5.5, -32.0, 0, 1,   // 115
		// bottom
		0.7, 3.5, -32.0, 0, 0, // 116
		0.5, 3.5, -32.0, 1, 0,  // 117
		0.5, 3.5, -31.5, 1, 1,  // 118
		0.7, 3.5, -31.5, 0, 1, // 119
		//TIANG 21
		// front
		0.7, 3.5, -33.0, 0, 0,  // 96 ,,kiba,
		0.5, 3.5, -33.0, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, -33.0, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, -33.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, -33.0, 0, 0,  // 100
		0.5, 4.5, -33.5, 1, 0,  // 101
		0.5, 2.5, -33.5, 1, 1,  // 102
		0.5, 2.5, -33.0, 0, 1,  // 103
		// back
		0.7, 2.5, -33.5, 0, 0, // 104
		0.5, 2.5, -33.5, 1, 0, // 105
		0.5, 4.5, -33.5, 1, 1, // 106
		0.7, 4.5, -33.5, 0, 1, // 107
		// left
		0.7, 2.5, -33.5, 0, 0, // 108
		0.7, 2.5, -33.0, 1, 0, // 109
		0.7, 4.5, -33.0, 1, 1, // 110
		0.7, 4.5, -33.5, 0, 1, // 111
		// upper
		0.5, 4.5, -33.0, 0, 0,   // 112
		0.7, 4.5, -33.0, 1, 0,  // 113
		0.7, 4.5, -33.5, 1, 1,  // 114
		0.5, 4.5, -33.5, 0, 1,   // 115
		// bottom
		0.7, 2.5, -33.5, 0, 0, // 116
		0.5, 2.5, -33.5, 1, 0,  // 117
		0.5, 2.5, -33.0, 1, 1,  // 118
		0.7, 2.5, -33.0, 0, 1, // 119
		//TIANG 22
		// front
		0.7, 2.5, -34.5, 0, 0,  // 96 ,,kiba,
		0.5, 2.5, -34.5, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, -34.5, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, -34.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, -34.5, 0, 0,  // 100
		0.5, 4.5, -35.0, 1, 0,  // 101
		0.5, 2.5, -35.0, 1, 1,  // 102
		0.5, 2.5, -34.5, 0, 1,  // 103
		// back
		0.7, 2.5, -35.0, 0, 0, // 104
		0.5, 2.5, -35.0, 1, 0, // 105
		0.5, 4.5, -35.0, 1, 1, // 106
		0.7, 4.5, -35.0, 0, 1, // 107
		// left
		0.7, 2.5, -35.0, 0, 0, // 108
		0.7, 2.5, -34.5, 1, 0, // 109
		0.7, 4.5, -34.5, 1, 1, // 110
		0.7, 4.5, -35.0, 0, 1, // 111
		// upper
		0.5, 4.5, -34.5, 0, 0,   // 112
		0.7, 4.5, -34.5, 1, 0,  // 113
		0.7, 4.5, -35.0, 1, 1,  // 114
		0.5, 4.5, -35.0, 0, 1,   // 115
		// bottom
		0.7, 2.5, -35.0, 0, 0, // 116
		0.5, 2.5, -35.0, 1, 0,  // 117
		0.5, 2.5, -34.5, 1, 1,  // 118
		0.7, 2.5, -34.5, 0, 1, // 119
		//TIANG 23
		// front
		0.7, 2.5, -36.0, 0, 0,  // 96 ,,kiba,
		0.5, 2.5, -36.0, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, -36.0, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, -36.0, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, -36.0, 0, 0,  // 100
		0.5, 4.5, -36.5, 1, 0,  // 101
		0.5, 2.5, -36.5, 1, 1,  // 102
		0.5, 2.5, -36.0, 0, 1,  // 103
		// back
		0.7, 2.5, -36.5, 0, 0, // 104
		0.5, 2.5, -36.5, 1, 0, // 105
		0.5, 4.5, -36.5, 1, 1, // 106
		0.7, 4.5, -36.5, 0, 1, // 107
		// left
		0.7, 2.5, -36.5, 0, 0, // 108
		0.7, 2.5, -36.0, 1, 0, // 109
		0.7, 4.5, -36.0, 1, 1, // 110
		0.7, 4.5, -36.5, 0, 1, // 111
		// upper
		0.5, 4.5, -36.0, 0, 0,   // 112
		0.7, 4.5, -36.0, 1, 0,  // 113
		0.7, 4.5, -36.5, 1, 1,  // 114
		0.5, 4.5, -36.5, 0, 1,   // 115
		// bottom
		0.7, 2.5, -36.5, 0, 0, // 116
		0.5, 2.5, -36.5, 1, 0,  // 117
		0.5, 2.5, -36.0, 1, 1,  // 118
		0.7, 2.5, -36.0, 0, 1, // 119
		//TIANG 24
		// front
		0.7, 2.5, -37.5, 0, 0,  // 96 ,,kiba,
		0.5, 2.5, -37.5, 1, 0,  // 97 ,,kaba,
		0.5, 4.5, -37.5, 1, 1,  // 98 ,,kaat,
		0.7, 4.5, -37.5, 0, 1,  // 99 ,,kiat
		// right
		0.5, 4.5, -37.5, 0, 0,  // 100
		0.5, 4.5, -38.0, 1, 0,  // 101
		0.5, 2.5, -38.0, 1, 1,  // 102
		0.5, 2.5, -37.5, 0, 1,  // 103
		// back
		0.7, 2.5, -38.0, 0, 0, // 104
		0.5, 2.5, -38.0, 1, 0, // 105
		0.5, 4.5, -38.0, 1, 1, // 106
		0.7, 4.5, -38.0, 0, 1, // 107
		// left
		0.7, 2.5, -38.0, 0, 0, // 108
		0.7, 2.5, -37.5, 1, 0, // 109
		0.7, 4.5, -37.5, 1, 1, // 110
		0.7, 4.5, -38.0, 0, 1, // 111
		// upper
		0.5, 4.5, -37.5, 0, 0,   // 112
		0.7, 4.5, -37.5, 1, 0,  // 113
		0.7, 4.5, -38.0, 1, 1,  // 114
		0.5, 4.5, -38.0, 0, 1,   // 115
		// bottom
		0.7, 2.5, -38.0, 0, 0, // 116
		0.5, 2.5, -38.0, 1, 0,  // 117
		0.5, 2.5, -37.5, 1, 1,  // 118
		0.7, 2.5, -37.5, 0, 1, // 119
	};

	unsigned int indices1[] = {
		//tiang 1
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang 2
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//tiang 3
		48, 49, 50, 48, 50, 51,   // front
		52, 53, 54, 52, 54, 55,   // right
		56, 57, 58, 56, 58, 59,  // back
		60, 62, 61, 60, 63, 62,  // left
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		//tiang 4
		72, 73, 74, 72, 74, 75,   // front
		76, 77, 78, 76, 78, 79,   // right
		80, 81, 82, 80, 82, 83,  // back
		84, 86, 85, 84, 87, 86,  // left
		88, 90, 89, 88, 91, 90,  // upper
		92, 94, 93, 92, 95, 94,   // bottom
		//tiang 5
		96, 97, 98, 96, 98, 99,   // front
		100, 101, 102, 100, 102, 103,   // right
		104, 105, 106, 104, 106, 107,  // back
		108, 110, 109, 108, 111, 110,  // left
		112, 114, 113, 112, 115, 114,  // upper
		116, 118, 117, 116, 119, 118,   // bottom
		//tiang 6
		120, 121, 122, 120, 122, 123,   // front
		124, 125, 126, 124, 126, 127,   // right
		128, 129, 130, 128, 130, 131,  // back
		132, 134, 133, 132, 135, 134,  // left
		136, 138, 137, 136, 139, 138,  // upper
		140, 142, 141, 140, 143, 142,   // bottom
		//tiang 7
		144, 145, 146, 144, 146, 147,   // front
		148, 149, 150, 148, 150, 151,   // right
		152, 153, 154, 152, 154, 155,  // back
		156, 158, 157, 156, 159, 158,  // left
		160, 162, 161, 160, 163, 162,  // upper
		164, 166, 165, 164, 167, 166,   // bottom
		//tiang 8
		168, 169, 170, 168, 170, 171,   // front
		172, 173, 174, 172, 174, 175,   // right
		176, 177, 178, 176, 178, 179,  // back
		180, 182, 181, 180, 183, 182,  // left
		184, 186, 185, 184, 187, 186,  // upper
		188, 190, 189, 188, 191, 190,   // bottom
		//tiang 9
		192, 193, 194, 192, 194, 195,   // front
		196, 197, 198, 196, 198, 199,   // right
		200, 201, 202, 200, 202, 203,  // back
		204, 206, 205, 204, 207, 206,  // left
		208, 210, 209, 208, 211, 211,  // upper
		212, 214, 213, 212, 215, 214,   // bottom
		//tiang 10
		216, 217, 218, 216, 218, 219,   // front
		220, 221, 222, 220, 222, 223,   // right
		224, 225, 226, 224, 226, 227,  // back
		228, 230, 229, 228, 231, 230,  // left
		232, 234, 233, 232, 235, 234,  // upper
		236, 238, 237, 236, 239, 238,   // bottom
		//tiang 11
		240, 241, 242, 240, 242, 243,   // front
		244, 245, 246, 244, 246, 247,   // right
		248, 249, 250, 248, 250, 251,  // back
		252, 254, 253, 252, 255, 254,  // left
		256, 258, 257, 256, 259, 258,  // upper
		260, 262, 261, 260, 263, 262,   // bottom
		//tiang 12
		264, 265, 266, 264, 266, 267,   // front
		268, 269, 270, 268, 270, 271,   // right
		272, 273, 274, 272, 274, 275,  // back
		276, 278, 277, 276, 279, 278,  // left
		280, 282, 281, 280, 283, 282,  // upper
		284, 286, 285, 284, 287, 286,   // bottom
		//tiang 13
		288, 289, 290, 288, 290, 291,   // front
		292, 293, 294, 292, 294, 295,   // right
		296, 297, 298, 296, 298, 299,  // back
		300, 302, 301, 300, 303, 302,  // left
		304, 306, 305, 304, 307, 306,  // upper
		308, 310, 309, 308, 311, 310,   // bottom
		//tiang 14
		312, 313, 314, 312, 314, 315,   // front
		316, 317, 318, 316, 318, 319,   // right
		320, 321, 322, 320, 322, 323,  // back
		324, 326, 325, 324, 327, 326,  // left
		328, 330, 329, 328, 331, 330,  // upper
		332, 334, 333, 332, 335, 334,   // bottom
		//tiang 15
		336, 337, 338, 336, 338, 339,   // front
		340, 341, 342, 340, 342, 343,   // right
		344, 345, 346, 344, 346, 347,  // back
		348, 350, 349, 348, 351, 350,  // left
		352, 354, 353, 352, 355, 354,  // upper
		356, 358, 357, 356, 359, 358,   // bottom
		//tiang 16
		360, 361, 362, 360, 362, 363,   // front
		364, 365, 366, 364, 366, 367,   // right
		368, 369, 370, 368, 370, 371,  // back
		372, 374, 373, 372, 375, 374,  // left
		376, 378, 377, 376, 379, 378,  // upper
		380, 382, 381, 380, 383, 382,   // bottom
		//tiang 17
		384, 385, 386, 384, 386, 387,   // front
		388, 389, 390, 388, 390, 391,   // right
		392, 393, 394, 392, 394, 395,  // back
		396, 398, 397, 396, 399, 398,  // left
		400, 402, 401, 400, 403, 402,  // upper
		404, 406, 405, 404, 407, 406,   // bottom
		//tiang 18
		408, 409, 410, 408, 409, 410,   // front
		412, 413, 414, 412, 414, 415,   // right
		416, 417, 418, 416, 418, 419,  // back
		420, 422, 421, 420, 423, 422,  // left
		424, 426, 425, 424, 427, 426,  // upper
		428, 430, 429, 428, 431, 430,   // bottom
		//tiang 19
		432, 433, 434, 432, 434, 435,   // front
		436, 437, 438, 436, 438, 439,   // right
		440, 441, 442, 440, 442, 443,  // back
		444, 446, 445, 444, 447, 446,  // left
		448, 450, 449, 448, 451, 450,  // upper
		452, 454, 453, 452, 455, 454,   // bottom
		//tiang 20
		456, 457, 458, 456, 458, 459,   // front
		460, 461, 462, 460, 462, 463,   // right
		464, 465, 466, 464, 466, 467,  // back
		468, 470, 469, 468, 471, 470,  // left
		472, 474, 473, 472, 475, 474,  // upper
		476, 478, 477, 476, 479, 478,   // bottom
		//tiang 21
		480, 481, 482, 480, 482, 483,   // front
		484, 485, 486, 484, 486, 487,   // right
		488, 489, 490, 488, 490, 491,  // back
		492, 494, 493, 492, 495, 494,  // left
		496, 498, 497, 496, 499, 498,  // upper
		500, 502, 501, 500, 503, 502,   // bottom
		//tiang 22
		504, 505, 506, 504, 506, 507,   // front
		508, 509, 510, 508, 510, 511,   // right
		512, 513, 514, 512, 514, 515,  // back
		516, 518, 517, 516, 519, 518,  // left
		520, 522, 521, 520, 523, 522,  // upper
		524, 526, 525, 524, 527, 526,   // bottom
		//tiang 23
		528, 529, 530, 528, 530, 531,   // front
		532, 533, 534, 532, 534, 535,   // right
		536, 537, 538, 536, 538, 539,  // back
		540, 542, 541, 540, 543, 542,  // left
		544, 546, 545, 544, 547, 546,  // upper
		548, 550, 549, 548, 551, 550,   // bottom
		//tiang 24
		552, 553, 554, 552, 554, 555,   // front
		556, 557, 558, 556, 558, 559,   // right
		560, 561, 562, 560, 562, 563,  // back
		564, 566, 565, 564, 567, 566,  // left
		568, 570, 569, 568, 571, 570,  // upper
		572, 574, 573, 572, 575, 574,   // bottom
	};


	glGenVertexArrays(1, &VAO12);
	glGenBuffers(1, &VBO12);
	glGenBuffers(1, &EBO12);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTiang2(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO12);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 864, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredAtap2() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices2[] = {
		// format position, tex coords
		//TIANG ATAP 0
		// upper
		0.7, 11.0, -4.0, 0, 0,   // 112 kiba
		0.5, 11.0, -4.0, 1, 0,  // 113 kaba
		0.5, 11.0, 4.0, 1, 1,  // 114 kaat
		0.7, 11.0, 4.0, 0, 1,   // 115 kiat
		// bottom
		0.5, 10.5, 4.0, 0, 0, // 116
		0.7, 10.5, 4.0, 1, 0,  // 117
		0.7, 10.5, -4.0, 1, 1,  // 118
		0.5, 10.5, -4.0, 0, 1, // 119
		// front
		0.5, 10.5, 4.0, 0, 0,  // 120
		0.5, 10.5, -4.0, 1, 0,  // 121
		0.5, 11.0, -4.0, 1, 1, // 122
		0.5, 11.0, 4.0, 0, 1, // 123
		// back
		0.7, 10.5, 4.0, 0, 0, // 124
		0.7, 10.5, -4.0, 1, 0, // 125
		0.7, 11.0, -4.0, 1, 1, // 126
		0.7, 11.0, 4.0, 0, 1, // 127
		//TIANG ATAP 1
		// upper
		0.7, 10.0, -4.0, 0, 0,   // 128 kiba
		0.5, 10.0, -4.0, 1, 0,  // 129 kaba
		0.5, 10.0, -8.5, 1, 1,  // 130 kaat
		0.7, 10.0, -8.5, 0, 1,   // 131 kiat
		// bottom
		0.5, 9.5, -8.5, 0, 0, // 132
		0.7, 9.5, -8.5, 1, 0,  // 133
		0.7, 9.5, -4.0, 1, 1,  // 134
		0.5, 9.5, -4.0, 0, 1, // 135
		// front
		0.5, 9.5, -8.5, 0, 0,  // 136
		0.5, 9.5, -4.0, 1, 0,  // 137
		0.5, 10.0,-4.0, 1, 1, // 138
		0.5, 10.0,-8.5, 0, 1, // 139
		// back
		0.7, 9.5, -8.5, 0, 0, // 140
		0.7, 9.5, -4.0, 1, 0, // 141
		0.7, 10.0,-4.0, 1, 1, // 142
		0.7, 10.0,-8.5, 0, 1, // 143
		//TIANG ATAP 2
		// upper
		0.7, 9.0, -8.0, 0, 0,   // 144
		0.5, 9.0, -8.0, 1, 0,  // 145
		0.5, 9.0, -12.0, 1, 1,  // 146
		0.7, 9.0, -12.0, 0, 1,   // 147
		// bottom
		0.5, 8.5, -12.0, 0, 0, // 148
		0.7, 8.5, -12.0, 1, 0,  // 149
		0.7, 8.5, -8.0, 1, 1,  // 150
		0.5, 8.5, -8.0, 0, 1, // 151
		// front
		0.5, 8.5, -12.0, 0, 0,  // 152
		0.5, 8.5, -8.0, 1, 0,  // 153
		0.5, 9.0,-8.0, 1, 1, // 154
		0.5, 9.0,-12.0, 0, 1, // 155
		// back
		0.7, 8.5, -12.0, 0, 0, // 156
		0.7, 8.5, -8.0, 1, 0, // 157
		0.7, 9.0,-8.0, 1, 1, // 158
		0.7, 9.0, -12.0, 0, 1, // 159
		//TIANG ATAP 3
		// upper
		0.7, 8.0, -12.0, 0, 0,   // 160
		0.5, 8.0, -12.0, 1, 0,  // 161
		0.5, 8.0, -15.5, 1, 1,  // 162
		0.7, 8.0, -15.5, 0, 1,   // 163
		// bottom
		0.5, 7.5, -15.5, 0, 0, // 164
		0.7, 7.5, -15.5, 1, 0,  //165
		0.7, 7.5, -12.0, 1, 1,  // 166
		0.5, 7.5, -12.0, 0, 1, // 167
		// front
		0.5, 7.5, -15.5, 0, 0,  // 168
		0.5, 7.5, -12.0, 1, 0,  // 169
		0.5, 8.0, -12.0, 1, 1, // 170
		0.5, 8.0, -15.5, 0, 1, // 171
		// back
		0.7, 8.0, -15.5, 0, 0, // 172
		0.7, 8.0, -12.0, 1, 0, // 173
		0.7, 7.5, -12.0, 1, 1, // 174
		0.7, 7.5, -15.5, 0, 1, // 175
		//TIANG ATAP 4
		// upper
		0.7, 7.0, -15.5, 0, 0,   // 176
		0.5, 7.0, -15.5, 1, 0,  // 177
		0.5, 7.0, -23.0, 1, 1,  // 178
		0.7, 7.0, -23.0, 0, 1,   // 179
		// bottom
		0.5, 6.5, -23.0, 0, 0, // 180
		0.7, 6.5, -23.0, 1, 0,  // 181
		0.7, 6.5, -15.5, 1, 1,  // 182
		0.5, 6.5, -15.5, 0, 1, // 183
		// front
		0.5, 6.5, -23.0, 0, 0,  // 184
		0.5, 6.5, -15.5, 1, 0,  // 185
		0.5, 7.0, -15.5, 1, 1, // 186
		0.5, 7.0, -23.0, 0, 1, // 187
		// back
		0.7, 6.5, -23.0, 0, 0, // 188
		0.7, 6.5, -15.5, 1, 0, // 189
		0.7, 7.0, -15.5, 1, 1, // 190
		0.7, 7.0, -23.0, 0, 1, // 191
		//TIANG ATAP 5
		// upper
		0.7, 6.0, -23.0, 0, 0,   // 192
		0.5, 6.0, -23.0, 1, 0,  // 193
		0.5, 6.0, -32.0, 1, 1,  // 194
		0.7, 6.0, -32.0, 0, 1,   // 195
		// bottom
		0.5, 5.5, -32.0, 0, 0, // 196
		0.7, 5.5, -32.0, 1, 0,  // 197
		0.7, 5.5, -23.0, 1, 1,  // 198
		0.5, 5.5, -23.0, 0, 1, // 199
		// front
		0.5, 5.5, -32.0, 0, 0,  // 200
		0.5, 5.5, -23.0, 1, 0,  // 201
		0.5, 6.0, -23.0, 1, 1, // 202
		0.5, 6.0, -32.0, 0, 1, // 203
		// back
		0.7, 5.5, -32.0, 0, 0, // 204
		0.7, 5.5, -23.0, 1, 0, // 205
		0.7, 6.0, -23.0, 1, 1, // 206
		0.7, 6.0, -32.0, 0, 1, // 207
		//TIANG ATAP 6
		// upper
		0.5, 4.5, -32.0, 0, 0,   // 208
		0.7, 4.5, -32.0, 1, 0,  // 209
		0.7, 4.5, -38.0, 1, 1,  // 210
		0.5, 4.5, -38.0, 0, 1,   // 211
		// bottom
		0.7, 5.0, -38.0, 0, 0, // 212
		0.5, 5.0, -38.0, 1, 0,  // 213
		0.5, 5.0, -32.0, 1, 1,  // 214
		0.7, 5.0, -32.0, 0, 1, // 215
		// front
		0.7, 4.5, -38.0, 0, 0,  // 216
		0.7, 4.5, -32.0, 1, 0,  // 217
		0.7, 5.0, -32.0, 1, 1, // 218
		0.7, 5.0, -38.0, 0, 1, // 219
		// back
		0.5, 4.5, -38.0, 0, 0, // 220
		0.5, 4.5, -32.0, 1, 0, // 221
		0.5, 5.0, -32.0, 1, 1, // 222
		0.5, 5.0, -38.0, 0, 1, // 223
	};

	unsigned int indices2[] = {
		//atap tiang -1
		0, 2, 1, 0, 3, 2,  // upper
		4, 6, 5, 4, 7, 6,   // bottom
		8, 9, 10, 8, 11, 10, // front
		12, 13, 14, 12, 15, 14, // back
		//atap tiang -2
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom
		24, 25, 26, 24, 27, 26, // front
		28, 29, 30, 28, 31, 30, // back
		//atap tiang -3
		32, 34, 33, 32, 35, 34,  // upper
		36, 38, 37, 36, 39, 38,   // bottom
		40, 41, 42, 40, 42, 43, // front
		44, 45, 46, 44, 46, 47, // back
		//atap tiang -4
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63, // back
		//atap tiang -5
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		72, 73, 74, 72, 74, 75, // front
		76, 77, 78, 76, 78, 79, // back
		//atap tiang -6
		80, 82, 81, 80, 83, 82,  // upper
		84, 86, 85, 84, 87, 86,   // bottom
		88, 89, 90, 88, 90, 91, // front
		92, 93, 94, 92, 94, 95, // back
		//atap tiang -7
		96, 98, 97, 96, 99, 98,  // upper
		100, 102, 101, 100, 103, 102,   // bottom
		104, 105, 106, 104, 106, 107, // front
		108, 109, 110, 108, 110, 111, // back
	};


	glGenVertexArrays(1, &VAO13);
	glGenBuffers(1, &VBO13);
	glGenBuffers(1, &EBO13);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO13);

	glBindBuffer(GL_ARRAY_BUFFER, VBO13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO13);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredAtap2(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO13);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 168, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
//Sebelah Kanan//
void Demo::BuildColoredTiang1Kanan() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices1[] = {
		// format position, tex coords
		// TIANG 1
		 //front
		4.5, 8.5, 2.5, 0, 0,  // 0
		4.3, 8.5, 2.5, 1, 0,   // 1
		4.3, 10.5, 2.5, 1, 1,   // 2
		4.5, 10.5, 2.5, 0, 1,  // 3
		// right
		4.3,  10.5,  2.5, 0, 0,  // 4
		4.3,  10.5, -2.0, 1, 0,  // 5
		4.3, 8.5, -2.0, 1, 1,  // 6
		4.3, 8.5,  2.5, 0, 1,  // 7
		// back
		4.5, 8.5, -2.0, 0, 0, // 8 
		4.3, 8.5, -2.0, 1, 0, // 9
		4.3, 10.5, -2.0, 1, 1, // 10
		4.5, 10.5, -2.0, 0, 1, // 11
		// left
		4.5, 8.5, -2.0, 0, 0, // 12
		4.5, 8.5,  2.5, 1, 0, // 13
		4.5, 10.5, 2.5, 1, 1, // 14
		4.5, 10.5, -2.0, 0, 1, // 15
		// upper
		4.3, 10.5, 2.5, 0, 0,   // 16
		4.5, 10.5, 2.5, 1, 0,  // 17
		4.5, 10.5, -2.0, 1, 1,  // 18
		4.3, 10.5, -2.0, 0, 1,   // 19
		// bottom
		4.5, 8.5, -2.0, 0, 0, // 20
		4.3, 8.5, -2.0, 1, 0,  // 21
		4.3, 8.5,  2.5, 1, 1,  // 22
		4.5, 8.5,  2.5, 0, 1, // 23
		//TIANG 2
		// front
		4.5, 8.5, 3.5, 0, 0,  // 24 ,,kiba,
		4.3, 8.5, 3.5, 1, 0,  // 25 ,,kaba,
		4.3, 10.5, 3.5, 1, 1,  // 26 ,,kaat,
		4.5, 10.5, 3.5, 0, 1,  // 27 ,,kiat
		// right
		4.3,  10.5, 3.5, 0, 0,  // 28
		4.3,  10.5, 4.0, 1, 0,  // 29
		4.3, 8.5, 4.0, 1, 1,  // 30
		4.3, 8.5, 3.5, 0, 1,  // 31
		// back
		4.5, 8.5, 4.0, 0, 0, // 32
		4.3, 8.5, 4.0, 1, 0, // 33
		4.3, 10.5, 4.0, 1, 1, // 34
		4.5, 10.5, 4.0, 0, 1, // 35
		// left
		4.5, 8.5, 4.0, 0, 0, // 36
		4.5, 8.5, 3.5, 1, 0, // 37
		4.5, 10.5,3.5, 1, 1, // 38
		4.5, 10.5,4.0, 0, 1, // 39
		// upper
		4.3, 10.5, 3.5, 0, 0,   // 40
		4.5, 10.5, 3.5, 1, 0,  // 41
		4.5, 10.5, 4.0, 1, 1,  // 42
		4.3, 10.5, 4.0, 0, 1,   // 43
		// bottom
		4.5, 8.5, 4.0, 0, 0, // 44
		4.3, 8.5, 4.0, 1, 0,  // 45
		4.3, 8.5, 3.5, 1, 1,  // 46
		4.5, 8.5, 3.5, 0, 1, // 47
		//TIANG 3
		// front
		4.5, 7.5, 5.0, 0, 0,  // 48 ,,kiba,
		4.3, 7.5, 5.0, 1, 0,  // 49 ,,kaba,
		4.3, 9.5, 5.0, 1, 1,  // 50 ,,kaat,
		4.5, 9.5, 5.0, 0, 1,  // 51 ,,kiat
		// right
		4.3,  9.5, 5.0, 0, 0,  // 52
		4.3,  9.5, 5.5, 1, 0,  // 53
		4.3, 7.5, 5.5, 1, 1,  // 54
		4.3, 7.5,  5.0, 0, 1,  // 55
		// back
		4.5, 7.5, 5.5, 0, 0, // 56
		4.3, 7.5, 5.5, 1, 0, // 57
		4.3,  9.5, 5.5, 1, 1, // 58
		4.5,  9.5, 5.5, 0, 1, // 59
		// left
		4.5, 7.5, 5.5, 0, 0, // 60
		4.5, 7.5, 5.0, 1, 0, // 61
		4.5, 9.5, 5.0, 1, 1, // 62
		4.5, 9.5, 5.5, 0, 1, // 63
		// upper
		4.3, 9.5,  5.0, 0, 0,   // 64
		4.5, 9.5, 5.0, 1, 0,  // 65
		4.5, 9.5, 5.5, 1, 1,  // 66
		4.3,9.5, 5.5, 0, 1,   // 67
		// bottom
		4.5, 7.5, 5.5, 0, 0, // 68
		4.3, 7.5, 5.5, 1, 0,  // 69
		4.3, 7.5, 5.0, 1, 1,  // 70
		4.5, 7.5, 5.0, 0, 1, // 71
		//TIANG 4
		// front
		4.5, 7.5, 6.5, 0, 0,  // 72 ,,kiba,
		4.3, 7.5, 6.5, 1, 0,  // 73 ,,kaba,
		4.3, 9.5, 6.5, 1, 1,  // 74 ,,kaat,
		4.5, 9.5, 6.5, 0, 1,  // 75 ,,kiat
		// right
		4.3,  9.5, 6.5, 0, 0,  // 76
		4.3,  9.5, 7.0, 1, 0,  // 77
		4.3, 7.5, 7.0, 1, 1,  // 78
		4.3, 7.5, 6.5, 0, 1,  // 79
		// back
		4.5, 7.5, 7.0, 0, 0, // 80
		4.3, 7.5, 7.0, 1, 0, // 81
		4.3, 9.5,7.0, 1, 1, // 82
		4.5, 9.5,7.0, 0, 1, // 83
		// left
		4.5, 7.5, 7.0, 0, 0, // 84
		4.5, 7.5, 6.5, 1, 0, // 85
		4.5, 9.5, 6.5, 1, 1, // 86
		4.5, 9.5, 7.0, 0, 1, // 87
		// upper
		4.3, 9.5, 6.5, 0, 0,   // 88
		4.5, 9.5, 6.5, 1, 0,  // 89
		4.5, 9.5, 7.0, 1, 1,  // 90
		4.3, 9.5,7.0, 0, 1,   // 91
		// bottom
		4.5, 7.5, 7.0, 0, 0, // 92
		4.3, 7.5, 7.0, 1, 0,  // 93
		4.3, 7.5, 6.5, 1, 1,  // 94
		4.5, 7.5, 6.5, 0, 1, // 95
		//TIANG 5
		// front
		4.5, 6.5, 8.0, 0, 0,  // 96 ,,kiba,
		4.3, 6.5, 8.0, 1, 0,  // 97 ,,kaba,
		4.3, 9.5, 8.0, 1, 1,  // 98 ,,kaat,
		4.5, 9.5, 8.0, 0, 1,  // 99 ,,kiat
		// right
		4.3,  9.5, 8.0, 0, 0,  // 100
		4.3,  9.5, 8.5, 1, 0,  // 101
		4.3, 6.5, 8.5, 1, 1,  // 102
		4.3, 6.5, 8.0, 0, 1,  // 103
		// back
		4.5, 6.5, 8.5, 0, 0, // 104
		4.3, 6.5, 8.5, 1, 0, // 105
		4.3,  9.5, 8.5, 1, 1, // 106
		4.5,  9.5, 8.5, 0, 1, // 107
		// left
		4.5, 6.5, 8.5, 0, 0, // 108
		4.5, 6.5, 8.0, 1, 0, // 109
		4.5,  9.5,8.0, 1, 1, // 110
		4.5,  9.5, 8.5, 0, 1, // 111
		// upper
		4.3, 9.5,  8.0, 0, 0,   // 112
		4.5, 9.5, 8.0, 1, 0,  // 113
		4.5, 9.5, 8.5, 1, 1,  // 114
		4.3, 9.5, 8.5, 0, 1,   // 115
		// bottom
		4.5, 6.5, 8.5, 0, 0, // 116
		4.3, 6.5,8.5, 1, 0,  // 117
		4.3, 6.5, 8.0, 1, 1,  // 118
		4.5, 6.5, 8.0, 0, 1, // 119
		//TIANG 6
		// front
		4.5, 6.5, 11.5, 0, 0,  // 96 ,,kiba,
		4.3, 6.5, 11.5, 1, 0,  // 97 ,,kaba,
		4.3, 8.5, 11.5, 1, 1,  // 98 ,,kaat,
		4.5, 8.5, 11.5, 0, 1,  // 99 ,,kiat
		// right
		4.3,  8.5, 11.5, 0, 0,  // 100
		4.3,  8.5, 12.0, 1, 0,  // 101
		4.3, 6.5, 12.0, 1, 1,  // 102
		4.3, 6.5, 11.5, 0, 1,  // 103
		// back
		4.5, 6.5, 12.0, 0, 0, // 104
		4.3, 6.5, 12.0, 1, 0, // 105
		4.3, 8.5, 12.0, 1, 1, // 106
		4.5, 8.5, 12.0, 0, 1, // 107
		// left
		4.5, 6.5, 12.0, 0, 0, // 108
		4.5, 6.5, 11.5, 1, 0, // 109
		4.5, 8.5, 11.5, 1, 1, // 110
		4.5, 8.5, 12.0, 0, 1, // 111
		// upper
		4.3, 8.5, 11.5, 0, 0,   // 112
		4.5, 8.5, 11.5, 1, 0,  // 113
		4.5, 8.5, 12.0, 1, 1,  // 114
		4.3, 8.5, 12.0, 0, 1,   // 115
		// bottom
		4.5, 6.5, 12.0, 0, 0, // 116
		4.3, 6.5, 12.0, 1, 0,  // 117
		4.3, 6.5, 11.5, 1, 1,  // 118
		4.5, 6.5, 11.5, 0, 1, // 119
		//TIANG 7
		// front
		4.5, 5.5, 12.0, 0, 0,  // 96 ,,kiba,
		4.3, 5.5, 12.0, 1, 0,  // 97 ,,kaba,
		4.3, 7.5, 12.0, 1, 1,  // 98 ,,kaat,
		4.5, 7.5, 12.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 7.5, 12.0, 0, 0,  // 100
		4.3, 7.5, 12.5, 1, 0,  // 101
		4.3, 5.5, 12.5, 1, 1,  // 102
		4.3, 5.5, 12.0, 0, 1,  // 103
		// back
		4.5, 5.5, 12.5, 0, 0, // 104
		4.3, 5.5, 12.5, 1, 0, // 105
		4.3, 7.5, 12.5, 1, 1, // 106
		4.5, 7.5, 12.5, 0, 1, // 107
		// left
		4.5, 5.5, 12.5, 0, 0, // 108
		4.5, 5.5, 12.0, 1, 0, // 109
		4.5, 7.5, 12.0, 1, 1, // 110
		4.5, 7.5, 12.5, 0, 1, // 111
		// upper
		4.3, 7.5, 12.0, 0, 0,   // 112
		4.5, 7.5, 12.0, 1, 0,  // 113
		4.5, 7.5, 12.5, 1, 1,  // 114
		4.3, 7.5, 12.5, 0, 1,   // 115
		// bottom
		4.5, 5.5, 12.5, 0, 0, // 116
		4.3, 5.5, 12.5, 1, 0,  // 117
		4.3, 5.5, 12.0, 1, 1,  // 118
		4.5, 5.5, 12.0, 0, 1, // 119
		//TIANG 8
		// front
		4.5, 5.5, 13.5, 0, 0,  // 96 ,,kiba,
		4.3, 5.5, 13.5, 1, 0,  // 97 ,,kaba,
		4.3, 7.5, 13.5, 1, 1,  // 98 ,,kaat,
		4.5, 7.5, 13.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 7.5, 13.5, 0, 0,  // 100
		4.3, 7.5, 14.0, 1, 0,  // 101
		4.3, 5.5, 14.0, 1, 1,  // 102
		4.3, 5.5, 13.5, 0, 1,  // 103
		// back
		4.5, 5.5, 14.0, 0, 0, // 104
		4.3, 5.5, 14.0, 1, 0, // 105
		4.3, 7.5, 14.0, 1, 1, // 106
		4.5, 7.5, 14.0, 0, 1, // 107
		// left
		4.5, 5.5, 14.0, 0, 0, // 108
		4.5, 5.5, 13.5, 1, 0, // 109
		4.5, 7.5, 13.5, 1, 1, // 110
		4.5, 7.5, 14.0, 0, 1, // 111
		// upper
		4.3, 7.5, 13.5, 0, 0,   // 112
		4.5, 7.5, 13.5, 1, 0,  // 113
		4.5, 7.5, 14.0, 1, 1,  // 114
		4.3, 7.5, 14.0, 0, 1,   // 115
		// bottom
		4.5, 5.5, 14.0, 0, 0, // 116
		4.3, 5.5, 14.0, 1, 0,  // 117
		4.3, 5.5, 13.5, 1, 1,  // 118
		4.5, 5.5, 13.5, 0, 1, // 119
		//TIANG 9
		// front
		4.5, 5.5, 15.0, 0, 0,  // 96 ,,kiba,
		4.3, 5.5, 15.0, 1, 0,  // 97 ,,kaba,
		4.3, 7.5, 15.0, 1, 1,  // 98 ,,kaat,
		4.5, 7.5, 15.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 7.5, 15.0, 0, 0,  // 100
		4.3, 7.5, 15.5, 1, 0,  // 101
		4.3, 5.5, 15.5, 1, 1,  // 102
		4.3, 5.5, 15.0, 0, 1,  // 103
		// back
		4.5, 5.5, 15.5, 0, 0, // 104
		4.3, 5.5, 15.5, 1, 0, // 105
		4.3, 7.5, 15.5, 1, 1, // 106
		4.5, 7.5, 15.5, 0, 1, // 107
		// left
		4.5, 5.5, 15.5, 0, 0, // 108
		4.5, 5.5, 15.0, 1, 0, // 109
		4.5, 7.5, 15.0, 1, 1, // 110
		4.5, 7.5, 15.5, 0, 1, // 111
		// upper
		4.3, 7.5, 15.0, 0, 0,   // 112
		4.5, 7.5, 15.0, 1, 0,  // 113
		4.5, 7.5, 15.5, 1, 1,  // 114
		4.3, 7.5, 15.5, 0, 1,   // 115
		// bottom
		4.5, 5.5, 15.5, 0, 0, // 116
		4.3, 5.5, 15.5, 1, 0,  // 117
		4.3, 5.5, 15.0, 1, 1,  // 118
		4.5, 5.5, 15.0, 0, 1, // 119
		//TIANG 10
		// front
		4.5, 4.5, 16.5, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, 16.5, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, 16.5, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, 16.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, 16.5, 0, 0,  // 100
		4.3, 6.5, 17.0, 1, 0,  // 101
		4.3, 4.5, 17.0, 1, 1,  // 102
		4.3, 4.5, 16.5, 0, 1,  // 103
		// back
		4.5, 4.5, 17.0, 0, 0, // 104
		4.3, 4.5, 17.0, 1, 0, // 105
		4.3, 6.5, 17.0, 1, 1, // 106
		4.5, 6.5, 17.0, 0, 1, // 107
		// left
		4.5, 4.5, 17.0, 0, 0, // 108
		4.5, 4.5, 16.5, 1, 0, // 109
		4.5, 6.5, 16.5, 1, 1, // 110
		4.5, 6.5, 17.0, 0, 1, // 111
		// upper
		4.3, 6.5, 16.5, 0, 0,   // 112
		4.5, 6.5, 16.5, 1, 0,  // 113
		4.5, 6.5, 17.0, 1, 1,  // 114
		4.3, 6.5, 17.0, 0, 1,   // 115
		// bottom
		4.5, 4.5, 17.0, 0, 0, // 116
		4.3, 4.5, 17.0, 1, 0,  // 117
		4.3, 4.5, 16.5, 1, 1,  // 118
		4.5, 4.5, 16.5, 0, 1, // 119
		//TIANG 11
		// front
		4.5, 4.5, 18.0, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, 18.0, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, 18.0, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, 18.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, 18.0, 0, 0,  // 100
		4.3, 6.5, 18.5, 1, 0,  // 101
		4.3, 4.5, 18.5, 1, 1,  // 102
		4.3, 4.5, 18.0, 0, 1,  // 103
		// back
		4.5, 4.5, 18.5, 0, 0, // 104
		4.3, 4.5, 18.5, 1, 0, // 105
		4.3, 6.5, 18.5, 1, 1, // 106
		4.5, 6.5, 18.5, 0, 1, // 107
		// left
		4.5, 4.5, 18.5, 0, 0, // 108
		4.5, 4.5, 18.0, 1, 0, // 109
		4.5, 6.5, 18.0, 1, 1, // 110
		4.5, 6.5, 18.5, 0, 1, // 111
		// upper
		4.3, 6.5, 18.0, 0, 0,   // 112
		4.5, 6.5, 18.0, 1, 0,  // 113
		4.5, 6.5, 18.5, 1, 1,  // 114
		4.3, 6.5, 18.5, 0, 1,   // 115
		// bottom
		4.5, 4.5, 18.5, 0, 0, // 116
		4.3, 4.5, 18.5, 1, 0,  // 117
		4.3, 4.5, 18.0, 1, 1,  // 118
		4.5, 4.5, 18.0, 0, 1, // 119
		//TIANG 12
		// front
		4.5, 4.5, 19.5, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, 19.5, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, 19.5, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, 19.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, 19.5, 0, 0,  // 100
		4.3, 6.5, 20.0, 1, 0,  // 101
		4.3, 4.5, 20.0, 1, 1,  // 102
		4.3, 4.5, 19.5, 0, 1,  // 103
		// back
		4.5, 4.5, 20.0, 0, 0, // 104
		4.3, 4.5, 20.0, 1, 0, // 105
		4.3, 6.5, 20.0, 1, 1, // 106
		4.5, 6.5, 20.0, 0, 1, // 107
		// left
		4.5, 4.5, 20.0, 0, 0, // 108
		4.5, 4.5, 19.5, 1, 0, // 109
		4.5, 6.5, 19.5, 1, 1, // 110
		4.5, 6.5, 20.0, 0, 1, // 111
		// upper
		4.3, 6.5, 19.5, 0, 0,   // 112
		4.5, 6.5, 19.5, 1, 0,  // 113
		4.5, 6.5, 20.0, 1, 1,  // 114
		4.3, 6.5, 20.0, 0, 1,   // 115
		// bottom
		4.5, 4.5, 20.0, 0, 0, // 116
		4.3, 4.5, 20.0, 1, 0,  // 117
		4.3, 4.5, 19.5, 1, 1,  // 118
		4.5, 4.5, 19.5, 0, 1, // 119
		//TIANG 13
		// front
		4.5, 4.5, 21.0, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, 21.0, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, 21.0, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, 21.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, 21.0, 0, 0,  // 100
		4.3, 6.5, 21.5, 1, 0,  // 101
		4.3, 4.5, 21.5, 1, 1,  // 102
		4.3, 4.5, 21.0, 0, 1,  // 103
		// back
		4.5, 4.5, 21.5, 0, 0, // 104
		4.3, 4.5, 21.5, 1, 0, // 105
		4.3, 6.5, 21.5, 1, 1, // 106
		4.5, 6.5, 21.5, 0, 1, // 107
		// left
		4.5, 4.5, 21.5, 0, 0, // 108
		4.5, 4.5, 21.0, 1, 0, // 109
		4.5, 6.5, 21.0, 1, 1, // 110
		4.5, 6.5, 21.5, 0, 1, // 111
		// upper
		4.3, 6.5, 21.0, 0, 0,   // 112
		4.5, 6.5, 21.0, 1, 0,  // 113
		4.5, 6.5, 21.5, 1, 1,  // 114
		4.3, 6.5, 21.5, 0, 1,   // 115
		// bottom
		4.5, 4.5, 21.5, 0, 0, // 116
		4.3, 4.5, 21.5, 1, 0,  // 117
		4.3, 4.5, 21.0, 1, 1,  // 118
		4.5, 4.5, 21.0, 0, 1, // 119
		//TIANG 14
		// front
		4.5, 4.5, 22.5, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, 22.5, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, 22.5, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, 22.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, 22.5, 0, 0,  // 100
		4.3, 6.5, 23.0, 1, 0,  // 101
		4.3, 4.5, 23.0, 1, 1,  // 102
		4.3, 4.5, 22.5, 0, 1,  // 103
		// back
		4.5, 4.5, 23.0, 0, 0, // 104
		4.3, 4.5, 23.0, 1, 0, // 105
		4.3, 6.5, 23.0, 1, 1, // 106
		4.5, 6.5, 23.0, 0, 1, // 107
		// left
		4.5, 4.5, 23.0, 0, 0, // 108
		4.5, 4.5, 22.5, 1, 0, // 109
		4.5, 6.5, 22.5, 1, 1, // 110
		4.5, 6.5, 23.0, 0, 1, // 111
		// upper
		4.3, 6.5, 22.5, 0, 0,   // 112
		4.5, 6.5, 22.5, 1, 0,  // 113
		4.5, 6.5, 23.0, 1, 1,  // 114
		4.3, 6.5, 23.0, 0, 1,   // 115
		// bottom
		4.5, 4.5, 23.0, 0, 0, // 116
		4.3, 4.5, 23.0, 1, 0,  // 117
		4.3, 4.5, 22.5, 1, 1,  // 118
		4.5, 4.5, 22.5, 0, 1, // 119
		//TIANG 15
		// front
		4.5, 3.5, 24.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 24.0, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, 24.0, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, 24.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, 24.0, 0, 0,  // 100
		4.3, 5.5, 24.5, 1, 0,  // 101
		4.3, 3.5, 24.5, 1, 1,  // 102
		4.3, 3.5, 24.0, 0, 1,  // 103
		// back
		4.5, 3.5, 24.5, 0, 0, // 104
		4.3, 3.5, 24.5, 1, 0, // 105
		4.3, 5.5, 24.5, 1, 1, // 106
		4.5, 5.5, 24.5, 0, 1, // 107
		// left
		4.5, 3.5, 24.5, 0, 0, // 108
		4.5, 3.5, 24.0, 1, 0, // 109
		4.5, 5.5, 24.0, 1, 1, // 110
		4.5, 5.5, 24.5, 0, 1, // 111
		// upper
		4.3, 5.5, 24.0, 0, 0,   // 112
		4.5, 5.5, 24.0, 1, 0,  // 113
		4.5, 5.5, 24.5, 1, 1,  // 114
		4.3, 5.5, 24.5, 0, 1,   // 115
		// bottom
		4.5, 3.5, 24.5, 0, 0, // 116
		4.3, 3.5, 24.5, 1, 0,  // 117
		4.3, 3.5, 24.0, 1, 1,  // 118
		4.5, 3.5, 24.0, 0, 1, // 119
		//TIANG 16
		// front
		4.5, 3.5, 25.5, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 25.5, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, 25.5, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, 25.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, 25.5, 0, 0,  // 100
		4.3, 5.5, 26.0, 1, 0,  // 101
		4.3, 3.5, 26.0, 1, 1,  // 102
		4.3, 3.5, 25.5, 0, 1,  // 103
		// back
		4.5, 3.5, 26.0, 0, 0, // 104
		4.3, 3.5, 25.5, 1, 0, // 105
		4.3, 5.5, 25.5, 1, 1, // 106
		4.5, 5.5, 26.0, 0, 1, // 107
		// left
		4.5, 3.5, 26.0, 0, 0, // 108
		4.5, 3.5, 25.5, 1, 0, // 109
		4.5, 5.5, 25.5, 1, 1, // 110
		4.5, 5.5, 26.0, 0, 1, // 111
		// upper
		4.3, 5.5, 25.5, 0, 0,   // 112
		4.5, 5.5, 25.5, 1, 0,  // 113
		4.5, 5.5, 26.0, 1, 1,  // 114
		4.3, 5.5, 26.0, 0, 1,   // 115
		// bottom
		4.5, 3.5, 26.0, 0, 0, // 116
		4.3, 3.5, 26.0, 1, 0,  // 117
		4.3, 3.5, 25.5, 1, 1,  // 118
		4.5, 3.5, 25.5, 0, 1, // 119
		//TIANG 17
		// front
		4.5, 3.5, 27.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 27.0, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, 27.0, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, 27.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, 27.0, 0, 0,  // 100
		4.3, 5.5, 27.5, 1, 0,  // 101
		4.3, 3.5, 27.5, 1, 1,  // 102
		4.3, 3.5, 27.0, 0, 1,  // 103
		// back
		4.5, 3.5, 27.5, 0, 0, // 104
		4.3, 3.5, 27.5, 1, 0, // 105
		4.3, 5.5, 27.5, 1, 1, // 106
		4.5, 5.5, 27.5, 0, 1, // 107
		// left
		4.5, 3.5, 27.5, 0, 0, // 108
		4.5, 3.5, 27.0, 1, 0, // 109
		4.5, 5.5, 27.0, 1, 1, // 110
		4.5, 5.5, 27.5, 0, 1, // 111
		// upper
		4.3, 5.5, 27.0, 0, 0,   // 112
		4.5, 5.5, 27.0, 1, 0,  // 113
		4.5, 5.5, 27.5, 1, 1,  // 114
		4.3, 5.5, 27.5, 0, 1,   // 115
		// bottom
		4.5, 3.5, 27.5, 0, 0, // 116
		4.3, 3.5, 27.5, 1, 0,  // 117
		4.3, 3.5, 27.0, 1, 1,  // 118
		4.5, 3.5, 27.0, 0, 1, // 119
		//TIANG 18
		// front
		4.5, 3.5, 28.5, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 28.5, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, 28.5, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, 28.5, 0, 1,  // 99 ,,kiat
		//right
		4.3, 5.5, 28.5, 0, 0,  // 100
		4.3, 5.5, 29.0, 1, 0,  // 101
		4.3, 3.5, 29.0, 1, 1,  // 102
		4.3, 3.5, 28.5, 0, 1,  // 103
		// back
		4.5, 3.5, 29.0, 0, 0, // 104
		4.3, 3.5, 29.0, 1, 0, // 105
		4.3, 5.5, 29.0, 1, 1, // 106
		4.5, 5.5, 29.0, 0, 1, // 107
		// left
		4.5, 3.5, 29.0, 0, 0, // 108
		4.5, 3.5, 28.5, 1, 0, // 109
		4.5, 5.5, 28.5, 1, 1, // 110
		4.5, 5.5, 29.0, 0, 1, // 111
		// upper
		4.3, 5.5, 28.5, 0, 0,   // 112
		4.5, 5.5, 28.5, 1, 0,  // 113
		4.5, 5.5, 29.0, 1, 1,  // 114
		4.3, 5.5, 29.0, 0, 1,   // 115
		// bottom
		4.5, 3.5, 29.0, 0, 0, // 116
		4.3, 3.5, 29.0, 1, 0,  // 117
		4.3, 3.5, 28.5, 1, 1,  // 118
		4.5, 3.5, 28.5, 0, 1, // 119
		//TIANG 19
		// front
		4.5, 3.5, 30.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 30.0, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, 30.0, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, 30.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, 30.0, 0, 0,  // 100
		4.3, 5.5, 30.5, 1, 0,  // 101
		4.3, 3.5, 30.5, 1, 1,  // 102
		4.3, 3.5, 30.0, 0, 1,  // 103
		// back
		4.5, 3.5, 30.5, 0, 0, // 104
		4.3, 3.5, 30.5, 1, 0, // 105
		4.3, 5.5, 30.5, 1, 1, // 106
		4.5, 5.5, 30.5, 0, 1, // 107
		// left
		4.5, 3.5, 30.5, 0, 0, // 108
		4.5, 3.5, 30.0, 1, 0, // 109
		4.5, 5.5, 30.0, 1, 1, // 110
		4.5, 5.5, 30.5, 0, 1, // 111
		// upper
		4.3, 5.5, 30.0, 0, 0,   // 112
		4.5, 5.5, 30.0, 1, 0,  // 113
		4.5, 5.5, 30.5, 1, 1,  // 114
		4.3, 5.5, 30.5, 0, 1,   // 115
		// bottom
		4.5, 3.5, 30.5, 0, 0, // 116
		4.3, 3.5, 30.5, 1, 0,  // 117
		4.3, 3.5, 30.0, 1, 1,  // 118
		4.5, 3.5, 30.0, 0, 1, // 119
		//TIANG 20
		// front
		4.5, 3.5, 31.5, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 31.5, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, 31.5, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, 31.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, 31.5, 0, 0,  // 100
		4.3, 5.5, 32.0, 1, 0,  // 101
		4.3, 3.5, 32.0, 1, 1,  // 102
		4.3, 3.5, 31.5, 0, 1,  // 103
		// back
		4.5, 3.5, 32.0, 0, 0, // 104
		4.3, 3.5, 32.0, 1, 0, // 105
		4.3, 5.5, 32.0, 1, 1, // 106
		4.5, 5.5, 32.0, 0, 1, // 107
		// left
		4.5, 3.5, 32.0, 0, 0, // 108
		4.5, 3.5, 31.5, 1, 0, // 109
		4.5, 5.5, 31.5, 1, 1, // 110
		4.5, 5.5, 32.0, 0, 1, // 111
		// upper
		4.3, 5.5, 31.5, 0, 0,   // 112
		4.5, 5.5, 31.5, 1, 0,  // 113
		4.5, 5.5, 32.0, 1, 1,  // 114
		4.3, 5.5, 32.0, 0, 1,   // 115
		// bottom
		4.5, 3.5, 32.0, 0, 0, // 116
		4.3, 3.5, 32.0, 1, 0,  // 117
		4.3, 3.5, 31.5, 1, 1,  // 118
		4.5, 3.5, 31.5, 0, 1, // 119
		//TIANG 21
		// front
		4.5, 3.5, 33.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, 33.0, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, 33.0, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, 33.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, 33.0, 0, 0,  // 100
		4.3, 4.5, 33.5, 1, 0,  // 101
		4.3, 2.5, 33.5, 1, 1,  // 102
		4.3, 2.5, 33.0, 0, 1,  // 103
		// back
		4.5, 2.5, 33.5, 0, 0, // 104
		4.3, 2.5, 33.5, 1, 0, // 105
		4.3, 4.5, 33.5, 1, 1, // 106
		4.5, 4.5, 33.5, 0, 1, // 107
		// left
		4.5, 2.5, 33.5, 0, 0, // 108
		4.5, 2.5, 33.0, 1, 0, // 109
		4.5, 4.5, 33.0, 1, 1, // 110
		4.5, 4.5, 33.5, 0, 1, // 111
		// upper
		4.3, 4.5, 33.0, 0, 0,   // 112
		4.5, 4.5, 33.0, 1, 0,  // 113
		4.5, 4.5, 33.5, 1, 1,  // 114
		4.3, 4.5, 33.5, 0, 1,   // 115
		// bottom
		4.5, 2.5, 33.5, 0, 0, // 116
		4.3, 2.5, 33.5, 1, 0,  // 117
		4.3, 2.5, 33.0, 1, 1,  // 118
		4.5, 2.5, 33.0, 0, 1, // 119
		//TIANG 22
		// front
		4.5, 2.5, 34.5, 0, 0,  // 96 ,,kiba,
		4.3, 2.5, 34.5, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, 34.5, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, 34.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, 34.5, 0, 0,  // 100
		4.3, 4.5, 35.0, 1, 0,  // 101
		4.3, 2.5, 35.0, 1, 1,  // 102
		4.3, 2.5, 34.5, 0, 1,  // 103
		// back
		4.5, 2.5, 35.0, 0, 0, // 104
		4.3, 2.5, 35.0, 1, 0, // 105
		4.3, 4.5, 35.0, 1, 1, // 106
		4.5, 4.5, 35.0, 0, 1, // 107
		// left
		4.5, 2.5, 35.0, 0, 0, // 108
		4.5, 2.5, 34.5, 1, 0, // 109
		4.5, 4.5, 34.5, 1, 1, // 110
		4.5, 4.5, 35.0, 0, 1, // 111
		// upper
		4.3, 4.5, 34.5, 0, 0,   // 112
		4.5, 4.5, 34.5, 1, 0,  // 113
		4.5, 4.5, 35.0, 1, 1,  // 114
		4.3, 4.5, 35.0, 0, 1,   // 115
		// bottom
		4.5, 2.5, 35.0, 0, 0, // 116
		4.3, 2.5, 35.0, 1, 0,  // 117
		4.3, 2.5, 34.5, 1, 1,  // 118
		4.5, 2.5, 34.5, 0, 1, // 119
		//TIANG 23
		// front
		4.5, 2.5, 36.0, 0, 0,  // 96 ,,kiba,
		4.3, 2.5, 36.0, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, 36.0, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, 36.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, 36.0, 0, 0,  // 100
		4.3, 4.5, 36.5, 1, 0,  // 101
		4.3, 2.5, 36.5, 1, 1,  // 102
		4.3, 2.5, 36.0, 0, 1,  // 103
		// back
		4.5, 2.5, 36.5, 0, 0, // 104
		4.3, 2.5, 36.5, 1, 0, // 105
		4.3, 4.5, 36.5, 1, 1, // 106
		4.5, 4.5, 36.5, 0, 1, // 107
		// left
		4.5, 2.5, 36.5, 0, 0, // 108
		4.5, 2.5, 36.0, 1, 0, // 109
		4.5, 4.5, 36.0, 1, 1, // 110
		4.5, 4.5, 36.5, 0, 1, // 111
		// upper
		4.3, 4.5, 36.0, 0, 0,   // 112
		4.5, 4.5, 36.0, 1, 0,  // 113
		4.5, 4.5, 36.5, 1, 1,  // 114
		4.3, 4.5, 36.5, 0, 1,   // 115
		// bottom
		4.5, 2.5, 36.5, 0, 0, // 116
		4.3, 2.5, 36.5, 1, 0,  // 117
		4.3, 2.5, 36.0, 1, 1,  // 118
		4.5, 2.5, 36.0, 0, 1, // 119
		//TIANG 24
		// front
		4.5, 2.5, 37.5, 0, 0,  // 96 ,,kiba,
		4.3, 2.5, 37.5, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, 37.5, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, 37.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, 37.5, 0, 0,  // 100
		4.3, 4.5, 38.0, 1, 0,  // 101
		4.3, 2.5, 38.0, 1, 1,  // 102
		4.3, 2.5, 37.5, 0, 1,  // 103
		// back
		4.5, 2.5, 38.0, 0, 0, // 104
		4.3, 2.5, 38.0, 1, 0, // 105
		4.3, 4.5, 38.0, 1, 1, // 106
		4.5, 4.5, 38.0, 0, 1, // 107
		// left
		4.5, 2.5, 38.0, 0, 0, // 108
		4.5, 2.5, 37.5, 1, 0, // 109
		4.5, 4.5, 37.5, 1, 1, // 110
		4.5, 4.5, 38.0, 0, 1, // 111
		// upper
		4.3, 4.5, 37.5, 0, 0,   // 112
		4.5, 4.5, 37.5, 1, 0,  // 113
		4.5, 4.5, 38.0, 1, 1,  // 114
		4.3, 4.5, 38.0, 0, 1,   // 115
		// bottom
		4.5, 2.5, 38.0, 0, 0, // 116
		4.3, 2.5, 38.0, 1, 0,  // 117
		4.3, 2.5, 37.5, 1, 1,  // 118
		4.5, 2.5, 37.5, 0, 1, // 119
	};

	unsigned int indices1[] = {
		//tiang 1
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang 2
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//tiang 3
		48, 49, 50, 48, 50, 51,   // front
		52, 53, 54, 52, 54, 55,   // right
		56, 57, 58, 56, 58, 59,  // back
		60, 62, 61, 60, 63, 62,  // left
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		//tiang 4
		72, 73, 74, 72, 74, 75,   // front
		76, 77, 78, 76, 78, 79,   // right
		80, 81, 82, 80, 82, 83,  // back
		84, 86, 85, 84, 87, 86,  // left
		88, 90, 89, 88, 91, 90,  // upper
		92, 94, 93, 92, 95, 94,   // bottom
		//tiang 5
		96, 97, 98, 96, 98, 99,   // front
		100, 101, 102, 100, 102, 103,   // right
		104, 105, 106, 104, 106, 107,  // back
		108, 110, 109, 108, 111, 110,  // left
		112, 114, 113, 112, 115, 114,  // upper
		116, 118, 117, 116, 119, 118,   // bottom
		//tiang 6
		120, 121, 122, 120, 122, 123,   // front
		124, 125, 126, 124, 126, 127,   // right
		128, 129, 130, 128, 130, 131,  // back
		132, 134, 133, 132, 135, 134,  // left
		136, 138, 137, 136, 139, 138,  // upper
		140, 142, 141, 140, 143, 142,   // bottom
		//tiang 7
		144, 145, 146, 144, 146, 147,   // front
		148, 149, 150, 148, 150, 151,   // right
		152, 153, 154, 152, 154, 155,  // back
		156, 158, 157, 156, 159, 158,  // left
		160, 162, 161, 160, 163, 162,  // upper
		164, 166, 165, 164, 167, 166,   // bottom
		//tiang 8
		168, 169, 170, 168, 170, 171,   // front
		172, 173, 174, 172, 174, 175,   // right
		176, 177, 178, 176, 178, 179,  // back
		180, 182, 181, 180, 183, 182,  // left
		184, 186, 185, 184, 187, 186,  // upper
		188, 190, 189, 188, 191, 190,   // bottom
		//tiang 9
		192, 193, 194, 192, 194, 195,   // front
		196, 197, 198, 196, 198, 199,   // right
		200, 201, 202, 200, 202, 203,  // back
		204, 206, 205, 204, 207, 206,  // left
		208, 210, 209, 208, 211, 211,  // upper
		212, 214, 213, 212, 215, 214,   // bottom
		//tiang 10
		216, 217, 218, 216, 218, 219,   // front
		220, 221, 222, 220, 222, 223,   // right
		224, 225, 226, 224, 226, 227,  // back
		228, 230, 229, 228, 231, 230,  // left
		232, 234, 233, 232, 235, 234,  // upper
		236, 238, 237, 236, 239, 238,   // bottom
		//tiang 11
		240, 241, 242, 240, 242, 243,   // front
		244, 245, 246, 244, 246, 247,   // right
		248, 249, 250, 248, 250, 251,  // back
		252, 254, 253, 252, 255, 254,  // left
		256, 258, 257, 256, 259, 258,  // upper
		260, 262, 261, 260, 263, 262,   // bottom
		//tiang 12
		264, 265, 266, 264, 266, 267,   // front
		268, 269, 270, 268, 270, 271,   // right
		272, 273, 274, 272, 274, 275,  // back
		276, 278, 277, 276, 279, 278,  // left
		280, 282, 281, 280, 283, 282,  // upper
		284, 286, 285, 284, 287, 286,   // bottom
		//tiang 13
		288, 289, 290, 288, 290, 291,   // front
		292, 293, 294, 292, 294, 295,   // right
		296, 297, 298, 296, 298, 299,  // back
		300, 302, 301, 300, 303, 302,  // left
		304, 306, 305, 304, 307, 306,  // upper
		308, 310, 309, 308, 311, 310,   // bottom
		//tiang 14
		312, 313, 314, 312, 314, 315,   // front
		316, 317, 318, 316, 318, 319,   // right
		320, 321, 322, 320, 322, 323,  // back
		324, 326, 325, 324, 327, 326,  // left
		328, 330, 329, 328, 331, 330,  // upper
		332, 334, 333, 332, 335, 334,   // bottom
		//tiang 15
		336, 337, 338, 336, 338, 339,   // front
		340, 341, 342, 340, 342, 343,   // right
		344, 345, 346, 344, 346, 347,  // back
		348, 350, 349, 348, 351, 350,  // left
		352, 354, 353, 352, 355, 354,  // upper
		356, 358, 357, 356, 359, 358,   // bottom
		//tiang 16
		360, 361, 362, 360, 362, 363,   // front
		364, 365, 366, 364, 366, 367,   // right
		368, 369, 370, 368, 370, 371,  // back
		372, 374, 373, 372, 375, 374,  // left
		376, 378, 377, 376, 379, 378,  // upper
		380, 382, 381, 380, 383, 382,   // bottom
		//tiang 17
		384, 385, 386, 384, 386, 387,   // front
		388, 389, 390, 388, 390, 391,   // right
		392, 393, 394, 392, 394, 395,  // back
		396, 398, 397, 396, 399, 398,  // left
		400, 402, 401, 400, 403, 402,  // upper
		404, 406, 405, 404, 407, 406,   // bottom
		//tiang 18
		408, 409, 410, 408, 409, 410,   // front
		412, 413, 414, 412, 414, 415,   // right
		416, 417, 418, 416, 418, 419,  // back
		420, 422, 421, 420, 423, 422,  // left
		424, 426, 425, 424, 427, 426,  // upper
		428, 430, 429, 428, 431, 430,   // bottom
		//tiang 19
		432, 433, 434, 432, 434, 435,   // front
		436, 437, 438, 436, 438, 439,   // right
		440, 441, 442, 440, 442, 443,  // back
		444, 446, 445, 444, 447, 446,  // left
		448, 450, 449, 448, 451, 450,  // upper
		452, 454, 453, 452, 455, 454,   // bottom
		//tiang 20
		456, 457, 458, 456, 458, 459,   // front
		460, 461, 462, 460, 462, 463,   // right
		464, 465, 466, 464, 466, 467,  // back
		468, 470, 469, 468, 471, 470,  // left
		472, 474, 473, 472, 475, 474,  // upper
		476, 478, 477, 476, 479, 478,   // bottom
		//tiang 21
		480, 481, 482, 480, 482, 483,   // front
		484, 485, 486, 484, 486, 487,   // right
		488, 489, 490, 488, 490, 491,  // back
		492, 494, 493, 492, 495, 494,  // left
		496, 498, 497, 496, 499, 498,  // upper
		500, 502, 501, 500, 503, 502,   // bottom
		//tiang 22
		504, 505, 506, 504, 506, 507,   // front
		508, 509, 510, 508, 510, 511,   // right
		512, 513, 514, 512, 514, 515,  // back
		516, 518, 517, 516, 519, 518,  // left
		520, 522, 521, 520, 523, 522,  // upper
		524, 526, 525, 524, 527, 526,   // bottom
		//tiang 23
		528, 529, 530, 528, 530, 531,   // front
		532, 533, 534, 532, 534, 535,   // right
		536, 537, 538, 536, 538, 539,  // back
		540, 542, 541, 540, 543, 542,  // left
		544, 546, 545, 544, 547, 546,  // upper
		548, 550, 549, 548, 551, 550,   // bottom
		//tiang 24
		552, 553, 554, 552, 554, 555,   // front
		556, 557, 558, 556, 558, 559,   // right
		560, 561, 562, 560, 562, 563,  // back
		564, 566, 565, 564, 567, 566,  // left
		568, 570, 569, 568, 571, 570,  // upper
		572, 574, 573, 572, 575, 574,   // bottom
	};


	glGenVertexArrays(1, &VAO14);
	glGenBuffers(1, &VBO14);
	glGenBuffers(1, &EBO14);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO14);

	glBindBuffer(GL_ARRAY_BUFFER, VBO14);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO14);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTiang1Kanan(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO14);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 864, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredAtap1Kanan() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices2[] = {
		// format position, tex coords
		//TIANG ATAP 0
		// upper
		4.6, 11.0, -4.0, 0, 0,   // 112 kiba
		4.3, 11.0, -4.0, 1, 0,  // 113 kaba
		4.3, 11.0, 4.0, 1, 1,  // 114 kaat
		4.5, 11.0, 4.0, 0, 1,   // 115 kiat
		// bottom
		4.3, 10.5, 4.0, 0, 0, // 116
		4.5, 10.5, 4.0, 1, 0,  // 117
		4.5, 10.5, -4.0, 1, 1,  // 118
		4.3, 10.5, -4.0, 0, 1, // 119
		// front
		4.3, 10.5, 4.0, 0, 0,  // 120
		4.3, 10.5, -4.0, 1, 0,  // 121
		4.3, 11.0, -4.0, 1, 1, // 122
		4.3, 11.0, 4.0, 0, 1, // 123
		// back
		4.5, 10.5, 4.0, 0, 0, // 124
		4.5, 10.5, -4.0, 1, 0, // 125
		4.5, 11.0, -4.0, 1, 1, // 126
		4.5, 11.0, 4.0, 0, 1, // 127
		//TIANG ATAP 1
		// upper
		4.5, 10.0, 4.0, 0, 0,   // 128 kiba
		4.3, 10.0, 4.0, 1, 0,  // 129 kaba
		4.3, 10.0, 8.5, 1, 1,  // 130 kaat
		4.5, 10.0, 8.5, 0, 1,   // 131 kiat
		// bottom
		4.3, 9.5, 8.5, 0, 0, // 132
		4.5, 9.5, 8.5, 1, 0,  // 133
		4.5, 9.5, 4.0, 1, 1,  // 134
		4.3, 9.5, 4.0, 0, 1, // 135
		// front
		4.3, 9.5, 8.5, 0, 0,  // 136
		4.3, 9.5, 4.0, 1, 0,  // 137
		4.3, 10.0,4.0, 1, 1, // 138
		4.3, 10.0,8.5, 0, 1, // 139
		// back
		4.5, 9.5, 8.5, 0, 0, // 140
		4.5, 9.5, 4.0, 1, 0, // 141
		4.5, 10.0,4.0, 1, 1, // 142
		4.5, 10.0,8.5, 0, 1, // 143
		//TIANG ATAP 2
		// upper
		4.5, 9.0, 8.0, 0, 0,   // 144
		4.3, 9.0, 8.0, 1, 0,  // 145
		4.3, 9.0, 12.0, 1, 1,  // 146
		4.5, 9.0, 12.0, 0, 1,   // 147
		// bottom
		4.3, 8.5, 12.0, 0, 0, // 148
		4.5, 8.5, 12.0, 1, 0,  // 149
		4.5, 8.5, 8.0, 1, 1,  // 150
		4.3, 8.5, 8.0, 0, 1, // 151
		// front
		4.3, 8.5, 12.0, 0, 0,  // 152
		4.3, 8.5, 8.0, 1, 0,  // 153
		4.3, 9.0,8.0, 1, 1, // 154
		4.3, 9.0,12.0, 0, 1, // 155
		// back
		4.5, 8.5, 12.0, 0, 0, // 156
		4.5, 8.5, 8.0, 1, 0, // 157
		4.5, 9.0,8.0, 1, 1, // 158
		4.5, 9.0, 12.0, 0, 1, // 159
		//TIANG ATAP 3
		// upper
		4.5, 8.0, 12.0, 0, 0,   // 160
		4.3, 8.0, 12.0, 1, 0,  // 161
		4.3, 8.0, 15.5, 1, 1,  // 162
		4.5, 8.0, 15.5, 0, 1,   // 163
		//bottom
		4.3, 7.5, 15.5, 0, 0, // 164
		4.5, 7.5, 15.5, 1, 0,  //165
		4.5, 7.5, 12.0, 1, 1,  // 166
		4.3, 7.5, 12.0, 0, 1, // 167
		// front
		4.3, 7.5, 15.5, 0, 0,  // 168
		4.3, 7.5, 12.0, 1, 0,  // 169
		4.3, 8.0, 12.0, 1, 1, // 170
		4.3, 8.0, 15.5, 0, 1, // 171
		// back
		4.5, 8.0, 15.5, 0, 0, // 172
		4.5, 8.0, 12.0, 1, 0, // 173
		4.5, 7.5, 12.0, 1, 1, // 174
		4.5, 7.5, 15.5, 0, 1, // 175
		//TIANG ATAP 4
		// upper
		4.5, 7.0, 15.5, 0, 0,   // 176
		4.3, 7.0, 15.5, 1, 0,  // 177
		4.3, 7.0, 23.0, 1, 1,  // 178
		4.5, 7.0, 23.0, 0, 1,   // 179
		// bottom
		4.3, 6.5, 23.0, 0, 0, // 180
		4.5, 6.5, 23.0, 1, 0,  // 181
		4.5, 6.5, 15.5, 1, 1,  // 182
		4.3, 6.5, 15.5, 0, 1, // 183
		// front
		4.3, 6.5, 23.0, 0, 0,  // 184
		4.3, 6.5, 15.5, 1, 0,  // 185
		4.3, 7.0, 15.5, 1, 1, // 186
		4.3, 7.0, 23.0, 0, 1, // 187
		// back
		4.5, 6.5, 23.0, 0, 0, // 188
		4.5, 6.5, 15.5, 1, 0, // 189
		4.5, 7.0, 15.5, 1, 1, // 190
		4.5, 7.0, 23.0, 0, 1, // 191
		//TIANG ATAP 5
		// upper
		4.5, 6.0, 23.0, 0, 0,   // 192
		4.3, 6.0, 23.0, 1, 0,  // 193
		4.3, 6.0, 32.0, 1, 1,  // 194
		4.5, 6.0, 32.0, 0, 1,   // 195
		// bottom
		4.3, 5.5, 32.0, 0, 0, // 196
		4.5, 5.5, 32.0, 1, 0,  // 197
		4.5, 5.5, 23.0, 1, 1,  // 198
		4.3, 5.5, 23.0, 0, 1, // 199
		// front
		4.3, 5.5, 32.0, 0, 0,  // 200
		4.3, 5.5, 23.0, 1, 0,  // 201
		4.3, 6.0, 23.0, 1, 1, // 202
		4.3, 6.0, 32.0, 0, 1, // 203
		// back
		4.5, 5.5, 32.0, 0, 0, // 204
		4.5, 5.5, 23.0, 1, 0, // 205
		4.5, 6.0, 23.0, 1, 1, // 206
		4.5, 6.0, 32.0, 0, 1, // 207
		//TIANG ATAP 6
		// upper
		4.3, 4.5, 32.0, 0, 0,   // 208
		4.5, 4.5, 32.0, 1, 0,  // 209
		4.5, 4.5, 38.0, 1, 1,  // 210
		4.3, 4.5, 38.0, 0, 1,   // 211
		// bottom
		4.5, 5.0, 38.0, 0, 0, // 212
		4.3, 5.0, 38.0, 1, 0,  // 213
		4.3, 5.0, 32.0, 1, 1,  // 214
		4.5, 5.0, 32.0, 0, 1, // 215
		// front
		4.5, 4.5, 38.0, 0, 0,  // 216
		4.5, 4.5, 32.0, 1, 0,  // 217
		4.5, 5.0, 32.0, 1, 1, // 218
		4.5, 5.0, 38.0, 0, 1, // 219
		// back
		4.3, 4.5, 38.0, 0, 0, // 220
		4.3, 4.5, 32.0, 1, 0, // 221
		4.3, 5.0, 32.0, 1, 1, // 222
		4.3, 5.0, 38.0, 0, 1, // 223
	};

	unsigned int indices2[] = {
		//atap tiang -1
		0, 2, 1, 0, 3, 2,  // upper
		4, 6, 5, 4, 7, 6,   // bottom
		8, 9, 10, 8, 11, 10, // front
		12, 13, 14, 12, 15, 14, // back
		//atap tiang -2
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom
		24, 25, 26, 24, 27, 26, // front
		28, 29, 30, 28, 31, 30, // back
		//atap tiang -3
		32, 34, 33, 32, 35, 34,  // upper
		36, 38, 37, 36, 39, 38,   // bottom
		40, 41, 42, 40, 42, 43, // front
		44, 45, 46, 44, 46, 47, // back
		//atap tiang -4
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63, // back
		//atap tiang -5
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		72, 73, 74, 72, 74, 75, // front
		76, 77, 78, 76, 78, 79, // back
		//atap tiang -6
		80, 82, 81, 80, 83, 82,  // upper
		84, 86, 85, 84, 87, 86,   // bottom
		88, 89, 90, 88, 90, 91, // front
		92, 93, 94, 92, 94, 95, // back
		//atap tiang -7
		96, 98, 97, 96, 99, 98,  // upper
		100, 102, 101, 100, 103, 102,   // bottom
		104, 105, 106, 104, 106, 107, // front
		108, 109, 110, 108, 110, 111, // back
	};


	glGenVertexArrays(1, &VAO16);
	glGenBuffers(1, &VBO16);
	glGenBuffers(1, &EBO16);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO16);

	glBindBuffer(GL_ARRAY_BUFFER, VBO16);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO16);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredAtap1Kanan(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO16);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 168, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTiang2Kanan() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices1[] = {
		// format position, tex coords
		// TIANG 1
		 //front
		4.5, 8.5, 2.5, 0, 0,  // 0
		4.3, 8.5, 2.5, 1, 0,   // 1
		4.3, 10.5, 2.5, 1, 1,   // 2
		4.5, 10.5, 2.5, 0, 1,  // 3
		// right
		4.3,  10.5,  2.5, 0, 0,  // 4
		4.3,  10.5, -2.0, 1, 0,  // 5
		4.3, 8.5, -2.0, 1, 1,  // 6
		4.3, 8.5,  2.5, 0, 1,  // 7
		// back
		4.5, 8.5, -2.0, 0, 0, // 8 
		4.3, 8.5, -2.0, 1, 0, // 9
		4.3, 10.5, -2.0, 1, 1, // 10
		4.5, 10.5, -2.0, 0, 1, // 11
		// left
		4.5, 8.5, -2.0, 0, 0, // 12
		4.5, 8.5,  2.5, 1, 0, // 13
		4.5, 10.5, 2.5, 1, 1, // 14
		4.5, 10.5, -2.0, 0, 1, // 15
		// upper
		4.3, 10.5, 2.5, 0, 0,   // 16
		4.5, 10.5, 2.5, 1, 0,  // 17
		4.5, 10.5, -2.0, 1, 1,  // 18
		4.3, 10.5, -2.0, 0, 1,   // 19
		// bottom
		4.5, 8.5, -2.0, 0, 0, // 20
		4.3, 8.5, -2.0, 1, 0,  // 21
		4.3, 8.5,  2.5, 1, 1,  // 22
		4.5, 8.5,  2.5, 0, 1, // 23
		//TIANG 2
		// front
		4.5, 8.5, -3.5, 0, 0,  // 24 ,,kiba,
		4.3, 8.5, -3.5, 1, 0,  // 25 ,,kaba,
		4.3, 10.5, -3.5, 1, 1,  // 26 ,,kaat,
		4.5, 10.5, -3.5, 0, 1,  // 27 ,,kiat
		// right
		4.3,  10.5, -3.5, 0, 0,  // 28
		4.3,  10.5, -4.0, 1, 0,  // 29
		4.3, 8.5, -4.0, 1, 1,  // 30
		4.3, 8.5, -3.5, 0, 1,  // 31
		// back
		4.5, 8.5, -4.0, 0, 0, // 32
		4.3, 8.5, -4.0, 1, 0, // 33
		4.3, 10.5, -4.0, 1, 1, // 34
		4.5, 10.5, -4.0, 0, 1, // 35
		// left
		4.5, 8.5, -4.0, 0, 0, // 36
		4.5, 8.5, -3.5, 1, 0, // 37
		4.5, 10.5,-3.5, 1, 1, // 38
		4.5, 10.5,-4.0, 0, 1, // 39
		// upper
		4.3, 10.5, -3.5, 0, 0,   // 40
		4.5, 10.5, -3.5, 1, 0,  // 41
		4.5, 10.5, -4.0, 1, 1,  // 42
		4.3, 10.5, -4.0, 0, 1,   // 43
		// bottom
		4.5, 8.5, -4.0, 0, 0, // 44
		4.3, 8.5, -4.0, 1, 0,  // 45
		4.3, 8.5, -3.5, 1, 1,  // 46
		4.5, 8.5, -3.5, 0, 1, // 47
		//TIANG 3
		// front
		4.5, 7.5, -5.0, 0, 0,  // 48 ,,kiba,
		4.3, 7.5, -5.0, 1, 0,  // 49 ,,kaba,
		4.3, 9.5, -5.0, 1, 1,  // 50 ,,kaat,
		4.5, 9.5, -5.0, 0, 1,  // 51 ,,kiat
		// right
		4.3,  9.5, -5.0, 0, 0,  // 52
		4.3,  9.5, -5.5, 1, 0,  // 53
		4.3, 7.5, -5.5, 1, 1,  // 54
		4.3, 7.5,  -5.0, 0, 1,  // 55
		// back
		4.5, 7.5, -5.5, 0, 0, // 56
		4.3, 7.5, -5.5, 1, 0, // 57
		4.3,  9.5, -5.5, 1, 1, // 58
		4.5,  9.5, -5.5, 0, 1, // 59
		// left
		4.5, 7.5, -5.5, 0, 0, // 60
		4.5, 7.5, -5.0, 1, 0, // 61
		4.5, 9.5, -5.0, 1, 1, // 62
		4.5, 9.5, -5.5, 0, 1, // 63
		// upper
		4.3, 9.5,  -5.0, 0, 0,   // 64
		4.5, 9.5, -5.0, 1, 0,  // 65
		4.5, 9.5, -5.5, 1, 1,  // 66
		4.3,9.5, -5.5, 0, 1,   // 67
		// bottom
		4.5, 7.5, -5.5, 0, 0, // 68
		4.3, 7.5, -5.5, 1, 0,  // 69
		4.3, 7.5, -5.0, 1, 1,  // 70
		4.5, 7.5, -5.0, 0, 1, // 71
		//TIANG 4
		// front
		4.5, 7.5, -6.5, 0, 0,  // 72 ,,kiba,
		4.3, 7.5, -6.5, 1, 0,  // 73 ,,kaba,
		4.3, 9.5, -6.5, 1, 1,  // 74 ,,kaat,
		4.5, 9.5, -6.5, 0, 1,  // 75 ,,kiat
		// right
		4.3,  9.5, -6.5, 0, 0,  // 76
		4.3,  9.5, -7.0, 1, 0,  // 77
		4.3, 7.5, -7.0, 1, 1,  // 78
		4.3, 7.5, -6.5, 0, 1,  // 79
		// back
		4.5, 7.5, -7.0, 0, 0, // 80
		4.3, 7.5, -7.0, 1, 0, // 81
		4.3, 9.5,-7.0, 1, 1, // 82
		4.5, 9.5,-7.0, 0, 1, // 83
		// left
		4.5, 7.5, -7.0, 0, 0, // 84
		4.5, 7.5, -6.5, 1, 0, // 85
		4.5, 9.5, -6.5, 1, 1, // 86
		4.5, 9.5, -7.0, 0, 1, // 87
		// upper
		4.3, 9.5, -6.5, 0, 0,   // 88
		4.5, 9.5, -6.5, 1, 0,  // 89
		4.5, 9.5, -7.0, 1, 1,  // 90
		4.3, 9.5,-7.0, 0, 1,   // 91
		// bottom
		4.5, 7.5, -7.0, 0, 0, // 92
		4.3, 7.5, -7.0, 1, 0,  // 93
		4.3, 7.5, -6.5, 1, 1,  // 94
		4.5, 7.5, -6.5, 0, 1, // 95
		//TIANG 5
		// front
		4.5, 6.5, -8.0, 0, 0,  // 96 ,,kiba,
		4.3, 6.5, -8.0, 1, 0,  // 97 ,,kaba,
		4.3, 9.5, -8.0, 1, 1,  // 98 ,,kaat,
		4.5, 9.5, -8.0, 0, 1,  // 99 ,,kiat
		// right
		4.3,  9.5, -8.0, 0, 0,  // 100
		4.3,  9.5, -8.5, 1, 0,  // 101
		4.3, 6.5, -8.5, 1, 1,  // 102
		4.3, 6.5, -8.0, 0, 1,  // 103
		// back
		4.5, 6.5, -8.5, 0, 0, // 104
		4.3, 6.5, -8.5, 1, 0, // 105
		4.3,  9.5, -8.5, 1, 1, // 106
		4.5,  9.5, -8.5, 0, 1, // 107
		// left
		4.5, 6.5, -8.5, 0, 0, // 108
		4.5, 6.5, -8.0, 1, 0, // 109
		4.5,  9.5,-8.0, 1, 1, // 110
		4.5,  9.5, -8.5, 0, 1, // 111
		// upper
		4.3, 9.5,  -8.0, 0, 0,   // 112
		4.5, 9.5, -8.0, 1, 0,  // 113
		4.5, 9.5, -8.5, 1, 1,  // 114
		4.3, 9.5, -8.5, 0, 1,   // 115
		// bottom
		4.5, 6.5, -8.5, 0, 0, // 116
		4.3, 6.5,-8.5, 1, 0,  // 117
		4.3, 6.5, -8.0, 1, 1,  // 118
		4.5, 6.5, -8.0, 0, 1, // 119
		//TIANG 6
		// front
		4.5, 6.5, -11.5, 0, 0,  // 96 ,,kiba,
		4.3, 6.5, -11.5, 1, 0,  // 97 ,,kaba,
		4.3, 8.5, -11.5, 1, 1,  // 98 ,,kaat,
		4.5, 8.5, -11.5, 0, 1,  // 99 ,,kiat
		// right
		4.3,  8.5, -11.5, 0, 0,  // 100
		4.3,  8.5, -12.0, 1, 0,  // 101
		4.3, 6.5, -12.0, 1, 1,  // 102
		4.3, 6.5, -11.5, 0, 1,  // 103
		// back
		4.5, 6.5, -12.0, 0, 0, // 104
		4.3, 6.5, -12.0, 1, 0, // 105
		4.3, 8.5, -12.0, 1, 1, // 106
		4.5, 8.5, -12.0, 0, 1, // 107
		// left
		4.5, 6.5, -12.0, 0, 0, // 108
		4.5, 6.5, -11.5, 1, 0, // 109
		4.5, 8.5, -11.5, 1, 1, // 110
		4.5, 8.5, -12.0, 0, 1, // 111
		// upper
		4.3, 8.5, -11.5, 0, 0,   // 112
		4.5, 8.5, -11.5, 1, 0,  // 113
		4.5, 8.5, -12.0, 1, 1,  // 114
		4.3, 8.5, -12.0, 0, 1,   // 115
		// bottom
		4.5, 6.5, -12.0, 0, 0, // 116
		4.3, 6.5, -12.0, 1, 0,  // 117
		4.3, 6.5, -11.5, 1, 1,  // 118
		4.5, 6.5, -11.5, 0, 1, // 119
		//TIANG 7
		// front
		4.5, 5.5, -12.0, 0, 0,  // 96 ,,kiba,
		4.3, 5.5, -12.0, 1, 0,  // 97 ,,kaba,
		4.3, 7.5, -12.0, 1, 1,  // 98 ,,kaat,
		4.5, 7.5, -12.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 7.5, -12.0, 0, 0,  // 100
		4.3, 7.5, -12.5, 1, 0,  // 101
		4.3, 5.5, -12.5, 1, 1,  // 102
		4.3, 5.5, -12.0, 0, 1,  // 103
		// back
		4.5, 5.5, -12.5, 0, 0, // 104
		4.3, 5.5, -12.5, 1, 0, // 105
		4.3, 7.5, -12.5, 1, 1, // 106
		4.5, 7.5, -12.5, 0, 1, // 107
		// left
		4.5, 5.5, -12.5, 0, 0, // 108
		4.5, 5.5, -12.0, 1, 0, // 109
		4.5, 7.5, -12.0, 1, 1, // 110
		4.5, 7.5, -12.5, 0, 1, // 111
		// upper
		4.3, 7.5, -12.0, 0, 0,   // 112
		4.5, 7.5, -12.0, 1, 0,  // 113
		4.5, 7.5, -12.5, 1, 1,  // 114
		4.3, 7.5, -12.5, 0, 1,   // 115
		// bottom
		4.5, 5.5, -12.5, 0, 0, // 116
		4.3, 5.5, -12.5, 1, 0,  // 117
		4.3, 5.5, -12.0, 1, 1,  // 118
		4.5, 5.5, -12.0, 0, 1, // 119
		//TIANG 8
		// front
		4.5, 5.5, -13.5, 0, 0,  // 96 ,,kiba,
		4.3, 5.5, -13.5, 1, 0,  // 97 ,,kaba,
		4.3, 7.5, -13.5, 1, 1,  // 98 ,,kaat,
		4.5, 7.5, -13.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 7.5, -13.5, 0, 0,  // 100
		4.3, 7.5, -14.0, 1, 0,  // 101
		4.3, 5.5, -14.0, 1, 1,  // 102
		4.3, 5.5, -13.5, 0, 1,  // 103
		// back
		4.5, 5.5, -14.0, 0, 0, // 104
		4.3, 5.5, -14.0, 1, 0, // 105
		4.3, 7.5, -14.0, 1, 1, // 106
		4.5, 7.5, -14.0, 0, 1, // 107
		// left
		4.5, 5.5, -14.0, 0, 0, // 108
		4.5, 5.5, -13.5, 1, 0, // 109
		4.5, 7.5, -13.5, 1, 1, // 110
		4.5, 7.5, -14.0, 0, 1, // 111
		// upper
		4.3, 7.5, -13.5, 0, 0,   // 112
		4.5, 7.5, -13.5, 1, 0,  // 113
		4.5, 7.5, -14.0, 1, 1,  // 114
		4.3, 7.5, -14.0, 0, 1,   // 115
		// bottom-
		4.5, 5.5, -14.0, 0, 0, // 116
		4.3, 5.5, -14.0, 1, 0,  // 117
		4.3, 5.5, -13.5, 1, 1,  // 118
		4.5, 5.5, -13.5, 0, 1, // 119
		//TIANG 9
		// front
		4.5, 5.5, -15.0, 0, 0,  // 96 ,,kiba,
		4.3, 5.5, -15.0, 1, 0,  // 97 ,,kaba,
		4.3, 7.5, -15.0, 1, 1,  // 98 ,,kaat,
		4.5, 7.5, -15.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 7.5, -15.0, 0, 0,  // 100
		4.3, 7.5, -15.5, 1, 0,  // 101
		4.3, 5.5, -15.5, 1, 1,  // 102
		4.3, 5.5, -15.0, 0, 1,  // 103
		// back
		4.5, 5.5, -15.5, 0, 0, // 104
		4.3, 5.5, -15.5, 1, 0, // 105
		4.3, 7.5, -15.5, 1, 1, // 106
		4.5, 7.5, -15.5, 0, 1, // 107
		// left
		4.5, 5.5, -15.5, 0, 0, // 108
		4.5, 5.5, -15.0, 1, 0, // 109
		4.5, 7.5, -15.0, 1, 1, // 110
		4.5, 7.5, -15.5, 0, 1, // 111
		// upper
		4.3, 7.5, -15.0, 0, 0,   // 112
		4.5, 7.5, -15.0, 1, 0,  // 113
		4.5, 7.5, -15.5, 1, 1,  // 114
		4.3, 7.5, -15.5, 0, 1,   // 115
		// bottom
		4.5, 5.5, -15.5, 0, 0, // 116
		4.3, 5.5, -15.5, 1, 0,  // 117
		4.3, 5.5, -15.0, 1, 1,  // 118
		4.5, 5.5, -15.0, 0, 1, // 119
		//TIANG 10
		// front
		4.5, 4.5, -16.5, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, -16.5, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, -16.5, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, -16.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, -16.5, 0, 0,  // 100
		4.3, 6.5, -17.0, 1, 0,  // 101
		4.3, 4.5, -17.0, 1, 1,  // 102
		4.3, 4.5, -16.5, 0, 1,  // 103
		// back
		4.5, 4.5, -17.0, 0, 0, // 104
		4.3, 4.5, -17.0, 1, 0, // 105
		4.3, 6.5, -17.0, 1, 1, // 106
		4.5, 6.5, -17.0, 0, 1, // 107
		// left
		4.5, 4.5, -17.0, 0, 0, // 108
		4.5, 4.5, -16.5, 1, 0, // 109
		4.5, 6.5, -16.5, 1, 1, // 110
		4.5, 6.5, -17.0, 0, 1, // 111
		// upper
		4.3, 6.5, -16.5, 0, 0,   // 112
		4.5, 6.5, -16.5, 1, 0,  // 113
		4.5, 6.5, -17.0, 1, 1,  // 114
		4.3, 6.5, -17.0, 0, 1,   // 115
		// bottom
		4.5, 4.5, -17.0, 0, 0, // 116
		4.3, 4.5, -17.0, 1, 0,  // 117
		4.3, 4.5, -16.5, 1, 1,  // 118
		4.5, 4.5, -16.5, 0, 1, // 119
		//TIANG 11
		// front
		4.5, 4.5, -18.0, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, -18.0, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, -18.0, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, -18.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, -18.0, 0, 0,  // 100
		4.3, 6.5, -18.5, 1, 0,  // 101
		4.3, 4.5, -18.5, 1, 1,  // 102
		4.3, 4.5, -18.0, 0, 1,  // 103
		// back
		4.5, 4.5, -18.5, 0, 0, // 104
		4.3, 4.5, -18.5, 1, 0, // 105
		4.3, 6.5, -18.5, 1, 1, // 106
		4.5, 6.5, -18.5, 0, 1, // 107
		// left
		4.5, 4.5, -18.5, 0, 0, // 108
		4.5, 4.5, -18.0, 1, 0, // 109
		4.5, 6.5, -18.0, 1, 1, // 110
		4.5, 6.5, -18.5, 0, 1, // 111
		// upper
		4.3, 6.5, -18.0, 0, 0,   // 112
		4.5, 6.5, -18.0, 1, 0,  // 113
		4.5, 6.5, -18.5, 1, 1,  // 114
		4.3, 6.5, -18.5, 0, 1,   // 115
		// bottom
		4.5, 4.5, -18.5, 0, 0, // 116
		4.3, 4.5, -18.5, 1, 0,  // 117
		4.3, 4.5, -18.0, 1, 1,  // 118
		4.5, 4.5, -18.0, 0, 1, // 119
		//TIANG 12
		// front
		4.5, 4.5, -19.5, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, -19.5, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, -19.5, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, -19.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, -19.5, 0, 0,  // 100
		4.3, 6.5, -20.0, 1, 0,  // 101
		4.3, 4.5, -20.0, 1, 1,  // 102
		4.3, 4.5, -19.5, 0, 1,  // 103
		// back
		4.5, 4.5, -20.0, 0, 0, // 104
		4.3, 4.5, -20.0, 1, 0, // 105
		4.3, 6.5, -20.0, 1, 1, // 106
		4.5, 6.5, -20.0, 0, 1, // 107
		// left
		4.5, 4.5, -20.0, 0, 0, // 108
		4.5, 4.5, -19.5, 1, 0, // 109
		4.5, 6.5, -19.5, 1, 1, // 110
		4.5, 6.5, -20.0, 0, 1, // 111
		// upper
		4.3, 6.5, -19.5, 0, 0,   // 112
		4.5, 6.5, -19.5, 1, 0,  // 113
		4.5, 6.5, -20.0, 1, 1,  // 114
		4.3, 6.5, -20.0, 0, 1,   // 115
		// bottom
		4.5, 4.5, -20.0, 0, 0, // 116
		4.3, 4.5, -20.0, 1, 0,  // 117
		4.3, 4.5, -19.5, 1, 1,  // 118
		4.5, 4.5, -19.5, 0, 1, // 119
		//TIANG 13
		// front
		4.5, 4.5, -21.0, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, -21.0, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, -21.0, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, -21.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, -21.0, 0, 0,  // 100
		4.3, 6.5, -21.5, 1, 0,  // 101
		4.3, 4.5, -21.5, 1, 1,  // 102
		4.3, 4.5, -21.0, 0, 1,  // 103
		// back
		4.5, 4.5, -21.5, 0, 0, // 104
		4.3, 4.5, -21.5, 1, 0, // 105
		4.3, 6.5, -21.5, 1, 1, // 106
		4.5, 6.5, -21.5, 0, 1, // 107
		// left
		4.5, 4.5, -21.5, 0, 0, // 108
		4.5, 4.5, -21.0, 1, 0, // 109
		4.5, 6.5, -21.0, 1, 1, // 110
		4.5, 6.5, -21.5, 0, 1, // 111
		// upper
		4.3, 6.5, -21.0, 0, 0,   // 112
		4.5, 6.5, -21.0, 1, 0,  // 113
		4.5, 6.5, -21.5, 1, 1,  // 114
		4.3, 6.5, -21.5, 0, 1,   // 115
		// bottom
		4.5, 4.5, -21.5, 0, 0, // 116
		4.3, 4.5, -21.5, 1, 0,  // 117
		4.3, 4.5, -21.0, 1, 1,  // 118
		4.5, 4.5, -21.0, 0, 1, // 119
		//TIANG 14
		// front
		4.5, 4.5, -22.5, 0, 0,  // 96 ,,kiba,
		4.3, 4.5, -22.5, 1, 0,  // 97 ,,kaba,
		4.3, 6.5, -22.5, 1, 1,  // 98 ,,kaat,
		4.5, 6.5, -22.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 6.5, -22.5, 0, 0,  // 100
		4.3, 6.5, -23.0, 1, 0,  // 101
		4.3, 4.5, -23.0, 1, 1,  // 102
		4.3, 4.5, -22.5, 0, 1,  // 103
		// back
		4.5, 4.5, -23.0, 0, 0, // 104
		4.3, 4.5, -23.0, 1, 0, // 105
		4.3, 6.5, -23.0, 1, 1, // 106
		4.5, 6.5, -23.0, 0, 1, // 107
		// left
		4.5, 4.5, -23.0, 0, 0, // 108
		4.5, 4.5, -22.5, 1, 0, // 109
		4.5, 6.5, -22.5, 1, 1, // 110
		4.5, 6.5, -23.0, 0, 1, // 111
		// upper
		4.3, 6.5, -22.5, 0, 0,   // 112
		4.5, 6.5, -22.5, 1, 0,  // 113
		4.5, 6.5, -23.0, 1, 1,  // 114
		4.3, 6.5, -23.0, 0, 1,   // 115
		// bottom
		4.5, 4.5, -23.0, 0, 0, // 116
		4.3, 4.5, -23.0, 1, 0,  // 117
		4.3, 4.5, -22.5, 1, 1,  // 118
		4.5, 4.5, -22.5, 0, 1, // 119
		//TIANG 15
		// front
		4.5, 3.5, -24.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -24.0, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, -24.0, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, -24.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, -24.0, 0, 0,  // 100
		4.3, 5.5, -24.5, 1, 0,  // 101
		4.3, 3.5, -24.5, 1, 1,  // 102
		4.3, 3.5, -24.0, 0, 1,  // 103
		// back
		4.5, 3.5, -24.5, 0, 0, // 104
		4.3, 3.5, -24.5, 1, 0, // 105
		4.3, 5.5, -24.5, 1, 1, // 106
		4.5, 5.5, -24.5, 0, 1, // 107
		// left
		4.5, 3.5, -24.5, 0, 0, // 108
		4.5, 3.5, -24.0, 1, 0, // 109
		4.5, 5.5, -24.0, 1, 1, // 110
		4.5, 5.5, -24.5, 0, 1, // 111
		// upper
		4.3, 5.5, -24.0, 0, 0,   // 112
		4.5, 5.5, -24.0, 1, 0,  // 113
		4.5, 5.5, -24.5, 1, 1,  // 114
		4.3, 5.5, -24.5, 0, 1,   // 115
		// bottom
		4.5, 3.5, -24.5, 0, 0, // 116
		4.3, 3.5, -24.5, 1, 0,  // 117
		4.3, 3.5, -24.0, 1, 1,  // 118
		4.5, 3.5, -24.0, 0, 1, // 119
		//TIANG 16
		// front
		4.5, 3.5, -25.5, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -25.5, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, -25.5, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, -25.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, -25.5, 0, 0,  // 100
		4.3, 5.5, -26.0, 1, 0,  // 101
		4.3, 3.5, -26.0, 1, 1,  // 102
		4.3, 3.5, -25.5, 0, 1,  // 103
		// back
		4.5, 3.5, -26.0, 0, 0, // 104
		4.3, 3.5, -25.5, 1, 0, // 105
		4.3, 5.5, -25.5, 1, 1, // 106
		4.5, 5.5, -26.0, 0, 1, // 107
		// left
		4.5, 3.5, -26.0, 0, 0, // 108
		4.5, 3.5, -25.5, 1, 0, // 109
		4.5, 5.5, -25.5, 1, 1, // 110
		4.5, 5.5, -26.0, 0, 1, // 111
		// upper
		4.3, 5.5, -25.5, 0, 0,   // 112
		4.5, 5.5, -25.5, 1, 0,  // 113
		4.5, 5.5, -26.0, 1, 1,  // 114
		4.3, 5.5, -26.0, 0, 1,   // 115
		// bottom
		4.5, 3.5, -26.0, 0, 0, // 116
		4.3, 3.5, -26.0, 1, 0,  // 117
		4.3, 3.5, -25.5, 1, 1,  // 118
		4.5, 3.5, -25.5, 0, 1, // 119
		//TIANG 17
		// front
		4.5, 3.5, -27.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -27.0, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, -27.0, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, -27.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, -27.0, 0, 0,  // 100
		4.3, 5.5, -27.5, 1, 0,  // 101
		4.3, 3.5, -27.5, 1, 1,  // 102
		4.3, 3.5, -27.0, 0, 1,  // 103
		// back
		4.5, 3.5, -27.5, 0, 0, // 104
		4.3, 3.5, -27.5, 1, 0, // 105
		4.3, 5.5, -27.5, 1, 1, // 106
		4.5, 5.5, -27.5, 0, 1, // 107
		// left
		4.5, 3.5, -27.5, 0, 0, // 108
		4.5, 3.5, -27.0, 1, 0, // 109
		4.5, 5.5, -27.0, 1, 1, // 110
		4.5, 5.5, -27.5, 0, 1, // 111
		// upper
		4.3, 5.5, -27.0, 0, 0,   // 112
		4.5, 5.5, -27.0, 1, 0,  // 113
		4.5, 5.5, -27.5, 1, 1,  // 114
		4.3, 5.5, -27.5, 0, 1,   // 115
		// bottom
		4.5, 3.5, -27.5, 0, 0, // 116
		4.3, 3.5, -27.5, 1, 0,  // 117
		4.3, 3.5, -27.0, 1, 1,  // 118
		4.5, 3.5, -27.0, 0, 1, // 119
		//TIANG 18
		// front
		4.5, 3.5, -28.5, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -28.5, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, -28.5, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, -28.5, 0, 1,  // 99 ,,kiat
		//right
		4.3, 5.5, -28.5, 0, 0,  // 100
		4.3, 5.5, -29.0, 1, 0,  // 101
		4.3, 3.5, -29.0, 1, 1,  // 102
		4.3, 3.5, -28.5, 0, 1,  // 103
		// back
		4.5, 3.5, -29.0, 0, 0, // 104
		4.3, 3.5, -29.0, 1, 0, // 105
		4.3, 5.5, -29.0, 1, 1, // 106
		4.5, 5.5, -29.0, 0, 1, // 107
		// left
		4.5, 3.5, -29.0, 0, 0, // 108
		4.5, 3.5, -28.5, 1, 0, // 109
		4.5, 5.5, -28.5, 1, 1, // 110
		4.5, 5.5, -29.0, 0, 1, // 111
		// upper
		4.3, 5.5, -28.5, 0, 0,   // 112
		4.5, 5.5, -28.5, 1, 0,  // 113
		4.5, 5.5, -29.0, 1, 1,  // 114
		4.3, 5.5, -29.0, 0, 1,   // 115
		// bottom
		4.5, 3.5, -29.0, 0, 0, // 116
		4.3, 3.5, -29.0, 1, 0,  // 117
		4.3, 3.5, -28.5, 1, 1,  // 118
		4.5, 3.5, -28.5, 0, 1, // 119
		//TIANG 19
		// front
		4.5, 3.5, -30.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -30.0, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, -30.0, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, -30.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, -30.0, 0, 0,  // 100
		4.3, 5.5, -30.5, 1, 0,  // 101
		4.3, 3.5, -30.5, 1, 1,  // 102
		4.3, 3.5, -30.0, 0, 1,  // 103
		// back
		4.5, 3.5, -30.5, 0, 0, // 104
		4.3, 3.5, -30.5, 1, 0, // 105
		4.3, 5.5, -30.5, 1, 1, // 106
		4.5, 5.5, -30.5, 0, 1, // 107
		// left
		4.5, 3.5, -30.5, 0, 0, // 108
		4.5, 3.5, -30.0, 1, 0, // 109
		4.5, 5.5, -30.0, 1, 1, // 110
		4.5, 5.5, -30.5, 0, 1, // 111
		// upper
		4.3, 5.5, -30.0, 0, 0,   // 112
		4.5, 5.5, -30.0, 1, 0,  // 113
		4.5, 5.5, -30.5, 1, 1,  // 114
		4.3, 5.5, -30.5, 0, 1,   // 115
		// bottom
		4.5, 3.5, -30.5, 0, 0, // 116
		4.3, 3.5, -30.5, 1, 0,  // 117
		4.3, 3.5, -30.0, 1, 1,  // 118
		4.5, 3.5, -30.0, 0, 1, // 119
		//TIANG 20
		// front
		4.5, 3.5, -31.5, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -31.5, 1, 0,  // 97 ,,kaba,
		4.3, 5.5, -31.5, 1, 1,  // 98 ,,kaat,
		4.5, 5.5, -31.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 5.5, -31.5, 0, 0,  // 100
		4.3, 5.5, -32.0, 1, 0,  // 101
		4.3, 3.5, -32.0, 1, 1,  // 102
		4.3, 3.5, -31.5, 0, 1,  // 103
		// back
		4.5, 3.5, -32.0, 0, 0, // 104
		4.3, 3.5, -32.0, 1, 0, // 105
		4.3, 5.5, -32.0, 1, 1, // 106
		4.5, 5.5, -32.0, 0, 1, // 107
		// left
		4.5, 3.5, -32.0, 0, 0, // 108
		4.5, 3.5, -31.5, 1, 0, // 109
		4.5, 5.5, -31.5, 1, 1, // 110
		4.5, 5.5, -32.0, 0, 1, // 111
		// upper
		4.3, 5.5, -31.5, 0, 0,   // 112
		4.5, 5.5, -31.5, 1, 0,  // 113
		4.5, 5.5, -32.0, 1, 1,  // 114
		4.3, 5.5, -32.0, 0, 1,   // 115
		// bottom
		4.5, 3.5, -32.0, 0, 0, // 116
		4.3, 3.5, -32.0, 1, 0,  // 117
		4.3, 3.5, -31.5, 1, 1,  // 118
		4.5, 3.5, -31.5, 0, 1, // 119
		//TIANG 21
		// front
		4.5, 3.5, -33.0, 0, 0,  // 96 ,,kiba,
		4.3, 3.5, -33.0, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, -33.0, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, -33.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, -33.0, 0, 0,  // 100
		4.3, 4.5, -33.5, 1, 0,  // 101
		4.3, 2.5, -33.5, 1, 1,  // 102
		4.3, 2.5, -33.0, 0, 1,  // 103
		// back
		4.5, 2.5, -33.5, 0, 0, // 104
		4.3, 2.5, -33.5, 1, 0, // 105
		4.3, 4.5, -33.5, 1, 1, // 106
		4.5, 4.5, -33.5, 0, 1, // 107
		// left
		4.5, 2.5, -33.5, 0, 0, // 108
		4.5, 2.5, -33.0, 1, 0, // 109
		4.5, 4.5, -33.0, 1, 1, // 110
		4.5, 4.5, -33.5, 0, 1, // 111
		// upper
		4.3, 4.5, -33.0, 0, 0,   // 112
		4.5, 4.5, -33.0, 1, 0,  // 113
		4.5, 4.5, -33.5, 1, 1,  // 114
		4.3, 4.5, -33.5, 0, 1,   // 115
		// bottom
		4.5, 2.5, -33.5, 0, 0, // 116
		4.3, 2.5, -33.5, 1, 0,  // 117
		4.3, 2.5, -33.0, 1, 1,  // 118
		4.5, 2.5, -33.0, 0, 1, // 119
		//TIANG 22
		// front
		4.5, 2.5, -34.5, 0, 0,  // 96 ,,kiba,
		4.3, 2.5, -34.5, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, -34.5, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, -34.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, -34.5, 0, 0,  // 100
		4.3, 4.5, -35.0, 1, 0,  // 101
		4.3, 2.5, -35.0, 1, 1,  // 102
		4.3, 2.5, -34.5, 0, 1,  // 103
		// back
		4.5, 2.5, -35.0, 0, 0, // 104
		4.3, 2.5, -35.0, 1, 0, // 105
		4.3, 4.5, -35.0, 1, 1, // 106
		4.5, 4.5, -35.0, 0, 1, // 107
		// left
		4.5, 2.5, -35.0, 0, 0, // 108
		4.5, 2.5, -34.5, 1, 0, // 109
		4.5, 4.5, -34.5, 1, 1, // 110
		4.5, 4.5, -35.0, 0, 1, // 111
		// upper
		4.3, 4.5, -34.5, 0, 0,   // 112
		4.5, 4.5, -34.5, 1, 0,  // 113
		4.5, 4.5, -35.0, 1, 1,  // 114
		4.3, 4.5, -35.0, 0, 1,   // 115
		// bottom
		4.5, 2.5, -35.0, 0, 0, // 116
		4.3, 2.5, -35.0, 1, 0,  // 117
		4.3, 2.5, -34.5, 1, 1,  // 118
		4.5, 2.5, -34.5, 0, 1, // 119
		//TIANG 23
		// front
		4.5, 2.5, -36.0, 0, 0,  // 96 ,,kiba,
		4.3, 2.5, -36.0, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, -36.0, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, -36.0, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, -36.0, 0, 0,  // 100
		4.3, 4.5, -36.5, 1, 0,  // 101
		4.3, 2.5, -36.5, 1, 1,  // 102
		4.3, 2.5, -36.0, 0, 1,  // 103
		// back
		4.5, 2.5, -36.5, 0, 0, // 104
		4.3, 2.5, -36.5, 1, 0, // 105
		4.3, 4.5, -36.5, 1, 1, // 106
		4.5, 4.5, -36.5, 0, 1, // 107
		// left
		4.5, 2.5, -36.5, 0, 0, // 108
		4.5, 2.5, -36.0, 1, 0, // 109
		4.5, 4.5, -36.0, 1, 1, // 110
		4.5, 4.5, -36.5, 0, 1, // 111
		// upper
		4.3, 4.5, -36.0, 0, 0,   // 112
		4.5, 4.5, -36.0, 1, 0,  // 113
		4.5, 4.5, -36.5, 1, 1,  // 114
		4.3, 4.5, -36.5, 0, 1,   // 115
		// bottom
		4.5, 2.5, -36.5, 0, 0, // 116
		4.3, 2.5, -36.5, 1, 0,  // 117
		4.3, 2.5, -36.0, 1, 1,  // 118
		4.5, 2.5, -36.0, 0, 1, // 119
		//TIANG 24
		// front
		4.5, 2.5, -37.5, 0, 0,  // 96 ,,kiba,
		4.3, 2.5, -37.5, 1, 0,  // 97 ,,kaba,
		4.3, 4.5, -37.5, 1, 1,  // 98 ,,kaat,
		4.5, 4.5, -37.5, 0, 1,  // 99 ,,kiat
		// right
		4.3, 4.5, -37.5, 0, 0,  // 100
		4.3, 4.5, -38.0, 1, 0,  // 101
		4.3, 2.5, -38.0, 1, 1,  // 102
		4.3, 2.5, -37.5, 0, 1,  // 103
		// back
		4.5, 2.5, -38.0, 0, 0, // 104
		4.3, 2.5, -38.0, 1, 0, // 105
		4.3, 4.5, -38.0, 1, 1, // 106
		4.5, 4.5, -38.0, 0, 1, // 107
		// left
		4.5, 2.5, -38.0, 0, 0, // 108
		4.5, 2.5, -37.5, 1, 0, // 109
		4.5, 4.5, -37.5, 1, 1, // 110
		4.5, 4.5, -38.0, 0, 1, // 111
		// upper
		4.3, 4.5, -37.5, 0, 0,   // 112
		4.5, 4.5, -37.5, 1, 0,  // 113
		4.5, 4.5, -38.0, 1, 1,  // 114
		4.3, 4.5, -38.0, 0, 1,   // 115
		// bottom
		4.5, 2.5, -38.0, 0, 0, // 116
		4.3, 2.5, -38.0, 1, 0,  // 117
		4.3, 2.5, -37.5, 1, 1,  // 118
		4.5, 2.5, -37.5, 0, 1, // 119
	};

	unsigned int indices1[] = {
		//tiang 1
		0, 1, 2, 0, 2, 3,   // front
		4, 5, 6, 4, 6, 7,   // right
		8, 9, 10, 8, 10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,  // bottom
		//tiang 2
		24, 25, 26, 24, 26, 27,   // front
		28, 29, 30, 28, 30, 31,   // right
		32, 33, 34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom
		//tiang 3
		48, 49, 50, 48, 50, 51,   // front
		52, 53, 54, 52, 54, 55,   // right
		56, 57, 58, 56, 58, 59,  // back
		60, 62, 61, 60, 63, 62,  // left
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		//tiang 4
		72, 73, 74, 72, 74, 75,   // front
		76, 77, 78, 76, 78, 79,   // right
		80, 81, 82, 80, 82, 83,  // back
		84, 86, 85, 84, 87, 86,  // left
		88, 90, 89, 88, 91, 90,  // upper
		92, 94, 93, 92, 95, 94,   // bottom
		//tiang 5
		96, 97, 98, 96, 98, 99,   // front
		100, 101, 102, 100, 102, 103,   // right
		104, 105, 106, 104, 106, 107,  // back
		108, 110, 109, 108, 111, 110,  // left
		112, 114, 113, 112, 115, 114,  // upper
		116, 118, 117, 116, 119, 118,   // bottom
		//tiang 6
		120, 121, 122, 120, 122, 123,   // front
		124, 125, 126, 124, 126, 127,   // right
		128, 129, 130, 128, 130, 131,  // back
		132, 134, 133, 132, 135, 134,  // left
		136, 138, 137, 136, 139, 138,  // upper
		140, 142, 141, 140, 143, 142,   // bottom
		//tiang 7
		144, 145, 146, 144, 146, 147,   // front
		148, 149, 150, 148, 150, 151,   // right
		152, 153, 154, 152, 154, 155,  // back
		156, 158, 157, 156, 159, 158,  // left
		160, 162, 161, 160, 163, 162,  // upper
		164, 166, 165, 164, 167, 166,   // bottom
		//tiang 8
		168, 169, 170, 168, 170, 171,   // front
		172, 173, 174, 172, 174, 175,   // right
		176, 177, 178, 176, 178, 179,  // back
		180, 182, 181, 180, 183, 182,  // left
		184, 186, 185, 184, 187, 186,  // upper
		188, 190, 189, 188, 191, 190,   // bottom
		//tiang 9
		192, 193, 194, 192, 194, 195,   // front
		196, 197, 198, 196, 198, 199,   // right
		200, 201, 202, 200, 202, 203,  // back
		204, 206, 205, 204, 207, 206,  // left
		208, 210, 209, 208, 211, 211,  // upper
		212, 214, 213, 212, 215, 214,   // bottom
		//tiang 10
		216, 217, 218, 216, 218, 219,   // front
		220, 221, 222, 220, 222, 223,   // right
		224, 225, 226, 224, 226, 227,  // back
		228, 230, 229, 228, 231, 230,  // left
		232, 234, 233, 232, 235, 234,  // upper
		236, 238, 237, 236, 239, 238,   // bottom
		//tiang 11
		240, 241, 242, 240, 242, 243,   // front
		244, 245, 246, 244, 246, 247,   // right
		248, 249, 250, 248, 250, 251,  // back
		252, 254, 253, 252, 255, 254,  // left
		256, 258, 257, 256, 259, 258,  // upper
		260, 262, 261, 260, 263, 262,   // bottom
		//tiang 12
		264, 265, 266, 264, 266, 267,   // front
		268, 269, 270, 268, 270, 271,   // right
		272, 273, 274, 272, 274, 275,  // back
		276, 278, 277, 276, 279, 278,  // left
		280, 282, 281, 280, 283, 282,  // upper
		284, 286, 285, 284, 287, 286,   // bottom
		//tiang 13
		288, 289, 290, 288, 290, 291,   // front
		292, 293, 294, 292, 294, 295,   // right
		296, 297, 298, 296, 298, 299,  // back
		300, 302, 301, 300, 303, 302,  // left
		304, 306, 305, 304, 307, 306,  // upper
		308, 310, 309, 308, 311, 310,   // bottom
		//tiang 14
		312, 313, 314, 312, 314, 315,   // front
		316, 317, 318, 316, 318, 319,   // right
		320, 321, 322, 320, 322, 323,  // back
		324, 326, 325, 324, 327, 326,  // left
		328, 330, 329, 328, 331, 330,  // upper
		332, 334, 333, 332, 335, 334,   // bottom
		//tiang 15
		336, 337, 338, 336, 338, 339,   // front
		340, 341, 342, 340, 342, 343,   // right
		344, 345, 346, 344, 346, 347,  // back
		348, 350, 349, 348, 351, 350,  // left
		352, 354, 353, 352, 355, 354,  // upper
		356, 358, 357, 356, 359, 358,   // bottom
		//tiang 16
		360, 361, 362, 360, 362, 363,   // front
		364, 365, 366, 364, 366, 367,   // right
		368, 369, 370, 368, 370, 371,  // back
		372, 374, 373, 372, 375, 374,  // left
		376, 378, 377, 376, 379, 378,  // upper
		380, 382, 381, 380, 383, 382,   // bottom
		//tiang 17
		384, 385, 386, 384, 386, 387,   // front
		388, 389, 390, 388, 390, 391,   // right
		392, 393, 394, 392, 394, 395,  // back
		396, 398, 397, 396, 399, 398,  // left
		400, 402, 401, 400, 403, 402,  // upper
		404, 406, 405, 404, 407, 406,   // bottom
		//tiang 18
		408, 409, 410, 408, 409, 410,   // front
		412, 413, 414, 412, 414, 415,   // right
		416, 417, 418, 416, 418, 419,  // back
		420, 422, 421, 420, 423, 422,  // left
		424, 426, 425, 424, 427, 426,  // upper
		428, 430, 429, 428, 431, 430,   // bottom
		//tiang 19
		432, 433, 434, 432, 434, 435,   // front
		436, 437, 438, 436, 438, 439,   // right
		440, 441, 442, 440, 442, 443,  // back
		444, 446, 445, 444, 447, 446,  // left
		448, 450, 449, 448, 451, 450,  // upper
		452, 454, 453, 452, 455, 454,   // bottom
		//tiang 20
		456, 457, 458, 456, 458, 459,   // front
		460, 461, 462, 460, 462, 463,   // right
		464, 465, 466, 464, 466, 467,  // back
		468, 470, 469, 468, 471, 470,  // left
		472, 474, 473, 472, 475, 474,  // upper
		476, 478, 477, 476, 479, 478,   // bottom
		//tiang 21
		480, 481, 482, 480, 482, 483,   // front
		484, 485, 486, 484, 486, 487,   // right
		488, 489, 490, 488, 490, 491,  // back
		492, 494, 493, 492, 495, 494,  // left
		496, 498, 497, 496, 499, 498,  // upper
		500, 502, 501, 500, 503, 502,   // bottom
		//tiang 22
		504, 505, 506, 504, 506, 507,   // front
		508, 509, 510, 508, 510, 511,   // right
		512, 513, 514, 512, 514, 515,  // back
		516, 518, 517, 516, 519, 518,  // left
		520, 522, 521, 520, 523, 522,  // upper
		524, 526, 525, 524, 527, 526,   // bottom
		//tiang 23
		528, 529, 530, 528, 530, 531,   // front
		532, 533, 534, 532, 534, 535,   // right
		536, 537, 538, 536, 538, 539,  // back
		540, 542, 541, 540, 543, 542,  // left
		544, 546, 545, 544, 547, 546,  // upper
		548, 550, 549, 548, 551, 550,   // bottom
		//tiang 24
		552, 553, 554, 552, 554, 555,   // front
		556, 557, 558, 556, 558, 559,   // right
		560, 561, 562, 560, 562, 563,  // back
		564, 566, 565, 564, 567, 566,  // left
		568, 570, 569, 568, 571, 570,  // upper
		572, 574, 573, 572, 575, 574,   // bottom
	};


	glGenVertexArrays(1, &VAO15);
	glGenBuffers(1, &VBO15);
	glGenBuffers(1, &EBO15);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO15);

	glBindBuffer(GL_ARRAY_BUFFER, VBO15);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO15);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTiang2Kanan(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO15);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 864, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredAtap2Kanan() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("besi.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices2[] = {
		// format position, tex coords
		//TIANG ATAP 1
		// upper
		4.5, 10.0, -4.0, 0, 0,   // 128 kiba
		4.3, 10.0, -4.0, 1, 0,  // 129 kaba
		4.3, 10.0, -8.5, 1, 1,  // 130 kaat
		4.5, 10.0, -8.5, 0, 1,   // 131 kiat
		// bottom
		4.3, 9.5, -8.5, 0, 0, // 132
		4.5, 9.5, -8.5, 1, 0,  // 133
		4.5, 9.5, -4.0, 1, 1,  // 134
		4.3, 9.5, -4.0, 0, 1, // 135
		// front
		4.3, 9.5, -8.5, 0, 0,  // 136
		4.3, 9.5, -4.0, 1, 0,  // 137
		4.3, 10.0,-4.0, 1, 1, // 138
		4.3, 10.0,-8.5, 0, 1, // 139
		// back
		4.5, 9.5, -8.5, 0, 0, // 140
		4.5, 9.5, -4.0, 1, 0, // 141
		4.5, 10.0,-4.0, 1, 1, // 142
		4.5, 10.0,-8.5, 0, 1, // 143
		//TIANG ATAP 2
		// upper
		4.5, 9.0, -8.0, 0, 0,   // 144
		4.3, 9.0, -8.0, 1, 0,  // 145
		4.3, 9.0, -12.0, 1, 1,  // 146
		4.5, 9.0, -12.0, 0, 1,   // 147
		// bottom
		4.3, 8.5, -12.0, 0, 0, // 148
		4.5, 8.5, -12.0, 1, 0,  // 149
		4.5, 8.5, -8.0, 1, 1,  // 150
		4.3, 8.5, -8.0, 0, 1, // 151
		// front
		4.3, 8.5, -12.0, 0, 0,  // 152
		4.3, 8.5, -8.0, 1, 0,  // 153
		4.3, 9.0,-8.0, 1, 1, // 154
		4.3, 9.0,-12.0, 0, 1, // 155
		// back
		4.5, 8.5, -12.0, 0, 0, // 156
		4.5, 8.5, -8.0, 1, 0, // 157
		4.5, 9.0,-8.0, 1, 1, // 158
		4.5, 9.0,-12.0, 0, 1, // 159
		//TIANG ATAP 3
		// upper
		4.5, 8.0, -12.0, 0, 0,   // 160
		4.3, 8.0, -12.0, 1, 0,  // 161
		4.3, 8.0, -15.5, 1, 1,  // 162
		4.5, 8.0, -15.5, 0, 1,   // 163
		//bottom
		4.3, 7.5, -15.5, 0, 0, // 164
		4.5, 7.5, -15.5, 1, 0,  //165
		4.5, 7.5, -12.0, 1, 1,  // 166
		4.3, 7.5, -12.0, 0, 1, // 167
		// front
		4.3, 7.5, -15.5, 0, 0,  // 168
		4.3, 7.5, -12.0, 1, 0,  // 169
		4.3, 8.0, -12.0, 1, 1, // 170
		4.3, 8.0, -15.5, 0, 1, // 171
		// back
		4.5, 8.0, -15.5, 0, 0, // 172
		4.5, 8.0, -12.0, 1, 0, // 173
		4.5, 7.5, -12.0, 1, 1, // 174
		4.5, 7.5, -15.5, 0, 1, // 175
		//TIANG ATAP 4
		// upper
		4.5, 7.0, -15.5, 0, 0,   // 176
		4.3, 7.0, -15.5, 1, 0,  // 177
		4.3, 7.0, -23.0, 1, 1,  // 178
		4.5, 7.0, -23.0, 0, 1,   // 179
		// bottom
		4.3, 6.5, -23.0, 0, 0, // 180
		4.5, 6.5, -23.0, 1, 0,  // 181
		4.5, 6.5, -15.5, 1, 1,  // 182
		4.3, 6.5, -15.5, 0, 1, // 183
		// front
		4.3, 6.5, -23.0, 0, 0,  // 184
		4.3, 6.5, -15.5, 1, 0,  // 185
		4.3, 7.0, -15.5, 1, 1, // 186
		4.3, 7.0, -23.0, 0, 1, // 187
		// back
		4.5, 6.5, -23.0, 0, 0, // 188
		4.5, 6.5, -15.5, 1, 0, // 189
		4.5, 7.0, -15.5, 1, 1, // 190
		4.5, 7.0, -23.0, 0, 1, // 191
		//TIANG ATAP 5
		// upper
		4.5, 6.0, -23.0, 0, 0,   // 192
		4.3, 6.0, -23.0, 1, 0,  // 193
		4.3, 6.0, -32.0, 1, 1,  // 194
		4.5, 6.0, -32.0, 0, 1,   // 195
		// bottom
		4.3, 5.5, -32.0, 0, 0, // 196
		4.5, 5.5, -32.0, 1, 0,  // 197
		4.5, 5.5, -23.0, 1, 1,  // 198
		4.3, 5.5, -23.0, 0, 1, // 199
		// front
		4.3, 5.5, -32.0, 0, 0,  // 200
		4.3, 5.5, -23.0, 1, 0,  // 201
		4.3, 6.0, -23.0, 1, 1, // 202
		4.3, 6.0, -32.0, 0, 1, // 203
		// back
		4.5, 5.5, -32.0, 0, 0, // 204
		4.5, 5.5, -23.0, 1, 0, // 205
		4.5, 6.0, -23.0, 1, 1, // 206
		4.5, 6.0, -32.0, 0, 1, // 207
		//TIANG ATAP 6
		// upper
		4.3, 4.5, -32.0, 0, 0,   // 208
		4.5, 4.5, -32.0, 1, 0,  // 209
		4.5, 4.5, -38.0, 1, 1,  // 210
		4.3, 4.5, -38.0, 0, 1,   // 211
		// bottom
		4.5, 5.0, -38.0, 0, 0, // 212
		4.3, 5.0, -38.0, 1, 0,  // 213
		4.3, 5.0, -32.0, 1, 1,  // 214
		4.5, 5.0, -32.0, 0, 1, // 215
		// front
		4.5, 4.5, -38.0, 0, 0,  // 216
		4.5, 4.5, -32.0, 1, 0,  // 217
		4.5, 5.0, -32.0, 1, 1, // 218
		4.5, 5.0, -38.0, 0, 1, // 219
		// back
		4.3, 4.5, -38.0, 0, 0, // 220
		4.3, 4.5, -32.0, 1, 0, // 221
		4.3, 5.0, -32.0, 1, 1, // 222
		4.3, 5.0, -38.0, 0, 1, // 223
	};

	unsigned int indices2[] = {
		//atap tiang -1
		0, 2, 1, 0, 3, 2,  // upper
		4, 6, 5, 4, 7, 6,   // bottom
		8, 9, 10, 8, 11, 10, // front
		12, 13, 14, 12, 15, 14, // back
		//atap tiang -2
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom
		24, 25, 26, 24, 27, 26, // front
		28, 29, 30, 28, 31, 30, // back
		//atap tiang -3
		32, 34, 33, 32, 35, 34,  // upper
		36, 38, 37, 36, 39, 38,   // bottom
		40, 41, 42, 40, 42, 43, // front
		44, 45, 46, 44, 46, 47, // back
		//atap tiang -4
		48, 50, 49, 48, 51, 50,  // upper
		52, 54, 53, 52, 55, 54,   // bottom
		56, 57, 58, 56, 58, 59, // front
		60, 61, 62, 60, 62, 63, // back
		//atap tiang -5
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		72, 73, 74, 72, 74, 75, // front
		76, 77, 78, 76, 78, 79, // back
		//atap tiang -6
		80, 82, 81, 80, 83, 82,  // upper
		84, 86, 85, 84, 87, 86,   // bottom
		88, 89, 90, 88, 90, 91, // front
		92, 93, 94, 92, 94, 95, // back
	};


	glGenVertexArrays(1, &VAO17);
	glGenBuffers(1, &VBO17);
	glGenBuffers(1, &EBO17);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO17);

	glBindBuffer(GL_ARRAY_BUFFER, VBO17);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO17);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredAtap2Kanan(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO17);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 144, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

///////////////////////////////////
///// INI KERJAAN WAWAN ///////////
//////////////////////////////////
void Demo::BuildColoredCube() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lamp.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		//lampu1
		// front
		0.5, 8.5, 0.5, 0, 0, 0.0f, 0.0f, 1.0f, // 0
		1.0, 8.5, 0.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
		1.0, 13.0, 0.5, 1, 1, 0.0f, 0.0f, 1.0f,   // 2
		0.5, 13.0, 0.5, 0, 1, 0.0f, 0.0f, 1.0f,  // 3
		// right
		1.0, 13.0,  0.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		1.0, 13.0, 0.0, 1, 0, 1.0f, 0.0f, 0.0f, // 5
		1.0, 8.5, 0.0, 1, 1, 1.0f, 0.0f, 0.0f, // 6
		1.0, 8.5,  0.5, 0, 1, 1.0f, 0.0f, 0.0f, // 7
		// back
		0.5, 8.5, 0.0, 0, 0, 0.0f, 0.0f, -1.0f,// 8 
		1.0, 8.5, 0.0, 1, 0, 0.0f, 0.0f, -1.0f,// 9
		1.0, 13.0, 0.0, 1, 1, 0.0f, 0.0f, -1.0f,// 10
		0.5, 13.0, 0.0, 0, 1,0.0f, 0.0f, -1.0f, // 11
		// left
		0.5, 8.5, 0.0, 0, 0, -1.0f, 0.0f, 0.0f,// 12
		0.5, 8.5,  0.5, 1, 0,-1.0f, 0.0f, 0.0f, // 13
		0.5, 13.0,  0.5, 1, 1,-1.0f, 0.0f, 0.0f, // 14
		0.5, 13.0, 0.0, 0, 1, -1.0f, 0.0f, 0.0f,// 15
		// upper
		1.0, 13.0,  0.5, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
		0.5, 13.0,  0.5, 1, 0, 0.0f, 1.0f, 0.0f, // 17
		0.5, 13.0, 0.0, 1, 1, 0.0f, 1.0f, 0.0f, // 18
		1.0, 13.0, 0.0, 0, 1,  0.0f, 1.0f, 0.0f, // 19
		// bottom
		0.5, 8.5, 0.0, 0, 0,0.0f, -1.0f, 0.0f, // 20
		1.0, 8.5, 0.0, 1, 0, 0.0f, -1.0f, 0.0f, // 21
		1.0, 8.5,  0.5, 1, 1,0.0f, -1.0f, 0.0f,  // 22
		0.5, 8.5,  0.5, 0, 1, 0.0f, -1.0f, 0.0f,// 23

		//lampu1kanan
		// front
		4.0, 8.5, 0.5, 0, 0, 0.0f, 0.0f, 1.0f, // 24
		4.5, 8.5, 0.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 25
		4.5, 13.0, 0.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 26
		4.0, 13.0, 0.5, 0, 1, 0.0f, 0.0f, 1.0f, // 27
		// right
		4.5, 13.0,  0.5, 0, 0, 1.0f, 0.0f, 0.0f, // 28
		4.5, 13.0, 0.0, 1, 0, 1.0f, 0.0f, 0.0f, // 29
		4.5, 8.5, 0.0, 1, 1, 1.0f, 0.0f, 0.0f, // 30
		4.5, 8.5,  0.5, 0, 1,1.0f, 0.0f, 0.0f,  // 31
		// back
		4.0, 8.5, 0.0, 0, 0,0.0f, 0.0f, -1.0f, // 32
		4.5, 8.5, 0.0, 1, 0, 0.0f, 0.0f, -1.0f,// 33
		4.5, 13.0, 0.0, 1, 1,0.0f, 0.0f, -1.0f, // 34
		4.0, 13.0, 0.0, 0, 1,0.0f, 0.0f, -1.0f, // 35
		// left
		4.0, 8.5, 0.0, 0, 0,-1.0f, 0.0f, 0.0f, // 36
		4.0, 8.5,  0.5, 1, 0,-1.0f, 0.0f, 0.0f,// 37
		4.0, 13.0,  0.5, 1, 1,-1.0f, 0.0f, 0.0f, // 38
		4.0, 13.0, 0.0, 0, 1,-1.0f, 0.0f, 0.0f, // 39
		// upper
		4.5, 13.0,  0.5, 0, 0,  0.0f, 1.0f, 0.0f, // 40
		4.0, 13.0,  0.5, 1, 0, 0.0f, 1.0f, 0.0f, // 41
		4.0, 13.0, 0.0, 1, 1, 0.0f, 1.0f, 0.0f, // 41
		4.5, 13.0, 0.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
		// bottom
		4.0, 8.5, 0.0, 0, 0,0.0f, -1.0f, 0.0f, // 44
		4.5, 8.5, 0.0, 1, 0, 0.0f, -1.0f, 0.0f, // 45
		4.5, 8.5,  0.5, 1, 1,0.0f, -1.0f, 0.0f,  // 46
		4.0, 8.5,  0.5, 0, 1,0.0f, -1.0f, 0.0f,// 47

		//lampu2
		// front
		0.5, 5.5, -14.5, 0, 0, 0.0f, 0.0f, 1.0f, // 0
		1.0, 5.5, -14.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
		1.0, 11.0, -14.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
		0.5, 11.0, -14.5, 0, 1, 0.0f, 0.0f, 1.0f, // 3
		// right
		1.0, 11.0,  -14.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		1.0, 11.0, -15.0, 1, 0, 1.0f, 0.0f, 0.0f, // 5
		1.0, 5.5, -15.0, 1, 1,  1.0f, 0.0f, 0.0f,// 6
		1.0, 5.5,  -14.5, 0, 1, 1.0f, 0.0f, 0.0f, // 7
		// back
		0.5, 5.5, -15.0, 0, 0,0.0f, 0.0f, -1.0f, // 8 
		1.0, 5.5, -15.0, 1, 0, 0.0f, 0.0f, -1.0f,// 9
		1.0, 11.0, -15.0, 1, 1, 0.0f, 0.0f, -1.0f,// 10
		0.5, 11.0, -15.0, 0, 1,0.0f, 0.0f, -1.0f, // 11
		// left
		0.5, 5.5, -15.0, 0, 0, -1.0f, 0.0f, 0.0f,// 12
		0.5, 5.5,  -14.5, 1, 0, -1.0f, 0.0f, 0.0f,// 13
		0.5, 11.0,  -14.5, 1, 1,-1.0f, 0.0f, 0.0f, // 14
		0.5, 11.0, -15.0, 0, 1,-1.0f, 0.0f, 0.0f, // 15
		// upper
		1.0, 11.0,  -14.5, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
		0.5, 11.0,  -14.5, 1, 0,0.0f, 1.0f, 0.0f,  // 17
		0.5, 11.0, -15.0, 1, 1, 0.0f, 1.0f, 0.0f, // 18
		1.0, 11.0, -15.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 19
		// bottom
		0.5, 5.5, -15.0, 0, 0,0.0f, -1.0f, 0.0f, // 20
		1.0, 5.5, -15.0, 1, 0, 0.0f, -1.0f, 0.0f, // 21
		1.0, 5.5,  -14.5, 1, 1, 0.0f, -1.0f, 0.0f, // 22
		0.5, 5.5,  -14.5, 0, 1,0.0f, -1.0f, 0.0f, // 23

		//lampu2kanan
		// front
		4.0, 5.5, -14.5, 0, 0, 0.0f, 0.0f, 1.0f, // 24
		4.5, 5.5, -14.5, 1, 0, 0.0f, 0.0f, 1.0f, // 25
		4.5, 11.0, -14.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 26
		4.0, 11.0, -14.5, 0, 1, 0.0f, 0.0f, 1.0f, // 27
		// right
		4.5, 11.0, -14.5, 0, 0, 1.0f, 0.0f, 0.0f, // 28
		4.5, 11.0, -15.0, 1, 0, 1.0f, 0.0f, 0.0f, // 29
		4.5, 5.5, -15.0, 1, 1, 1.0f, 0.0f, 0.0f, // 30
		4.5, 5.5, -14.5, 0, 1, 1.0f, 0.0f, 0.0f, // 31
		// back
		4.0, 5.5, -15.0, 0, 0, 0.0f, 0.0f, -1.0f, // 32
		4.5, 5.5, -15.0, 1, 0, 0.0f, 0.0f, -1.0f,// 33
		4.5, 11.0, -15.0, 1, 1, 0.0f, 0.0f, -1.0f, // 34
		4.0, 11.0, -15.0, 0, 1, 0.0f, 0.0f, -1.0f,// 35
		// left
		4.0, 5.5, -15.0, 0, 0, -1.0f, 0.0f, 0.0f, // 36
		4.0, 5.5, -14.5, 1, 0, -1.0f, 0.0f, 0.0f,// 37
		4.0, 11.0, -14.5, 1, 1, -1.0f, 0.0f, 0.0f, // 38
		4.0, 11.0, -15.0, 0, 1, -1.0f, 0.0f, 0.0f,// 39
		// upper
		4.5, 11.0, -14.5, 0, 0, 0.0f, 1.0f, 0.0f,  // 40
		4.0, 11.0, -14.5, 1, 0, 0.0f, 1.0f, 0.0f, // 41
		4.0, 11.0, -15.0, 1, 1, 0.0f, 1.0f, 0.0f, // 41
		4.5, 11.0, -15.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
		// bottom
		4.0, 5.5, -15.0, 0, 0, 0.0f, -1.0f, 0.0f,// 44
		4.5, 5.5, -15.0, 1, 0, 0.0f, -1.0f, 0.0f,  // 45
		4.5, 5.5, -14.5, 1, 1, 0.0f, -1.0f, 0.0f,  // 46
		4.0, 5.5, -14.5, 0, 1, 0.0f, -1.0f, 0.0f,// 47

		//lampu3
		// front
			0.5, 3.5, -29.5, 0, 0, 0.0f, 0.0f, 1.0f, // 0
			1.0, 3.5, -29.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
			1.0, 8.0, -29.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
			0.5, 8.0, -29.5, 0, 1, 0.0f, 0.0f, 1.0f, // 3
			// right
			1.0, 8.0, -29.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
			1.0, 8.0, -30.0, 1, 0, 1.0f, 0.0f, 0.0f, // 5
			1.0, 3.5, -30.0, 1, 1, 1.0f, 0.0f, 0.0f, // 6
			1.0, 3.5, -29.5, 0, 1, 1.0f, 0.0f, 0.0f, // 7
			// back
			0.5, 3.5, -30.0, 0, 0, 0.0f, 0.0f, -1.0f, // 8 
			1.0, 3.5, -30.0, 1, 0, 0.0f, 0.0f, -1.0f, // 9
			1.0, 8.0, -30.0, 1, 1, 0.0f, 0.0f, -1.0f,// 10
			0.5, 8.0, -30.0, 0, 1, 0.0f, 0.0f, -1.0f,// 11
			// left
			0.5, 3.5, -30.0, 0, 0, -1.0f, 0.0f, 0.0f,// 12
			0.5, 3.5, -29.5, 1, 0, -1.0f, 0.0f, 0.0f,// 13
			0.5, 8.0, -29.5, 1, 1, -1.0f, 0.0f, 0.0f,// 14
			0.5, 8.0, -30.0, 0, 1, -1.0f, 0.0f, 0.0f,// 15
			// upper
			1.0, 8.0, -29.5, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
			0.5, 8.0, -29.5, 1, 0, 0.0f, 1.0f, 0.0f, // 17
			0.5, 8.0, -30.0, 1, 1, 0.0f, 1.0f, 0.0f, // 18
			1.0, 8.0, -30.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 19
			// bottom
			0.5, 3.5, -30.0, 0, 0, 0.0f, -1.0f, 0.0f,// 20
			1.0, 3.5, -30.0, 1, 0, 0.0f, -1.0f, 0.0f, // 21
			1.0, 3.5, -29.5, 1, 1, 0.0f, -1.0f, 0.0f, // 22
			0.5, 3.5, -29.5, 0, 1, 0.0f, -1.0f, 0.0f,// 23
			//lampu3kanan
			// front
			4.0, 3.5, -29.5, 0, 0, 0.0f, 0.0f, 1.0f, // 24
			4.5, 3.5, -29.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 25
			4.5, 8.0, -29.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 26
			4.0, 8.0, -29.5, 0, 1, 0.0f, 0.0f, 1.0f, // 27
			// right
			4.5, 8.0, -29.5, 0, 0, 1.0f, 0.0f, 0.0f, // 28
			4.5, 8.0, -30.0, 1, 0, 1.0f, 0.0f, 0.0f, // 29
			4.5, 3.5, -30.0, 1, 1, 1.0f, 0.0f, 0.0f, // 30
			4.5, 3.5, -29.5, 0, 1, 1.0f, 0.0f, 0.0f, // 31
			// back
			4.0, 3.5, -30.0, 0, 0, 0.0f, 0.0f, -1.0f,// 32
			4.5, 3.5, -30.0, 1, 0, 0.0f, 0.0f, -1.0f,// 33
			4.5, 8.0, -30.0, 1, 1, 0.0f, 0.0f, -1.0f,// 34
			4.0, 8.0, -30.0, 0, 1, 0.0f, 0.0f, -1.0f,// 35
			// left
			4.0, 3.5, -30.0, 0, 0, -1.0f, 0.0f, 0.0f,// 36
			4.0, 3.5, -29.5, 1, 0, -1.0f, 0.0f, 0.0f,// 37
			4.0, 8.0, -29.5, 1, 1, -1.0f, 0.0f, 0.0f,// 38
			4.0, 8.0, -30.0, 0, 1, -1.0f, 0.0f, 0.0f,// 39
			// upper
			4.5, 8.0, -29.5, 0, 0, 0.0f, 1.0f, 0.0f, // 40
			4.0, 8.0, -29.5, 1, 0, 0.0f, 1.0f, 0.0f, // 41
			4.0, 8.0, -30.0, 1, 1, 0.0f, 1.0f, 0.0f, // 41
			4.5, 8.0, -30.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
			// bottom
			4.0, 3.5, -30.0, 0, 0, 0.0f, -1.0f, 0.0f,// 44
			4.5, 3.5, -30.0, 1, 0, 0.0f, -1.0f, 0.0f, // 45
			4.5, 3.5, -29.5, 1, 1, 0.0f, -1.0f, 0.0f, // 46
			4.0, 3.5, -29.5, 0, 1, 0.0f, -1.0f, 0.0f,// 47

			//lampu4
		// front
			0.5, 2.5, -44.5, 0, 0, 0.0f, 0.0f, 1.0f, // 0
			1.0, 2.5, -44.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
			1.0, 7.0, -44.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
			0.5, 7.0, -44.5, 0, 1, 0.0f, 0.0f, 1.0f, // 3
			// right
			1.0, 7.0, -44.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
			1.0, 7.0, -45.0, 1, 0, 1.0f, 0.0f, 0.0f, // 5
			1.0, 2.5, -45.0, 1, 1, 1.0f, 0.0f, 0.0f, // 6
			1.0, 2.5, -44.5, 0, 1, 1.0f, 0.0f, 0.0f, // 7
			// back
			0.5, 2.5, -45.0, 0, 0, 0.0f, 0.0f, -1.0f, // 8 
			1.0, 2.5, -45.0, 1, 0, 0.0f, 0.0f, -1.0f, // 9
			1.0, 7.0, -45.0, 1, 1, 0.0f, 0.0f, -1.0f,// 10
			0.5, 7.0, -45.0, 0, 1, 0.0f, 0.0f, -1.0f,// 11
			// left
			0.5, 2.5, -45.0, 0, 0, -1.0f, 0.0f, 0.0f,// 12
			0.5, 2.5, -44.5, 1, 0, -1.0f, 0.0f, 0.0f,// 13
			0.5, 7.0, -44.5, 1, 1, -1.0f, 0.0f, 0.0f,// 14
			0.5, 7.0, -45.0, 0, 1, -1.0f, 0.0f, 0.0f,// 15
			// upper
			1.0, 7.0, -44.5, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
			0.5, 7.0, -44.5, 1, 0, 0.0f, 1.0f, 0.0f, // 17
			0.5, 7.0, -45.0, 1, 1, 0.0f, 1.0f, 0.0f, // 18
			1.0, 7.0, -45.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 19
			// bottom
			0.5, 2.5, -45.0, 0, 0, 0.0f, -1.0f, 0.0f,// 20
			1.0, 2.5, -45.0, 1, 0, 0.0f, -1.0f, 0.0f, // 21
			1.0, 2.5, -44.5, 1, 1, 0.0f, -1.0f, 0.0f, // 22
			0.5, 2.5, -44.5, 0, 1, 0.0f, -1.0f, 0.0f,// 23
			//lampu4kanan
			// front
			4.0, 2.5, -44.5, 0, 0, 0.0f, 0.0f, 1.0f, // 24
			4.5, 2.5, -44.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 25
			4.5, 7.0, -44.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 26
			4.0, 7.0, -44.5, 0, 1, 0.0f, 0.0f, 1.0f, // 27
			// right
			4.5, 7.0, -44.5, 0, 0, 1.0f, 0.0f, 0.0f, // 28
			4.5, 7.0, -45.0, 1, 0, 1.0f, 0.0f, 0.0f, // 29
			4.5, 2.5, -45.0, 1, 1, 1.0f, 0.0f, 0.0f, // 30
			4.5, 2.5, -44.5, 0, 1, 1.0f, 0.0f, 0.0f, // 31
			// back
			4.0, 2.5, -45.0, 0, 0, 0.0f, 0.0f, -1.0f,// 32
			4.5, 2.5, -45.0, 1, 0, 0.0f, 0.0f, -1.0f,// 33
			4.5, 7.0, -45.0, 1, 1, 0.0f, 0.0f, -1.0f,// 34
			4.0, 7.0, -45.0, 0, 1, 0.0f, 0.0f, -1.0f,// 35
			// left
			4.0, 2.5, -45.0, 0, 0, -1.0f, 0.0f, 0.0f,// 36
			4.0, 2.5, -44.5, 1, 0, -1.0f, 0.0f, 0.0f,// 37
			4.0, 7.0, -44.5, 1, 1, -1.0f, 0.0f, 0.0f,// 38
			4.0, 7.0, -45.0, 0, 1, -1.0f, 0.0f, 0.0f,// 39
			// upper
			4.5, 7.0, -44.5, 0, 0, 0.0f, 1.0f, 0.0f,  // 40
			4.0, 7.0, -44.5, 1, 0, 0.0f, 1.0f, 0.0f, // 41
			4.0, 7.0, -45.0, 1, 1, 0.0f, 1.0f, 0.0f, // 41
			4.5, 7.0, -45.0, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
			// bottom
			4.0, 2.5, -45.0, 0, 0, 0.0f, -1.0f, 0.0f, // 44
			4.5, 2.5, -45.0, 1, 0, 0.0f, -1.0f, 0.0f, // 45
			4.5, 2.5, -44.5, 1, 1, 0.0f, -1.0f, 0.0f, // 46
			4.0, 2.5, -44.5, 0, 1, 0.0f, -1.0f, 0.0f,// 47

			//lampu5
			// front
				0.5, 5.5, 15.0, 0, 0, 0.0f, 0.0f, 1.0f, // 0
				1.0, 5.5, 15.0, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
				1.0, 11.0, 15.0, 1, 1, 0.0f, 0.0f, 1.0f,   // 2
				0.5, 11.0, 15.0, 0, 1, 0.0f, 0.0f, 1.0f,  // 3
				// right
				1.0, 11.0, 15.0, 0, 0, 1.0f, 0.0f, 0.0f, // 4
				1.0, 11.0, 14.5, 1, 0, 1.0f, 0.0f, 0.0f, // 5
				1.0, 5.5, 14.5, 1, 1, 1.0f, 0.0f, 0.0f,// 6
				1.0, 5.5, 15.0, 0, 1, 1.0f, 0.0f, 0.0f, // 7
				// back
				0.5, 5.5, 14.5, 0, 0, 0.0f, 0.0f, -1.0f,// 8 
				1.0, 5.5, 14.5, 1, 0, 0.0f, 0.0f, -1.0f,// 9
				1.0, 11.0, 14.5, 1, 1, 0.0f, 0.0f, -1.0f, // 10
				0.5, 11.0, 14.5, 0, 1, 0.0f, 0.0f, -1.0f, // 11
				// left
				0.5, 5.5, 14.5, 0, 0, -1.0f, 0.0f, 0.0f,// 12
				0.5, 5.5, 15.0, 1, 0, -1.0f, 0.0f, 0.0f,// 13
				0.5, 11.0, 15.0, 1, 1, -1.0f, 0.0f, 0.0f,// 14
				0.5, 11.0, 14.5, 0, 1, -1.0f, 0.0f, 0.0f,// 15
				// upper
				1.0, 11.0, 15.0, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
				0.5, 11.0, 15.0, 1, 0, 0.0f, 1.0f, 0.0f, // 17
				0.5, 11.0, 14.5, 1, 1, 0.0f, 1.0f, 0.0f, // 18
				1.0, 11.0, 14.5, 0, 1, 0.0f, 1.0f, 0.0f,  // 19
				// bottom
				0.5, 5.5, 14.5, 0, 0, 0.0f, -1.0f, 0.0f, // 20
				1.0, 5.5, 14.5, 1, 0, 0.0f, -1.0f, 0.0f, // 21
				1.0, 5.5, 15.0, 1, 1, 0.0f, -1.0f, 0.0f, // 22
				0.5, 5.5, 15.0, 0, 1, 0.0f, -1.0f, 0.0f,// 23
				//lampu5kanan
				// front
				4.0, 5.5, 15.0, 0, 0, 0.0f, 0.0f, 1.0f, // 24
				4.5, 5.5, 15.0, 1, 0, 0.0f, 0.0f, 1.0f,  // 25
				4.5, 11.0, 15.0, 1, 1, 0.0f, 0.0f, 1.0f,   // 26
				4.0, 11.0, 15.0, 0, 1, 0.0f, 0.0f, 1.0f,  // 27
				// right
				4.5, 11.0, 15.0, 0, 0, 1.0f, 0.0f, 0.0f, // 28
				4.5, 11.0, 14.5, 1, 0, 1.0f, 0.0f, 0.0f, // 29
				4.5, 5.5, 14.5, 1, 1, 1.0f, 0.0f, 0.0f,// 30
				4.5, 5.5, 15.0, 0, 1, 1.0f, 0.0f, 0.0f,// 31
				// back
				4.0, 5.5, 14.5, 0, 0, 0.0f, 0.0f, -1.0f,// 32
				4.5, 5.5, 14.5, 1, 0, 0.0f, 0.0f, -1.0f,// 33
				4.5, 11.0, 14.5, 1, 1, 0.0f, 0.0f, -1.0f,// 34
				4.0, 11.0, 14.5, 0, 1, 0.0f, 0.0f, -1.0f,// 35
				// left
				4.0, 5.5, 14.5, 0, 0, -1.0f, 0.0f, 0.0f,// 36
				4.0, 5.5, 15.0, 1, 0, -1.0f, 0.0f, 0.0f,// 37
				4.0, 11.0, 15.0, 1, 1, -1.0f, 0.0f, 0.0f, // 38
				4.0, 11.0, 14.5, 0, 1, -1.0f, 0.0f, 0.0f, // 39
				// upper
				4.5, 11.0, 15.0, 0, 0, 0.0f, 1.0f, 0.0f, // 40
				4.0, 11.0, 15.0, 1, 0, 0.0f, 1.0f, 0.0f,// 41
				4.0, 11.0, 14.5, 1, 1, 0.0f, 1.0f, 0.0f, // 41
				4.5, 11.0, 14.5, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
				// bottom
				4.0, 5.5, 14.5, 0, 0, 0.0f, -1.0f, 0.0f,// 44
				4.5, 5.5, 14.5, 1, 0, 0.0f, -1.0f, 0.0f, // 45
				4.5, 5.5, 15.0, 1, 1, 0.0f, -1.0f, 0.0f, // 46
				4.0, 5.5, 15.0, 0, 1, 0.0f, -1.0f, 0.0f,// 47

				//lampu6
				// front
				0.5, 3.5, 30.0, 0, 0, 0.0f, 0.0f, 1.0f, // 0
				1.0, 3.5, 30.0, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
				1.0, 8.0, 30.0, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
				0.5, 8.0, 30.0, 0, 1, 0.0f, 0.0f, 1.0f, // 3
				// right
				1.0, 8.0, 30.0, 0, 0, 1.0f, 0.0f, 0.0f, // 4
				1.0, 8.0, 29.5, 1, 0, 1.0f, 0.0f, 0.0f, // 5
				1.0, 3.5, 29.5, 1, 1, 1.0f, 0.0f, 0.0f, // 6
				1.0, 3.5, 30.0, 0, 1, 1.0f, 0.0f, 0.0f, // 7
				// back
				0.5, 3.5, 29.5, 0, 0, 0.0f, 0.0f, -1.0f, // 8 
				1.0, 3.5, 29.5, 1, 0, 0.0f, 0.0f, -1.0f,// 9
				1.0, 8.0, 29.5, 1, 1, 0.0f, 0.0f, -1.0f,// 10
				0.5, 8.0, 29.5, 0, 1, 0.0f, 0.0f, -1.0f,// 11
				// left
				0.5, 3.5, 29.5, 0, 0, -1.0f, 0.0f, 0.0f,// 12
				0.5, 3.5, 30.0, 1, 0, -1.0f, 0.0f, 0.0f,// 13
				0.5, 8.0, 30.0, 1, 1, -1.0f, 0.0f, 0.0f,// 14
				0.5, 8.0, 29.5, 0, 1, -1.0f, 0.0f, 0.0f,// 15
				// upper
				1.0, 8.0, 30.0, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
				0.5, 8.0, 30.0, 1, 0, 0.0f, 1.0f, 0.0f, // 17
				0.5, 8.0, 29.5, 1, 1, 0.0f, 1.0f, 0.0f, // 18
				1.0, 8.0, 29.5, 0, 1, 0.0f, 1.0f, 0.0f,  // 19
				// bottom
				0.5, 3.5, 29.5, 0, 0, 0.0f, -1.0f, 0.0f, // 20
				1.0, 3.5, 29.5, 1, 0, 0.0f, -1.0f, 0.0f, // 21
				1.0, 3.5, 30.0, 1, 1, 0.0f, -1.0f, 0.0f, // 22
				0.5, 3.5, 30.0, 0, 1, 0.0f, -1.0f, 0.0f,// 23

				//lampu6kanan
				// front
				4.0, 3.5, 30.0, 0, 0, 0.0f, 0.0f, 1.0f, // 24
				4.5, 3.5, 30.0, 1, 0, 0.0f, 0.0f, 1.0f,  // 25
				4.5, 8.0, 30.0, 1, 1, 0.0f, 0.0f, 1.0f,  // 26
				4.0, 8.0, 30.0, 0, 1, 0.0f, 0.0f, 1.0f, // 27
				// right
				4.5, 8.0, 30.0, 0, 0, 1.0f, 0.0f, 0.0f, // 28
				4.5, 8.0, 29.5, 1, 0, 1.0f, 0.0f, 0.0f, // 29
				4.5, 3.5, 29.5, 1, 1, 1.0f, 0.0f, 0.0f, // 30
				4.5, 3.5, 30.0, 0, 1, 1.0f, 0.0f, 0.0f, // 31
				// back
				4.0, 3.5, 29.5, 0, 0, 0.0f, 0.0f, -1.0f,// 32
				4.5, 3.5, 29.5, 1, 0, 0.0f, 0.0f, -1.0f,// 33
				4.5, 8.0, 29.5, 1, 1, 0.0f, 0.0f, -1.0f,// 34
				4.0, 8.0, 29.5, 0, 1, 0.0f, 0.0f, -1.0f, // 35
				// left
				4.0, 3.5, 29.5, 0, 0, -1.0f, 0.0f, 0.0f,// 36
				4.0, 3.5, 30.0, 1, 0, -1.0f, 0.0f, 0.0f,// 37
				4.0, 8.0, 30.0, 1, 1, -1.0f, 0.0f, 0.0f,// 38
				4.0, 8.0, 29.5, 0, 1, -1.0f, 0.0f, 0.0f,// 39
				// upper
				4.5, 8.0, 30.0, 0, 0, 0.0f, 1.0f, 0.0f,  // 40
				4.0, 8.0, 30.0, 1, 0, 0.0f, 1.0f, 0.0f, // 41
				4.0, 8.0, 29.5, 1, 1, 0.0f, 1.0f, 0.0f, // 41
				4.5, 8.0, 29.5, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
				// bottom
				4.0, 3.5, 29.5, 0, 0, 0.0f, -1.0f, 0.0f,// 44
				4.5, 3.5, 29.5, 1, 0, 0.0f, -1.0f, 0.0f, // 45
				4.5, 3.5, 30.0, 1, 1, 0.0f, -1.0f, 0.0f, // 46
				4.0, 3.5, 30.0, 0, 1, 0.0f, -1.0f, 0.0f,// 47

				//lampu7
			// front
				0.5, 2.5, 45.0, 0, 0, 0.0f, 0.0f, 1.0f, // 0
				1.0, 2.5, 45.0, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
				1.0, 7.0, 45.0, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
				0.5, 7.0, 45.0, 0, 1, 0.0f, 0.0f, 1.0f, // 3
				// right
				1.0, 7.0, 45.0, 0, 0, 1.0f, 0.0f, 0.0f, // 4
				1.0, 7.0, 44.5, 1, 0, 1.0f, 0.0f, 0.0f, // 5
				1.0, 2.5, 44.5, 1, 1, 1.0f, 0.0f, 0.0f, // 6
				1.0, 2.5, 45.0, 0, 1, 1.0f, 0.0f, 0.0f, // 7
				// back
				0.5, 2.5, 44.5, 0, 0, 0.0f, 0.0f, -1.0f,// 8 
				1.0, 2.5, 44.5, 1, 0, 0.0f, 0.0f, -1.0f,// 9
				1.0, 7.0, 44.5, 1, 1, 0.0f, 0.0f, -1.0f,// 10
				0.5, 7.0, 44.5, 0, 1, 0.0f, 0.0f, -1.0f,// 11
				// left
				0.5, 2.5, 44.5, 0, 0, -1.0f, 0.0f, 0.0f,// 12
				0.5, 2.5, 45.0, 1, 0, -1.0f, 0.0f, 0.0f,// 13
				0.5, 7.0, 45.0, 1, 1, -1.0f, 0.0f, 0.0f,// 14
				0.5, 7.0, 44.5, 0, 1, -1.0f, 0.0f, 0.0f,// 15
				// upper
				1.0, 7.0, 45.0, 0, 0, 0.0f, 1.0f, 0.0f,  // 16
				0.5, 7.0, 45.0, 1, 0, 0.0f, 1.0f, 0.0f, // 17
				0.5, 7.0, 44.5, 1, 1, 0.0f, 1.0f, 0.0f, // 18
				1.0, 7.0, 44.5, 0, 1, 0.0f, 1.0f, 0.0f,  // 19
				// bottom
				0.5, 2.5, 44.5, 0, 0, 0.0f, -1.0f, 0.0f,// 20
				1.0, 2.5, 44.5, 1, 0, 0.0f, -1.0f, 0.0f, // 21
				1.0, 2.5, 45.0, 1, 1, 0.0f, -1.0f, 0.0f, // 22
				0.5, 2.5, 45.0, 0, 1, 0.0f, -1.0f, 0.0f,// 23
				//lampu7kanan
				// front
				4.0, 2.5, 45.0, 0, 0, 0.0f, 0.0f, 1.0f, // 24
				4.5, 2.5, 45.0, 1, 0, 0.0f, 0.0f, 1.0f,  // 25
				4.5, 7.0, 45.0, 1, 1, 0.0f, 0.0f, 1.0f,  // 26
				4.0, 7.0, 45.0, 0, 1, 0.0f, 0.0f, 1.0f, // 27
				// right
				4.5, 7.0, 45.0, 0, 0, 1.0f, 0.0f, 0.0f, // 28
				4.5, 7.0, 44.5, 1, 0, 1.0f, 0.0f, 0.0f, // 29
				4.5, 2.5, 44.5, 1, 1, 1.0f, 0.0f, 0.0f, // 30
				4.5, 2.5, 45.0, 0, 1, 1.0f, 0.0f, 0.0f, // 31
				// back
				4.0, 2.5, 44.5, 0, 0, 0.0f, 0.0f, -1.0f,// 32
				4.5, 2.5, 44.5, 1, 0, 0.0f, 0.0f, -1.0f,// 33
				4.5, 7.0, 44.5, 1, 1, 0.0f, 0.0f, -1.0f,// 34
				4.0, 7.0, 44.5, 0, 1, 0.0f, 0.0f, -1.0f,// 35
				// left
				4.0, 2.5, 44.5, 0, 0, -1.0f, 0.0f, 0.0f, // 36
				4.0, 2.5, 45.0, 1, 0, -1.0f, 0.0f, 0.0f,// 37
				4.0, 7.0, 45.0, 1, 1, -1.0f, 0.0f, 0.0f,// 38
				4.0, 7.0, 44.5, 0, 1, -1.0f, 0.0f, 0.0f,// 39
				// upper
				4.5, 7.0, 45.0, 0, 0, 0.0f, 1.0f, 0.0f,  // 40
				4.0, 7.0, 45.0, 1, 0, 0.0f, 1.0f, 0.0f, // 41
				4.0, 7.0, 44.5, 1, 1, 0.0f, 1.0f, 0.0f, // 41
				4.5, 7.0, 44.5, 0, 1, 0.0f, 1.0f, 0.0f,  // 42
				// bottom
				4.0, 2.5, 44.5, 0, 0, 0.0f, -1.0f, 0.0f,// 44
				4.5, 2.5, 44.5, 1, 0, 0.0f, -1.0f, 0.0f, // 45
				4.5, 2.5, 45.0, 1, 1, 0.0f, -1.0f, 0.0f, // 46
				4.0, 2.5, 45.0, 0, 1, 0.0f, -1.0f, 0.0f,// 47

	};

	unsigned int indices[] = {
		//lampu1
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom
		//lampu1kanan
		24,  25,  26,  24,  26,  27,   // front
		28,  29,  30,  28,  30,  31,   // right
		32,  33,  34, 32,  34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46,   // bottom

		//lampu2
		48,  49,  50,  48,  50,  51,   // front
		52,  53,  54,  52,  54,  55,   // right
		56,  57,  58, 56,  58, 59,  // back
		60, 62, 61, 60, 63, 62,  // left
		64, 66, 65, 64, 67, 66,  // upper
		68, 70, 69, 68, 71, 70,   // bottom
		//lampu2kanan
		72,  73,  74,  72,  74,  75,   // front
		76,  77,  78,  76,  78,  79,   // right
		80,  81,  82, 80,  82, 83,  // back
		84, 86, 85, 84, 87, 86,  // left
		88, 90, 89, 88, 91, 90,  // upper
		92, 94, 93, 92, 95, 94,   // bottom

		//lampu3
		96,  97,  98,  96,  98,  99,   // front
		100,  101,  102,  100,  102,  103,   // right
		104,  105,  106, 104,  106, 107,  // back
		108, 110, 109, 108, 111, 110,  // left
		112, 114, 113, 112, 115, 114,  // upper
		116, 118, 117, 116, 119, 118,   // bottom
		//lampu3kanan
		120,  121,  122,  120,  122,  123,   // front
		124,  125,  126,  124,  126,  127,   // right
		128,  129,  130, 128,  130, 131,  // back
		132, 134, 133, 132, 135, 134,  // left
		136, 138, 137, 136, 139, 138,  // upper
		140, 142, 141, 140, 143, 142,   // bottom

		//lampu4
		144,  145,  146,  144,  146,  147,   // front
		148,  149,  150,  148,  150,  151,   // right
		152,  153,  154, 152,  154, 155,  // back
		156, 158, 157, 156, 159, 158,  // left
		160, 162, 161, 160, 163, 162,  // upper
		164, 166, 165, 164, 167, 166,   // bottom
		//lampu4kanan
		168,  169,  170,  168,  170,  171,   // front
		172,  173,  174,  172,  174,  175,   // right
		176,  177,  178, 176,  178, 179,  // back
		180, 182, 181, 180, 183, 182,  // left
		184, 186, 185, 184, 187, 186,  // upper
		188, 190, 189, 188, 191, 190,   // bottom

		//lampu5
		192,  193,  194,  192,  194,  195,   // front
		196,  197,  198,  196,  198,  199,   // right
		200,  201,  202, 200,  202, 203,  // back
		204, 206, 205, 204, 207, 206,  // left
		208, 210, 209, 208, 211, 210,  // upper
		212, 214, 213, 212, 215, 214,   // bottom
		//lampu5kanan
		216,  217,  218,  216,  218,  219,   // front
		220,  221,  222,  220,  222,  223,   // right
		224,  225,  226, 224,  226, 227,  // back
		228, 230, 229, 228, 231, 230,  // left
		232, 234, 233, 232, 235, 234,  // upper
		236, 238, 237, 236, 239, 238,   // bottom

		//lampu6
		240,  241,  242,  240,  242,  243,   // front
		244,  245,  246,  244,  246,  247,   // right
		248,  249,  250, 248,  250, 251,  // back
		252, 254, 253, 252, 255, 254,  // left
		256, 258, 257, 256, 259, 258,  // upper
		260, 262, 261, 260, 263, 262,   // bottom
		//lampu6kanan
		264,  265,  266,  264,  266,  267,   // front
		268,  269,  270,  268,  270,  271,   // right
		272,  273,  274,  272,  274, 275,  // back
		276, 278, 277, 276, 279, 278,  // left
		280, 282, 281, 280, 283, 282,  // upper
		284, 286, 285, 284, 287, 286,   // bottom

		//lampu7
		288,  289,  290,  288,  290,  291,   // front
		292,  293,  294,  292,  294,  295,   // right
		296,  297,  298,  296,  298, 299,  // back
		300, 302, 301, 300, 303, 302,  // left
		304, 306, 305, 304, 307, 306,  // upper
		308, 310, 309, 308, 311, 310,   // bottom
		//lampu7kanan
		312,  313,  314,  312,  314,  315,   // front
		316,  317,  318,  316,  318,  319,   // right
		320,  321,  322,  320,  322,  323,  // back
		324, 326, 325, 324, 327, 326,  // left
		328, 330, 329, 328, 331, 330,  // upper
		332, 334, 333, 332, 335, 334,   // bottom
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCube(GLuint shader)
{
	UseShader(shader);
	glBindVertexArray(VAO11);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 504, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildDepthMap() {
	// configure depth map FBO
	// -----------------------
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Demo::BuildShaders()
{
	// build and compile our shader program
	// ------------------------------------
	shadowmapShader = BuildShader("shadowMapping.vert", "shadowMapping.frag", nullptr);
	depthmapShader = BuildShader("depthMap.vert", "depthMap.frag", nullptr);
}

void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::FlyCamera(float speed)
{
	float x = viewCamX - posCamX;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamY = posCamY + x * speed;
	viewCamY = viewCamY + x * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Camera: Free Camera Implementation", 800, 600, false, false);
}
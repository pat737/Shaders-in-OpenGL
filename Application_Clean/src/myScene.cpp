#pragma once
#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\shaders\\1.glsl", "..\\shaders\\2.glsl");
	makeVAO();

}
void MyScene::makeVAO()
//
{

	glCreateBuffers(1, &VBO); // creating vertex buffer called VBO

	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT); // sending data to VBO, size date and vertex data(xyz positions)

	glCreateBuffers(1, &EBO); // creating bufffer called EBO 

	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT); // we putting indicies into EBO

	glCreateVertexArrays(1, &VAO); // creating VAO, "stores" VBO & EBO

	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 3); // "STRIDE" if we want RGB we need 6 or xyz

	glVertexArrayElementBuffer(VAO, EBO); // we adding EBO to VAO

	glEnableVertexArrayAttrib(VAO, 0); // we saying thay attributes are at posiotion 0

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0); // adddin information about attributes and its position

	glVertexArrayAttribBinding(VAO, 0, 0);

}

void MyScene::render()

{
	m_model = glm::mat4(1.0f);
	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();

	m_myShader->use();
	m_myShader->setMat4("View", m_view);
	m_myShader->setMat4("Projection", m_projection);
	m_myShader->setMat4("Model", m_model);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertexData.size(), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0 ,3);
	m_model = glm::translate(m_model, glm::vec3(5.0, 0.0, 0.0)); // HERE is something to do with WSAD and moving cube
	m_model = glm::rotate(m_model, (float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	m_myShader->setMat4("Model", m_model);
	glDrawElements(GL_TRIANGLES, vertexData.size(), GL_UNSIGNED_INT, 0);

}
/*
* HERE SOMETHING TO DO WITH WSAD moving cube
* 
if (m_handler->keyHasBeenPressed()) {
	if (m_handler->isKeyPressed(GLFW_KEY_W)) {
		m_position += m_front * vel;
	}
	if (m_handler->isKeyPressed(GLFW_KEY_S)) {
		m_position -= m_front * vel;
	}
	if (m_handler->isKeyPressed(GLFW_KEY_A)) {
		m_position -= m_right * vel;
	}
	if (m_handler->isKeyPressed(GLFW_KEY_D)) {
		m_position += m_right * vel;
	}
}

*/

/*
{
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * 36, vertexData, GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 6);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);

}
void MyScene::render()
{	
	m_myShader->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
*/
void MyScene::update(float dt) {
	m_camera->update(dt);
	render();
}


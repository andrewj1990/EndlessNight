#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>


class Window {
public:
	Window(int width, int height, char* title);
	~Window();

	bool shouldClose();
	void update();
	GLFWwindow* getWindow() { return m_Window; }
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void getMousePos(double& x, double& y);

	inline const int& getWidth() const { return m_Width; }
	inline const int& getHeight() const { return m_Height; }

private:
	bool init();

private:
	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
	const char* m_Title;
};
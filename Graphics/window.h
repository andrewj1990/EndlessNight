#pragma once

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

constexpr int MAX_KEYS = 1024;
constexpr int MAX_BUTTONS = 32;

class Window {
public:
	Window(int width, int height, char* title);
	~Window();

	bool shouldClose();
	void update();
	GLFWwindow* getWindow() { return m_Window; }
	void getMousePos(double& x, double& y);

	inline const int& getWidth() const { return m_Width; }
	inline const int& getHeight() const { return m_Height; }

	bool isKeyPressed(unsigned int keycode) const;
	bool isKeyTyped(unsigned int keycode) const;
	bool isMouseButtonPressed(unsigned int button) const;
	bool isMouseButtonClicked(unsigned int button) const;

private:
	bool init();
	friend void window_resize(GLFWwindow* window, int width, int height);
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

private:
	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
	const char* m_Title;

	bool m_Keys[MAX_KEYS];
	bool m_KeyTyped[MAX_KEYS];
	bool m_KeyState[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	bool m_MouseClicked[MAX_BUTTONS];
	bool m_MouseState[MAX_BUTTONS];
	double m_X;
	double m_Y;
};
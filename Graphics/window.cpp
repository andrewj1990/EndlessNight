#include "window.h"

Window::Window(int width, int height, char* title)
	: m_Width(width), m_Height(height), m_Title(title)
{
	if (!init())
	{
		std::cout << "failed ot initialize window\n";
	}
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_Window) == 1;
}

void Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "here\n";
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		std::cout << "w is pressed\n";
	}
}

bool Window::init()
{
	if (!glfwInit()) {
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	// vsync
	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize glew\n";
		return false;
	}

	std::cout << "OpenGL version : " << glGetString(GL_VERSION);

	return true;
}

void Window::getMousePos(double& x, double& y)
{
	glfwGetCursorPos(m_Window, &x, &y);
	y = m_Height - y;
	//*x = *x * 16 / 1280;
	//*y = 9 - (*y * 9 / 720);
}
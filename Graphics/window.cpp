#include "window.h"

Window::Window(int width, int height, char* title)
	: m_Width(width), m_Height(height), m_Title(title)
{
	if (!init())
	{
		std::cout << "failed ot initialize window\n";
	}

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		m_Keys[i] = m_KeyTyped[i] = m_KeyState[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		m_MouseButtons[i] = m_MouseClicked[i] = m_MouseState[i] = false;
	}
}

Window::~Window()
{	FreeImage_Initialise();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_Window) == 1;
}

void Window::update()
{
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
	}

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];
	}

	memcpy(m_KeyState, m_Keys, MAX_KEYS);
	memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error : " << error << "\n";
	}

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}


bool Window::init()
{
	FreeImage_Initialise();

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
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
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

bool Window::isKeyPressed(unsigned int keycode) const
{
	if (keycode >= MAX_KEYS) return false;
	return m_Keys[keycode];
}

bool Window::isKeyTyped(unsigned int keycode) const
{
	if (keycode >= MAX_KEYS) return false;
	return m_KeyTyped[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const
{
	if (button >= MAX_BUTTONS) return false;
	return m_MouseButtons[button];
}

bool Window::isMouseButtonClicked(unsigned int button) const
{
	if (button >= MAX_BUTTONS) return false;
	return m_MouseClicked[button];
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = action != GLFW_RELEASE;
}

void window_resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Width = width;
	win->m_Height = height;
}

void Window::getMousePos(double& x, double& y)
{
	glfwGetCursorPos(m_Window, &x, &y);
	y = m_Height - y;
}
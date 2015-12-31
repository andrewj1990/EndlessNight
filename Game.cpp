#include <iostream>
#include "Graphics\window.h"
#include "Utils\shader.h"
#include "Graphics\batchrenderer.h"

#include "Graphics\renderable.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/matrix.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Utils\timer.h"
#include "Graphics\Layers\layer.h"

int main(int argc, char** argv)
{
	Window window(1280, 720, "First Night");

	Shader shader("Shaders/vertShader.vert", "Shaders/fragShader.frag");
	Shader shader2("Shaders/vertShader.vert", "Shaders/fragShader.frag");

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);	
	Layer layer(&shader, ortho);
	Layer layer2(&shader2, ortho);

	glm::vec3 position(0, 0, 0);
	glm::vec2 size(5, 5);
	glm::vec4 colour(1, 0, 1, 1);

	srand(time(NULL));

	Timer time;
	float timer = 0;
	int frames = 0;
	int counter = 0;
	for (float i = 0; i < 16; i += 0.5f)
	{
		for (float j = 0; j < 9; j += 0.5f)
		{
			++counter;
			layer.add(new Renderable(glm::vec3(i, j, 0), glm::vec2(0.4f, 0.4f), glm::vec4(0, 0, rand() % 1000 / 1000.0f, 1)));
		}
	}

	layer2.add(new Renderable(glm::vec3(4, 4, 0), glm::vec2(5, 5), glm::vec4(1, 0, 1, 0.5)));

	while (!window.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window.getWindow(), GLFW_KEY_W)) {
			std::cout << "w is pressed\n";
		}

		double x;
		double y;
		window.getMousePos(&x, &y);

//		std::cout << "x : " << x << ", y : " << y << "\n";
		shader.setUniform2f("light_pos", glm::vec2(x * 16 / 1280,  9 - (y * 9 / 720)));

		layer.render();
		layer2.render();

		window.update();

		++frames;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps , sprites : %d \n", frames, counter);
			frames = 0;
		}

	}

	return 0;
}
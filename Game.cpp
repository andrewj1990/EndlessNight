#include <iostream>
#include "Utils\timer.h"
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
#include "Graphics\window.h"
#include "Graphics\Layers\layer.h"

#include "Level\level.h"
#include "Graphics\texture.h"

#include "Graphics\light.h"

int main(int argc, char** argv)
{

	Window window(1280, 720, "Don't be square!");
	Level level(window);

	Shader shader("Shaders/vertShader.vert", "Shaders/fragShader.frag");
	glm::mat4 ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	Layer shadowLayer(shader, ortho);

	//shadowLayer.add(new Sprite(glm::vec3(0, 0, 0), glm::vec2(1000, 1000), glm::vec4(0, 0, 0, 1)));
	//shadowLayer.add(new Sprite(glm::vec3(200, 200, 0), glm::vec2(250, 250), glm::vec4(0, 0, 0, 1)));

	//level.getLayer().add(new Sprite(glm::vec3(399, 399, 0), glm::vec2(100, 100), glm::vec4(1, 1, 1, 1)));

	Sprite* block = new Sprite(glm::vec3(200, 200, 0), glm::vec2(100, 100), glm::vec4(0, 1, 1, 1));
	//Renderable* block2 = new Renderable(100, 0, 100, 300, 400, 600, 200, 0);
	std::vector<Renderable*> renderables;
	//renderables.push_back(block);
	//renderables.push_back(block2);

	auto rends = level.getPlatform();

	//Light light(shadowLayer, rends, 0, 0, glm::vec4(1,1,0,1));

	Timer time;
	Timer time2;
	float timer = 0;
	int frames = 0;
	int updates = 0;
	float updateTimer = 0.0f;
	float tick = 1.0f / 60.0f;
	//glClearColor(0, 0.0f / 255.0f, 102.0f / 255.0f, 1);
	glClearColor(0.1f, 0.2f, 0.3f, 1);
	double mouseX = 0;
	double mouseY = 0;
	while (!window.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		window.getMousePos(mouseX, mouseY);
		// place block
		if (window.isKeyTyped(GLFW_KEY_B))
		{
			std::cout << "here";
			level.addBlock(mouseX, mouseY);
		}

		// place light
		if (window.isKeyTyped(GLFW_KEY_L))
		{
			Light light(shadowLayer, level.getLayer().getRenderables());
		}

		while (time.elapsed() - updateTimer > tick && updates < 60)
		{
			level.update();
			++updates;
			updateTimer += tick;
		}

		glEnable(GL_STENCIL_TEST);
		//glColorMask(false, false, false, false);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		shadowLayer.render(renderables);

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, 0, 1);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE, GL_ONE);
		//glColorMask(true, true, true, true);
		
		//light.update(mouseX, mouseY);
		//shadowLayer.render();

		glDisable(GL_BLEND);
		glDisable(GL_STENCIL_TEST);
		level.render();

		window.update();

		++frames;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps , %d ups\n", frames, updates);
			frames = 0;
			updates = 0;
		}

	}

	return 0;
}



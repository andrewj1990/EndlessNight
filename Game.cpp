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

int main(int argc, char** argv)
{
	//FT_Library  library;
	//if (FT_Init_FreeType(&library))
	//{
	//	std::cout << "failed to init";
	//	return 0;
	//}

	Window window(1280, 720, "Don't be square!");
	Level level(window);

	//glActiveTexture(GL_TEXTURE0);
	//Texture texture("test.png");
	//texture.bind();

	Timer time;
	Timer time2;
	float timer = 0;
	int frames = 0;
	int updates = 0;
	float updateTimer = 0.0f;
	float tick = 1.0f / 60.0f;
	while (!window.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);

		while (time.elapsed() - updateTimer > tick)
		{
			level.update();
			++updates;
			updateTimer += tick;
		}

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



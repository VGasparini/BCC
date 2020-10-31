#include "commons.hpp"
#include "global_vars.hpp"
#include "rt_headers.hpp"
#include "scene.hpp"
#include "driver.hpp"

void doRender()
{
	while (!die){
		mut.lock();
		if (rerender){
			rmut.lock();
			render(rW, rH, pixels);
			rerender = false;
			rmut.unlock();
		}
		mut.unlock();
	}
}

/* MAIN PROGRAM */
int main(int argc, char **argv){
	MAXTRACE = 3;

	if (argc > 1) { sscanf(argv[1], "%u", &W); sscanf(argv[2], "%u", &H); }
	if (argc > 3) { sscanf(argv[3], "%u", &MAXTRACE); }
	if (argc > 4) { toFile = true; sscanf(argv[4], "%s", outfile); }

	rW = W; rH = H;
	sf::ContextSettings ContextSettings(unsigned int depth = 10,
										 unsigned int stencil = 0,
										 unsigned int antialiasing = 100,
										 unsigned int major = 2,
										 unsigned int minor = 0);
	sf::RenderWindow window(sf::VideoMode(W, H), "MultiThreaded SFML RayTracing - Vinicius e Menderson", sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	window.clear();
	window.display();
	window.getSettings();

	image.create(W, H, sf::Color::Black);
	if (!texture.create(W, H))
		printf("Erro ao criar textura\n");

	pixels = new sf::Uint8[rW * rH * 4];

	texture.update(pixels);
	sprite.setTexture(texture);

	InitArealightVectors();
	InitDefaultScene();

	std::stringstream command;
	std::string line, op;

	float f_x, f_y, f_z, f_a, f_b;
	int i_a, i_b, i_iw, i_ih;
	bool redraw = true, sketch = false;

	int frametime;
	sf::Clock clock;
	sf::Event event;
	std::thread renderThread(doRender);

	std::thread consoleThread(consoleReader, &window);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}
	
		if (toFile)
		{
			image.create(rW, rH, pixels);
			image.saveToFile(outfile);
			toFile = false;
		}
		else
		{
			dmut.lock();
			window.clear();
			//window.display();
			if (resize) window.setSize(sf::Vector2u(W, H));
			// Atualizar textura
			texture.update(pixels);
			sprite.setTexture(texture, true);
			// Apresentar resultado
			window.draw(sprite);
			window.display();
			dmut.unlock();
		}

		if (die)
			break;
	}
	window.close();
	renderThread.join();
	consoleThread.join();

	return 0;
}

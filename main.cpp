#include "Visualizer.hpp"

int main()
{
	Visualizer app;
	app.showFPS(true);
	app.setMaxFPS(120);
	app.run();

	return 0;
}

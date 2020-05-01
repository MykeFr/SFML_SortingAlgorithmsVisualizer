#include <cmath>

#include "Visualizer.hpp"
#include "SortingAlgorithms.hpp"

void sortIt(Sorter func, ArrayController<int>* vec, std::atomic<bool>* done)
{
	*done = false;
	vec->sort(func);
	*done = true;
}

Visualizer::Visualizer(std::string t) : vec(SIZE), done(false), algorithmsIndex(0)
{
	title = t;
	setupWindow(1650.f * SW, 900.f * SH, 10.f, 10.f, sf::Style::Default);
	algorithms.push_back(std::make_pair(&pancakeSort, "PancakeSort"));
	algorithms.push_back(std::make_pair(&bitonicSort, "BitonicSort"));
	algorithms.push_back(std::make_pair(&insertionSort, "InsertionSort"));
	algorithms.push_back(std::make_pair(&insertionSortRec, "Recursive InsertionSort"));
	algorithms.push_back(std::make_pair(&insertionSortBin, "Binary InsertionSort"));
	algorithms.push_back(std::make_pair(&bubbleSort, "BubbleSort"));
	algorithms.push_back(std::make_pair(&bubbleSortRec, "Recursive BubbleSort"));
	algorithms.push_back(std::make_pair(&cocktailSort, "CocktailSort"));
	algorithms.push_back(std::make_pair(&combSort, "CombSort"));
	algorithms.push_back(std::make_pair(&cycleSort, "CycleSort"));
	algorithms.push_back(std::make_pair(&shellSort, "ShellSort"));
	algorithms.push_back(std::make_pair(&heapSort, "HeapSort"));
	algorithms.push_back(std::make_pair(&selectionSort, "SelectionSort"));
	algorithms.push_back(std::make_pair(&quickSort, "QuickSort"));
	algorithms.push_back(std::make_pair(&quickSortIt, "Iterative QuickSort"));
	algorithms.push_back(std::make_pair(&mergeSort, "MergeSort"));
	algorithms.push_back(std::make_pair(&mergeSortIt, "Iterative MergeSort"));

	vec.randomize();
}

// called once before the loop starts
bool Visualizer::onCreate()
{
	sortThread = std::thread(sortIt, algorithms[algorithmsIndex].first, &vec, &done);
	txt.create(SCREENWIDTH, SCREENHEIGHT);
	return true;
}

// first thing to be called every frame
bool Visualizer::onHandleEvent(GF::Event& event)
{
	static GF::ToggleKey SPACE(sf::Keyboard::Space);

	if (SPACE.isKeyPressedOnce(event))
		vec.setSleep(0.);

	return true;
}

// called every frame before draw
bool Visualizer::onUpdate(const float fElapsedTime, const float fTotalTime)
{
	if (done && algorithmsIndex + 1 < algorithms.size()) {
		sortThread.join();
		vec.randomize();
		totalTime = 0.;
		sleepTime = 0.;
		sortThread = std::thread(sortIt, algorithms[++algorithmsIndex].first, &vec, &done);
	}

	totalTime += fElapsedTime;
	sleepTime = vec.getSleepTime();

	if (counter++ % FRAME_RATIO == 1) {
		img.setTexture(txt);
		float scale = pow(0.99f, fElapsedTime * getMaxFPS());
		float scale_a = pow(0.96f,  fElapsedTime * getMaxFPS());
		img.setScale(scale, scale);
		img.setColor(sf::Color(255, 255, 255, 255 * scale_a));
		// img.setPosition(sf::Vector2f(-5., -2.));
		img.setPosition(sf::Vector2f(-1. * SCREENWIDTH / 1260., -0.6 * SCREENHEIGHT / 720.));
	}

	return true;
}

// last thing to be called every frame
bool Visualizer::onDraw()
{
	window.draw(img);

	float rightPosition = SCREENWIDTH * 9.8 / 10.;
	float topPosition = SCREENHEIGHT * 1.5 / 5.;
	float bottomPosition = SCREENHEIGHT * 9.8 / 10.;
	float leftPosition = SCREENWIDTH * 3. / 10.;

	float step = (rightPosition - leftPosition) / vec.size();
	float maxHeight = bottomPosition - topPosition;

	float x = leftPosition;
	float height = maxHeight / vec.size();

	sf::Color color = WHITE;

	for (unsigned i = 0; i < vec.size(); ++i) {

		if (!vec.wasAssigned(i))
			// window.draw(GF::Line(sf::Vector2f(x, bottomPosition), sf::Vector2f(x, bottomPosition - height * vec[i]), color, color));
			window.draw(GF::Rectangle(sf::Vector2f(step, height * vec[i]),
			                          sf::Vector2f(x, bottomPosition - height * vec[i] / 2.),
			                          GF::CENTERED, color));

		x += step;
	}

	if (counter % FRAME_RATIO == 1)
		txt.update(window);

	x = leftPosition;

	for (unsigned i = 0; i < vec.size(); ++i) {

		if (vec.wasAssigned(i))
			color = RED;
		else
			color = NAVY;

		// window.draw(GF::Line(sf::Vector2f(x, bottomPosition), sf::Vector2f(x, bottomPosition - height * vec[i]), color, color));
		window.draw(GF::Rectangle(sf::Vector2f(color == RED ? step * 3. : step, height * vec[i]),
		                          sf::Vector2f(x, bottomPosition - height * vec[i] / 2.),
		                          GF::CENTERED, color, BLACK, 0.5));

		x += step;
	}

	window.draw(GF::Text(algorithms[algorithmsIndex].second + " ( " + std::to_string(
	                         algorithmsIndex + 1) + "/" + std::to_string(algorithms.size()) + " )",
	                     TOPLEFT_F + sf::Vector2f(1, 20 * SH * SH),
	                     (int)(SH * 15),
	                     WHITE,
	                     GF::TOPLEFT));
	window.draw(GF::Text("Comparisons: " + std::to_string(vec.getComparisonsCounter()),
	                     TOPLEFT_F + sf::Vector2f(1, 40 * SH),
	                     (int)(SH * 15),
	                     WHITE,
	                     GF::TOPLEFT));
	window.draw(GF::Text("Assignments: " + std::to_string(vec.getAssignmentsCounter()),
	                     TOPLEFT_F + sf::Vector2f(1, 60 * SH),
	                     (int)(SH * 15),
	                     WHITE,
	                     GF::TOPLEFT));

	window.draw(GF::Text("Total time (secs): " + std::to_string(totalTime),
	                     TOPLEFT_F + sf::Vector2f(1, 80 * SH),
	                     (int)(SH * 15),
	                     WHITE,
	                     GF::TOPLEFT));
	window.draw(GF::Text("Sleep time (secs): " + std::to_string(sleepTime / 1000000),
	                     TOPLEFT_F + sf::Vector2f(1, 100 * SH),
	                     (int)(SH * 15),
	                     WHITE,
	                     GF::TOPLEFT));
	window.draw(GF::Text("Real time (secs): " + std::to_string((totalTime - sleepTime / 1000000)),
	                     TOPLEFT_F + sf::Vector2f(1, 120 * SH),
	                     (int)(SH * 15),
	                     WHITE,
	                     GF::TOPLEFT));

	return true;
}

// called before exiting the app
void Visualizer::onDestroy()
{
	if(!done) exit(1);
}

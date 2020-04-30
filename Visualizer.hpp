#pragma once

#include <iostream>
#include <atomic>

#include "GraphicsFramework/Tools.h"
#include "GraphicsFramework/main.h"
#include "GraphicsFramework/sfml.h"

#include "ArrayController.hpp"

#define SIZE 512
#define FRAME_RATIO 12

class Visualizer : public GF::App
{
public:
    Visualizer(std::string t = "Window");

    // called once before the main loop starts
    bool onCreate() override;

    // first thing to be called every frame
    bool onHandleEvent(GF::Event& event) override;

    // called every frame before draw
    virtual bool onUpdate(const float fElapsedTime, const float fTotalTime) override;

    // last thing to be called every frame
    bool onDraw() override;

    // called once before exiting the app
    void onDestroy() override;

    // called when switching between states. 'other' is the name of the state that switched to this one
    void onSwitch(std::string other) override {};

private:
    ArrayController<int> vec;

    std::thread sortThread;
    std::atomic<bool> done;

    std::vector<std::pair<Sorter, std::string>> algorithms;
    unsigned algorithmsIndex;

    float totalTime;
    float sleepTime;

    sf::Sprite img;
    sf::Texture txt;
    unsigned counter = 0;
};

#ifndef APP_H
#define APP_H

#include "b_app.h"
#include "cave_Auto.h"

class InputManager {
public:
    static int askInt(const char* message, int minVal, int maxVal);
};

class CaveApp : public BaseApp {
private:
    int simWidth;
    int simHeight;
    int birthRule;
    int deathRule;
    int startChance;
    float cellSize;
    sf::RectangleShape btnNext;
    CaveAutomata caveSystem;

public:
    CaveApp();
    virtual void setup() override;
    virtual void handleInput(const sf::Event& event) override;
    virtual void update() override;
    virtual void render() override;
};

#endif

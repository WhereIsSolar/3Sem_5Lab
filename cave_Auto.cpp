#include "cave_Auto.h"
#include <cstdlib>
#include <ctime>

CaveAutomata::CaveAutomata() : widthC(0), heightC(0) {}

int CaveAutomata::getCellSafe(int x, int y) const {
    if (x < 0 || y < 0 || x >= widthC || y >= heightC) {
        return 1;
    }
    return gridMap[y * widthC + x];
}

int CaveAutomata::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) { 
        for (int dx = -1; dx <= 1; ++dx) { 
            if (dx == 0 && dy == 0) 
                continue;
            if (getCellSafe(x + dx, y + dy) == 1) {
                count++;
            }
        }
    }
    return count;
}

void CaveAutomata::initialize(int w, int h) {
    widthC = w;
    heightC = h;
    gridMap.resize(w * h); 
    for (auto& c : gridMap) {
        c = 0;
    }
}

void CaveAutomata::randomize(int chancePercent) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (auto& cell : gridMap) {
        int r = std::rand() % 100;
        cell = (r < chancePercent) ? 1 : 0;
    }
}

void CaveAutomata::updateSim(int birthLimit, int deathLimit) {
    PixelBuffer<int> nextState;
    nextState.resize(widthC * heightC);

    for (int y = 0; y < heightC; ++y) {
        for (int x = 0; x < widthC; ++x) {
            int neighbors = countNeighbors(x, y); 
            int currentIdx = y * widthC + x;
            int currentState = gridMap[currentIdx];

            if (currentState == 1) {
                // Стена
                nextState[currentIdx] = (neighbors < deathLimit) ? 0 : 1;
            } else {
                // Пустая клетка
                nextState[currentIdx] = (neighbors > birthLimit) ? 1 : 0;
            }
        }
    }
    
    // Копируем новое состояние
    for (int i = 0; i < gridMap.getSize(); ++i) {
        gridMap[i] = nextState[i]; 
    }
}

void CaveAutomata::drawWindow(sf::RenderWindow& window, float cellSize) const {
    sf::RectangleShape shape(sf::Vector2f(cellSize - 1, cellSize - 1)); 
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Black);  
    shape.setOutlineThickness(1.0f);

    int index = 0;
    for (const auto& cellValue : gridMap) {
        if (cellValue == 1) { 
            int posX = index % widthC; 
            int posY = index / widthC;
            shape.setPosition({posX * cellSize, posY * cellSize});  // SFML 3 style
            window.draw(shape);
        }
        index++;
    }
}

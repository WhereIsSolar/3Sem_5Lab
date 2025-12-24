#include "app.h"
#include <iostream>

using namespace std;

CaveApp::CaveApp() : simWidth(0), simHeight(0), birthRule(0), deathRule(0), 
                     startChance(0), cellSize(20.0f) {
    winTitle = "Генератор Пещер";

    btnNext.setSize(sf::Vector2f(140.0f, 40.0f));
    btnNext.setFillColor(sf::Color::Black);        
    btnNext.setOutlineColor(sf::Color::White);
    btnNext.setOutlineThickness(6.0f);
}

int InputManager::askInt(const char* message, int minVal, int maxVal) {
    int inputVal;
    while (true) {
        cout << message << " (" << minVal << " - " << maxVal << "): ";
        if (cin >> inputVal && inputVal >= minVal && inputVal <= maxVal) {
            return inputVal;
        } else {
            cout << "Ошибка: Введите число в заданном диапазоне.\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

void CaveApp::setup() {
    cout << "--- Настройка симуляции ---" << endl;
    simWidth = InputManager::askInt("Ширина поля", 10, 500); 
    simHeight = InputManager::askInt("Высота поля", 10, 500);
    startChance = InputManager::askInt("Шанс стен %", 0, 100);
    deathRule = InputManager::askInt("Предел смерти", 0, 8);
    birthRule = InputManager::askInt("Предел рождения", 0, 8);

    caveSystem.initialize(simWidth, simHeight);
    caveSystem.randomize(startChance); 

    // ОТЛАДКА
    cout << "\n=== РАСЧЁТЫ ===" << endl;
    cout << "Размер пещеры в клетках: " << simWidth << "x" << simHeight << endl;
    cout << "Размер клетки: " << cellSize << endl;

    // 1. Размер пещеры в пикселях
    float caveWidthPx = simWidth * cellSize;
    float caveHeightPx = simHeight * cellSize;
    
    cout << "Пещера в пикселях: " << caveWidthPx << "x" << caveHeightPx << endl;

    // 2. Если пещера слишком большая - уменьшаем cellSize
    const float MAX_CAVE_SIZE = 800.0f;  // Макс размер пещеры
    
    if (caveWidthPx > MAX_CAVE_SIZE) {
        cellSize = MAX_CAVE_SIZE / simWidth;
        caveWidthPx = simWidth * cellSize;
        caveHeightPx = simHeight * cellSize;
        cout << "cellSize уменьшен до: " << cellSize << endl;
    }
    
    if (caveHeightPx > MAX_CAVE_SIZE) {
        cellSize = MAX_CAVE_SIZE / simHeight;
        caveWidthPx = simWidth * cellSize;
        caveHeightPx = simHeight * cellSize;
        cout << "cellSize уменьшен до: " << cellSize << endl;
    }

    // 3. Мин размеры
    if (caveWidthPx < 300) caveWidthPx = 300;
    if (caveHeightPx < 300) caveHeightPx = 300;
    
    winWidth = static_cast<int>(caveWidthPx);
    winHeight = static_cast<int>(caveHeightPx) + 80;  // +80 для кнопки
    
    cout << "Размер окна: " << winWidth << "x" << winHeight << endl;

    
     float btnX = (winWidth - 160) / 2.0f;
     float btnY = 50;
    

    cout <<  btnX << "X button" << endl;
    cout <<  btnY << "Y button" << winHeight << "heih" << endl;
    
    btnNext.setPosition({btnX, btnY});
    
    // 6. Проверка
    // if (btnY + 40 > winHeight) {
    //     cout << "ОШИБКА: Кнопка выходит за пределы окна!" << endl;
    //     cout << "Увеличиваю высоту окна..." << endl;
    //     winHeight = static_cast<int>(btnY + 50);  // Добавляем запас
    //     cout << "Новый размер окна: " << winWidth << "x" << winHeight << endl;
    // }
}


void CaveApp::handleInput(const sf::Event& appEvent) {
    if (auto mouseEvent = appEvent.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mPos((float)mouseEvent->position.x, 
                              (float)mouseEvent->position.y);
            
            cout << "\nКлик мыши: (" << mPos.x << ", " << mPos.y << ")" << endl;
            
            sf::Vector2f btnPos = btnNext.getPosition();
            sf::Vector2f btnSize = btnNext.getSize();
            
            cout << "Кнопка: x[" << btnPos.x << "-" << btnPos.x + btnSize.x 
                 << "], y[" << btnPos.y << "-" << btnPos.y + btnSize.y << "]" << endl;
            
            if (mPos.x >= btnPos.x && mPos.x <= btnPos.x + btnSize.x &&
                mPos.y >= btnPos.y && mPos.y <= btnPos.y + btnSize.y) {
                cout << ">>> КЛИК ПО КНОПКЕ! <<<" << endl;
                caveSystem.updateSim(birthRule, deathRule);
                cout << "Симуляция обновлена" << endl;
            } else {
                cout << "Клик мимо кнопки" << endl;
            }
        }
    }
}


void CaveApp::render() {

    caveSystem.drawWindow(window, cellSize);
    window.draw(btnNext);
}

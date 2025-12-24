#ifndef BASE_APP_H
#define BASE_APP_H

#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

class BaseApp {
protected:
    sf::RenderWindow window;
    int winWidth;
    int winHeight;
    const char* winTitle;

public:
    BaseApp() : winWidth(800), winHeight(600), winTitle("Cave Generator") {}
    virtual ~BaseApp() = default;

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleInput(const sf::Event& event) = 0;

    void run() {
        // Создаем окно
        window.create(
            sf::VideoMode({
                static_cast<unsigned int>(winWidth),
                static_cast<unsigned int>(winHeight)
            }),
            winTitle
        );
        window.setFramerateLimit(60);
        
        // Отладочная информация
        std::cout << "Окно создано: " << winWidth << "x" << winHeight << std::endl;
        
        setup();

        while (window.isOpen()) {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                } else {
                    handleInput(*event);
                }
            }

            update();
            window.clear(sf::Color::White);  // Белый фон
            render();
            window.display();
        }
    }
};

#endif

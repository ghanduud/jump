#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  // Include for audio functionality
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>


float jumpFunction(float t, float duration, float scale) {
    float scaledT = t / duration;
    if (scaledT > 1.0f) {
        scaledT = 1.0f;
    }
    return (-4 * scaledT * scaledT + 4 * scaledT) * scale;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML Snake", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    sf::CircleShape circle(25.f);
    circle.setFillColor(sf::Color::Blue);
    circle.setOrigin(25.f, 25.f);
    float initialX = 400.f;
    float initialY = 350.f;
    circle.setPosition(initialX, initialY);


    bool isJumping = false;
    float jumpDuration = 3.0f;
    float timeElapsed = 0.0f;
    float jumpScale = 200;

    sf::Clock jumpClock;

    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 80.f);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isJumping) {
                isJumping = true;
                timeElapsed = 0.0f;
                jumpClock.restart();
            }
        }

        sf::Time elapsedTime = clock.restart();

        while (elapsedTime > timePerFrame) {
            if (isJumping) {
            timeElapsed += jumpClock.restart().asSeconds();

            float jumpHeight = jumpFunction(timeElapsed, jumpDuration, jumpScale);

            circle.setPosition(initialX, initialY - jumpHeight);

            if (timeElapsed >= jumpDuration) {
                isJumping = false;
                circle.setPosition(initialX, initialY);
            }
        }
        else {
            jumpClock.restart();
        }

            elapsedTime -= timePerFrame;
        }

        window.clear();

        window.draw(circle);

        window.display();
    }

    return 0;
}


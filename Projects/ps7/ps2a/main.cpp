// Copyright 2023 William Susi

#include <iostream>
#include "Sokoban.hpp"

// Call ./Sokoban level1.txt

int main(int argc, char** argv) {
    Sokoban game(argv[1]);
    // std::cout << game << std::endl;

    sf::RenderWindow window(sf::VideoMode(game.getWidth() * 64, game.getHeight() * 64), "Sokoban");

    sf::Clock clock;
    sf::Time time;
    time = clock.getElapsedTime();

    sf::Font font;
    font.loadFromFile("SpaceMono-Regular.ttf");
    sf::Text text("00:00", font);
    text.setCharacterSize(18);
    text.setPosition(5, 12);
    text.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        time = clock.getElapsedTime();
        int seconds = time.asSeconds();

        if (seconds / 60 < 10 && seconds % 60 < 10) {
            text.setString("0" + to_string(seconds/60) + ":0" + to_string(seconds%60));
        } else if (seconds / 60 < 10) {
            text.setString("0" + to_string(seconds/60) + ":" + to_string(seconds%60));
        } else if (seconds % 60 < 10) {
            text.setString(to_string(seconds/60) + ":0" + to_string(seconds%60));
        } else {
            text.setString(to_string(seconds/60) + ":" + to_string(seconds%60));
        }

        window.clear();
        window.draw(game);
        window.draw(text);
        window.display();
    }

    return 0;
}

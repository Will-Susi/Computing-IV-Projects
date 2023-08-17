// Copyright 2023 William Susi

#include <iostream>
#include "Sokoban.hpp"

// Call ./Sokoban level1.txt

int main(int argc, char** argv) {
    string level = argv[1];
    START: Sokoban game(level);
    // std::cout << game << std::endl;

    sf::RenderWindow window(sf::VideoMode(game.getWidth() * 64, game.getHeight() * 64), "Sokoban");

    // Set up clock
    sf::Clock clock;
    sf::Time time;
    time = clock.getElapsedTime();

    // Set up default font
    sf::Font font;
    font.loadFromFile("SpaceMono-Regular.ttf");

    // Set up intital timer display
    sf::Text timerText("00:00", font);
    timerText.setFillColor(sf::Color::Green);
    timerText.setCharacterSize(18);
    timerText.setPosition(5, 12);

    // Pre-load victory display text
    sf::Text victoryText("You Win!", font);
    victoryText.setFillColor(sf::Color::Green);
    int size = 12;
    victoryText.setCharacterSize((game.getWidth() < game.getHeight()) ?
    game.getWidth() * size : game.getHeight() * size);
    victoryText.setPosition(window.getView().getCenter().x - (victoryText.getLocalBounds().width/2),
    window.getView().getCenter().y - 64);

    // Set up victory sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("victory.ogg")) {
        return EXIT_FAILURE;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    bool soundPlayed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for different keyboard input events
            if (event.type == sf::Event::KeyPressed) {
                // Check for movement
                if (event.key.code == sf::Keyboard::W|| event.key.code == sf::Keyboard::Up) {
                    game.movePlayer(UP);
                } else if (event.key.code == sf::Keyboard::S||
                event.key.code == sf::Keyboard::Down) {
                    game.movePlayer(DOWN);
                } else if (event.key.code == sf::Keyboard::A ||
                event.key.code == sf::Keyboard::Left) {
                    game.movePlayer(LEFT);
                } else if (event.key.code == sf::Keyboard::D ||
                event.key.code == sf::Keyboard::Right) {
                    game.movePlayer(RIGHT);
                }

                // Check for restart
                if (event.key.code == sf::Keyboard::R) {
                    goto START;
                }

                // Check for previous or next levels
                int levelNum = stoi(level.substr(5, (level.size() - 9)));
                if (game.isWon() && event.key.code == sf::Keyboard::N) {
                    string tempLevel = "level" + to_string(levelNum + 1) + ".lvl";
                    std::fstream test;
                    test.open(tempLevel, std::fstream::in);
                    if (!test.good()) {
                        break;
                    }
                    level = tempLevel;
                    goto START;
                } else if (game.isWon() && event.key.code == sf::Keyboard::P) {
                    string tempLevel = "level" + to_string(levelNum - 1) + ".lvl";
                    std::fstream test;
                    test.open(tempLevel, std::fstream::in);
                    if (!test.good()) {
                        break;
                    }
                    level = tempLevel;
                    goto START;
                }
            }
        }

        // Update timer
        if (!game.isWon()) {
            time = clock.getElapsedTime();
        }

        // Set timer
        int seconds = time.asSeconds();
        if (seconds / 60 < 10 && seconds % 60 < 10) {
            timerText.setString("0" + to_string(seconds/60) + ":0" + to_string(seconds%60));
        } else if (seconds / 60 < 10) {
            timerText.setString("0" + to_string(seconds/60) + ":" + to_string(seconds%60));
        } else if (seconds % 60 < 10) {
            timerText.setString(to_string(seconds/60) + ":0" + to_string(seconds%60));
        } else {
            timerText.setString(to_string(seconds/60) + ":" + to_string(seconds%60));
        }

        // Display everything
        window.clear();
        window.draw(game);
        window.draw(timerText);
        if (game.isWon()) {
            window.draw(victoryText);
            if (!soundPlayed) {
                sound.play();
                soundPlayed = true;
            }
        }
        window.display();
    }

    return 0;
}

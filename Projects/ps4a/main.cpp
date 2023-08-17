// Copyright 2023 William Susi

#include <iostream>
#include "Checkers.hpp"

int main(int argc, char** argv) {
    Checkers game = Checkers();

    sf::RenderWindow window(sf::VideoMode(TILE_LENGTH * BOARD_SIZE + 2 * BORDER_WIDTH,
                                          TILE_LENGTH * BOARD_SIZE + 2 * BORDER_WIDTH), "Checkers");

    sf::Font font;
    font.loadFromFile("SpaceMono-Regular.ttf");

    sf::Text turnText("Turn: Black", font);
    turnText.setFillColor(sf::Color::Green);
    turnText.setCharacterSize(16);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Checks for player trying to select a piece
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    game.onPiece(sf::Vector2f(event.mouseButton.x, event.mouseButton.y),
                    game.isBlackTurn());
                }
            }
        }

        // Sets whose turn it is
        if (game.isBlackTurn() == true) {
            turnText.setString("Turn: Black");
        } else {
            turnText.setString("Turn: Red");
        }
        turnText.setPosition(window.getView().getCenter().x - (turnText.getLocalBounds().width/2),
                             BORDER_WIDTH/4);

        // Creates border
        sf::RectangleShape border(sf::Vector2f(TILE_LENGTH * BOARD_SIZE + 2 * BORDER_WIDTH,
                                               TILE_LENGTH * BOARD_SIZE + 2 * BORDER_WIDTH));
        border.setFillColor(sf::Color(65, 25, 0));

        // Display everything
        window.clear();
        window.draw(border);
        window.draw(game);
        window.draw(turnText);
        window.display();
    }

    return 0;
}

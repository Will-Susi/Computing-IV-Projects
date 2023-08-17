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
    turnText.setCharacterSize(BORDER_WIDTH/2);

    sf::Text victoryText("", font);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setCharacterSize(TILE_LENGTH);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Checks for player trying to select a piece
            if (event.type == sf::Event::MouseButtonPressed && !game.isWon()) {
                if (event.mouseButton.button == sf::Mouse::Left &&
                    event.mouseButton.x >= BORDER_WIDTH &&
                    event.mouseButton.x < TILE_LENGTH * BOARD_SIZE + BOARD_SIZE &&
                    event.mouseButton.y >= BORDER_WIDTH &&
                    event.mouseButton.y < TILE_LENGTH * BOARD_SIZE + BOARD_SIZE) {
                    game.makeMove(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    if (!game.clickPiece(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        game.clearHighlights();
                    }
                }
            }
        }

        // Displays the winner if someone has won
        if (game.isWon()) {
            if (game.isBlackTurn()) {
                victoryText.setString("Red Wins!");
            } else {
                victoryText.setString("Black Wins!");
            }
            victoryText.setPosition(window.getView().getCenter().x -
                                   (victoryText.getLocalBounds().width/2),
                                    window.getView().getCenter().y -
                                   (victoryText.getLocalBounds().height/2));
        }

        // Sets whose turn it is
        if (game.isBlackTurn()) {
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
        window.draw(victoryText);
        window.display();
    }

    return 0;
}

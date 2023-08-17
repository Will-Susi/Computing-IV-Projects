// Copyright 2023 William Susi

#include "Checkers.hpp"

Pawn::Pawn(sf::Sprite piece) {
    _piece = piece;
    _isKing = false;
}

sf::Sprite Pawn::getPiece() const {
    return _piece;
}

void Pawn::makeKing() {
    _isKing = true;
}

Checkers::Checkers() {
    sf::Image img;
    sf::Texture text;

    // Load textures
    if (!img.loadFromFile("piece_images/blackpawn.png")) {
        exit(-1);
    }
    text.loadFromImage(img);
    _textures.push_back(text);

    if (!img.loadFromFile("piece_images/blackking.png")) {
        exit(-1);
    }
    text.loadFromImage(img);
    _textures.push_back(text);

    if (!img.loadFromFile("piece_images/redpawn.png")) {
        exit(-1);
    }
    text.loadFromImage(img);
    _textures.push_back(text);

    if (!img.loadFromFile("piece_images/redking.png")) {
        exit(-1);
    }
    text.loadFromImage(img);
    _textures.push_back(text);

    // Set up initial game board state
    for (int h = 0; h < BOARD_SIZE; h++) {
        _tiles.emplace_back();
        for (int w = 0; w < BOARD_SIZE; w++) {
            sf::RectangleShape tile(sf::Vector2f(TILE_LENGTH, TILE_LENGTH));
            sf::Sprite piece;
            if ((h + w) % 2 == 0) {  // Tile red
                tile.setFillColor(sf::Color(165, 0, 0));
            } else {  // Tile Black
                tile.setFillColor(sf::Color::Black);
                if (h < 3) {  // Black pawn
                    piece.setTexture(_textures[0]);
                    piece.setPosition(w * TILE_LENGTH + BORDER_WIDTH,
                                      h * TILE_LENGTH + BORDER_WIDTH);
                    _blackPieces.push_back(Pawn(piece));
                } else if (h > 4) {  // red pawn
                    piece.setTexture(_textures[2]);
                    piece.setPosition(w * TILE_LENGTH + BORDER_WIDTH,
                                      h * TILE_LENGTH + BORDER_WIDTH);
                    _redPieces.push_back(Pawn(piece));
                }
            }
            tile.setPosition(w * TILE_LENGTH + BORDER_WIDTH, h * TILE_LENGTH + BORDER_WIDTH);
            _tiles.at(h).push_back(tile);
        }
    }

    // Black starts
    _blackTurn = true;
}

bool Checkers::isBlackTurn() const {
    return _blackTurn;
}

// Clears any previously highlighted pieces
void Checkers::clearHighlights() {
    for (int h = 0; h < BOARD_SIZE; h++) {
        for (int w = 0; w < BOARD_SIZE; w++) {
            if ((h + w) % 2 == 0) {  // Tile red
                _tiles.at(h).at(w).setFillColor(sf::Color(165, 0, 0));
            } else {
                _tiles.at(h).at(w).setFillColor(sf::Color::Black);
            }
        }
    }
}

void Checkers::onPiece(sf::Vector2f mouseXY, bool isBlackTurn) {
    // Allows player to only pick their own pieces
    vector<Pawn> pieces;
    if (isBlackTurn == true) {
        pieces = _blackPieces;
    } else {
        pieces = _redPieces;
    }

    int mouseX = ((mouseXY.x - BORDER_WIDTH) / TILE_LENGTH);
    int mouseY = ((mouseXY.y - BORDER_WIDTH) / TILE_LENGTH);
    for (Pawn const& piece : pieces) {
        int tileX = ((piece.getPiece().getPosition().x - BORDER_WIDTH) / TILE_LENGTH);
        int tileY = ((piece.getPiece().getPosition().y - BORDER_WIDTH) / TILE_LENGTH);
        if (mouseX == tileX && mouseY == tileY) {
            clearHighlights();
            _tiles.at(tileY).at(tileX).setFillColor(sf::Color(255, 245, 195));
        }
    }
}

void Checkers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (size_t h = 0; h < _tiles.size(); h++) {
        for (size_t w = 0; w < _tiles.at(0).size(); w++) {
            target.draw(_tiles.at(h).at(w), states);
        }
    }

    for (Pawn const& piece : _blackPieces) {
        target.draw(piece.getPiece(), states);
    }

    for (Pawn const& piece : _redPieces) {
        target.draw(piece.getPiece(), states);
    }
}

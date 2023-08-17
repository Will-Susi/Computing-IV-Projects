// Copyright 2023 William Susi

#include "Checkers.hpp"

const sf::Color moveHighlight(255, 245, 195);
const sf::Color pieceHighlight(185, 255, 185);

Pawn::Pawn(sf::Sprite piece): _piece(piece), _isKing(false) {}

bool Pawn::isKing() const {
    return _isKing;
}

sf::Sprite Pawn::getPiece() const {
    return _piece;
}

void Pawn::movePiece(sf::Vector2f pieceXY) {
    _piece.setPosition(pieceXY.x, pieceXY.y);
}

void Pawn::makeKing(sf::Texture& texture) {
    _piece.setTexture(texture);
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
            if ((h + w) % 2 == 0) {  // Set red tiles
                tile.setFillColor(sf::Color(165, 0, 0));
            } else {  // Set black tiles
                tile.setFillColor(sf::Color::Black);
                if (h < 3) {  // Set black pawns
                    piece.setTexture(_textures[0]);
                    piece.setPosition(w * TILE_LENGTH + BORDER_WIDTH,
                                      h * TILE_LENGTH + BORDER_WIDTH);
                    _blackPieces.push_back(Pawn(piece));
                } else if (h > 4) {  // Set red pawns
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

// Switches player turn
void Checkers::takeTurn() {
    if (isBlackTurn()) {
        _blackTurn = false;
    } else {
        _blackTurn = true;
    }
}

// Clears any previously highlighted tiles
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

// Coverts a given pixel coordinate to a tile coordinate
int Checkers::toTile(double pixel) {
    return (pixel - BORDER_WIDTH) / TILE_LENGTH;
}

// Checks if a given move is inbounds
bool Checkers::inBounds(int move) {
    return move >= 0 && move < BOARD_SIZE;
}

// Gets the current player's pieces
vector<Pawn>& Checkers::getCurrPieces() {
    if (isBlackTurn()) {
        return _blackPieces;
    }
    return _redPieces;
}

// Get the opposing player's pieces
vector<Pawn>& Checkers::getOppPieces() {
    if (isBlackTurn()) {
        return _redPieces;
    }
    return _blackPieces;
}

void Checkers::checkKing() {
    for (Pawn& piece : _blackPieces) {
        if (((piece.getPiece().getPosition().y - BORDER_WIDTH) / TILE_LENGTH) == 7) {
            piece.makeKing(_textures[1]);
        }
    }

    for (Pawn& piece : _redPieces) {
        if (((piece.getPiece().getPosition().y - BORDER_WIDTH) / TILE_LENGTH) == 0) {
            piece.makeKing(_textures[3]);
        }
    }
}

// Check if a player has won
bool Checkers::isWon() {
    return _blackPieces.size() == 0 || _redPieces.size() == 0;
}

// Checks if a piece could be found on a given tile
bool Checkers::onTile(int tileX, int tileY, vector<Pawn>& pieces) {
    if (tileX >= 0 && tileX < BOARD_SIZE && tileY >= 0 && tileY < BOARD_SIZE) {
       for (Pawn& piece : pieces) {
            int pieceX = toTile(piece.getPiece().getPosition().x);
            int pieceY = toTile(piece.getPiece().getPosition().y);
            if (tileX == pieceX && tileY == pieceY) {
                return true;
            }
        }
    }
    return false;
}

// Given a mouse click, highlight a tile if the click was on a piece
bool Checkers::clickPiece(sf::Vector2f mouseXY) {
    vector<Pawn>& pieces = getCurrPieces();
    int mouseX = toTile(mouseXY.x);
    int mouseY = toTile(mouseXY.y);
    for (Pawn& piece : pieces) {
        int pieceX = toTile(piece.getPiece().getPosition().x);
        int pieceY = toTile(piece.getPiece().getPosition().y);
        if (mouseX == pieceX && mouseY == pieceY) {
            clearHighlights();
            _tiles.at(pieceY).at(pieceX).setFillColor(pieceHighlight);
            showMoves(sf::Vector2f(pieceX, pieceY), piece);
            return true;
        }
    }
    return false;
}

// Highlight the possible tiles a current piece can move to
void Checkers::showMoves(sf::Vector2f pieceXY, Pawn& piece) {
    vector<Pawn> yourPieces = getCurrPieces();
    vector<Pawn> oppPieces = getOppPieces();
    vector<sf::Vector2f> moves;

    // Choose possible moveable directions
    if (isBlackTurn()) {
        if (piece.isKing()) {
            moves = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
        } else {
            moves = {{1, 1}, {-1, 1}};
        }
    } else {
        if (piece.isKing()) {
            moves = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
        } else {
            moves = {{-1, -1}, {1, -1}};
        }
    }

    // Highlight possible moves
    for (auto& disp : moves) {
        if (!onTile(pieceXY.x + disp.x, pieceXY.y + disp.y, yourPieces) &&
            !onTile(pieceXY.x + disp.x, pieceXY.y + disp.y, oppPieces) &&
            inBounds(pieceXY.x + disp.x) && inBounds(pieceXY.y + disp.y)) {
            _tiles.at(pieceXY.y + disp.y).at(pieceXY.x + disp.x).setFillColor(moveHighlight);
        } else if (onTile(pieceXY.x + disp.x, pieceXY.y + disp.y, oppPieces) &&
            !(onTile(pieceXY.x + 2 * disp.x, pieceXY.y + 2 * disp.y, oppPieces)) &&
            !(onTile(pieceXY.x + 2 * disp.x, pieceXY.y + 2 * disp.y, yourPieces)) &&
            inBounds(pieceXY.x + 2 * disp.x) && inBounds(pieceXY.y + 2 * disp.y)) {
            _tiles.at(pieceXY.y + 2 * disp.y).at(pieceXY.x + 2 * disp.x)
            .setFillColor(moveHighlight);
        }
    }
}

// Moves a players pawn if selected to a highlighted spot
void Checkers::makeMove(sf::Vector2f mouseXY) {
    int tileX = toTile(mouseXY.x);
    int tileY = toTile(mouseXY.y);
    vector<Pawn>& pieces = getCurrPieces();
    vector<Pawn>& oppPieces = getOppPieces();
    if (_tiles.at(tileY).at(tileX).getFillColor() == moveHighlight) {
        for (size_t h = 0; h < _tiles.size(); h++) {
            for (size_t w = 0; w < _tiles.at(0).size(); w++) {
                if (_tiles.at(h).at(w).getFillColor() == pieceHighlight) {
                    for (Pawn& piece : pieces) {
                        int pieceX = toTile(piece.getPiece().getPosition().x);
                        int pieceY = toTile(piece.getPiece().getPosition().y);
                        if (static_cast<int>(w) == pieceX && static_cast<int>(h) == pieceY) {
                            piece.movePiece(sf::Vector2f(tileX * TILE_LENGTH + BORDER_WIDTH,
                                                         tileY * TILE_LENGTH + BORDER_WIDTH));
                            removePieceJumped(oppPieces, w, h, tileX, tileY);
                            checkKing();
                            takeTurn();
                            clearHighlights();
                            return;
                        }
                    }
                }
            }
        }
    }
}

// Removes a opponents piece if a jump was detected
void Checkers::removePieceJumped(vector<Pawn>& pieces, int srcX, int srcY, int destX, int destY) {
    int pieceX = srcX + (destX - srcX)/2;
    int pieceY = srcY + (destY - srcY)/2;

    auto end = pieces.end();
    pieces.erase(remove_if(pieces.begin(), end,
    [pieceX, pieceY](Pawn& piece) {
        return pieceX == (piece.getPiece().getPosition().x - BORDER_WIDTH) / TILE_LENGTH &&
               pieceY == (piece.getPiece().getPosition().y - BORDER_WIDTH) / TILE_LENGTH;
    }), end);
}

// Overloaded draw function for Checkers class
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

// Copyright 2023 William Susi

#include <iostream>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::vector;
using std::string;
using std::cout;
using std::endl;

#define TILE_LENGTH 64
#define BORDER_WIDTH 32
#define BOARD_SIZE 8

class Pawn {
 public:
  explicit Pawn(sf::Sprite piece);

  sf::Sprite getPiece() const;
  bool isKing() const;
  void movePiece(sf::Vector2f pieceXY);
  void makeKing(sf::Texture& texture);

 private:
  sf::Sprite _piece;
  bool _isKing;
};

class Checkers: public sf::Drawable {
 public:
  Checkers();

  bool isBlackTurn() const;
  void takeTurn();
  int toTile(double pixel);
  bool inBounds(int move);
  vector<Pawn>& getCurrPieces();
  vector<Pawn>& getOppPieces();

  void checkKing();
  bool isWon();

  void clearHighlights();
  bool onTile(int tileX, int tileY, vector<Pawn>& pieces);
  bool clickPiece(sf::Vector2f mouseXY);
  void showMoves(sf::Vector2f pieceXY, Pawn& piece);


  void makeMove(sf::Vector2f mouseXY);
  void removePieceJumped(vector<Pawn>& pieces, int srcX, int srcY, int destX, int destY);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  vector<sf::Texture> _textures;
  vector<vector<sf::RectangleShape>> _tiles;
  vector<Pawn> _blackPieces;
  vector<Pawn> _redPieces;
  bool _blackTurn;
};

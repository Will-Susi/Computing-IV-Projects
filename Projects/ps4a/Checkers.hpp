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
  void makeKing();

 private:
  sf::Sprite _piece;
  bool _isKing;
};

class Checkers: public sf::Drawable {
 public:
  Checkers();

  bool isBlackTurn() const;
  void clearHighlights();
  void onPiece(sf::Vector2f mouseXY, bool isBlackTurn);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  vector<sf::Texture> _textures;
  vector<vector<sf::RectangleShape>> _tiles;
  vector<Pawn> _blackPieces;
  vector<Pawn> _redPieces;
  bool _blackTurn;
};

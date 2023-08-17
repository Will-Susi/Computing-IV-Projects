// Copyright 2023 William Susi
#pragma once

#include <math.h>
#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::string;
using std::cout;
using std::endl;
using std::stod;
using std::stoi;

class Node: public sf::Drawable {
 public:
  Node(double sideLength, sf::Vector2f origin,
      sf::Vector2f position, double rotation, sf::Color color);
  void grow(double angle, int repeat);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::RectangleShape _square;
  Node* _leftSquare;
  Node* _rightSquare;
};

class Tree: public sf::Drawable {
 public:
  Tree(double length, int depth, double angle, sf::Vector2f center);
  double getLength() const;
  void pTree();

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  Node* _base;
  double _sideLength;
  int _recDepth;
  double _angle;
};

sf::Color generateColor(int repeat);

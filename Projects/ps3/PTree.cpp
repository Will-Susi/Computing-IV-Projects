// Copyright 2023 William Susi

#include "PTree.hpp"

Tree::Tree(double length, int depth, double angle, sf::Vector2f center) {
    _sideLength = length;
    _recDepth = depth;
    _angle = angle;
    sf::Color color = sf::Color(165, 55, 0);
    _base = new Node(_sideLength, sf::Vector2f(0, 0), center, 0, color);
}

double Tree::getLength() const {
    return _sideLength;
}

// Starts the grow of the tree at the root
void Tree::pTree() {
    _base->grow(_angle, _recDepth);
}

// Calls draw on the root Node
void Tree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*_base, states);
}

Node::Node(double sideLength, sf::Vector2f origin,
           sf::Vector2f position, double rotation, sf::Color color) {
    _square.setSize(sf::Vector2f(sideLength, sideLength));
    _square.setOrigin(origin.x, origin.y);
    _square.setPosition(position.x, position.y);
    _square.setRotation(rotation);
    _square.setFillColor(color);

    _leftSquare = nullptr;
    _rightSquare = nullptr;
}

// Recursion function that generates branches of the tree
void Node::grow(double angle, int repeat) {
    // End recursion after depth is reached
    if (repeat == 0) {
        return;
    }
    repeat--;

    // Calculate left and right square lengths
    double side = _square.getLocalBounds().width;
    double leftSide = (side * cos(angle * M_PI / 180));
    double rightSide = (side * sin(angle * M_PI / 180));

    // Set left square's origin to the bottom left and right square's origin to the bottom right
    sf::Vector2f leftOri(0, leftSide);
    sf::Vector2f rightOri(rightSide, rightSide);

    auto bounds = _square.getLocalBounds();
    sf::Vector2f leftPos(_square.getTransform().
    transformPoint(bounds.left, bounds.top));
    sf::Vector2f rightPos(_square.getTransform().
    transformPoint(bounds.left + bounds.width, bounds.top));

    // Make new rotation
    double leftRotate = _square.getRotation() - angle;
    double rightRotate = _square.getRotation() - (angle - 90);

    // Get depth color
    sf::Color color = generateColor(repeat);

    _leftSquare = new Node(leftSide, leftOri, leftPos, leftRotate, color);
    _rightSquare = new Node(rightSide, rightOri, rightPos, rightRotate, color);

    // Call recursive 'grow' on each new square
    _leftSquare->grow(angle, repeat);
    _rightSquare->grow(angle, repeat);
}

// Overload of SFML draw to draw each child node of a given parent
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_square, states);
    if (_leftSquare == nullptr || _rightSquare == nullptr) {
        return;
    }
    target.draw(*_leftSquare, states);
    target.draw(*_rightSquare, states);
}

// Generates the next color of the rainbow given a depth
sf::Color generateColor(int repeat) {
    sf::Color colors[6] = {sf::Color(255, 0, 0), sf::Color(255, 125, 0), sf::Color(255, 255, 0),
                           sf::Color(0, 255, 0), sf::Color(0, 0, 255), sf::Color(125, 0, 125)};
    return (colors[repeat % 6]);
}

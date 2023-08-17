// Copyright 2023 William Susi

#include "PTree.hpp"

int main(int argc, char** argv) {
    double side = stod(argv[1]);
    int depth = stoi(argv[2]);
    double angle = 45;
    if (argc == 4) {
        angle = stod(argv[3]);
    }

    // double side1 = side * cos(angle * M_PI / 180);
    // double side2 = side * sin(angle * M_PI / 180);

    // double width = depth * abs(side1-side2) * 2;
    // double height = depth * abs(side1-side2) * 1.5 - side1;

    // sf::Vector2f center(width/2 - side/2 + (side1-side2) * 3 , (height - side * 1.5));

    // Tree tree(side, depth, angle, center);
    // tree.pTree();
    // sf::RenderWindow window(sf::VideoMode(width, height), "Pythagorean Tree");

    double width = side * 6;
    double height = side * 4;
    sf::Vector2f center(width/2 - side/2, height - side);
    Tree tree(side, depth, angle, center);
    tree.pTree();
    sf::RenderWindow window(sf::VideoMode(width, height), "Pythagorean Tree");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(tree);
        window.display();
    }

    return 0;
}

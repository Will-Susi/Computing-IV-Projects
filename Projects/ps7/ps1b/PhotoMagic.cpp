// Copyright 2023 William Susi

#include <iostream>
#include <string>
#include "FibLFSR.hpp"

/*
Encrypt: "./PhotoMagic image.png output.png 1010101010101010"
         "./PhotoMagic image.png output.png banana"
Decrypt: "./PhotoMagic output.png output2.png 1010101010101010"
         "./PhotoMagic output.png output2.png banana"
*/

int main(int argc, char** argv) {
    sf::Image sourceImage;
    sf::Image transformedImage;
    if (!sourceImage.loadFromFile(argv[1]) || !transformedImage.loadFromFile(argv[1])) {
        return -1;
    }

    // Convert string seed to binary seed
    FibLFSR seed = FibLFSR(generateBinarySeed(argv[3]));
    transform(transformedImage, &seed);

    sf::Vector2u size = sourceImage.getSize();
    sf::RenderWindow sourceWindow(sf::VideoMode(size.x, size.y), "Source_Image");
    sf::RenderWindow transformedWindow(sf::VideoMode(size.x, size.y), "Transformed_Image");

    sf::Texture sourceTexture;
    sourceTexture.loadFromImage(sourceImage);
    sf::Sprite sourceSprite;
    sourceSprite.setTexture(sourceTexture);

    sf::Texture transformedTexture;
    transformedTexture.loadFromImage(transformedImage);
    sf::Sprite transformedSprite;
    transformedSprite.setTexture(transformedTexture);

    while (sourceWindow.isOpen() && transformedWindow.isOpen()) {
        sf::Event event;
        while (sourceWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                sourceWindow.close();
            }
        }
        while (transformedWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                transformedWindow.close();
            }
        }

        sourceWindow.clear();
        sourceWindow.draw(sourceSprite);
        sourceWindow.display();

        transformedWindow.clear();
        transformedWindow.draw(transformedSprite);
        transformedWindow.display();
    }

    if (!transformedImage.saveToFile(argv[2])) {
        return -1;
    }

    return 0;
}

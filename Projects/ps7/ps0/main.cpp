// Copyright 2023 William Susi

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    // Set up green circle window
    sf::RenderWindow circleWindow(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Set up extended code demo window
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Window");
    sf::Texture texture;
    if (!texture.loadFromFile("sprite.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    sprite.setScale(.2, .2);

    // Create lightsaber audio
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("lightsaber_swing.ogg")) {
        return EXIT_FAILURE;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    // Keep window open until closed
    while (circleWindow.isOpen() && window.isOpen()) {
        sf::Event event;
        while (circleWindow.pollEvent(event) || window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                circleWindow.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {  // move sprite up
            sprite.move(0, -1);
            sound.play();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {  // move sprite down
            sprite.move(0, 1);
            sound.play();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {  // move sprite left
            sprite.move(-1, 0);
            sound.play();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  // move sprite right
            sprite.move(1, 0);
            sound.play();
        }

        window.clear();
        window.draw(sprite);
        window.display();

        circleWindow.clear();
        circleWindow.draw(shape);
        circleWindow.display();
    }

    return 0;
}

// Copyright 2023 William Susi

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::to_string;

typedef enum {
    RIGHT,
    DOWN,
    LEFT,
    UP
} Direction;

class Sokoban: public sf::Drawable{
 public:
    explicit Sokoban(string lvl);

    int getWidth() const;
    int getHeight() const;

    void movePlayer(Direction dir);

    friend std::istream& operator>>(std::istream& inStream, Sokoban& level);
    friend std::ostream& operator<<(std::ostream& outStream, const Sokoban& level);

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    vector<vector<char>> mapChar;
    vector<vector<sf::Sprite>> terrainSprites;
    vector<sf::Sprite> boxSprites;
    sf::Sprite playerSprite;
    vector<sf::Texture> textures;
};

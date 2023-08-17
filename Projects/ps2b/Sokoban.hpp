// Copyright 2023 William Susi

#include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::vector;
using std::pair;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

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
    bool isWon() const;

    friend std::istream& operator>>(std::istream& inStream, Sokoban& level);
    friend std::ostream& operator<<(std::ostream& outStream, const Sokoban& level);

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    vector<vector<char>> mapChar;
    vector<vector<sf::Sprite>> terrainSprites;
    vector<sf::Sprite> boxSprites;
    vector<pair<int, int>> storageLocations;
    sf::Sprite playerSprite;
    vector<sf::Texture> textures;
};

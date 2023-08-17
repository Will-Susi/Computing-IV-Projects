// Copyright 2023 William Susi

#include "Sokoban.hpp"

Sokoban::Sokoban(std::string lvl) {
    sf::Image img;
    sf::Texture text;

    if (!img.loadFromFile("block_06.png")) {  // Wall
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("ground_01.png")) {  // Floor
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("ground_04.png")) {  // Storage
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("crate_03.png")) {  // Box
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("player_17.png")) {  // Player_Right
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("player_05.png")) {  // Player_Down
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("player_20.png")) {  // Player_Left
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    if (!img.loadFromFile("player_08.png")) {  // Player_Up
        exit(-1);
    }
    text.loadFromImage(img);
    textures.push_back(text);

    std::fstream level;
    level.open(lvl, std::fstream::in);  // Load level file
    if (!level.good()) {
        cout << "Input file unable to open." << endl;
        exit(-1);
    }

    level >> *this;  // Create game from level
}

int Sokoban::getWidth() const {
    return mapChar.at(0).size();
}

int Sokoban::getHeight() const {
    return mapChar.size();
}

void Sokoban::movePlayer(Direction dir) {
    if (isWon()) {  // Prevent movement after game ends
        return;
    }

    vector<pair<int, int>> xyDisp = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int xP = playerSprite.getPosition().x/64;
    int yP = playerSprite.getPosition().y/64;
    pair<int, int> disp = xyDisp[dir];

    // Prevent player from moving outside bounds
    if (xP + disp.first < 0 || xP + disp.first >= static_cast<int>(mapChar.at(0).size()) ||
        yP + disp.second < 0 || yP + disp.second >= static_cast<int>(mapChar.size())) {
        return;
    }

    // Prevent player from moving through walls
    if (mapChar.at(yP + disp.second).at(xP + disp.first) == '#') {
        return;
    }

    // Implementation of proper box/player physics
    for (sf::Sprite &box : boxSprites) {
        int xB = box.getPosition().x/64;
        int yB = box.getPosition().y/64;
        // If box is in front of player
        if (xB == xP + disp.first && yB == yP + disp.second) {
            // Does not allow box to move if next space is out of bounds
            if (xB + disp.first < 0 || xB + disp.first >= static_cast<int>(mapChar.at(0).size()) ||
                yB + disp.second < 0 || yB + disp.second >= static_cast<int>(mapChar.size())) {
                return;
            }
            // If the space after the box is a wall or another box do now allow the player to move
            if (mapChar.at(yB + disp.second).at(xB + disp.first) != '#' &&
                mapChar.at(yB + disp.second).at(xB + disp.first) != 'A' ) {
                mapChar.at(yB + disp.second).at(xB + disp.first) = 'A';
                box.move(disp.first * 64, disp.second * 64);
            } else {
                return;
            }
        }
    }

    // Move player and update changed sprites
    mapChar.at(yP).at(xP) = '.';
    mapChar.at(yP + disp.second).at(xP + disp.first) = '@';
    playerSprite.move(disp.first * 64, disp.second * 64);
    playerSprite.setTexture(textures[dir + 4]);
}

bool Sokoban::isWon() const {
    int size = (boxSprites.size() < storageLocations.size()) ?
    boxSprites.size() : storageLocations.size();
    int inPlace = 0;

    // Check for different game winning scenarios
    for (pair<int, int> const& storage : storageLocations) {
        vector<sf::Sprite>::const_iterator result = find_if(boxSprites.cbegin(), boxSprites.cend(),
        [storage](const sf::Sprite& box) {
            return (box.getPosition().x == storage.first && box.getPosition().y == storage.second);
        });
        if (result != boxSprites.cend()) {
            inPlace++;
        }
    }

    return (inPlace == size);
}

std::istream& operator>>(std::istream& inStream, Sokoban& game) {
    string line;
    int width, height;
    inStream >> height >> width;

    getline(inStream, line);
    game.terrainSprites.clear();
    game.mapChar.clear();

    for (int h = 0; h < height; h++) {
        getline(inStream, line);
        game.terrainSprites.emplace_back();
        game.mapChar.emplace_back();

        for (int w = 0; w < width; w++) {
            char space = line[w];
            sf::Sprite terrain;

            if (space == '#') {  // Wall
                terrain.setTexture(game.textures[0]);
            } else if (space == '.') {  // Floor
                terrain.setTexture(game.textures[1]);
            } else if (space == 'a') {  // Storage
                terrain.setTexture(game.textures[2]);
                game.storageLocations.push_back(std::make_pair(w * 64, h * 64));
            } else if (space == 'A') {  // Box
                terrain.setTexture(game.textures[1]);
                sf::Sprite box;
                box.setTexture(game.textures[3]);
                box.setPosition(w * 64, h * 64);
                game.boxSprites.push_back(box);
            } else if (space == '@') {  // Player
                terrain.setTexture(game.textures[1]);
                sf::Sprite player;
                player.setTexture(game.textures[5]);
                player.setPosition(w * 64, h * 64);
                game.playerSprite = player;
            } else {
                cout << "Character not recognized from file." << endl;
                exit(-1);
            }
            terrain.setPosition(w * 64, h * 64);
            game.terrainSprites.at(h).push_back(terrain);
            game.mapChar.at(h).push_back(space);
        }
    }

    return inStream;
}

std::ostream& operator<<(std::ostream& outStream, const Sokoban& game) {
    for (size_t h = 0; h < game.mapChar.size(); h++) {
        for (size_t w = 0; w < game.mapChar.at(0).size(); w++) {
            outStream << game.mapChar.at(h).at(w);
        }
        outStream << endl;
    }
    return outStream;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (size_t h = 0; h < terrainSprites.size(); h++) {
        for (size_t w = 0; w < terrainSprites.at(0).size(); w++) {
            target.draw(terrainSprites.at(h).at(w), states);
        }
    }

    for (sf::Sprite const& box : boxSprites) {
        target.draw(box, states);
    }

    target.draw(playerSprite, states);
}

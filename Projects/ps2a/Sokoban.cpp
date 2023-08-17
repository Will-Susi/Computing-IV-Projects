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
    level.open(lvl, std::fstream::in);
    if (!level.good()) {
        cout << "Input file unable to open." << endl;
        exit(-1);
    }

    level >> *this;
}

int Sokoban::getWidth() const {
    return mapChar.at(0).size();
}

int Sokoban::getHeight() const {
    return mapChar.size();
}

void Sokoban::movePlayer(Direction dir) {
    cout << "TODO in PS2B"  << endl;
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
        outStream << std::endl;
    }
    return outStream;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (size_t h = 0; h < terrainSprites.size(); h++) {
        for (size_t w = 0; w < terrainSprites.at(0).size(); w++) {
            target.draw(terrainSprites.at(h).at(w), states);
        }
    }

    for (size_t i = 0; i < boxSprites.size(); i++) {
        target.draw(boxSprites.at(i), states);
    }

    target.draw(playerSprite, states);
}

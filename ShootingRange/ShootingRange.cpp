#include "ShootingRange.h"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class scene{
    std::vector<sf::Sprite> toDraw;
    std::vector<sf::Texture> textures;
    sf::RenderWindow MyWindow;
public:
    scene() : MyWindow(sf::VideoMode(1600, 800), "Shooting Range game"){
    }

    void drawScene(){
    }

    void loop(){
    }

};

class target{
    double DisplayTime;
    int position;
    int scale;
public:
    target(){

    }
    int hit(){

    }

};

class player{
    int hp;
    sf::Vector2<int> size(1, 1);
public:
    void setPosition(){
    }
    void onHit(){
    }
};




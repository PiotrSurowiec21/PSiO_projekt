#ifndef SHOOTINGRANGE_H
#define SHOOTINGRANGE_H
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class scene{
    std::vector<sf::Sprite> toDraw;
    std::vector<sf::Texture> textures;
    sf::RenderWindow MyWindow;
public:
    scene(int W, int H) : MyWindow(sf::VideoMode(W,H), "Shooting Range game"){
    }

    void drawScene(){
    }

    void loop(){
    }

};

class gameplay{

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
    int score;
    sf::Vector2<int> size(1, 1);


};

#endif // SHOOTINGRANGE_H

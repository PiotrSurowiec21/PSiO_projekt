#ifndef SHOOTINGRANGE_H
#define SHOOTINGRANGE_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class obiect: public sf::Sprite{
protected:

public:
    obiect(sf::Vector2f position ){
        setPosition(position);
    }

};

class target: public obiect{
protected:
    double DisplayTime;
    sf::Vector2f position;
    float speedPerSec;
    int scale;
public:
    target(sf::Texture texture, sf::Vector2f position, int scale, int move): obiect(position){
        setTexture(texture);
        switch (scale) {
        case 1: setScale(1,1);
            break;
        case 2: setScale(2,2);
            break;
        case 3: setScale(3,3);
        }

    }
    int hit(sf::Vector2f gunpointPos){

    }

    void animate(){

    }



};

class player: public obiect{
protected:
    int points;
    int hp;
public:
    player(sf::Texture & texture,sf::Vector2f position, sf::Vector2f scale) : obiect(position){
        setTexture(texture);
        setScale(scale);
    }

    sf::Vector2f checkIfHit(){
        sf::FloatRect bounds= getGlobalBounds();
        sf::Vector2f centerPos(bounds.left+(bounds.width/2), bounds.top+(bounds.height/2));
        std::cout<<centerPos.x<<"   "<<centerPos.y<<std::endl;

    }

    void move(sf::Vector2f Recoil, sf::RenderWindow & window){
        sf::Vector2f mousePos= window.mapPixelToCoords(sf::Mouse::getPosition(window))+Recoil;
        setPosition(mousePos);
    }
};

class bulletMarks: public obiect{
public:
    bulletMarks(sf::Vector2f point, sf::Texture& texture, sf::Vector2f scale):obiect(point){
        setTexture(texture);
        setScale(scale);
    }
};

#endif // SHOOTINGRANGE_H

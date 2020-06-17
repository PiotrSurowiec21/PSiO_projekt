#ifndef SHOOTINGRANGE_H
#define SHOOTINGRANGE_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <cmath>
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
    sf::FloatRect bounds;
    sf::Vector2f position;
    float speedPerSec=100, maxSpeed=200;
    int scale;
public:
    target(sf::Texture & texture, sf::Vector2f position, int Scale): obiect(position){
        setTexture(texture);
        scale=Scale;
        switch (Scale) {
        case 1: setScale(1,1);
            break;
        case 2: setScale(2,2);
            break;
        case 3: setScale(3,3);
            break;
        }
        bounds=getGlobalBounds();
    }

    int hit(sf::Vector2f GPPos){
        sf::Vector2f center=sf::Vector2f(bounds.left+(bounds.width/2), bounds.top+(bounds.height/2));
        float r1 = 21*scale, r2 = 10*scale;
        int points=0;
        if(GPPos.x>=bounds.left && GPPos.x<=(bounds.left+bounds.width) &&
                GPPos.y>=bounds.top && GPPos.y<=bounds.top+bounds.height){
            points++;
            //std::cout<<powf(GPPos.x-center.x, 2)<<"      "<<((r1*r1)-powf(GPPos.y-center.y,2))<<"      "<< center.x<<"      "<< center.y<<"      "<<r1*r1 <<std::endl;
           if(powf(GPPos.x-center.x, 2)<=((r1*r1)-powf(GPPos.y-center.y,2))){
                points++;
                if(powf(GPPos.x-center.x, 2)<=((r2*r2)-powf(GPPos.y-center.y,2))){
                    points++;
                }
            }
        }
        return (points*10)/scale;
    }

    void animate(int round, float fTime){
        if(round>10){
            if(bounds.left<(150/scale)){
                speedPerSec=fabs(speedPerSec);
            }
            else if (bounds.left+bounds.width>1600-(150/scale)) {
                speedPerSec=-(fabs(speedPerSec));
            }
            move(speedPerSec*fTime, 0);
            bounds=getGlobalBounds();
        }
    }
};

class player: public obiect{
protected:
    int score=0;
    int hp=5;
public:
    player(sf::Texture & texture,sf::Vector2f position, sf::Vector2f scale) : obiect(position){
        setTexture(texture);
        setScale(scale);
    }

    sf::Vector2f checkIfHit(){
        sf::FloatRect bounds= getGlobalBounds();
        sf::Vector2f centerPos(bounds.left+(bounds.width/2), bounds.top+(bounds.height/2));
        //std::cout<<centerPos.x<<"   "<<centerPos.y<<std::endl;
        return centerPos;
    }

    void move(sf::Vector2f Recoil, sf::RenderWindow & window){
        sf::Vector2f mousePos= window.mapPixelToCoords(sf::Mouse::getPosition(window))+Recoil;
        setPosition(mousePos);
    }
    void modifyStats(int points){
        if(points==0){
            hp--;
        }
        else {
            score+=points;

        }
        std::cout<<"hp:"<<hp<<"      score:"<<score<<std::endl;
    }
};

class bulletMarks: public obiect{
public:
    bulletMarks(sf::Vector2f point, sf::Texture & texture, sf::Vector2f scale):obiect(point){
        setTexture(texture);
        setScale(scale);
    }
};

class interface{

};

#endif // SHOOTINGRANGE_H

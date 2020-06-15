#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ShootingRange.h"

int main()
{
    srand( time( NULL ) );


    sf::RenderWindow window(sf::VideoMode(1600, 800), "My window");
    window.setMouseCursorVisible(false);


    sf::Texture BackgroundTex;
    if(!BackgroundTex.loadFromFile("background.png")){
        std::cout<<"texture loading fail"<<std::endl;
    }

    sf::Sprite background;
    background.setTexture(BackgroundTex);


    sf::Texture GunPointTex;
    if(!GunPointTex.loadFromFile("GunPoint.png")){
        std::cout<<"texture loading fail"<<std::endl;
    }
    player Player(GunPointTex, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(0.05, 0.05));
    sf::Sprite GunPoint;
    GunPoint.setTexture(GunPointTex);
    GunPoint.setScale(0.05, 0.05);

    sf::Texture BulletMarkTex;
    if(!BulletMarkTex.loadFromFile("bulletMark.png")){
        std::cout<<"texture loading fail"<<std::endl;
    }

    sf::Texture TargetTex;
    if(!TargetTex.loadFromFile("Target2.png")){
        std::cout<<"texture loading fail"<<std::endl;
    }
    sf::Vector2f recoil;
    std::vector<obiect*> marks;
    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {

                    //std::cout<<"click"<<std::endl;
                    recoil=sf::Vector2f((std::rand()%20)-20,(std::rand()%20)-10);
                    marks.emplace_back(new bulletMarks(Player.checkIfHit(), BulletMarkTex, sf::Vector2f(0.1, 0.1)));
                }
            }
        }
        Player.move(recoil, window);
        window.clear(sf::Color::Black);

        window.draw(background);

        for(auto& o : marks){
            window.draw(*o);
        }

        window.draw(Player);

        window.display();
    }

    return 0;
}


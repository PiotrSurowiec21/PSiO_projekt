#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ShootingRange.h"

int main()
{
    srand( time( NULL ) );

    //1.OKNO I TLO
    sf::RenderWindow window(sf::VideoMode(1600, 800), "My window");
    window.setMouseCursorVisible(false);


    sf::Texture BackgroundTex;
    BackgroundTex.loadFromFile("textures/background.png");

    sf::Sprite background;
    background.setTexture(BackgroundTex);

    //2.CELOWNIK
    sf::Texture GunPointTex;
    GunPointTex.loadFromFile("textures/GunPoint.png");

    //3.TARCZE
    sf::Texture TargetTex;
    TargetTex.loadFromFile("textures/Target.png");

    sf::Texture TargetTex2;
    TargetTex2.loadFromFile("textures/Target2.png");

    //4.PRZESTRZELINY
    sf::Texture BulletMarkTex;
    BulletMarkTex.loadFromFile("textures/bulletMark.png");

    //5. SERCE

    sf::Texture hpTex;
    hpTex.loadFromFile("textures/hp.png");

    //5. CZCIONKA
    sf::Font font;
    if(!font.loadFromFile("fonts/airstrike.ttf")){
        std::cout<<"no i chu no i czesc"<<std::endl;
    }

    gameplay play(GunPointTex, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2),sf::Vector2f(0.05, 0.05), font);
    sf::Vector2f recoil;
    sf::Clock clockFrame, clockAnim;
    while (window.isOpen()) {
        sf::Event event;
        sf::Time frameTime = clockFrame.restart();
        sf::Time animTime = clockAnim.getElapsedTime();

        play.generateObiects(TargetTex,clockAnim, hpTex);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            play.onEvent(event, BulletMarkTex);
            break;

        }

        play.updateAll(window, animTime.asSeconds(), frameTime.asSeconds());

        play.nextRound();

        window.clear(sf::Color::Black);

        window.draw(background);

        play.drawAll(window);

        window.display();
    }

    return 0;
}


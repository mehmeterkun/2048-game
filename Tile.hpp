#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Tile {
private:
    int deger;
    sf::Vector2f currentPos;
    sf::Vector2f targetPos;
    float moveSpeed;
    float kutuBoyutu;

    sf::RectangleShape kutuSekil;
    sf::Text yaziSekil;

    void renkleriGuncelle();

public:
    // Constructor artık doğuş koordinatlarını peşin peşin alıyor
    Tile(int ilkDeger, const sf::Font& font, float dogusX, float dogusY, float boyut);
    
    void setPozisyon(float x, float y, float boyut);
    void setTarget(float x, float y);
    void update(float deltaTime);
    void ciz(sf::RenderWindow& pencere);

    int getDeger() const { return deger; }
    void setDeger(int yeniDeger);
};

#endif
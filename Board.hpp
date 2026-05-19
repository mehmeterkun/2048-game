#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class Board {
private:
    Tile* harita[4][4];
    sf::Font oyunFontu;

    sf::RectangleShape arkaPlanIzgara;
    sf::RectangleShape bosKutuSekil;

    // Sabit görsel ölçülerimiz
    const float IZGARA_BOYUTU = 500.0f;
    const float KUTU_BOYUTU = 100.0f;
    const float BOSLUK = 20.0f;
    const float IZGARA_X = 150.0f;
    const float IZGARA_Y = 150.0f;

    void konumlariGuncelle();

public:
    Board(const sf::Font& font);
    ~Board();

    void ciz(sf::RenderWindow& pencere);
    void sayiUret();
    void update(float deltaTime);
    void testMatrisiYukle();

    void solaKaydir();
    void sagaKaydir();
    void yukariKaydir();
    void asagiKaydir();
};

#endif
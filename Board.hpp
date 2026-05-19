#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class Board {
private:
    //IZGARA OLCULERI
    const float IZGARA_BOYUTU = 580.0f;
    const float IZGARA_X = 110.0f;
    const float IZGARA_Y = 110.0f;
    const float KUTU_BOYUTU = 120.0f;
    const float BOSLUK = 20.0f;

    sf::RectangleShape arkaPlanIzgara;
    sf::RectangleShape bosKutuSekil;


    Tile* harita[4][4]; 
    const sf::Font& oyunFontu; // font referansı

public:
    //Tahtayı kurar, arka plan renklerini ayarlar
    Board(const sf::Font& font);

    // Hafızada oluşturulan dinamik Tile nesnelerini temizler 
    ~Board();
    void solaKaydir();

    // rastgele 2 veya 4 uretecek fonksiyonu cagırıyoruz
    void sayiUret();
    void testMatrisiYukle();
    // Tüm tahtayı ekrana çizen fonksiyon
    void ciz(sf::RenderWindow& pencere);
};

#endif
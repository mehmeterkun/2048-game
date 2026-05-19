#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile {
private:
    int deger;                     //Kutunun içindeki sayı 
    sf::RectangleShape kutuSekil;  //Kutunun renkli karesi
    sf::Text yaziSekil;            //Kutunun içindeki yazı nesnesi

    // Sayı değerine göre kutu ve yazı renklerini güncelleyen iç fonksiyon
    void renkleriGuncelle();

public:
    
    Tile(int ilkDeger, const sf::Font& font);

   
    void setDeger(int yeniDeger);
    int getDeger() const;

    //Kutunun konumunu ve boyutunu ayarlayan fonksiyon
    void setPozisyon(float x, float y, float boyut);

    //Kutuyu ve üzerindeki yazıyı ekrana çizdiren fonksiyon
    void ciz(sf::RenderWindow& pencere);
};

#endif
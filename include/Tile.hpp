#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

//Tile (Kutu) sınıfı: Oyun alanındaki her bir sayı hücresini temsil eder
class Tile {
private:
    int deger;                //Kutunun üzerinde yazan sayı değeri 
    sf::Vector2f currentPos;  //Kutunun şu anki ekrandaki konumu
    sf::Vector2f targetPos;   //Kutunun gitmesi gereken hedef konumu
    float moveSpeed;          //Kutuların hareket hızı
    float kutuBoyutu;         //Kutunun genişlik ve yükseklik değeri

    sf::RectangleShape kutuSekil; //Kutunun arka plan dikdörtgeni
    sf::Text yaziSekil;           //Kutunun üzerindeki sayıyı gösteren metin nesnesi

    //Kutucuk değerine göre renkleri güncelleyen özel yardımcı fonksiyon
    void renkleriGuncelle();

public:
    //Başlangıç değeri, font, konum ve boyut bilgileri ile kutuyu oluşturur
    Tile(int ilkDeger, const sf::Font& font, float dogusX, float dogusY, float boyut);
    
    //Kutunun boyutlarını ve konumunu manuel olarak güncellemek için
    void setPozisyon(float x, float y, float boyut);
    
    // Hareket animasyonu için hedef noktayı belirler
    void setTarget(float x, float y);
    
    //Her karede kutunun konumunu hedef noktaya doğru günceller (hareket animasyonu)
    void update(float deltaTime);
    
    // Kutuyu verilen pencereye çizer
    void ciz(sf::RenderWindow& pencere);

    //Kutunun mevcut değerini döndürür
    int getDeger() const { return deger; }
    
    //Kutunun değerini günceller ve buna bağlı olarak renkleri değiştirir
    void setDeger(int yeniDeger);
};

#endif
#include "Tile.hpp"

//Tile sınıfı yeni bir kutucuk oluşturur
Tile::Tile(int ilkDeger, const sf::Font& font, float dogusX, float dogusY, float boyut) 
    : deger(ilkDeger), moveSpeed(1500.f), kutuBoyutu(boyut){
    
    //Kutucuğun başlangıç ve hedef konumları
    currentPos = sf::Vector2f(dogusX, dogusY);
    targetPos = currentPos;

    //Kutunun fiziksel boyutu ve başlangıç pozisyonu
    kutuSekil.setSize(sf::Vector2f(boyut, boyut));
    kutuSekil.setPosition(currentPos);

    //Üzerindeki sayı yazısının özellikleri
    yaziSekil.setFont(font);
    yaziSekil.setCharacterSize(45); 
    yaziSekil.setStyle(sf::Text::Bold);
    
    //Kutunun değerine göre başlangıç rengini ata
    renkleriGuncelle();
}

//Kutunun boyutunu güncelleyen yardımcı metod
void Tile::setPozisyon(float x, float y, float boyut){
    kutuBoyutu = boyut;
    kutuSekil.setSize(sf::Vector2f(boyut, boyut));
}

//Kutucuğun hareket edeceği hedef koordinatı oluşuturur
void Tile::setTarget(float x, float y){
    targetPos = sf::Vector2f(x, y);
}

//Kutu değerini değiştirir ve renk güncellenir
void Tile::setDeger(int yeniDeger){
    deger = yeniDeger;
    renkleriGuncelle();
}

// Kutunun akıcı bir şekilde hareket etmesini sağlar
void Tile::update(float deltaTime){
    // Mevcut pozisyon ile hedef arasındaki farkı hesapla
    sf::Vector2f diff = targetPos - currentPos;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    //Eğer hedef ile aramızda mesafe varsa hareket et
    if(distance > 1.f){
        sf::Vector2f direction = diff / distance; // Birim vektörü hesapla
        currentPos += direction * moveSpeed * deltaTime; // Hıza göre pozisyonu güncelle
        
        //Kutu hedefi geçtiyse tam hedefe sabitle
        float newDistance = std::sqrt((targetPos.x - currentPos.x) * (targetPos.x - currentPos.x) + (targetPos.y - currentPos.y) * (targetPos.y - currentPos.y));
        if (newDistance > distance){
            currentPos = targetPos;
        }
    } 
    else{
        //Hedefe yeterince yaklaşıldıysa konumu hedefe eşitle
        currentPos = targetPos;

    }

    //Şekli yeni konuma taşı
    kutuSekil.setPosition(currentPos);

    //Sayıyı kutunun tam merkezine hizalar
    sf::FloatRect yaziBoyut = yaziSekil.getLocalBounds();
    yaziSekil.setOrigin(yaziBoyut.left + yaziBoyut.width / 2.0f, yaziBoyut.top + yaziBoyut.height / 2.0f);
    yaziSekil.setPosition(currentPos.x + kutuBoyutu / 2.0f, currentPos.y + kutuBoyutu / 2.0f);
}

// Kutuyu ekrana çizen fonksiyon
void Tile::ciz(sf::RenderWindow& pencere){
    pencere.draw(kutuSekil);
    pencere.draw(yaziSekil);
}

// Kutucuğun üzerindeki sayıya göre renklerini günceller
void Tile::renkleriGuncelle(){
    yaziSekil.setString(std::to_string(deger));

    // Her değer için özel renk atamaları
    if(deger == 2){
        kutuSekil.setFillColor(sf::Color(238, 228, 218));
        yaziSekil.setFillColor(sf::Color(119, 110, 101));
    } 
    else if(deger == 4){
        kutuSekil.setFillColor(sf::Color(237, 224, 200));
        yaziSekil.setFillColor(sf::Color(119, 110, 101));
    } 
    else if(deger == 8){
        kutuSekil.setFillColor(sf::Color(242, 177, 121));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 16){
        kutuSekil.setFillColor(sf::Color(245, 149, 99));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 32){
        kutuSekil.setFillColor(sf::Color(246, 124, 95));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 64){
        kutuSekil.setFillColor(sf::Color(246, 94, 59));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 128){
        kutuSekil.setFillColor(sf::Color(237, 207, 114));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 256){
        kutuSekil.setFillColor(sf::Color(237, 204, 97));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 512){
        kutuSekil.setFillColor(sf::Color(237, 200, 80));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 1024){
        kutuSekil.setFillColor(sf::Color(237, 197, 63));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else if(deger == 2048){
        kutuSekil.setFillColor(sf::Color(237, 194, 46));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } 
    else{
        //2048 den büyük değerler için 
        kutuSekil.setFillColor(sf::Color(60, 58, 50));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    }
}
#include "Tile.hpp"

Tile::Tile(int ilkDeger, const sf::Font& font, float dogusX, float dogusY, float boyut) 
    : deger(ilkDeger), moveSpeed(1500.f), kutuBoyutu(boyut) {
    
    // Doğduğu saniyede ekrandaki gerçek yerini biliyor, (0,0) krizi yaşanmıyor
    currentPos = sf::Vector2f(dogusX, dogusY);
    targetPos = currentPos;

    kutuSekil.setSize(sf::Vector2f(boyut, boyut));
    kutuSekil.setPosition(currentPos);

    yaziSekil.setFont(font);
    yaziSekil.setCharacterSize(45); 
    yaziSekil.setStyle(sf::Text::Bold);
    
    renkleriGuncelle();
}

void Tile::setPozisyon(float x, float y, float boyut) {
    kutuBoyutu = boyut;
    kutuSekil.setSize(sf::Vector2f(boyut, boyut));
}

void Tile::setTarget(float x, float y) {
    targetPos = sf::Vector2f(x, y);
}

void Tile::setDeger(int yeniDeger) {
    deger = yeniDeger;
    renkleriGuncelle();
}

void Tile::update(float deltaTime) {
    // Mesafe hesaplama (Pisagor)
    sf::Vector2f diff = targetPos - currentPos;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (distance > 1.f) {
        sf::Vector2f direction = diff / distance;
        currentPos += direction * moveSpeed * deltaTime;
        
        // Hedefi aştık mı kontrolü
        float newDistance = std::sqrt((targetPos.x - currentPos.x) * (targetPos.x - currentPos.x) + 
                                     (targetPos.y - currentPos.y) * (targetPos.y - currentPos.y));
        if (newDistance > distance) {
            currentPos = targetPos;
        }
    } else {
        currentPos = targetPos;
    }

    kutuSekil.setPosition(currentPos);

    // Yazıyı kutunun tam ortasına hizalama
    sf::FloatRect yaziBoyut = yaziSekil.getLocalBounds();
    yaziSekil.setOrigin(yaziBoyut.left + yaziBoyut.width / 2.0f, yaziBoyut.top + yaziBoyut.height / 2.0f);
    yaziSekil.setPosition(currentPos.x + kutuBoyutu / 2.0f, currentPos.y + kutuBoyutu / 2.0f);
}

void Tile::ciz(sf::RenderWindow& pencere) {
    pencere.draw(kutuSekil);
    pencere.draw(yaziSekil);
}

void Tile::renkleriGuncelle() {
    yaziSekil.setString(std::to_string(deger));

    // Orijinal 2048 renk paleti
    if (deger == 2) {
        kutuSekil.setFillColor(sf::Color(238, 228, 218));
        yaziSekil.setFillColor(sf::Color(119, 110, 101));
    } else if (deger == 4) {
        kutuSekil.setFillColor(sf::Color(237, 224, 200));
        yaziSekil.setFillColor(sf::Color(119, 110, 101));
    } else if (deger == 8) {
        kutuSekil.setFillColor(sf::Color(242, 177, 121));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 16) {
        kutuSekil.setFillColor(sf::Color(245, 149, 99));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 32) {
        kutuSekil.setFillColor(sf::Color(246, 124, 95));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 64) {
        kutuSekil.setFillColor(sf::Color(246, 94, 59));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 128) {
        kutuSekil.setFillColor(sf::Color(237, 207, 114));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 256) {
        kutuSekil.setFillColor(sf::Color(237, 204, 97));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 512) {
        kutuSekil.setFillColor(sf::Color(237, 200, 80));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 1024) {
        kutuSekil.setFillColor(sf::Color(237, 197, 63));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else if (deger == 2048) {
        kutuSekil.setFillColor(sf::Color(237, 194, 46));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    } else {
        kutuSekil.setFillColor(sf::Color(60, 58, 50));
        yaziSekil.setFillColor(sf::Color(249, 246, 242));
    }
}
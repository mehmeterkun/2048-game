#include "Tile.hpp"

//Kutu ilk yaratıldığında fontunu bağlar ve boyut ayarını yapar
Tile::Tile(int ilkDeger, const sf::Font& font) {
    deger = ilkDeger;

    // Yazı nesnesinin font, boyut ve kalınlık ayarları
    yaziSekil.setFont(font);
    yaziSekil.setCharacterSize(52); 
    yaziSekil.setStyle(sf::Text::Bold);

    // Değere göre renkleri belirle
    renkleriGuncelle();
}

void Tile::setDeger(int yeniDeger) {
    deger = yeniDeger;
    renkleriGuncelle(); // Değer her değiştiğinde rengi de otomatik güncellenir
}

int Tile::getDeger() const {
    return deger;
}


void Tile::renkleriGuncelle() {
    yaziSekil.setString(std::to_string(deger));

    sf::Color kutuRengi;
    sf::Color yaziRengi = sf::Color(119, 110, 101); // Varsayılan koyu renk yazı

    switch (deger) {
        case 2:    kutuRengi = sf::Color(238, 228, 218); break;
        case 4:    kutuRengi = sf::Color(237, 224, 200); break;
        case 8:    kutuRengi = sf::Color(242, 177, 121); yaziRengi = sf::Color(249, 246, 242); break; // Beyaz yazı
        case 16:   kutuRengi = sf::Color(245, 149, 99);  yaziRengi = sf::Color(249, 246, 242); break;
        case 32:   kutuRengi = sf::Color(246, 124, 95);  yaziRengi = sf::Color(249, 246, 242); break;
        case 64:   kutuRengi = sf::Color(246, 94, 59);   yaziRengi = sf::Color(249, 246, 242); break;
        case 128:  kutuRengi = sf::Color(237, 207, 114); yaziRengi = sf::Color(249, 246, 242); break;
        default:   kutuRengi = sf::Color(60, 58, 50);    yaziRengi = sf::Color(249, 246, 242); break;
    }

    kutuSekil.setFillColor(kutuRengi);
    yaziSekil.setFillColor(yaziRengi);
}

// Kutunun yerini belirleyen ve içindeki yazıyı tam merkezini ayarlar
void Tile::setPozisyon(float x, float y, float boyut) {
    kutuSekil.setSize(sf::Vector2f(boyut, boyut));
    kutuSekil.setPosition(x, y);
    sf::FloatRect yaziBoyut = yaziSekil.getLocalBounds();
    yaziSekil.setOrigin(yaziBoyut.left + yaziBoyut.width / 2.0f, yaziBoyut.top + yaziBoyut.height / 2.0f);
    yaziSekil.setPosition(x + boyut / 2.0f, y + boyut / 2.0f);
}


void Tile::ciz(sf::RenderWindow& pencere) {
    pencere.draw(kutuSekil); // Önce kare kutu
    pencere.draw(yaziSekil); // Üstüne merkezlenmiş sayı yazısı
}
#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() {
    // 2048 adlı pencereyi oluşturuyoruz
    sf::RenderWindow pencere(sf::VideoMode(800, 800), "2048", sf::Style::Default);

    const float OYUN_GENISLIK = 800.0f;
    const float OYUN_YUKSEKLIK = 800.0f;
    sf::View gorunum(sf::FloatRect(0, 0, OYUN_GENISLIK, OYUN_YUKSEKLIK));

    // Font nesnesi
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    // Oyun tahtasını oluşturuyoruz
    Board oyunTahtasi(font);

    

    //Oyun başında rastgele iki sayı doğsun
    oyunTahtasi.sayiUret();
    oyunTahtasi.sayiUret();

    while (pencere.isOpen()) {
        sf::Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed)
                pencere.close();

            // Tam ekran oran koruma 
            if (olay.type == sf::Event::Resized) {
                float yeniGenislik = static_cast<float>(olay.size.width);
                float yeniYukseklik = static_cast<float>(olay.size.height);
                float ekranOrani = yeniGenislik / yeniYukseklik;
                float oyunOrani = OYUN_GENISLIK / OYUN_YUKSEKLIK;
                float gorunumX = 0.0f, gorunumY = 0.0f;
                float gorunumGenislik = 1.0f, gorunumYukseklik = 1.0f;

                if (ekranOrani > oyunOrani) {
                    gorunumGenislik = oyunOrani / ekranOrani;
                    gorunumX = (1.0f - gorunumGenislik) / 2.0f;
                } else {
                    gorunumYukseklik = ekranOrani / oyunOrani;
                    gorunumY = (1.0f - gorunumYukseklik) / 2.0f;
                }
                gorunum.setViewport(sf::FloatRect(gorunumX, gorunumY, gorunumGenislik, gorunumYukseklik));
            }
        }

        // Çizim Aşaması
        pencere.clear(sf::Color(243, 239, 227));
        pencere.setView(gorunum);

        
        oyunTahtasi.ciz(pencere);

        pencere.display();
    }

    return 0;
}
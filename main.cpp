#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() {
    sf::RenderWindow pencere(sf::VideoMode(800, 800), "2048", sf::Style::Default);
    pencere.setFramerateLimit(60); 

    const float OYUN_GENISLIK = 800.0f;
    const float OYUN_YUKSEKLIK = 800.0f;
    sf::View gorunum(sf::FloatRect(0, 0, OYUN_GENISLIK, OYUN_YUKSEKLIK));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    Board oyunTahtasi(font);
    sf::Clock saat; 

    oyunTahtasi.sayiUret();
    oyunTahtasi.sayiUret();

    while (pencere.isOpen()) {
        float deltaTime = saat.restart().asSeconds();

        sf::Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed)
                pencere.close();

            if (olay.type == sf::Event::KeyPressed) {
                if (olay.key.code == sf::Keyboard::Left || olay.key.code == sf::Keyboard::A) {
                    oyunTahtasi.solaKaydir();
                }
                else if (olay.key.code == sf::Keyboard::Right || olay.key.code == sf::Keyboard::D) {
                    oyunTahtasi.sagaKaydir();
                }
                else if (olay.key.code == sf::Keyboard::Up || olay.key.code == sf::Keyboard::W) {
                    oyunTahtasi.yukariKaydir();
                }
                else if (olay.key.code == sf::Keyboard::Down || olay.key.code == sf::Keyboard::S) {
                    oyunTahtasi.asagiKaydir();
                }
            }

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

        // Fiziksel kayma animasyonunu besliyoruz
        oyunTahtasi.update(deltaTime);

        pencere.clear(sf::Color(243, 239, 227));
        pencere.setView(gorunum);

        oyunTahtasi.ciz(pencere);

        pencere.display();
    }

    return 0;
}
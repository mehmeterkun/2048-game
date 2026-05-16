#include <SFML/Graphics.hpp>

int main() {
    // 2048 adli pencereyi olusturuyor
    sf::RenderWindow pencere(sf::VideoMode(800, 800), "2048", sf::Style::Default);

    const float OYUN_GENISLIK = 800.0f;
    const float OYUN_YUKSEKLIK = 800.0f;
    sf::View gorunum(sf::FloatRect(0, 0, OYUN_GENISLIK, OYUN_YUKSEKLIK));

    // --- IZGARA TASARIM AYARLARI ---
    const float IZGARA_BOYUTU = 580.0f;
    const float IZGARA_X = 110.0f;
    const float IZGARA_Y = 110.0f;
    
    const float KUTU_BOYUTU = 120.0f;
    const float BOSLUK = 20.0f;

    sf::RectangleShape arkaPlanIzgara(sf::Vector2f(IZGARA_BOYUTU, IZGARA_BOYUTU));
    arkaPlanIzgara.setFillColor(sf::Color(187, 173, 160)); 
    arkaPlanIzgara.setPosition(IZGARA_X, IZGARA_Y);

    sf::RectangleShape bosKutu(sf::Vector2f(KUTU_BOYUTU, KUTU_BOYUTU));
    bosKutu.setFillColor(sf::Color(205, 193, 180)); 

    while (pencere.isOpen()) {
        sf::Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed)
                pencere.close();

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

        pencere.clear(sf::Color(243,239,227));
        pencere.setView(gorunum);

        pencere.draw(arkaPlanIzgara);

        for (int satir = 0; satir < 4; satir++) {
            for (int sutun = 0; sutun < 4; sutun++) {
                float kutuX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
                float kutuY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);
                
                bosKutu.setPosition(kutuX, kutuY);
                pencere.draw(bosKutu);
            }
        }

        pencere.display();
    }

    return 0;
}
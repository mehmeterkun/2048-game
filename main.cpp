#include <SFML/Graphics.hpp>

int main() {
    // asagidaki kod pencere olusturuyor
    sf::RenderWindow pencere(sf::VideoMode(800, 800), "2048 - Ana Proje", sf::Style::Default);

    
    const float OYUN_GENISLIK = 800.0f;
    const float OYUN_YUKSEKLIK = 800.0f;

    // kare formunu koruyor
    sf::View gorunum(sf::FloatRect(0, 0, OYUN_GENISLIK, OYUN_YUKSEKLIK));

    while (pencere.isOpen()) {
        sf::Event olay;
        while (pencere.pollEvent(olay)){
            if (olay.type == sf::Event::Closed)
                pencere.close();

            // tam ekranda ölçüleri koruyo
            if(olay.type == sf::Event::Resized){
                float yeniGenislik = static_cast<float>(olay.size.width);
                float yeniYukseklik = static_cast<float>(olay.size.height);

                float ekranOrani = yeniGenislik / yeniYukseklik;
                float oyunOrani = OYUN_GENISLIK / OYUN_YUKSEKLIK;

                float gorunumX = 0.0f, gorunumY = 0.0f;
                float gorunumGenislik = 1.0f, gorunumYukseklik = 1.0f;

                //oyun ekrani disindaki yerleri siyah yap
                if(ekranOrani > oyunOrani){
                    gorunumGenislik = oyunOrani / ekranOrani;
                    gorunumX = (1.0f - gorunumGenislik) / 2.0f;
                }
                else{
                    gorunumYukseklik = ekranOrani / oyunOrani;
                    gorunumY = (1.0f - gorunumYukseklik) / 2.0f;
                }

                // Hesaplanan yeni oranlari gorunume sabitliyoruz
                gorunum.setViewport(sf::FloatRect(gorunumX, gorunumY, gorunumGenislik, gorunumYukseklik));
            }
        }

        pencere.clear(sf::Color::Black); // Arka plan siyah

        // Ayarladigimiz akilli gorunumu pencereye uyguluyoruz
        pencere.setView(gorunum);

        // Ortadaki test karemizi tekrar ciziyoruz
        sf::RectangleShape testKaresi(sf::Vector2f(400.0f, 400.0f));
        testKaresi.setFillColor(sf::Color::Green);
        testKaresi.setPosition(200.0f, 200.0f); 
        
        pencere.draw(testKaresi);

        pencere.display();
    }
    return 0;
}
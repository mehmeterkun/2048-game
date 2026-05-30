#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <iostream>

// Oyunun o anki durumunu takip etmek için tanımlanan enum yapısı
enum OyunDurumu { MENU, OYUN, OYUN_BITTI, KAZANDIN };

int main() {
    //Pencere boyutları
    const unsigned int LOGICAL_WIDTH = 1200;
    const unsigned int LOGICAL_HEIGHT = 700;

    //2048 adlı SFML penceresi ,60 FPS
    sf::RenderWindow window(sf::VideoMode(LOGICAL_WIDTH, LOGICAL_HEIGHT), "2048");
    window.setFramerateLimit(60);

    // Oyunun çizileceği görünüm (View) ayarı
    sf::View gameView(sf::FloatRect(0.f, 0.f, static_cast<float>(LOGICAL_WIDTH), static_cast<float>(LOGICAL_HEIGHT)));

    //font yükleme işlemi,yüklenemezse program hata verip kapanır
    sf::Font font;
    if(!font.loadFromFile("assets/arial.ttf")){
        std::cout << "Font yuklenemedi!" << std::endl;
        return -1;
    }

    //Oyun ızgarasını oluştur ve rastgele 2 sayı üret
    Board board(font);
    board.update(0.01f);
    board.sayiUret();
    board.sayiUret();

    //Oyunun başlangıç durumunu ana menü olarak başlatıyoruz
    OyunDurumu durum = MENU;

    //Menü ekranının görünümü
    sf::Text menuLogosu, baslatYazisi, cikisYazisi;
    menuLogosu.setFont(font); menuLogosu.setString("2048"); menuLogosu.setCharacterSize(140); menuLogosu.setFillColor(sf::Color(242, 177, 121));
    baslatYazisi.setFont(font); baslatYazisi.setString("OYUNA BASLA [ ENTER ]"); baslatYazisi.setCharacterSize(32); baslatYazisi.setFillColor(sf::Color(143, 122, 102));
    cikisYazisi.setFont(font); cikisYazisi.setString("CIKIS YAP [ SPACE ]"); cikisYazisi.setCharacterSize(32); cikisYazisi.setFillColor(sf::Color(238, 110, 110));

    //Oyun bittiğinde ekranın üzerine gelecek karartma katmanı
    sf::RectangleShape oyunBittiArkaPlan(sf::Vector2f(LOGICAL_WIDTH, LOGICAL_HEIGHT));
    oyunBittiArkaPlan.setFillColor(sf::Color(0, 0, 0, 225));
    
    //Oyun sonu mesajları için metinlerin özelliği (hamle kalmadı,skor..)
    sf::Text mesajYazisi;
    mesajYazisi.setFont(font); mesajYazisi.setCharacterSize(56); mesajYazisi.setFillColor(sf::Color(242, 108, 79));    
    sf::Text detayYazisi;
    detayYazisi.setFont(font); detayYazisi.setCharacterSize(28); detayYazisi.setFillColor(sf::Color(250, 248, 239));
    sf::Clock clock;

    //Pencere açık kaldığı sürece çalışır
    while(window.isOpen()){
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        // Kullanıcı girişlerini (klavye, fare, pencere kapatma) kontrol eder
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            
            if(event.type == sf::Event::KeyPressed){
                // Menü ekranındayken klavye komutlarını yönetir
                if(durum == MENU && event.key.code == sf::Keyboard::Enter) durum = OYUN;
                else if(durum == MENU && event.key.code == sf::Keyboard::Space) window.close();
                
                //Oyun içindeyken yön tuşları ile tahtayı hareket ettirir
                else if(durum == OYUN){
                    if(event.key.code == sf::Keyboard::Left) board.solaKaydir();
                    else if(event.key.code == sf::Keyboard::Right) board.sagaKaydir();
                    else if(event.key.code == sf::Keyboard::Up) board.yukariKaydir();
                    else if(event.key.code == sf::Keyboard::Down) board.asagiKaydir();                    
                    //Oyuncunun kazanıp kazanmadığını veya hamle kalıp kalmadığını kontrol eder
                    if(board.getUlasildi2048() && durum != KAZANDIN){
                        durum = KAZANDIN;
                    } 
                    else if(board.oyunBittiMi()) durum = OYUN_BITTI;
                }
                //Oyun bittiğinde 'M' tuşu ile tahtayı sıfırla ve menüye dön
                else if((durum == OYUN_BITTI || durum == KAZANDIN) && event.key.code == sf::Keyboard::M){
                    board.~Board(); new (&board) Board(font); board.sayiUret(); board.sayiUret(); durum = MENU;
                }
            }
        }
        //Oyun tahtasınıgüncelle
        board.update(deltaTime);

        //Ekranı temizle ve çizim işlemlerini başlat
        window.clear(sf::Color(250, 248, 239));
        window.setView(gameView);

        //Duruma göre ekranı çiz (Menü veya Oyun ekranı)
        if(durum == MENU){
            menuLogosu.setPosition(LOGICAL_WIDTH/2.f - menuLogosu.getLocalBounds().width/2.f, 150);
            baslatYazisi.setPosition(LOGICAL_WIDTH/2.f - baslatYazisi.getLocalBounds().width/2.f, 350);
            cikisYazisi.setPosition(LOGICAL_WIDTH/2.f - cikisYazisi.getLocalBounds().width/2.f, 450);
            window.draw(menuLogosu); window.draw(baslatYazisi); window.draw(cikisYazisi);
        }
        else{
            board.ciz(window);
            
            //Oyun sonu durumlarına göre sonuç mesajlarını yazar
            if(durum == OYUN_BITTI || durum == KAZANDIN){
                window.draw(oyunBittiArkaPlan);
                mesajYazisi.setString(durum == KAZANDIN ? "TEBRIKLER! 2048'E ULASTIN!" : "HAMLE KALMADI!");
                mesajYazisi.setPosition(LOGICAL_WIDTH/2.f - mesajYazisi.getLocalBounds().width/2.f, 200);
                window.draw(mesajYazisi);
                detayYazisi.setString("Skor: " + std::to_string(board.getSkor()) + "   |   Rekor: " + std::to_string(board.getEnYuksekSkor()));
                detayYazisi.setPosition(LOGICAL_WIDTH/2.f - detayYazisi.getLocalBounds().width/2.f, 300);
                window.draw(detayYazisi);
                detayYazisi.setString("Menu'ye donmek icin [ M ]'ye basin");
                detayYazisi.setPosition(LOGICAL_WIDTH/2.f - detayYazisi.getLocalBounds().width/2.f, 400);
                window.draw(detayYazisi);
            }
        }
        //Çizilen her şeyi ekranda oluştur
        window.display();
    }
    return 0;
}
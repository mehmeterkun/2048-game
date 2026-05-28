#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <iostream>

enum OyunDurumu { MENU, OYUN, OYUN_BITTI };

int main() {
    const unsigned int LOGICAL_WIDTH = 1200;
    const unsigned int LOGICAL_HEIGHT = 700;

    sf::RenderWindow window(sf::VideoMode(LOGICAL_WIDTH, LOGICAL_HEIGHT), "2048 Proje Oyunu");
    window.setFramerateLimit(60);

    // KAREYİ 1 KEZ TANIMLA: Tüm oyunun ana ekranı bu olacak.
    sf::View gameView(sf::FloatRect(0.f, 0.f, static_cast<float>(LOGICAL_WIDTH), static_cast<float>(LOGICAL_HEIGHT)));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Font yuklenemedi!" << std::endl;
        return -1;
    }

    Board board(font);
    board.update(0.01f);
    board.sayiUret();
    board.sayiUret();

    OyunDurumu durum = MENU;

    // --- MENU TASARIMI (Sadece değişken tanımları) ---
    sf::Text menuLogosu, baslatYazisi, cikisYazisi;
    menuLogosu.setFont(font); menuLogosu.setString("2048"); menuLogosu.setCharacterSize(140); menuLogosu.setFillColor(sf::Color(242, 177, 121));
    baslatYazisi.setFont(font); baslatYazisi.setString("OYUNA BASLA [ ENTER ]"); baslatYazisi.setCharacterSize(32); baslatYazisi.setFillColor(sf::Color(143, 122, 102));
    cikisYazisi.setFont(font); cikisYazisi.setString("CIKIS YAP [ SPACE ]"); cikisYazisi.setCharacterSize(32); cikisYazisi.setFillColor(sf::Color(238, 110, 110));

    sf::RectangleShape oyunBittiArkaPlan(sf::Vector2f(LOGICAL_WIDTH, LOGICAL_HEIGHT));
    oyunBittiArkaPlan.setFillColor(sf::Color(0, 0, 0, 225));
    sf::Text oyunBittiYazisi, oyunBittiDetayYazisi;
    oyunBittiYazisi.setFont(font); oyunBittiYazisi.setCharacterSize(56); oyunBittiYazisi.setFillColor(sf::Color(242, 108, 79));
    oyunBittiDetayYazisi.setFont(font); oyunBittiDetayYazisi.setCharacterSize(28); oyunBittiDetayYazisi.setFillColor(sf::Color(250, 248, 239));

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            
            // TAM EKRAN ORAN KORUMA (Letterbox)
            if (event.type == sf::Event::Resized) {
                float windowRatio = (float)event.size.width / (float)event.size.height;
                float logicalRatio = (float)LOGICAL_WIDTH / (float)LOGICAL_HEIGHT;
                sf::FloatRect viewPort(0.f, 0.f, 1.f, 1.f);
                if (windowRatio > logicalRatio) {
                    float width = logicalRatio / windowRatio;
                    viewPort.width = width; viewPort.left = (1.f - width) / 2.f;
                } else {
                    float height = windowRatio / logicalRatio;
                    viewPort.height = height; viewPort.top = (1.f - height) / 2.f;
                }
                gameView.setViewport(viewPort);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (durum == MENU && event.key.code == sf::Keyboard::Enter) durum = OYUN;
                else if (durum == MENU && event.key.code == sf::Keyboard::Space) window.close();
                else if (durum == OYUN) {
                    if (event.key.code == sf::Keyboard::Left) board.solaKaydir();
                    else if (event.key.code == sf::Keyboard::Right) board.sagaKaydir();
                    else if (event.key.code == sf::Keyboard::Up) board.yukariKaydir();
                    else if (event.key.code == sf::Keyboard::Down) board.asagiKaydir();
                    if (board.oyunBittiMi()) durum = OYUN_BITTI;
                }
                else if (durum == OYUN_BITTI && event.key.code == sf::Keyboard::M) {
                    board.~Board(); new (&board) Board(font); board.sayiUret(); board.sayiUret(); durum = MENU;
                }
            }
        }

        board.update(deltaTime);

        // --- DRAW BLOĞU: Burası artık çok kararlı ---
        window.clear(sf::Color(250, 248, 239));
        window.setView(gameView); // Kamerayı oyunun ana evrenine kilitliyoruz.

        if (durum == MENU) {
            menuLogosu.setPosition(LOGICAL_WIDTH/2.f - menuLogosu.getLocalBounds().width/2.f, 150);
            baslatYazisi.setPosition(LOGICAL_WIDTH/2.f - baslatYazisi.getLocalBounds().width/2.f, 350);
            cikisYazisi.setPosition(LOGICAL_WIDTH/2.f - cikisYazisi.getLocalBounds().width/2.f, 450);
            window.draw(menuLogosu); window.draw(baslatYazisi); window.draw(cikisYazisi);
        }
        else {
            // OYUN VEYA OYUN_BITTI
            board.ciz(window); // Board kendi sabit koordinatlarını çizer, gameView zaten 1200x700 olduğu için çakışma olmaz.
            
            if (durum == OYUN_BITTI) {
            window.draw(oyunBittiArkaPlan); // Ekranı karart
            
            // HAMLE KALMADI
            oyunBittiYazisi.setString("HAMLE KALMADI!");
            oyunBittiYazisi.setPosition(LOGICAL_WIDTH/2.f - oyunBittiYazisi.getLocalBounds().width/2.f, 200);
            window.draw(oyunBittiYazisi);

            // Skor ve Rekor
            oyunBittiDetayYazisi.setString("Skor: " + std::to_string(board.getSkor()) + "   |   Rekor: " + std::to_string(board.getEnYuksekSkor()));
            oyunBittiDetayYazisi.setPosition(LOGICAL_WIDTH/2.f - oyunBittiDetayYazisi.getLocalBounds().width/2.f, 300);
            window.draw(oyunBittiDetayYazisi);

            // Menü Dönüş
            oyunBittiDetayYazisi.setString("Menu'ye donmek icin [ M ]'ye basin");
            oyunBittiDetayYazisi.setPosition(LOGICAL_WIDTH/2.f - oyunBittiDetayYazisi.getLocalBounds().width/2.f, 400);
            window.draw(oyunBittiDetayYazisi);
        }
        }
        window.display();
    }
    return 0;
}
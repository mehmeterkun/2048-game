#include "Board.hpp"
#include <cstdlib> // rand() ve srand() 
#include <ctime>   // time() 
#include <vector>
//Izgara renklerini ayarlar ve matrisin içini tamamen boşaltır 
Board::Board(const sf::Font& font) : oyunFontu(font) {
    // Rastgelelik motoru
    std::srand(std::time(nullptr));

    arkaPlanIzgara.setSize(sf::Vector2f(IZGARA_BOYUTU, IZGARA_BOYUTU));
    arkaPlanIzgara.setFillColor(sf::Color(187, 173, 160));
    arkaPlanIzgara.setPosition(IZGARA_X, IZGARA_Y);

    bosKutuSekil.setSize(sf::Vector2f(KUTU_BOYUTU, KUTU_BOYUTU));
    bosKutuSekil.setFillColor(sf::Color(205, 193, 180));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            harita[i][j] = nullptr;
        }
    }
}

// Oyun kapandığında hafızada açık kalan Tile pencerelerini kapatıp temizler
Board::~Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] != nullptr) {
                delete harita[i][j];
            }
        }
    }
}


void Board::testMatrisiYukle() {
    int geciciHarita[4][4] = {
        {2, 0, 4, 0},
        {0, 8, 0, 0},
        {16, 0, 0, 2},
        {0, 0, 4, 0}
    };

    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
            int deger = geciciHarita[satir][sutun];
            if (deger != 0) {
                // Eğer sayı sıfır değilse, hafızada yeni bir Tile nesnesi yaratıyoruz
                harita[satir][sutun] = new Tile(deger, oyunFontu);
            }
        }
    }
}

// Çizim fonksiyonu
void Board::ciz(sf::RenderWindow& pencere) {
    //en arkadaki büyük panel
    pencere.draw(arkaPlanIzgara);

    // 4x4 matrisi tarar ve kutuları yerleştirir
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
          
            float kutuX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
            float kutuY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);

            // Hücre boşsa düz boş gri kutuyu çiz
            if (harita[satir][sutun] == nullptr) {
                bosKutuSekil.setPosition(kutuX, kutuY);
                pencere.draw(bosKutuSekil);
            } 
            // Hücre doluysa o hücredeki Tile nesnesine konumunu bildir ve onu çizdir
            else {
                harita[satir][sutun]->setPozisyon(kutuX, kutuY, KUTU_BOYUTU);
                harita[satir][sutun]->ciz(pencere); 
            }
        }
    }
}
void Board::sayiUret() {
    //haritadaki boş yerlerin koordinatları
    std::vector<std::pair<int, int>> bosYerler;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] == nullptr) {
                bosYerler.push_back({i, j});
            }
        }
    }

    // Game Over durumu
    if (bosYerler.empty()) return;

    // Boş yerler listesinden rastgele bir indeks seçelim
    int rastgeleIndeks = std::rand() % bosYerler.size();
    int satir = bosYerler[rastgeleIndeks].first;
    int sutun = bosYerler[rastgeleIndeks].second;

    // %90 ihtimalle 2, %10 ihtimalle 4 
    int yeniDeger = (std::rand() % 10 == 0) ? 4 : 2;

    // Seçilen boş koordinatta yeni kutuyu oluşturalım
    harita[satir][sutun] = new Tile(yeniDeger, oyunFontu);
}
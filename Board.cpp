#include "Board.hpp"

//Izgara renklerini ayarlar ve matrisin içini tamamen boşaltır 
Board::Board(const sf::Font& font) : oyunFontu(font) {
    // Büyük kahverengi arka plan paneli
    arkaPlanIzgara.setSize(sf::Vector2f(IZGARA_BOYUTU, IZGARA_BOYUTU));
    arkaPlanIzgara.setFillColor(sf::Color(187, 173, 160));
    arkaPlanIzgara.setPosition(IZGARA_X, IZGARA_Y);

    // Boş hücrelerin gri renkli karesi
    bosKutuSekil.setSize(sf::Vector2f(KUTU_BOYUTU, KUTU_BOYUTU));
    bosKutuSekil.setFillColor(sf::Color(205, 193, 180));

    // İlk başta tüm harita bomboş 
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
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
void Board::solaKaydir() {
    bool hareketEttiMi = false; // Eğer hiçbir kutu oynamadıysa yeni sayı doğmasın diye kontrol

    for (int satir = 0; satir < 4; satir++) {
        // sola sıkıştırma
        for (int sutun = 0; sutun < 4; sutun++) {
            if (harita[satir][sutun] == nullptr) {
                // Eğer burası boşsa, sağındaki ilk dolu kutuyu bulup buraya çekiyoruz
                for (int k = sutun + 1; k < 4; k++) {
                    if (harita[satir][k] != nullptr) {
                        harita[satir][sutun] = harita[satir][k];
                        harita[satir][k] = nullptr;
                        hareketEttiMi = true;
                        break;
                    }
                }
            }
        }

        //birleştirme
        for (int sutun = 0; sutun < 3; sutun++) {
            // Yan yana iki kutu da doluysa ve değerleri eşitse
            if (harita[satir][sutun] != nullptr && harita[satir][sutun + 1] != nullptr) {
                if (harita[satir][sutun]->getDeger() == harita[satir][sutun + 1]->getDeger()) {
                    
                    // Soldakinin değerini iki katına çıkar 
                    int yeniDeger = harita[satir][sutun]->getDeger() * 2;
                    harita[satir][sutun]->setDeger(yeniDeger);

                    // Sağdaki kutuyu hafızadan sil ve boşalt
                    delete harita[satir][sutun + 1];
                    harita[satir][sutun + 1] = nullptr;

                    hareketEttiMi = true;
                }
            }
        }

        
        // Birleşen kutulardan sonra sağda oluşan yeni boşlukları kapatmak için tekrar sola yanaştırıyoruz
        for (int sutun = 0; sutun < 4; sutun++) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = sutun + 1; k < 4; k++) {
                    if (harita[satir][k] != nullptr) {
                        harita[satir][sutun] = harita[satir][k];
                        harita[satir][k] = nullptr;
                        break;
                    }
                }
            }
        }
    }

    //yeni bir sayı
    if (hareketEttiMi) {
        sayiUret();
    }
}
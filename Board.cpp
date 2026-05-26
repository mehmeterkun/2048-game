#include "Board.hpp"
#include <cstdlib> 
#include <ctime>   
#include <vector>
#include <fstream> // Dosya okuma ve yazma için ekledik

Board::Board(const sf::Font& font) : oyunFontu(font) {
    std::srand(std::time(nullptr));

    // --- SKOR BAŞLANGIÇ AYARLARI ---
    skor = 0;
    enYuksekSkor = 0; 

    // --- REKORU DOSYADAN OKUMA ---
    std::ifstream dosyaOku("rekor.txt");
    if (dosyaOku.is_open()) {
        dosyaOku >> enYuksekSkor;
        dosyaOku.close();
    }
    // ------------------------------

    skorYazisi.setFont(oyunFontu);
    skorYazisi.setCharacterSize(28); // Ekran yerleşimi için ideal boyuta getirildi
    skorYazisi.setFillColor(sf::Color(119, 110, 101));
    // Izgaranın sol köşesine yakın hizalandı
    skorYazisi.setPosition(IZGARA_X + 10, IZGARA_Y - 70); 

    enYuksekSkorYazisi.setFont(oyunFontu);
    enYuksekSkorYazisi.setCharacterSize(28);
    enYuksekSkorYazisi.setFillColor(sf::Color(119, 110, 101));
    // Izgaranın sağ köşesine şık bir şekilde yaslandı
    enYuksekSkorYazisi.setPosition(IZGARA_X + 320, IZGARA_Y - 70);
    // -------------------------------

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

Board::~Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] != nullptr) {
                delete harita[i][j];
            }
        }
    }
}

void Board::update(float deltaTime) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] != nullptr) {
                harita[i][j]->update(deltaTime);
            }
        }
    }
}

void Board::konumlariGuncelle() {
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
            if (harita[satir][sutun] != nullptr) {
                float hedefX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
                float hedefY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);
                
                harita[satir][sutun]->setPozisyon(hedefX, hedefY, KUTU_BOYUTU);
                harita[satir][sutun]->setTarget(hedefX, hedefY);
            }
        }
    }
}

void Board::ciz(sf::RenderWindow& pencere) {
    // Sabit arka plan paneli
    pencere.draw(arkaPlanIzgara);

    // --- SKOR YAZILARINI GÜNCELLE VE ÇİZ ---
    skorYazisi.setString("Skor: " + std::to_string(skor));
    enYuksekSkorYazisi.setString("Rekor: " + std::to_string(enYuksekSkor)); // " En Yuksek" yerine temiz "Rekor" yapıldı
    pencere.draw(skorYazisi);
    pencere.draw(enYuksekSkorYazisi);
    // ---------------------------------------

    // 1. Önce 16 tane boş gri kareyi çizelim
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
            float kutuX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
            float kutuY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);
            bosKutuSekil.setPosition(kutuX, kutuY);
            pencere.draw(bosKutuSekil);
        }
    }

    // 2. Dolu sayı taşlarını matristen bağımsız, kendi piksel konumlarında akıcı çizelim
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
            if (harita[satir][sutun] != nullptr) {
                harita[satir][sutun]->ciz(pencere); 
            }
        }
    }
}

void Board::sayiUret() {
    std::vector<std::pair<int, int>> bosYerler;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] == nullptr) {
                bosYerler.push_back({i, j});
            }
        }
    }

    if (bosYerler.empty()) return;

    int rastgeleIndeks = std::rand() % bosYerler.size();
    int satir = bosYerler[rastgeleIndeks].first;
    int sutun = bosYerler[rastgeleIndeks].second;

    int yeniDeger = (std::rand() % 10 == 0) ? 4 : 2;

    float dogusX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
    float dogusY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);

    harita[satir][sutun] = new Tile(yeniDeger, oyunFontu, dogusX, dogusY, KUTU_BOYUTU);
}

void Board::solaKaydir() {
    bool hareketEttiMi = false;
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
            if (harita[satir][sutun] == nullptr) {
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
        for (int sutun = 0; sutun < 3; sutun++) {
            if (harita[satir][sutun] != nullptr && harita[satir][sutun + 1] != nullptr) {
                if (harita[satir][sutun]->getDeger() == harita[satir][sutun + 1]->getDeger()) {
                    int yeniDeger = harita[satir][sutun]->getDeger() * 2;
                    harita[satir][sutun]->setDeger(yeniDeger);
                    
                    // SKOR VE ANLIK DOSYA REKOR GÜNCELLEME
                    skor += yeniDeger;
                    if (skor > enYuksekSkor) {
                        enYuksekSkor = skor;
                        std::ofstream dosyaYaz("rekor.txt");
                        if (dosyaYaz.is_open()) {
                            dosyaYaz << enYuksekSkor;
                            dosyaYaz.close();
                        }
                    }

                    delete harita[satir][sutun + 1];
                    harita[satir][sutun + 1] = nullptr;
                    hareketEttiMi = true;
                }
            }
        }
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
    if (hareketEttiMi) {
        konumlariGuncelle();
        sayiUret();
    }
}

void Board::sagaKaydir() {
    bool hareketEttiMi = false;
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 3; sutun >= 0; sutun--) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = sutun - 1; k >= 0; k--) {
                    if (harita[satir][k] != nullptr) {
                        harita[satir][sutun] = harita[satir][k];
                        harita[satir][k] = nullptr;
                        hareketEttiMi = true;
                        break;
                    }
                }
            }
        }
        for (int sutun = 3; sutun > 0; sutun--) {
            if (harita[satir][sutun] != nullptr && harita[satir][sutun - 1] != nullptr) {
                if (harita[satir][sutun]->getDeger() == harita[satir][sutun - 1]->getDeger()) {
                    int yeniDeger = harita[satir][sutun]->getDeger() * 2;
                    harita[satir][sutun]->setDeger(yeniDeger);
                    
                    // SKOR VE ANLIK DOSYA REKOR GÜNCELLEME
                    skor += yeniDeger;
                    if (skor > enYuksekSkor) {
                        enYuksekSkor = skor;
                        std::ofstream dosyaYaz("rekor.txt");
                        if (dosyaYaz.is_open()) {
                            dosyaYaz << enYuksekSkor;
                            dosyaYaz.close();
                        }
                    }

                    delete harita[satir][sutun - 1];
                    harita[satir][sutun - 1] = nullptr;
                    hareketEttiMi = true;
                }
            }
        }
        for (int sutun = 3; sutun >= 0; sutun--) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = sutun - 1; k >= 0; k--) {
                    if (harita[satir][k] != nullptr) {
                        harita[satir][sutun] = harita[satir][k];
                        harita[satir][k] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    if (hareketEttiMi) {
        konumlariGuncelle();
        sayiUret();
    }
}

void Board::yukariKaydir() {
    bool hareketEttiMi = false;
    for (int sutun = 0; sutun < 4; sutun++) {
        for (int satir = 0; satir < 4; satir++) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = satir + 1; k < 4; k++) {
                    if (harita[k][sutun] != nullptr) {
                        harita[satir][sutun] = harita[k][sutun];
                        harita[k][sutun] = nullptr;
                        hareketEttiMi = true;
                        break;
                    }
                }
            }
        }
        for (int satir = 0; satir < 3; satir++) {
            if (harita[satir][sutun] != nullptr && harita[satir + 1][sutun] != nullptr) {
                if (harita[satir][sutun]->getDeger() == harita[satir + 1][sutun]->getDeger()) {
                    int yeniDeger = harita[satir][sutun]->getDeger() * 2;
                    harita[satir][sutun]->setDeger(yeniDeger);
                    
                    // SKOR VE ANLIK DOSYA REKOR GÜNCELLEME
                    skor += yeniDeger;
                    if (skor > enYuksekSkor) {
                        enYuksekSkor = skor;
                        std::ofstream dosyaYaz("rekor.txt");
                        if (dosyaYaz.is_open()) {
                            dosyaYaz << enYuksekSkor;
                            dosyaYaz.close();
                        }
                    }

                    delete harita[satir + 1][sutun];
                    harita[satir + 1][sutun] = nullptr;
                    hareketEttiMi = true;
                }
            }
        }
        for (int satir = 0; satir < 4; satir++) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = satir + 1; k < 4; k++) {
                    if (harita[k][sutun] != nullptr) {
                        harita[satir][sutun] = harita[k][sutun];
                        harita[k][sutun] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    if (hareketEttiMi) {
        konumlariGuncelle();
        sayiUret();
    }
}

void Board::asagiKaydir() {
    bool hareketEttiMi = false;
    for (int sutun = 0; sutun < 4; sutun++) {
        for (int satir = 3; satir >= 0; satir--) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = satir - 1; k >= 0; k--) {
                    if (harita[k][sutun] != nullptr) {
                        harita[satir][sutun] = harita[k][sutun];
                        harita[k][sutun] = nullptr;
                        hareketEttiMi = true;
                        break;
                    }
                }
            }
        }
        for (int satir = 3; satir > 0; satir--) {
            if (harita[satir][sutun] != nullptr && harita[satir - 1][sutun] != nullptr) {
                if (harita[satir][sutun]->getDeger() == harita[satir - 1][sutun]->getDeger()) {
                    int yeniDeger = harita[satir][sutun]->getDeger() * 2;
                    harita[satir][sutun]->setDeger(yeniDeger);
                    
                    // SKOR VE ANLIK DOSYA REKOR GÜNCELLEME
                    skor += yeniDeger;
                    if (skor > enYuksekSkor) {
                        enYuksekSkor = skor;
                        std::ofstream dosyaYaz("rekor.txt");
                        if (dosyaYaz.is_open()) {
                            dosyaYaz << enYuksekSkor;
                            dosyaYaz.close();
                        }
                    }

                    delete harita[satir - 1][sutun];
                    harita[satir - 1][sutun] = nullptr;
                    hareketEttiMi = true;
                }
            }
        }
        for (int satir = 3; satir >= 0; satir--) {
            if (harita[satir][sutun] == nullptr) {
                for (int k = satir - 1; k >= 0; k--) {
                    if (harita[k][sutun] != nullptr) {
                        harita[satir][sutun] = harita[k][sutun];
                        harita[k][sutun] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    if (hareketEttiMi) {
        konumlariGuncelle();
        sayiUret();
    }
}
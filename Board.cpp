#include "Board.hpp"
#include <cstdlib> 
#include <ctime>   
#include <vector>

Board::Board(const sf::Font& font) : oyunFontu(font) {
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
                float dogusX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
                float dogusY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);
                harita[satir][sutun] = new Tile(deger, oyunFontu, dogusX, dogusY, KUTU_BOYUTU);
            }
        }
    }
}

void Board::ciz(sf::RenderWindow& pencere) {
    // Sabit arka plan paneli
    pencere.draw(arkaPlanIzgara);

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
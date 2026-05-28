#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

Board::Board(const sf::Font& font) : oyunFontu(font) {
    std::srand(std::time(nullptr));
    skor = 0; enYuksekSkor = 0;

    std::ifstream dosyaOku("rekor.txt");
    if (dosyaOku.is_open()) { dosyaOku >> enYuksekSkor; dosyaOku.close(); }

    skorYazisi.setFont(oyunFontu); skorYazisi.setCharacterSize(28); skorYazisi.setFillColor(sf::Color(119, 110, 101));
    enYuksekSkorYazisi.setFont(oyunFontu); enYuksekSkorYazisi.setCharacterSize(28); enYuksekSkorYazisi.setFillColor(sf::Color(119, 110, 101));
    
    arkaPlanIzgara.setSize(sf::Vector2f(IZGARA_BOYUTU, IZGARA_BOYUTU)); arkaPlanIzgara.setFillColor(sf::Color(187, 173, 160));
    bosKutuSekil.setSize(sf::Vector2f(KUTU_BOYUTU, KUTU_BOYUTU)); bosKutuSekil.setFillColor(sf::Color(205, 193, 180));

    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) harita[i][j] = nullptr;
}

Board::~Board() {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] != nullptr) delete harita[i][j];
}

void Board::update(float deltaTime) {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] != nullptr) harita[i][j]->update(deltaTime);
}

void Board::konumlariGuncelle() {
    for (int satir = 0; satir < 4; satir++) {
        for (int sutun = 0; sutun < 4; sutun++) {
            if (harita[satir][sutun] != nullptr) {
                float hedefX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
                float hedefY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);
                harita[satir][sutun]->setTarget(hedefX, hedefY);
            }
        }
    }
}

void Board::solaKaydir() {
    bool hareket = false;
    for (int i = 0; i < 4; i++) {
        int pos = 0;
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] != nullptr) {
                if (j != pos) { harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; hareket = true; }
                pos++;
            }
        }
        for (int j = 0; j < 3; j++) {
            if (harita[i][j] && harita[i][j+1] && harita[i][j]->getDeger() == harita[i][j+1]->getDeger()) {
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                skor += harita[i][j]->getDeger();
                delete harita[i][j+1]; harita[i][j+1] = nullptr; hareket = true;
            }
        }
        pos = 0;
        for (int j = 0; j < 4; j++) {
            if (harita[i][j] != nullptr) {
                if (j != pos) { harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; }
                pos++;
            }
        }
    }
    if (hareket) { konumlariGuncelle(); sayiUret(); }
}

void Board::sagaKaydir() {
    bool hareket = false;
    for (int i = 0; i < 4; i++) {
        int pos = 3;
        for (int j = 3; j >= 0; j--) {
            if (harita[i][j] != nullptr) {
                if (j != pos) { harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; hareket = true; }
                pos--;
            }
        }
        for (int j = 3; j > 0; j--) {
            if (harita[i][j] && harita[i][j-1] && harita[i][j]->getDeger() == harita[i][j-1]->getDeger()) {
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                skor += harita[i][j]->getDeger();
                delete harita[i][j-1]; harita[i][j-1] = nullptr; hareket = true;
            }
        }
        pos = 3;
        for (int j = 3; j >= 0; j--) {
            if (harita[i][j] != nullptr) {
                if (j != pos) { harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; }
                pos--;
            }
        }
    }
    if (hareket) { konumlariGuncelle(); sayiUret(); }
}

void Board::yukariKaydir() {
    bool hareket = false;
    for (int j = 0; j < 4; j++) {
        int pos = 0;
        for (int i = 0; i < 4; i++) {
            if (harita[i][j] != nullptr) {
                if (i != pos) { harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; hareket = true; }
                pos++;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (harita[i][j] && harita[i+1][j] && harita[i][j]->getDeger() == harita[i+1][j]->getDeger()) {
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                skor += harita[i][j]->getDeger();
                delete harita[i+1][j]; harita[i+1][j] = nullptr; hareket = true;
            }
        }
        pos = 0;
        for (int i = 0; i < 4; i++) {
            if (harita[i][j] != nullptr) {
                if (i != pos) { harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; }
                pos++;
            }
        }
    }
    if (hareket) { konumlariGuncelle(); sayiUret(); }
}

void Board::asagiKaydir() {
    bool hareket = false;
    for (int j = 0; j < 4; j++) {
        int pos = 3;
        for (int i = 3; i >= 0; i--) {
            if (harita[i][j] != nullptr) {
                if (i != pos) { harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; hareket = true; }
                pos--;
            }
        }
        for (int i = 3; i > 0; i--) {
            if (harita[i][j] && harita[i-1][j] && harita[i][j]->getDeger() == harita[i-1][j]->getDeger()) {
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                skor += harita[i][j]->getDeger();
                delete harita[i-1][j]; harita[i-1][j] = nullptr; hareket = true;
            }
        }
        pos = 3;
        for (int i = 3; i >= 0; i--) {
            if (harita[i][j] != nullptr) {
                if (i != pos) { harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; }
                pos--;
            }
        }
    }
    if (hareket) { konumlariGuncelle(); sayiUret(); }
}

void Board::sayiUret() {
    std::vector<std::pair<int, int>> bos;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] == nullptr) bos.push_back({i, j});
    if (bos.empty()) return;
    int r = std::rand() % bos.size();
    float x = IZGARA_X + BOSLUK + bos[r].second * (KUTU_BOYUTU + BOSLUK);
    float y = IZGARA_Y + BOSLUK + bos[r].first * (KUTU_BOYUTU + BOSLUK);
    harita[bos[r].first][bos[r].second] = new Tile((std::rand() % 10 == 0) ? 4 : 2, oyunFontu, x, y, KUTU_BOYUTU);
}

void Board::ciz(sf::RenderWindow& pencere) {
    arkaPlanIzgara.setPosition(IZGARA_X, IZGARA_Y); pencere.draw(arkaPlanIzgara);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            bosKutuSekil.setPosition(IZGARA_X + BOSLUK + j * (KUTU_BOYUTU + BOSLUK), IZGARA_Y + BOSLUK + i * (KUTU_BOYUTU + BOSLUK));
            pencere.draw(bosKutuSekil);
        }
    }
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] != nullptr) harita[i][j]->ciz(pencere);
    
    skorYazisi.setString("Skor: " + std::to_string(skor));
    skorYazisi.setPosition(IZGARA_X, IZGARA_Y - 80.f);
    enYuksekSkorYazisi.setString("Rekor: " + std::to_string(enYuksekSkor));
    enYuksekSkorYazisi.setPosition(IZGARA_X + IZGARA_BOYUTU - enYuksekSkorYazisi.getLocalBounds().width, IZGARA_Y - 80.f);
    pencere.draw(skorYazisi); pencere.draw(enYuksekSkorYazisi);
}

bool Board::oyunBittiMi() {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] == nullptr) return false;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 3; j++) if (harita[i][j]->getDeger() == harita[i][j+1]->getDeger()) return false;
    for (int j = 0; j < 4; j++) for (int i = 0; i < 3; i++) if (harita[i][j]->getDeger() == harita[i+1][j]->getDeger()) return false;
    return true;
}
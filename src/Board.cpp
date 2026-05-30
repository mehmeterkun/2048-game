#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

//Board sınıfı tahtayı, skorları ve ızgarayı ayarlar
Board::Board(const sf::Font& font) : oyunFontu(font){
    std::srand(std::time(nullptr)); // Rastgele sayı için
    skor = 0; enYuksekSkor = 0; ulasildi2048 = false;

    //Kayıtlı yüksek skoru dosyadan okur
    std::ifstream dosyaOku("rekor.txt");
    if (dosyaOku.is_open()) { dosyaOku >> enYuksekSkor; dosyaOku.close(); }
    // Skor gösterge yazılarının font ve renk ayarları
    skorYazisi.setFont(oyunFontu); skorYazisi.setCharacterSize(28); skorYazisi.setFillColor(sf::Color(119, 110, 101));
    enYuksekSkorYazisi.setFont(oyunFontu); enYuksekSkorYazisi.setCharacterSize(28); enYuksekSkorYazisi.setFillColor(sf::Color(119, 110, 101));   
    //Arka plan ızgara ve kutucuk şekillerinin görünüm ayarları
    arkaPlanIzgara.setSize(sf::Vector2f(IZGARA_BOYUTU, IZGARA_BOYUTU)); arkaPlanIzgara.setFillColor(sf::Color(187, 173, 160));
    bosKutuSekil.setSize(sf::Vector2f(KUTU_BOYUTU, KUTU_BOYUTU)); bosKutuSekil.setFillColor(sf::Color(205, 193, 180));
    //Oyun ızgarasını başlangıçta boşalt
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) harita[i][j] = nullptr;
}

// Board yıkıcısı: Bellekte ayrılan Tile nesnelerini temizler (Memory leak önleme)
Board::~Board(){
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] != nullptr) delete harita[i][j];
}

//Oyun tahtasındaki tüm kutucukların güncellenmesini tetikler 
void Board::update(float deltaTime){
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] != nullptr) harita[i][j]->update(deltaTime);
}

// Kutuların ızgara üzerindeki hedef koordinatlarını hesaplar
void Board::konumlariGuncelle(){
    for(int satir = 0; satir < 4; satir++){
        for(int sutun = 0; sutun < 4; sutun++){
            if(harita[satir][sutun] != nullptr){
                float hedefX = IZGARA_X + BOSLUK + sutun * (KUTU_BOYUTU + BOSLUK);
                float hedefY = IZGARA_Y + BOSLUK + satir * (KUTU_BOYUTU + BOSLUK);
                harita[satir][sutun]->setTarget(hedefX, hedefY);
            }
        }
    }
}

// Sol tuş
void Board::solaKaydir(){
    bool hareket = false;
    // Kutucukları sol boşluklara sıkıştır
    for(int i = 0; i < 4; i++){
        int pos = 0;
        for(int j = 0; j < 4; j++){
            if(harita[i][j] != nullptr){
                if(j != pos) { harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; hareket = true; 
                }
                pos++;
            }
        }
        //Aynı değerli yan yana kutucukları birleştir
        for(int j = 0; j < 3; j++){
            if(harita[i][j] && harita[i][j+1] && harita[i][j]->getDeger() == harita[i][j+1]->getDeger()){
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                if(harita[i][j]->getDeger() == 2048) ulasildi2048 = true;
                skor += harita[i][j]->getDeger();
                skorKontrolEt();
                delete harita[i][j+1]; harita[i][j+1] = nullptr; hareket = true;
            }
        }
        // Birleştirme sonrası oluşan boşlukları tekrar doldur
        pos = 0;
        for(int j = 0; j < 4; j++){
            if(harita[i][j]!= nullptr){
                if(j != pos){ 
                    harita[i][pos] = harita[i][j]; harita[i][j] = nullptr;
                 }
                pos++;
            }
        }
    }
    if(hareket){ 
        konumlariGuncelle(); sayiUret(); 
    }
}

// Sağ tuş
void Board::sagaKaydir(){
    bool hareket = false;
    for(int i = 0; i < 4; i++){
        int pos = 3;
        for(int j = 3; j >= 0; j--){
            if(harita[i][j] != nullptr) {
                if(j != pos){ 
                    harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; hareket = true; 
                }
                pos--;
            }
        }
        for(int j = 3; j > 0; j--){
            if(harita[i][j] && harita[i][j-1] && harita[i][j]->getDeger() == harita[i][j-1]->getDeger()){
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                if (harita[i][j]->getDeger() == 2048) ulasildi2048 = true;
                skor += harita[i][j]->getDeger();
                skorKontrolEt();
                delete harita[i][j-1]; harita[i][j-1] = nullptr; hareket = true;
            }
        }
        pos = 3;
        for(int j = 3; j >= 0; j--){
            if(harita[i][j] != nullptr){
                if (j != pos) { harita[i][pos] = harita[i][j]; harita[i][j] = nullptr; }
                pos--;
            }
        }
    }
    if(hareket){
         konumlariGuncelle(); sayiUret(); 
        }
}

// Yukarı tuş
void Board::yukariKaydir(){
    bool hareket = false;
    for(int j = 0; j < 4; j++){
        int pos = 0;
        for(int i = 0; i < 4; i++){
            if(harita[i][j] != nullptr){
                if(i != pos){
                     harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; hareket = true; 
                    }
                pos++;
            }
        }
        for(int i = 0; i < 3; i++){
            if(harita[i][j] && harita[i+1][j] && harita[i][j]->getDeger() == harita[i+1][j]->getDeger()){
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                if(harita[i][j]->getDeger() == 2048) ulasildi2048 = true;
                skor += harita[i][j]->getDeger();
                skorKontrolEt();
                delete harita[i+1][j]; harita[i+1][j] = nullptr; hareket = true;
            }
        }
        pos = 0;
        for(int i = 0; i < 4; i++){
            if(harita[i][j] != nullptr){
                if(i != pos){ 
                    harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; 
                }
                pos++;
            }
        }
    }
    if(hareket){
         konumlariGuncelle(); sayiUret(); 
        }
}

// Aşağı tuş
void Board::asagiKaydir(){
    bool hareket = false;
    for(int j = 0; j < 4; j++){
        int pos = 3;
        for(int i = 3; i >= 0; i--){
            if(harita[i][j] != nullptr){
                if(i != pos){
                     harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; hareket = true; 
                    }
                pos--;
            }
        }
        for(int i = 3; i > 0; i--){
            if(harita[i][j] && harita[i-1][j] && harita[i][j]->getDeger() == harita[i-1][j]->getDeger()){
                harita[i][j]->setDeger(harita[i][j]->getDeger() * 2);
                if(harita[i][j]->getDeger() == 2048) ulasildi2048 = true;
                skor += harita[i][j]->getDeger();
                skorKontrolEt();
                delete harita[i-1][j]; harita[i-1][j] = nullptr; hareket = true;
            }
        }
        pos = 3;
        for(int i = 3; i >= 0; i--){
            if(harita[i][j] != nullptr){
                if(i != pos){
                     harita[pos][j] = harita[i][j]; harita[i][j] = nullptr; 
                    }
                pos--;
            }
        }
    }
    if(hareket){
         konumlariGuncelle(); sayiUret();
    }
}

//Tahtadaki boş bir yere rastgele 2 veya 4 değerinde kutu üretir
void Board::sayiUret(){
    std::vector<std::pair<int, int>> bos;
    for(int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] == nullptr) bos.push_back({i, j});
    if (bos.empty()) return;
    
    int r = std::rand() % bos.size();
    float x = IZGARA_X + BOSLUK + bos[r].second * (KUTU_BOYUTU + BOSLUK);
    float y = IZGARA_Y + BOSLUK + bos[r].first * (KUTU_BOYUTU + BOSLUK);
    // %10 ihtimalle 4, %90 ihtimalle 2 
    harita[bos[r].first][bos[r].second] = new Tile((std::rand() % 10 == 0) ? 4 : 2, oyunFontu, x, y, KUTU_BOYUTU);
}

//Tahtayı, ızgarayı ve skorları ekrana çizer
void Board::ciz(sf::RenderWindow& pencere){
    arkaPlanIzgara.setPosition(IZGARA_X, IZGARA_Y); pencere.draw(arkaPlanIzgara);
    //Izgara üzerindeki boş hücre kutularını çiz
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            bosKutuSekil.setPosition(IZGARA_X + BOSLUK + j * (KUTU_BOYUTU + BOSLUK), IZGARA_Y + BOSLUK + i * (KUTU_BOYUTU + BOSLUK));
            pencere.draw(bosKutuSekil);
        }
    }
    // Mevcut kutuları çiz
    for(int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] != nullptr) harita[i][j]->ciz(pencere);
    
    //Skor yazılarını güncelle ve yaz
    skorYazisi.setString("Skor: " + std::to_string(skor));
    skorYazisi.setPosition(IZGARA_X, IZGARA_Y - 80.f);
    enYuksekSkorYazisi.setString("Rekor: " + std::to_string(enYuksekSkor));
    enYuksekSkorYazisi.setPosition(IZGARA_X + IZGARA_BOYUTU - enYuksekSkorYazisi.getLocalBounds().width, IZGARA_Y - 80.f);
    pencere.draw(skorYazisi); pencere.draw(enYuksekSkorYazisi);
}

// Oyunda yapılabilecek herhangi bir hamle kalıp kalmadığını kontrol eder
bool Board::oyunBittiMi() {
    // Boş alan varsa oyun bitmemiştir
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (harita[i][j] == nullptr) return false;
    // Yatay veya dikey yönde birleştirilebilecek komşu kutu varsa oyun bitmemiştir
    for (int i = 0; i < 4; i++) for (int j = 0; j < 3; j++) if (harita[i][j]->getDeger() == harita[i][j+1]->getDeger()) return false;
    for (int j = 0; j < 4; j++) for (int i = 0; i < 3; i++) if (harita[i][j]->getDeger() == harita[i+1][j]->getDeger()) return false;
    return true; // Hamle kalmadı
}
void Board::skorKontrolEt() {
    if (skor > enYuksekSkor) {
        enYuksekSkor = skor;
        std::ofstream dosyaYaz("rekor.txt");
        if (dosyaYaz.is_open()) {
            dosyaYaz << enYuksekSkor;
            dosyaYaz.close();
        }
    }
}
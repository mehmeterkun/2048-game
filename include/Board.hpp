#ifndef BOARD_HPP
#define BOARD_HPP
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

//Board (Oyun Tahtası) sınıfı: ızgarayı, skor yönetimini ve oyun mantığını yönetir
class Board {
private:
    Tile* harita[4][4];       //oyun ızgarasını tutan pointer dizisi
    sf::Font oyunFontu;       //Oyunda kullanılan yazı tipi nesnesi

    sf::RectangleShape arkaPlanIzgara; //Ana ızgara arka planı
    sf::RectangleShape bosKutuSekil;   //Boş hücreleri temsil eden kutucuklar

    //Izgara ve kutuların boyutlari
    const float IZGARA_BOYUTU = 500.0f;
    const float KUTU_BOYUTU = 100.0f;
    const float BOSLUK = 20.0f;
    const float IZGARA_X = 350.0f;
    const float IZGARA_Y = 130.0f;

    //Kutucukların hedef koordinatlarını hesaplayan yardımcı fonksiyon
    void konumlariGuncelle();

     
    int skor;                 // Mevcut oyun skoru
    int enYuksekSkor;         // Kayıtlı yüksek skor
    sf::Text skorYazisi;      // Ekranda gösterilecek skor metni
    sf::Text enYuksekSkorYazisi; // Ekranda gösterilecek rekor metni
    
    bool ulasildi2048 = false;
    void skorKontrolEt();
     

public:
    // Fontu alır ve ızgarayı, skorları başlatır
    Board(const sf::Font& font);
    
    // Bellekteki Tile nesnelerini temizler
    ~Board();
    
    // Oyunun bitip bitmediğini kontrol eden mantık
    bool oyunBittiMi();
    
    // Skor değerlerini dışarıya döndüren fonksiyonlar
    int getSkor() const { return skor; }
    int getEnYuksekSkor() const { return enYuksekSkor; }
    
    // Tahtayı ve üzerindeki kutuları ekrana çizer
    void ciz(sf::RenderWindow& pencere);
    
    // Rastgele bir boş hücreye yeni kutucuk üretir
    void sayiUret();
    
    // Animasyonlar ve konum güncellemeleri için çağrılan fonksiyon
    void update(float deltaTime);

    // Dört yöne kaydırma işlemleri 
    void solaKaydir();
    void sagaKaydir();
    void yukariKaydir();
    void asagiKaydir();
    bool getUlasildi2048() const { return ulasildi2048; }
};

#endif
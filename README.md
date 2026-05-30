# 2048 Oyun Projesi

Bu proje, YZM104 Programlama II dersi kapsamında geliştirilmiş, C++ ve SFML kütüphanesi kullanılarak yazılmış bir 2048 bulmaca oyunudur.

## 1. Proje Hakkında
2048, 4x4'lük bir ızgara üzerinde, aynı değerdeki kutucukları birleştirerek 2048 değerine ulaşmayı hedefleyen stratejik bir bulmaca oyunudur. Proje, nesne yönelimli programlama (OOP) prensipleri benimsenerek geliştirilmiştir.

## 2. Özellikler
* **Dinamik Oyun Akışı:** Rastgele sayı üretimi ve kutucuk birleştirme mantığı.
* **Modüler Mimari:** `Board` ve `Tile` sınıfları ile birbirinden ayrılmış temiz kod yapısı.
* **Skor Takibi:** Oyun içi en yüksek skorun kayıt altına alınması.
* **Akıcı Arayüz:** SFML kütüphanesi ile 60 FPS hedefli görsel deneyim.

## 3. Teknoloji Yığını

| Kategori | Teknoloji | Açıklama |
| :--- | :--- | :--- |
| **Programlama Dili** | C++ (C++17) | Ana oyun mantığı ve sınıf yönetimi |
| **Grafik Kütüphanesi** | SFML 2.5 | Görsel çizim, font yönetimi ve pencereleme |
| **Derleme Sistemi** | Makefile | Projenin otomatik derlenmesi ve linklenmesi |
| **Geliştirme Ortamı** | VS Code | Proje geliştirme ve hata ayıklama |

## 4. Kontroller
* **Yön Tuşları:** Kutucukları yukarı, aşağı, sağa veya sola hareket ettirir.
* **ENTER:** Menüden oyunu başlatır.
* **ESC/SPACE:** Oyundan çıkış yapar.

## 5. Kurulum ve Çalıştırma

### Ön Gereksinimler
* C++ Derleyicisi (g++)
* SFML Kütüphanesi

### Kurulum Adımları
1. Projeyi bilgisayarınıza klonlayın.
2. Terminali ana dizinde açın.
3. Derlemek için:
   ```bash
   make
2. Oyunu başlatmak için:
   ./2048
3. Derleme dosyalarını temizlemek için:
   make clean
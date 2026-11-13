# 15 Days Until Survive - Mars Kolonisi Yaşam Destek Simülatörü

Bu proje, Kırklareli Üniversitesi Yazılım Mühendisliği Bölümü **Algoritma ve Programlama** dersi kapsamında C dili kullanılarak geliştirilmiş metin tabanlı bir hayatta kalma simülasyonudur.

Oyunda Mars'taki küçük bir araştırma istasyonunda tek başına kalan bir mühendisi yönetiyoruz. Temel amacımız; istasyonun oksijen, su, enerji, yedek parça ve modül hasarı gibi değerlerini dengede tutarak kurtarma ekibi gelene kadar **15 gün** boyunca hayatta kalmak.

## Oyunun Temel Mantığı ve Özellikleri

Program tamamen C dilinin temel yapıları (`if-else`, `switch-case`, `for`, `do-while`, aritmetik ve mantıksal operatörler) kullanılarak yazılmıştır.

- **Zorluk Seviyeleri:** Oyun başında **Kolay (K)**, **Normal (N)** veya **Zor (Z)** seviyelerinden biri seçilir. Seçilen zorluğa göre başlangıç kaynakları, kum fırtınasının tur sayısı ve verdiği hasar değişir.
- **Rastgele Olay Sistemi:** Keşif, tamir ve kum fırtınası gibi olaylarda `srand(time(NULL))` ve `rand() % 100` yapısıyla rastgele zar üretilir. Üretilen zar ve karşılaştırıldığı eşik değer her adımda ekranda gösterilir.
- **Zaman Akışı:** Durum raporu (`D`) ve geçersiz girişler hariç her geçerli komut 1 tur harcar. Her **3 turda bir** yeni bir güne geçilir ve gece tüketimi olarak oksijen azalır.
- **Dinamik Hava Kilidi Şifresi:** Hava kilidi şifresi sabit değildir; o anki gün sayısına göre alfabedeki harflerden (`'A' + (gun % 26)`) otomatik hesaplanır ve oyuncuya 3 deneme hakkı verilir.

## Komut Tablosu

Oyun içerisinde büyük/küçük harf fark etmeksizin aşağıdaki tek karakterli komutlar kullanılır:

| Komut | İşlev | Açıklama |
| :--- | :--- | :--- |
| **G / g** | Keşif Görevi | Enerji ve oksijen harcayarak yüzeyde su veya yedek parça arar. |
| **O / o** | Oksijen Üretimi | Elektroliz ile her 2 birim suyu 3 birim oksijene dönüştürür. Tek sayı girilirse 1 birim su depoda kalır. |
| **T / t** | Tamir | Yedek parça kullanarak modül hasarını kademeli olarak (Hafif / Orta / Ağır) onarır. |
| **D / d** | Durum Raporu | Tur harcamadan tüm sistem değerlerini ve kritik uyarıları ekrana yazdırır. |
| **U / u** | Uyu / Dinlen | Enerji ve sağlığı artırır (oksijen 20'nin altındaysa sağlık azalır). |
| **K / k** | Kum Fırtınası | Zorluk seviyesine göre 3, 5 veya 7 turluk kum fırtınasını simüle eder. |
| **H / h** | Hava Kilidi | Kum fırtınasındaki oksijen sızıntısını önlemek için şifre panelini açar. |
| **Q / q** | Çıkış | Simülasyonu sonlandırır ve oyun sonu puan tablosunu gösterir. |

## Puan Hesaplama

Oyun kazanıldığında, kaybedildiğinde veya `Q` komutuyla çıkıldığında aşağıdaki formüle göre toplam puan hesaplanır:

```text
Puan = (Gün x 100) + Sağlık + Oksijen - Modül Hasarı
```

## Derleme ve Çalıştırma

Kodu bilgisayarınızda GCC derleyicisi ile derleyip çalıştırmak için terminalde şu komutları kullanabilirsiniz:

```bash
gcc 15_days_until_survive.c -o 15_days_until_survive
./15_days_until_survive
```

## Hazırlayan

- **Ad Soyad:** Muhammed Taha Kılıç
- **Öğrenci No:** 1260505064
- **Bölüm:** Yazılım Mühendisliği (1. Sınıf)

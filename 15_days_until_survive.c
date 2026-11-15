/*
 * Proje Adi     : 15 Days Until Survive (Mars Kolonisi Yasam Destek Simulatoru)
 * Ders          : Algoritma ve Programlama
 * Hazirlayan    : Muhammed Taha Kilic
 * Ogrenci No    : 1260505064
 * Bolum         : Yazilim Muhendisligi (1. Sinif)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    /* Durum yonetimi degiskenleri */
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 6;
    int yedekParca = 2;
    int modulHasari = 20;
    int kilitMuhurlu = 0;
    int gun = 1;
    int tur = 0;

    /* Zorluk ve kontrol degiskenleri */
    char zorlukSecimi;
    int zorlukGecerli = 0;
    int firtinaTurSayisi = 5;
    int firtinaBazHasar = 10;

    char komut;
    int cikis = 0;
    int turHarca = 0;
    int sonTurKontrol = 0;

    /* Komut ici yardimci degiskenler */
    int zar, esik;
    int kullanilacakSu, artikSu, harcananSu, uretilenOksijen;
    int i, carpan, turHasari, turOksijenKaybi;
    int hasarAlanTurSayisi, toplamKaybedilenSaglik, toplamKaybedilenOksijen;
    char dogruSifre, girilenSifre;
    int kalanHak;
    int puan;

    /* Rastgele sayi uretecini baslatma */
    srand((unsigned int)time(NULL));

    printf("============================================================\n");
    printf("              15 DAYS UNTIL SURVIVE                         \n");
    printf("       MARS KOLONISI YASAM DESTEK SIMULATORU                \n");
    printf("============================================================\n");
    printf("Kurtarma ekibi gelene kadar Mars arastirma istasyonunda\n");
    printf("15 gun boyunca hayatta kalmaya calisin!\n\n");

    /* Zorluk seviyesi secimi (DO-WHILE ve SWITCH-CASE) */
    do {
        printf("Zorluk Seviyesi Seciniz (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorlukSecimi);

        switch (zorlukSecimi) {
            case 'k':
            case 'K':
                saglik = 100;
                enerji = 100;
                oksijen = 100;
                su = 10;
                yedekParca = 3;
                modulHasari = 10;
                firtinaTurSayisi = 3;
                firtinaBazHasar = 8;
                zorlukGecerli = 1;
                printf("\n[BILGI] Kolay zorluk seviyesi secildi. Baslangic kaynaklari bol, firtina 3 tur.\n");
                break;

            case 'n':
            case 'N':
                saglik = 85;
                enerji = 85;
                oksijen = 85;
                su = 6;
                yedekParca = 2;
                modulHasari = 25;
                firtinaTurSayisi = 5;
                firtinaBazHasar = 12;
                zorlukGecerli = 1;
                printf("\n[BILGI] Normal zorluk seviyesi secildi. Dengeli kaynaklar, firtina 5 tur.\n");
                break;

            case 'z':
            case 'Z':
                saglik = 70;
                enerji = 70;
                oksijen = 75;
                su = 4;
                yedekParca = 1;
                modulHasari = 40;
                firtinaTurSayisi = 7;
                firtinaBazHasar = 15;
                zorlukGecerli = 1;
                printf("\n[BILGI] Zor zorluk seviyesi secildi! Baslangic suyu az, firtina 7 tur ve daha yikici.\n");
                break;

            default:
                printf("[UYARI] Gecersiz zorluk seviyesi girdiniz! Lutfen K, N veya Z giriniz.\n\n");
                zorlukGecerli = 0;
                break;
        }
    } while (zorlukGecerli == 0);

    /* Ana oyun komut dinleme dongusu (DO-WHILE) */
    do {
        printf("\n------------------------------------------------------------\n");
        printf("[GUN: %d/15 | TUR: %d] Saglik:%d | Enerji:%d | Oksijen:%d | Su:%d | Parca:%d | Hasar:%d | Kilit:%s\n",
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari,
               (kilitMuhurlu == 1) ? "Muhurlu" : "Acik");
        printf("Komutlar: [G]Kesif [O]Oksijen [T]Tamir [D]Durum [U]Uyu [K]Firtina [H]Hava Kilidi [Q]Cikis\n");
        printf("Komutunuzu girin: ");
        scanf(" %c", &komut);

        turHarca = 0;

        /* Komut sistemi (SWITCH-CASE ve Fall-Through) */
        switch (komut) {
            case 'g':
            case 'G':
                /* Kesif gorevi */
                if (enerji < 15) {
                    printf("[IPTAL] Kesif gorevi icin yeterli enerjiniz yok! (Gereken: 15, Mevcut: %d)\n", enerji);
                } else {
                    enerji = enerji - 15;
                    oksijen = oksijen - 10;
                    turHarca = 1;

                    /* Su ve kaynak bulma esigi enerji ve oksijen durumuna gore belirlenir */
                    if (enerji > 40 && oksijen > 30) {
                        esik = 65;
                    } else {
                        esik = 40;
                    }

                    zar = rand() % 100;
                    printf("[KESIF] Enerji -15, Oksijen -10 harcandi.\n");

                    if (zar < esik) {
                        printf("Zar: %d / Esik: %d -> BASARILI\n", zar, esik);
                        /* Basarili kesifte mod operatoruyle su veya yedek parca ayrimi */
                        if (zar % 2 == 0) {
                            su = su + 4;
                            printf("[SONUC 1 - SU BULUNDU] Yuzey altinda buz kutlesi buldunuz! (+4 Birim Su)\n");
                        } else {
                            yedekParca = yedekParca + 1;
                            printf("[SONUC 2 - PARCA BULUNDU] Eski kesif aracindan yedek parca soktunuz! (+1 Yedek Parca)\n");
                        }
                    } else {
                        printf("Zar: %d / Esik: %d -> BASARISIZ\n", zar, esik);
                        printf("[SONUC 3 - ELI BOS] Kayalik bolgede kullanilabilir kaynak bulamadiniz.\n");
                    }

                    /* Yaralanma kontrolu (zar < 10 || modulHasari > 70) */
                    if (zar < 10 || modulHasari > 70) {
                        saglik = saglik - 10;
                        printf("[TEHLIKE] Kesif sirasinda radyasyon/kaza nedeniyle yaralandiniz! (-10 Saglik)\n");
                    }
                }
                break;

            case 'o':
            case 'O':
                /* Oksijen uretimi */
                if (enerji < 10) {
                    printf("[IPTAL] Oksijen uretimi icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else if (su < 2) {
                    printf("[IPTAL] Elektroliz icin en az 2 birim su gereklidir! (Mevcut Su: %d)\n", su);
                } else {
                    printf("Oksijen uretimi icin kac birim su kullanmak istiyorsunuz? (Mevcut Su: %d): ", su);
                    scanf("%d", &kullanilacakSu);

                    if (kullanilacakSu > su) {
                        printf("[IPTAL] Mevcut sudan (%d) daha fazla miktar giremezsiniz!\n", su);
                    } else if (kullanilacakSu < 2) {
                        printf("[IPTAL] Donusum icin en az 2 birim su girmelisiniz!\n");
                    } else {
                        /* Mod (%) operatoru ile cift/tek kontrolu */
                        artikSu = kullanilacakSu % 2;
                        harcananSu = kullanilacakSu - artikSu;
                        uretilenOksijen = (harcananSu / 2) * 3;

                        su = su - harcananSu;
                        oksijen = oksijen + uretilenOksijen;
                        enerji = enerji - 10;
                        turHarca = 1;

                        zar = rand() % 100;
                        esik = 100;
                        printf("Zar: %d / Esik: %d -> BASARILI\n", zar, esik);

                        if (artikSu == 1) {
                            printf("[OKSIJEN URETIMI] Girilen %d birim su tek sayidir; 1 birimi artik olarak depoda kaldi.\n", kullanilacakSu);
                        } else {
                            printf("[OKSIJEN URETIMI] Girilen %d birim su cift sayidir; tamami kullanildi.\n", kullanilacakSu);
                        }
                        printf("%d birim su -> +%d birim oksijen uretildi (Enerji -10).\n", harcananSu, uretilenOksijen);
                    }
                }
                break;

            case 't':
            case 'T':
                /* Tamir gorevi */
                if (yedekParca <= 0) {
                    printf("[IPTAL] Yedek parcaniz yok! Tamir yapilamaz.\n");
                } else if (enerji < 10) {
                    printf("[IPTAL] Tamir yapmak icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else if (modulHasari == 0) {
                    printf("[BILGI] Istasyon modulleri tamamen saglam (Hasar: 0). Tamire gerek yok.\n");
                } else {
                    zar = rand() % 100;
                    esik = 90;
                    printf("Zar: %d / Esik: %d -> %s\n", zar, esik, (zar < esik) ? "BASARILI" : "KISMI ONARIM");

                    /* IF - ELSE IF - ELSE zinciri ile 3 hasar kademesi */
                    if (modulHasari <= 30) {
                        /* 0-30 Hafif Hasar Kademesi */
                        yedekParca = yedekParca - 1;
                        modulHasari = modulHasari - 15;
                        enerji = enerji - 10;
                        printf("[TAMIR - HAFIF KADEME (0-30)] 1 yedek parca ve 10 enerji harcandi, 15 birim hasar onarildi.\n");
                    } else if (modulHasari <= 70) {
                        /* 31-70 Orta Hasar Kademesi */
                        if (yedekParca >= 2) {
                            yedekParca = yedekParca - 2;
                            modulHasari = modulHasari - 30;
                            printf("[TAMIR - ORTA KADEME (31-70)] 2 yedek parca harcandi, 30 birim hasar onarildi.\n");
                        } else {
                            yedekParca = yedekParca - 1;
                            modulHasari = modulHasari - 20;
                            printf("[TAMIR - ORTA KADEME (31-70)] Tek parca mevcut oldugu icin 1 parca ile 20 birim hasar onarildi.\n");
                        }
                        enerji = enerji - 15;
                    } else {
                        /* 71-100 Agir Hasar Kademesi */
                        if (yedekParca >= 3) {
                            yedekParca = yedekParca - 3;
                            modulHasari = modulHasari - 45;
                            printf("[TAMIR - AGIR KADEME (71-100)] 3 yedek parca harcandi, 45 birim kritik hasar onarildi.\n");
                        } else {
                            printf("[TAMIR - AGIR KADEME (71-100)] Mevcut %d yedek parca kullanildi, %d birim hasar onarildi.\n",
                                   yedekParca, yedekParca * 15);
                            modulHasari = modulHasari - (yedekParca * 15);
                            yedekParca = 0;
                        }
                        enerji = enerji - 20;
                    }
                    turHarca = 1;
                }
                break;

            case 'd':
            case 'D':
                /* Durum raporu (Tur harcamaz) */
                printf("\n================ DETAYLI DURUM RAPORU ================\n");
                printf("Gun Sayisi         : %d / 15\n", gun);
                printf("Toplam Komut (Tur) : %d\n", tur);
                printf("Saglik             : %d / 100\n", saglik);
                printf("Enerji             : %d / 100\n", enerji);
                printf("Oksijen            : %d / 100\n", oksijen);
                printf("Su Miktari         : %d birim\n", su);
                printf("Yedek Parca Sayisi : %d adet\n", yedekParca);
                printf("Modul Hasari       : %d / 100\n", modulHasari);
                printf("Hava Kilidi Durumu : %s (%d)\n", (kilitMuhurlu == 1) ? "Muhurlu" : "Acik", kilitMuhurlu);
                printf("------------------------------------------------------\n");

                /* Kritik seviye uyarilari (Her deger icin ayri IF) */
                if (oksijen < 25) {
                    printf("[KRITIK UYARI] Oksijen seviyesi cok dusuk (%d < 25)! Acilen O komutuyla oksijen uretin!\n", oksijen);
                }
                if (saglik < 30) {
                    printf("[KRITIK UYARI] Saglik seviyesi kritik (%d < 30)! Dinlenmeniz gerekiyor!\n", saglik);
                }
                if (enerji < 20) {
                    printf("[KRITIK UYARI] Enerji tukenmek uzere (%d < 20)! U komutuyla dinlenin!\n", enerji);
                }
                if (modulHasari > 70) {
                    printf("[KRITIK UYARI] Modul hasari tehlikeli boyutta (%d > 70)! T komutuyla tamir yapin!\n", modulHasari);
                }

                /* Tum degerler guvenli araliktaysa && ile birlestirilmis tek kosul */
                if (oksijen >= 25 && saglik >= 30 && enerji >= 20 && modulHasari <= 70) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                printf("======================================================\n");
                turHarca = 0;
                break;

            case 'u':
            case 'U':
                /* Uyu / Dinlen (Ic ice IF yapisi zorunlu) */
                zar = rand() % 100;
                esik = 50;
                printf("Zar: %d / Esik: %d -> %s\n", zar, esik, (zar < esik) ? "DERIN UYKU" : "NORMAL UYKU");

                enerji = enerji + 25;
                oksijen = oksijen - 8;

                /* Ic ice IF ile oksijen < 20 kontrolu */
                if (enerji > 0) {
                    if (oksijen < 20) {
                        saglik = saglik - 10;
                        printf("[UYARI] Oksijen 20'nin altinda (%d)! Yetersiz oksijenle uyudugunuz icin saglik azaldi (-10 Saglik, +25 Enerji, -8 Oksijen).\n", oksijen);
                    } else {
                        saglik = saglik + 15;
                        printf("[DINLENME] Uyudunuz ve dinlendiniz (+25 Enerji, +15 Saglik, -8 Oksijen).\n");
                    }
                }
                turHarca = 1;
                break;

            case 'k':
            case 'K':
                /* Kum firtinasini FOR dongusu ile simule et */
                if (enerji < 10) {
                    printf("[IPTAL] Firtina protokolu icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else {
                    enerji = enerji - 10;
                    turHarca = 1;
                    hasarAlanTurSayisi = 0;
                    toplamKaybedilenSaglik = 0;
                    toplamKaybedilenOksijen = 0;

                    printf("\n[KUM FIRTINASI BASLADI] Zorluk seviyesine gore %d tur surecek!\n", firtinaTurSayisi);

                    for (i = 1; i <= firtinaTurSayisi; i++) {
                        zar = rand() % 100;
                        esik = 65;

                        /* Cift numarali turlarda ruzgar siddetlenir ve hasar 2 katina cikar (mod operatoru) */
                        if (i % 2 == 0) {
                            carpan = 2;
                            printf("\n--- Firtina Turu %d (CIFT TUR - Ruzgar Siddetlendi! Hasar x2) ---\n", i);
                        } else {
                            carpan = 1;
                            printf("\n--- Firtina Turu %d ---\n", i);
                        }

                        /* Zar < 30 ise oksijen sizintisi olayi */
                        if (zar < 30) {
                            printf("Zar: %d / Esik: 30 -> OKSIJEN SIZINTISI TEHLIKESI\n", zar);
                            if (kilitMuhurlu == 1) {
                                printf("[CONTINUE] Hava kilidi muhurlu (kilitMuhurlu == 1)! Oksijen sizintisi bu tur atlandi.\n");
                                continue;
                            }
                            turOksijenKaybi = 6 * carpan;
                            oksijen = oksijen - turOksijenKaybi;
                            toplamKaybedilenOksijen = toplamKaybedilenOksijen + turOksijenKaybi;
                            hasarAlanTurSayisi = hasarAlanTurSayisi + 1;
                            printf("[HASAR] Hava kilidi acik oldugu icin %d birim oksijen sizdi!\n", turOksijenKaybi);
                        } else if (zar < esik) {
                            printf("Zar: %d / Esik: %d -> BASARISIZ (Firtina Darbesi)\n", zar, esik);
                            turHasari = (firtinaBazHasar / 2) * carpan;
                            saglik = saglik - turHasari;
                            modulHasari = modulHasari + (5 * carpan);
                            toplamKaybedilenSaglik = toplamKaybedilenSaglik + turHasari;
                            hasarAlanTurSayisi = hasarAlanTurSayisi + 1;
                            printf("[HASAR] Firtinada %d saglik kaybettiniz, modul hasari +%d artti.\n", turHasari, 5 * carpan);
                        } else {
                            printf("Zar: %d / Esik: %d -> BASARILI (Korunma)\n", zar, esik);
                            printf("[GUVENLI] Bu firtina turundan zararsiz korundunuz.\n");
                        }

                        /* Saglik veya oksijen 0'a duserse dongu BREAK ile derhal sonlandirilir */
                        if (saglik <= 0 || oksijen <= 0) {
                            printf("[KRITIK] Firtina sirasinda yasamsal degerler 0'a dustu! Dongu BREAK ile sonlandiriliyor!\n");
                            break;
                        }
                    }

                    printf("\n--- KUM FIRTINASI OZETI ---\n");
                    printf("Hasar Alinan Tur Sayisi   : %d / %d\n", hasarAlanTurSayisi, firtinaTurSayisi);
                    printf("Toplam Kaybedilen Saglik  : %d\n", toplamKaybedilenSaglik);
                    printf("Toplam Kaybedilen Oksijen : %d\n", toplamKaybedilenOksijen);
                    printf("---------------------------\n");
                }
                break;

            case 'h':
            case 'H':
                /* Hava kilidi sifresi (DO-WHILE dogrulama dongusu) */
                if (enerji < 5) {
                    printf("[IPTAL] Hava kilidi panelini calistirmak icin en az 5 enerji gerekli! (Mevcut: %d)\n", enerji);
                } else if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten muhurlu durumda!\n");
                } else {
                    /* Sifre o anki gun sayisindan aritmetik olarak turetilir */
                    dogruSifre = (char)('A' + (gun % 26));
                    kalanHak = 3;
                    turHarca = 1;

                    zar = rand() % 100;
                    esik = 50;
                    printf("Zar: %d / Esik: %d -> GUVENLIK PANELI AKTIF\n", zar, esik);
                    printf("\n[HAVA KILIDI SIFRE PANELI]\n");
                    printf("Ipucu: Sifre, Ingiliz alfabesinde 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);

                    /* DO-WHILE dongusu: hem sifrenin yanlis olmasini hem deneme hakkinin bitmemis olmasini tek mantiksal ifadede kontrol eder */
                    do {
                        printf("Sifre tahmininizi girin (A-Z, Kalan Hak: %d): ", kalanHak);
                        scanf(" %c", &girilenSifre);

                        /* Kucuk harf girildiyse buyuk harfe donusturme */
                        if (girilenSifre >= 'a' && girilenSifre <= 'z') {
                            girilenSifre = (char)(girilenSifre - ('a' - 'A'));
                        }

                        if (girilenSifre != dogruSifre) {
                            enerji = enerji - 5;
                            if (enerji < 0) {
                                enerji = 0;
                            }
                            kalanHak = kalanHak - 1;

                            if (girilenSifre < dogruSifre) {
                                printf("[YANLIS] Enerji -5 azaldi. Ipucu: Alfabede ILERI git!\n");
                            } else {
                                printf("[YANLIS] Enerji -5 azaldi. Ipucu: Alfabede GERI git!\n");
                            }
                        }
                    } while (girilenSifre != dogruSifre && kalanHak > 0);

                    if (girilenSifre == dogruSifre) {
                        kilitMuhurlu = 1;
                        printf("[BASARILI] Dogru sifre (%c)! Hava kilidi basariyla muhurlendi (kilitMuhurlu = 1).\n", dogruSifre);
                    } else {
                        modulHasari = modulHasari + 20;
                        printf("[BASARISIZ] 3 deneme hakkiniz da bitti! Dogru sifre '%c' idi. Basinc kaybi nedeniyle modul hasari +20 artti!\n", dogruSifre);
                    }
                }
                break;

            case 'q':
            case 'Q':
                /* Cikis komutu */
                printf("\n[CIKIS] Simulasyondan cikis komutu (Q) verildi...\n");
                cikis = 1;
                turHarca = 0;
                break;

            default:
                /* Tanimsiz komut uyarisi - tur harcamaz */
                printf("[HATA] Tanimsiz bir komut girdiniz ('%c')! Lutfen gecerli bir komut giriniz (Tur harcanmadi).\n", komut);
                turHarca = 0;
                break;
        }

        /* Sinirlandirma (0-100 araligi kontrolu - IF yapilariyla) */
        if (saglik > 100) {
            saglik = 100;
        }
        if (saglik < 0) {
            saglik = 0;
        }
        if (enerji > 100) {
            enerji = 100;
        }
        if (enerji < 0) {
            enerji = 0;
        }
        if (oksijen > 100) {
            oksijen = 100;
        }
        if (oksijen < 0) {
            oksijen = 0;
        }
        if (modulHasari > 100) {
            modulHasari = 100;
        }
        if (modulHasari < 0) {
            modulHasari = 0;
        }

        /* Zaman akisi: Gecerli her komut tur sayacini 1 artirir (D, Q ve iptal/tanimsiz haric) */
        if (turHarca == 1 && saglik > 0 && oksijen > 0) {
            tur = tur + 1;

            /* Her 3 turda bir (tur % 3 == 0) yeni bir gun baslar */
            if (tur % 3 == 0 && tur != sonTurKontrol) {
                sonTurKontrol = tur;
                gun = gun + 1;

                if (gun <= 15) {
                    oksijen = oksijen - 8;
                    printf("\n>>> [YENI GUN BASLADI: %d. GUN] Gece boyu oksijen tuketimi: -8 Oksijen.\n", gun);

                    if (modulHasari > 70) {
                        saglik = saglik - 5;
                        printf(">>> [AGIR HASAR ETKISI] Modul hasari 70'in uzerinde oldugu icin -5 Saglik kaybettiniz!\n");
                    }

                    /* Yeni gun basinda tekrar 0-100 sinirlandirma kontrolu */
                    if (oksijen < 0) {
                        oksijen = 0;
                    }
                    if (saglik < 0) {
                        saglik = 0;
                    }
                }
            }
        }

    } while (cikis == 0 && saglik > 0 && oksijen > 0 && gun <= 15);

    /* Oyun Sonu Durum Mesaji */
    printf("\n============================================================\n");
    if (saglik <= 0 || oksijen <= 0) {
        printf("                    OYUN BITTI: KAYBETTINIZ!                \n");
        if (saglik <= 0) {
            printf("Sebep: Saglik degeriniz 0'a dustu. Muhendis hayatini kaybetti.\n");
        } else {
            printf("Sebep: Oksijen tamamen tukendi (0). Yasam destek sistemi durdu.\n");
        }
    } else if (gun > 15) {
        gun = 15; /* 15. gun basariyla tamamlandi */
        printf("           TEBRIKLER! 15 GUN HAYATTA KALDINIZ!              \n");
        printf("Kurtarma ekibi Mars istasyonuna ulasti ve sizi kurtardi!\n");
    } else {
        printf("            SIMULASYON KULLANICI TARAFINDAN SONLANDIRILDI   \n");
    }
    printf("============================================================\n");

    /* Oyun Sonu Raporu ve Aritmetik Puan Hesabi */
    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("\n==================== OYUN SONU RAPORU ======================\n");
    printf("Hayatta Kalinan Gun : %d\n", gun);
    printf("Toplam Gecen Tur    : %d\n", tur);
    printf("Son Saglik Degeri   : %d\n", saglik);
    printf("Son Enerji Degeri   : %d\n", enerji);
    printf("Son Oksijen Degeri  : %d\n", oksijen);
    printf("Kalan Su Miktari    : %d birim\n", su);
    printf("Kalan Yedek Parca   : %d adet\n", yedekParca);
    printf("Son Modul Hasari    : %d\n", modulHasari);
    printf("------------------------------------------------------------\n");
    printf("TOPLAM PUAN         : %d\n", puan);
    printf("(Formul: (Gun x 100) + Saglik + Oksijen - Modul Hasari)\n");
    printf("============================================================\n");

    printf("\nCikmak icin Enter tusuna basin...");
    while (getchar() != '\n');
    getchar();

    return 0;
}

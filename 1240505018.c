#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASTA 100 // Maksimum hasta kapasitesi

// Hasta bilgilerini tutan yap� (struct)
typedef struct {
    char ad[50]; // Hasta ad�
    char soyad[50]; // Hasta soyad�
    int yas; // Hasta ya��
    char cinsiyet; // Hasta cinsiyeti (E/K)
    int oncelik; // �ncelik seviyesi (1: �ok Acil, 2: Orta, 3: Normal)
    int receteNo; // Re�ete numaras�
} Hasta;

Hasta hastaListesi[MAX_HASTA]; // Hasta bilgilerini tutan dizi
int hastaSayisi = 0; // Kay�tl� hasta say�s�
int receteSayaci = 1000; // Re�ete numaras� i�in saya�

// Girdi tamponunu temizleme fonksiyonu
void temizleBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Tampondaki fazla karakterleri temizler
}

// Yeni hasta ekleme fonksiyonu
void hastaEkle() {
    if (hastaSayisi >= MAX_HASTA) { // Hasta kapasitesi kontrol�
        printf("Hasta kapasitesi dolu!\n");
        return;
    }

    Hasta yeniHasta; // Yeni hasta bilgileri i�in ge�ici struct
    printf("Hasta Adi: ");
    scanf("%s", yeniHasta.ad); // Hasta ad�n� al
    printf("Hasta Soyadi: ");
    scanf("%s", yeniHasta.soyad); // Hasta soyad�n� al
    printf("Yas: ");
    scanf("%d", &yeniHasta.yas); // Hasta ya��n� al
    printf("Cinsiyet (E/K): ");
    scanf(" %c", &yeniHasta.cinsiyet); // Hasta cinsiyetini al
    printf("Oncelik Seviyesi (1: Cok Acil, 2: Orta, 3: Normal): ");
    scanf("%d", &yeniHasta.oncelik); // �ncelik seviyesini al

    yeniHasta.receteNo = receteSayaci++; // Re�ete numaras�n� ata ve sayac� art�r
    hastaListesi[hastaSayisi++] = yeniHasta; // Hastay� listeye ekle
    printf("Hasta kaydedildi!\n");
}

// Hasta listesini g�r�nt�leme fonksiyonu
void hastaListele() {
    if (hastaSayisi == 0) { // Kay�tl� hasta yoksa uyar� ver
        printf("Kayitli hasta bulunmamaktadir.\n");
        return;
    }

    printf("\n--- Hasta Listesi ---\n");
    for (int i = 0; i < hastaSayisi; i++) { // T�m hastalar� listele
        printf("Ad: %s, Soyad: %s, Yas: %d, Cinsiyet: %c, Oncelik: %d, Recete No: %d\n",
               hastaListesi[i].ad, hastaListesi[i].soyad, hastaListesi[i].yas,
               hastaListesi[i].cinsiyet, hastaListesi[i].oncelik, hastaListesi[i].receteNo);
    }
}

// Hasta bilgilerini HL7 format�nda dosyaya kaydetme fonksiyonu
void dosyayaHL7Kaydet() {
    FILE *dosya = fopen("hasta_kayitlari.hl7", "w"); // Dosyay� yazma modunda a�
    if (dosya == NULL) { // Dosya a��lamazsa hata ver
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < hastaSayisi; i++) { // Her hasta i�in HL7 format�nda kay�t olu�tur
        // MSH Segmenti: Mesaj ba�l�k bilgileri
        fprintf(dosya, "MSH|^~\\&|HOSPITAL|A|||202310101200||ADT^A01|123456|P|2.5\n");
        // PID Segmenti: Hasta kimlik bilgileri
        fprintf(dosya, "PID|1||%d||%s^%s||%d|%c|||123 Main St^^City^ST^12345^USA\n",
                i + 1, hastaListesi[i].soyad, hastaListesi[i].ad, hastaListesi[i].yas, hastaListesi[i].cinsiyet);
        // PV1 Segmenti: Hasta ziyaret bilgileri
        fprintf(dosya, "PV1|1|E|ER^1^1^HOSPITAL^ER^1^1^HOSPITAL||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        // ORC Segmenti: Re�ete bilgileri
        fprintf(dosya, "ORC|NW|%d^HOSPITAL|||CM||||202310101200\n\n", hastaListesi[i].receteNo);
    }

    fclose(dosya); // Dosyay� kapat
    printf("Hasta kayitlari HL7 formatinda dosyaya kaydedildi!\n");
}

// HL7 format�ndaki kay�tlar� dosyadan okuma fonksiyonu
void dosyadanHL7Oku() {
    FILE *dosya = fopen("hasta_kayitlari.hl7", "r"); // Dosyay� okuma modunda a�
    if (dosya == NULL) { // Dosya a��lamazsa hata ver
        printf("Dosya bulunamadi veya acilamadi!\n");
        return;
    }

    printf("\n--- Dosyadan Okunan HL7 Kayitlari ---\n");
    char satir[256]; // Dosyadan okunan her sat�r� tutmak i�in dizi
    while (fgets(satir, sizeof(satir), dosya) != NULL) { // Dosyay� sat�r sat�r oku
        printf("%s", satir); // Sat�r� ekrana yazd�r
    }

    fclose(dosya); // Dosyay� kapat
}

// Ana men� fonksiyonu
void menu() {
    printf("\n--- Acil Servis Sistemi ---\n");
    printf("1. Hasta Ekle\n");
    printf("2. Hasta Listesi Goruntule\n");
    printf("3. HL7 Formatinda Kaydet\n");
    printf("4. HL7 Kayitlarini Goster\n");
    printf("5. Cikis\n");
    printf("Seciminiz: ");
}

// Ana fonksiyon
int main() {
    int secim;
    while (1) {
        menu(); // Men�y� g�ster
        scanf("%d", &secim); // Kullan�c�dan se�im al
        temizleBuffer(); // Girdi tamponunu temizle

        switch (secim) {
            case 1:
                hastaEkle(); // Hasta ekle
                break;
            case 2:
                hastaListele(); // Hasta listesini g�ster
                break;
            case 3:
                dosyayaHL7Kaydet(); // HL7 format�nda kaydet
                break;
            case 4:
                dosyadanHL7Oku(); // HL7 kay�tlar�n� g�ster
                break;
            case 5:
                printf("Sistemden cikiliyor...\n");
                return 0; // Programdan ��k
            default:
                printf("Gecersiz secim, tekrar deneyin.\n"); // Ge�ersiz se�im uyar�s�
        }
    }
    return 0;
}

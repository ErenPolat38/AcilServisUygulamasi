#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASTA 100 // Maksimum hasta kapasitesi

// Hasta bilgilerini tutan yapý (struct)
typedef struct {
    char ad[50]; // Hasta adý
    char soyad[50]; // Hasta soyadý
    int yas; // Hasta yaþý
    char cinsiyet; // Hasta cinsiyeti (E/K)
    int oncelik; // Öncelik seviyesi (1: Çok Acil, 2: Orta, 3: Normal)
    int receteNo; // Reçete numarasý
} Hasta;

Hasta hastaListesi[MAX_HASTA]; // Hasta bilgilerini tutan dizi
int hastaSayisi = 0; // Kayýtlý hasta sayýsý
int receteSayaci = 1000; // Reçete numarasý için sayaç

// Girdi tamponunu temizleme fonksiyonu
void temizleBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Tampondaki fazla karakterleri temizler
}

// Yeni hasta ekleme fonksiyonu
void hastaEkle() {
    if (hastaSayisi >= MAX_HASTA) { // Hasta kapasitesi kontrolü
        printf("Hasta kapasitesi dolu!\n");
        return;
    }

    Hasta yeniHasta; // Yeni hasta bilgileri için geçici struct
    printf("Hasta Adi: ");
    scanf("%s", yeniHasta.ad); // Hasta adýný al
    printf("Hasta Soyadi: ");
    scanf("%s", yeniHasta.soyad); // Hasta soyadýný al
    printf("Yas: ");
    scanf("%d", &yeniHasta.yas); // Hasta yaþýný al
    printf("Cinsiyet (E/K): ");
    scanf(" %c", &yeniHasta.cinsiyet); // Hasta cinsiyetini al
    printf("Oncelik Seviyesi (1: Cok Acil, 2: Orta, 3: Normal): ");
    scanf("%d", &yeniHasta.oncelik); // Öncelik seviyesini al

    yeniHasta.receteNo = receteSayaci++; // Reçete numarasýný ata ve sayacý artýr
    hastaListesi[hastaSayisi++] = yeniHasta; // Hastayý listeye ekle
    printf("Hasta kaydedildi!\n");
}

// Hasta listesini görüntüleme fonksiyonu
void hastaListele() {
    if (hastaSayisi == 0) { // Kayýtlý hasta yoksa uyarý ver
        printf("Kayitli hasta bulunmamaktadir.\n");
        return;
    }

    printf("\n--- Hasta Listesi ---\n");
    for (int i = 0; i < hastaSayisi; i++) { // Tüm hastalarý listele
        printf("Ad: %s, Soyad: %s, Yas: %d, Cinsiyet: %c, Oncelik: %d, Recete No: %d\n",
               hastaListesi[i].ad, hastaListesi[i].soyad, hastaListesi[i].yas,
               hastaListesi[i].cinsiyet, hastaListesi[i].oncelik, hastaListesi[i].receteNo);
    }
}

// Hasta bilgilerini HL7 formatýnda dosyaya kaydetme fonksiyonu
void dosyayaHL7Kaydet() {
    FILE *dosya = fopen("hasta_kayitlari.hl7", "w"); // Dosyayý yazma modunda aç
    if (dosya == NULL) { // Dosya açýlamazsa hata ver
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < hastaSayisi; i++) { // Her hasta için HL7 formatýnda kayýt oluþtur
        // MSH Segmenti: Mesaj baþlýk bilgileri
        fprintf(dosya, "MSH|^~\\&|HOSPITAL|A|||202310101200||ADT^A01|123456|P|2.5\n");
        // PID Segmenti: Hasta kimlik bilgileri
        fprintf(dosya, "PID|1||%d||%s^%s||%d|%c|||123 Main St^^City^ST^12345^USA\n",
                i + 1, hastaListesi[i].soyad, hastaListesi[i].ad, hastaListesi[i].yas, hastaListesi[i].cinsiyet);
        // PV1 Segmenti: Hasta ziyaret bilgileri
        fprintf(dosya, "PV1|1|E|ER^1^1^HOSPITAL^ER^1^1^HOSPITAL||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        // ORC Segmenti: Reçete bilgileri
        fprintf(dosya, "ORC|NW|%d^HOSPITAL|||CM||||202310101200\n\n", hastaListesi[i].receteNo);
    }

    fclose(dosya); // Dosyayý kapat
    printf("Hasta kayitlari HL7 formatinda dosyaya kaydedildi!\n");
}

// HL7 formatýndaki kayýtlarý dosyadan okuma fonksiyonu
void dosyadanHL7Oku() {
    FILE *dosya = fopen("hasta_kayitlari.hl7", "r"); // Dosyayý okuma modunda aç
    if (dosya == NULL) { // Dosya açýlamazsa hata ver
        printf("Dosya bulunamadi veya acilamadi!\n");
        return;
    }

    printf("\n--- Dosyadan Okunan HL7 Kayitlari ---\n");
    char satir[256]; // Dosyadan okunan her satýrý tutmak için dizi
    while (fgets(satir, sizeof(satir), dosya) != NULL) { // Dosyayý satýr satýr oku
        printf("%s", satir); // Satýrý ekrana yazdýr
    }

    fclose(dosya); // Dosyayý kapat
}

// Ana menü fonksiyonu
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
        menu(); // Menüyü göster
        scanf("%d", &secim); // Kullanýcýdan seçim al
        temizleBuffer(); // Girdi tamponunu temizle

        switch (secim) {
            case 1:
                hastaEkle(); // Hasta ekle
                break;
            case 2:
                hastaListele(); // Hasta listesini göster
                break;
            case 3:
                dosyayaHL7Kaydet(); // HL7 formatýnda kaydet
                break;
            case 4:
                dosyadanHL7Oku(); // HL7 kayýtlarýný göster
                break;
            case 5:
                printf("Sistemden cikiliyor...\n");
                return 0; // Programdan çýk
            default:
                printf("Gecersiz secim, tekrar deneyin.\n"); // Geçersiz seçim uyarýsý
        }
    }
    return 0;
}

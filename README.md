# Acil Servis Yönetim Sistemi

Bu proje, acil servislerdeki hasta kayıtlarını yönetmek için geliştirilmiş bir C programıdır. Kullanıcılar, hasta bilgilerini kaydedebilir, listeleyebilir ve verileri HL7 formatında dosyaya kaydedebilir. HL7, sağlık verilerinin uluslararası bir standartta güvenli bir şekilde iletilmesini sağlayan bir protokoldür.

## Özellikler

- *Hasta Ekleme:* Kullanıcı, hasta bilgilerini girerek yeni hasta kaydı oluşturabilir.
- *Hasta Listeleme:* Kayıtlı hastalar listelenebilir.
- *HL7 Formatında Kaydetme:* Hastaların bilgileri HL7 formatında dosyaya kaydedilir.
- *HL7 Formatında Okuma:* HL7 formatında kaydedilen dosya okunarak veriler görüntülenebilir.

## Kullanım

### 1. Hasta Ekleme
- Kullanıcı, hasta adı, soyadı, yaşı, cinsiyeti ve öncelik seviyesi gibi bilgileri girerek yeni bir hasta ekleyebilir.
- Her hasta için benzersiz bir reçete numarası otomatik olarak oluşturulur.

### 2. Hasta Listeleme
- Kayıtlı hastalar liste halinde görüntülenir.

### 3. HL7 Formatında Kaydetme
- Sistemdeki tüm hasta bilgileri HL7 formatında bir dosyaya kaydedilir.

### 4. HL7 Kaydını Gösterme
- Daha önce kaydedilen HL7 formatındaki hasta bilgileri dosyadan okunarak ekrana yazdırılır.

## HL7 Formatı

HL7 (Health Level 7), sağlık verilerinin iletiminde kullanılan bir protokoldür. Bu protokol, verilerin farklı sistemler arasında güvenli ve uyumlu bir şekilde aktarılmasını sağlar. HL7 mesajları, bir dizi segmentten oluşur. Bu projede kullanılan segmentler:

- *MSH (Message Header):* Mesaj başlık bilgilerini içerir.
- *PID (Patient Identification):* Hasta kimlik bilgilerini içerir.
- *PV1 (Patient Visit):* Hasta ziyaret bilgilerini içerir.
- *ORC (Order Control):* Reçeteler veya tedavi talimatlarını içerir.

## Akış Şeması

Aşağıda, sistemin genel işleyişini ve hasta ekleme sürecini gösteren bir akış şeması bulunmaktadır.

```mermaid
flowchart TD
    A[Başlangıç] --> B[Menü Göster]
    B --> C{Seçim Yap}
    C -->|Hasta Ekle| D[Hasta Ekleme Ekranı]
    D --> E[Hasta Bilgileri Kaydet]
    E --> F[Hasta Listele]
    F --> B
    C -->|Hasta Listele| F
    C -->|HL7 Kaydet| G[HL7 Formatında Kaydet]
    G --> H[Dosyaya HL7 Kaydet]
    H --> B
    C -->|HL7 Kaydını Göster| I[HL7 Kaydını Oku]
    I --> B
    C -->|Çıkış| J[Çıkış]

AKILLI OTOPARK SİSTEMİ v3.0
===========================

PROJE TANIMI
------------
Akıllı Otopark Sistemi, büyük ölçekli bir otoparkın doluluk durumunu
gerçek zamanlı olarak takip etmek amacıyla geliştirilmiş grafik tabanlı
bir simülasyon uygulamasıdır.

Proje Raylib grafik kütüphanesi ve C programlama dili kullanılarak
geliştirilmiştir. Kullanıcı otoparktaki park alanlarının durumunu
görüntüleyebilir ve sistem anlık olarak doluluk istatistiklerini
hesaplayabilir.

KULLANILAN TEKNOLOJİLER
-----------------------
- C Programlama Dili
- Raylib Grafik Kütüphanesi
- Struct Veri Yapıları
- Grafiksel Kullanıcı Arayüzü (GUI)

PROJE ÖZELLİKLERİ
-----------------
✓ 56 araç kapasiteli otopark modeli

✓ 4 farklı park bloğu
  - Blok A
  - Blok B
  - Blok C
  - Blok D

✓ Giriş ve çıkış noktaları

✓ Araç bekleme ve yıkama bölümü

✓ Gerçek zamanlı istatistik paneli

✓ Toplam park sayısı görüntüleme

✓ Boş park sayısı görüntüleme

✓ Dolu park sayısı görüntüleme

✓ Doluluk oranı hesaplama

✓ Blok bazlı doluluk analizi

✓ En yakın boş park alanı gösterimi

✓ Tahmini doluluk bilgisi

✓ Grafiksel araç gösterimi

✓ Yol ve yönlendirme sistemi

✓ Modern kullanıcı arayüzü

SİSTEMİN ÇALIŞMA PRENSİBİ
-------------------------
Sistem içerisinde her park alanı bir veri yapısı
(Struct) olarak tutulmaktadır.

Her park alanı için:

- Park numarası
- Doluluk durumu
- Ekran koordinatları
- Blok bilgisi

saklanmaktadır.

Program çalıştığında tüm park alanlarının durumları
hesaplanır ve aşağıdaki bilgiler otomatik olarak güncellenir:

- Toplam araç sayısı
- Boş park sayısı
- Dolu park sayısı
- Doluluk yüzdesi
- Blok doluluk oranları
- En yakın boş park alanı

ARAYÜZ BİLGİLERİ
----------------
Sol panelde:

- Toplam park kapasitesi
- Boş park sayısı
- Dolu park sayısı
- Doluluk oranı
- Yaklaşık doluluk tahmini
- En yakın boş park
- Blok durumları

gösterilmektedir.

Sağ tarafta ise otopark haritası yer almakta olup
park alanları renklerle temsil edilmektedir.

RENKLERİN ANLAMI
----------------
Yeşil  : Boş park alanı

Kırmızı : Dolu park alanı

Mavi araç görselleri : Park etmiş araçlar

Sarı yol çizgileri : Araç yönlendirme yolları

PROJEDE KAZANILAN BECERİLER
---------------------------
- Struct kullanımı
- Dizilerle çalışma
- Grafik programlama
- Olay yönetimi
- Koordinat sistemi kullanımı
- Veri görselleştirme
- Kullanıcı arayüzü tasarımı
- Algoritma geliştirme

SONUÇ
------
Bu proje ile gerçek bir otopark yönetim sisteminin
temel çalışma mantığı grafiksel olarak modellenmiştir.
Sistem, park alanlarının takibini kolaylaştırmakta ve
kullanıcıya anlık doluluk bilgileri sunmaktadır.
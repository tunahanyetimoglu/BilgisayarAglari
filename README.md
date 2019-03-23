# Bilgisayar Ağları Lab. Dersi Kodları

[![OMÜ CEng](https://img.shields.io/badge/OM%C3%9C-CEng-blue.svg)](http://bil.muhendislik.omu.edu.tr)

## İçerik

**Ondokuz Mayıs Üniversitesi** (OMÜ) **Bilgisayar Mühendisliği** lisans programı **Bilgisayar Ağları** dersi kapsamında 
dönem boyunca labaratuvarda verilen projelerin **OmNet++** kullanılarak tarafımdan gerçekleştirilen çözümleri yer almaktadır.

## OmNet++ 

+ **OmNet++** (Objective Modular Network Testbed in C++), nesneye yönelik (object-oriented) modüler bir ayrık olay ağ benzeticisidir.
+ Ağların Modellenmesini sağlar.
+ **C / C++** programlama dilleri kullanılır.
+ Platformdan bağımsız çalışmaktadır.

### OmNet++ Programlama

+ **OmNet++** da programlama 2 kavram öne çıkar.
+ Topoloji 
  ++ **OmNet++** da ağ topolojisi tanımlamaarı *.ned* (Network Description File) uzantılı dosyalarda gerçekleştirilir.
  ++ Kod olarak yazılabileceği gibi görsel olarakta bu tanımlamayı gerçekleştirmemize imkan sağlar.
+ Kaynak Kod ( Davranış )
  ++ **OmNet++** da yer alan modüller C++ dilinde yazılmıştır.
  ++ Bu kodlar **GPL** ( General Public Licence) ' a sahiptir.

## Repo'nun Dizin Yapısı

+ **Examples** içerisinde OmNet++ ile gelen kendi örnek projeleri ve kodları yer almaktadır.
+ **Projects** içerisinde tarafımdan gerçekleştirilen kodlar yer almaktadır.

## Projelerin Dizin Yapısı
+ **.cc** uzantılı dosyalar kaynak koddur. **C++** dili ile yazılmıştır.
+ **.ini** uzantılı dosyalar başlangıç ayarlarının yapıldığı dosyalardır. **omnetpp.ini** şeklinde tanımlanması gerekmektedir. 
  Ağ yapısı seçilir.
+ **.ned** uzantılı dosyalar topolojinin tanımlandığı dosyalardır. **NED** (Network Description File) dili ile gerçekleştirilmiştir.
+ **.msg** uzantılı dosyalar düğümler arası mesaj gönderilen mesajların içeriğini tanımlamımıza imkan sağlar. Bu uzantıda ki dosyalar
  derlendikten sonra **_m.cc ve _m.h** uzantılı 2 adet dosya oluşur. Kullanmak için kaynak kodumuzun içerisinde **_m.h** uzantılı 
  dosyayı **include** etmemiz gerekmektedir.


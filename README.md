# Jam Digital LCD 20x4 dengan RTC DS3231 dan Buzzer

Proyek Arduino yang menampilkan jam digital pada layar LCD 20x4 dengan menggunakan modul RTC DS3231 untuk akurasi waktu real-time, serta dilengkapi dengan buzzer untuk indikasi audio.

## 📋 Daftar Isi
- [Gambaran Umum](#gambaran-umum)
- [Komponen yang Dibutuhkan](#komponen-yang-dibutuhkan)
- [Koneksi Hardware](#koneksi-hardware)
- [Instalasi](#instalasi)
- [Fitur](#fitur)
- [Cara Kerja](#cara-kerja)
- [Library yang Digunakan](#library-yang-digunakan)
- [Catatan Penting](#catatan-penting)
- [Troubleshooting](#troubleshooting)

## 📌 Gambaran Umum

Proyek ini merupakan sistem penampil jam digital yang menampilkan informasi lengkap meliputi:
- **Hari dalam bahasa Indonesia** (Ahad, Senin, Selasa, dst.)
- **Tanggal** dalam format DD/MM/YYYY
- **Waktu** dalam format HH:MM:SS
- **Nama Institusi** di bagian bawah layar

Sistem ini menggunakan Arduino Uno sebagai mikrokontroler, LCD 20x4 untuk display, dan modul RTC DS3231 untuk menjaga akurasi waktu bahkan ketika Arduino dimatikan.

## 🔧 Komponen yang Dibutuhkan

| Komponen | Jumlah | Keterangan |
|----------|--------|-----------|
| Arduino Uno | 1 | Mikrokontroler utama |
| LCD 20x4 | 1 | Display dengan backlight |
| RTC DS3231 | 1 | Real-Time Clock dengan baterai cadangan |
| Buzzer | 1 | Speaker untuk indikasi audio |
| Potentiometer 10kΩ | 1 | Untuk mengatur kontras LCD |
| Resistor 220Ω | 1 | Untuk backlight LCD |
| Kabel Jumper | Sesuai kebutuhan | Male-Male atau Male-Female |
| Power Supply 5V | 1 | Sumber tenaga Arduino |

## 🔌 Koneksi Hardware

### Koneksi LCD 20x4 ke Arduino Uno:

| Pin LCD | Pin Arduino | Fungsi |
|---------|------------|--------|
| RS (Pin 4) | Pin 7 | Register Select |
| EN (Pin 6) | Pin 6 | Enable |
| D4 (Pin 11) | Pin 5 | Data 4 |
| D5 (Pin 12) | Pin 4 | Data 5 |
| D6 (Pin 13) | Pin 3 | Data 6 |
| D7 (Pin 14) | Pin 2 | Data 7 |
| VSS (Pin 1) | GND | Ground |
| VDD (Pin 2) | 5V | Power |
| V0 (Pin 3) | Potentiometer | Kontras |
| A (Pin 15) | 5V (via R 220Ω) | Backlight |
| K (Pin 16) | GND | Backlight |

### Koneksi RTC DS3231 ke Arduino Uno:

| Pin RTC | Pin Arduino | Fungsi |
|---------|------------|--------|
| GND | GND | Ground |
| VCC | 5V | Power |
| SDA | A4 | I2C Data |
| SCL | A5 | I2C Clock |

### Koneksi Buzzer ke Arduino Uno:

| Buzzer | Pin Arduino | Fungsi |
|--------|------------|--------|
| Positif (+) | Pin 8 | Signal (PWM) |
| Negatif (-) | GND | Ground |

**Catatan:** Pin 10 juga dikonfigurasi sebagai OUTPUT (untuk perluasan fitur di masa depan)

## 💻 Instalasi

### Persyaratan Software:
- [PlatformIO](https://platformio.org/) atau Arduino IDE
- Board support untuk Arduino Uno
- Library yang diperlukan (lihat bagian Library)

### Langkah-langkah Instalasi:

1. **Klon atau download proyek ini**
   ```bash
   git clone [repository-url]
   cd "Arduino With LCD 20x4 and RTC DS3231 and Buzzer"
   ```

2. **Buka proyek di PlatformIO**
   - Jika menggunakan PlatformIO CLI:
   ```bash
   platformio init
   ```

3. **Instal dependencies**
   - Library akan otomatis terinstal melalui `platformio.ini`

4. **Upload ke Arduino**
   ```bash
   platformio run --target upload
   ```

5. **Konfigurasi RTC (jika pertama kali)**
   - Saat pertama kali program berjalan, RTC akan otomatis disetel ke waktu kompilasi
   - Untuk mengatur waktu manual, modifikasi kode di `setup()`:
   ```cpp
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   ```

## ⚡ Fitur

✅ **Display Real-Time**
- Menampilkan waktu, tanggal, dan hari secara real-time
- Update setiap 250ms untuk responsivitas optimal

✅ **Dukungan Bahasa Indonesia**
- Nama-nama hari ditampilkan dalam bahasa Indonesia
- Format tanggal yang familiar untuk pengguna lokal

✅ **RTC Backup Power**
- Modul RTC dilengkapi baterai CR2032
- Waktu tetap akurat meskipun Arduino dimatikan
- Deteksi otomatis kehilangan daya RTC

✅ **Indikasi Audio**
- Buzzer menghasilkan nada 1000 Hz setiap detik
- Berfungsi sebagai indikator visual dan audio

✅ **Display Estetis**
- Layout informasi yang terstruktur di LCD 4 baris
- Pesan sambutan di startup
- Identitas institusi di baris terakhir

## 🎯 Cara Kerja

### Inisialisasi (Setup):
1. Mengatur pin 10 sebagai OUTPUT (siaga untuk ekspansi)
2. Menginisialisasi LCD 20x4
3. Menginisialisasi koneksi RTC melalui I2C
4. Memeriksa apakah RTC pernah kehilangan daya
5. Menampilkan splash screen selama 1 detik
6. Membersihkan layar

### Loop (Operasi Utama):
1. Membaca waktu dan tanggal dari RTC
2. Menampilkan hari di baris 0
3. Menampilkan tanggal (DD/MM/YYYY) di baris 0-1
4. Menampilkan waktu (HH:MM:SS) di baris 1
5. Mengaktifkan buzzer dengan nada 1000 Hz selama 50ms
6. Menampilkan nama institusi di baris 3
7. Menunggu 250ms sebelum loop berikutnya

### Format Tampilan LCD:
```
Line 0: Senin, 05/12/2025
Line 1:       12,30,45
Line 2: [kosong/dapat dimodifikasi]
Line 3:  SMP BQ Islamic BS Bogor
```

## 📚 Library yang Digunakan

| Library | Versi | Fungsi |
|---------|-------|--------|
| LiquidCrystal | ^1.0.7 | Kontrol LCD 20x4 |
| RTClib | ^2.1.4 | Kontrol modul RTC DS3231 |
| Arduino (Built-in) | - | Fungsi dasar Arduino |

### Cara Menambah Library (jika manual):
**Menggunakan Arduino IDE:**
- Sketch → Include Library → Manage Libraries
- Cari "LiquidCrystal" dan "RTClib"
- Klik Install

## 📝 Catatan Penting

1. **Tegangan I2C RTC**
   - RTC DS3231 mengoperasikan I2C pada tegangan 3.3V
   - Arduino Uno mengoperasikan pada 5V
   - Untuk kompatibilitas penuh, gunakan level shifter I2C atau RTC yang kompatibel 5V

2. **Baterai RTC**
   - Ganti baterai CR2032 jika RTC tidak menyimpan waktu saat dimatikan
   - Baterai berfungsi ~5 tahun tergantung penggunaan

3. **Kontras LCD**
   - Sesuaikan potentiometer jika tampilan tidak jelas
   - Putar perlahan-lahan sampai teks terlihat jelas

4. **Buzzer dan Frekuensi**
   - Frekuensi 1000 Hz dapat diubah sesuai preferensi
   - Durasi nada saat ini 50ms, dapat dimodifikasi

5. **Konsumsi Daya**
   - LCD backlight mengkonsumsi daya cukup besar (~200mA)
   - Arduino Uno + RTC + Buzzer sekitar ~50mA
   - Gunakan power supply 5V minimal 1A

## 🆘 Troubleshooting

### LCD tidak menampilkan apa-apa
- **Solusi:**
  1. Periksa koneksi power (VCC dan GND)
  2. Sesuaikan potentiometer untuk kontras
  3. Periksa koneksi pin data (D4-D7)
  4. Verifikasi library LiquidCrystal terinstal

### RTC menunjukkan waktu yang salah
- **Solusi:**
  1. Periksa koneksi I2C (SDA dan SCL)
  2. Ganti baterai RTC jika diperlukan
  3. Jalankan kode untuk reset waktu RTC
  4. Pastikan library RTClib terinstal dengan benar

### Buzzer tidak mengeluarkan suara
- **Solusi:**
  1. Periksa koneksi pin 8 ke buzzer
  2. Verifikasi buzzer tidak rusak
  3. Ubah frekuensi untuk mendengar suara berbeda
  4. Periksa GND terkoneksi dengan baik

### Program tidak ter-upload
- **Solusi:**
  1. Periksa COM port di Device Manager
  2. Pastikan board dipilih "Arduino Uno"
  3. Coba reset Arduino sebelum upload
  4. Gunakan kabel USB yang berbeda

## 📄 Lisensi

Proyek ini dapat digunakan untuk keperluan pendidikan dan non-komersial.

---

**Dibuat untuk:** SMP BQ Islamic BS Bogor - Lab Robotik  
**Update terakhir:** [Tanggal Update]  
**Status:** ✅ Production Ready

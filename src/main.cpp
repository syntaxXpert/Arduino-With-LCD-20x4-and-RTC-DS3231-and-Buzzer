#include <Arduino.h>
#include "RTClib.h"
#include <LiquidCrystal.h>


// Inisialisasi objek LCD dengan menentukan pin yang terhubung ke Arduino
// Sintaks: LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


// Inisialisasi objek RTC, menggunakan DS3231 sebagai chip RTC
RTC_DS3231 rtc;


// Array karakter untuk menyimpan nama-nama hari dalam bahasa Indonesia
// Diakses menggunakan indeks 0 (Ahad) hingga 6 (Sabtu)
char nameDay[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};


void setup() {
  // Mengatur pin 10 sebagai OUTPUT (meskipun tidak digunakan dalam loop ini, mungkin untuk buzzer/LED)
  pinMode(10, OUTPUT);
  
  // Memulai antarmuka LCD dengan menentukan jumlah kolom (20) dan baris (4)
  lcd.begin(20, 4);
  
  // Memulai komunikasi dengan modul RTC
  rtc.begin();


  // Memeriksa apakah RTC kehilangan daya (pertama kali dijalankan atau baterai habis)
  if (rtc.lostPower()) {
    // Jika kehilangan daya, atur waktu RTC ke waktu kompilasi program
    // F(__DATE__) dan F(__TIME__) adalah makro yang berisi tanggal dan waktu saat kompilasi
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // Mengatur posisi kursor di kolom 0, baris 0
  lcd.setCursor(0,0);
  // Menampilkan pesan judul
  lcd.print("   JAM DIGITAL   ");
  
  // Mengatur posisi kursor di kolom 0, baris 1
  lcd.setCursor(0,1);
  // Menampilkan pesan sub-judul
  lcd.print("   LAB ROBOTIK   ");
  
  // Menunda eksekusi selama 1000 milidetik (1 detik)
  delay(1000);
  
  // Menghapus semua yang ada di layar LCD
  lcd.clear();
}




// Fungsi pembantu untuk mencetak angka dengan format dua digit (misalnya, 05, 12)
void printAngka (int digits){
  // Jika angka kurang dari 10 (misalnya 1, 5, 9)
  if (digits < 10){
    // Cetak angka 0 di depannya
    lcd.print("0");
    // Kemudian cetak angkanya
    lcd.print(digits);
  }
  // Jika angka 10 atau lebih, cetak langsung angkanya
  else lcd.print(digits);
}


void loop()
{
  // Mendapatkan tanggal dan waktu saat ini dari modul RTC
  DateTime now = rtc.now();
  
  // Mengatur posisi kursor untuk menampilkan hari (kolom 2, baris 0)
  lcd.setCursor(2,0);
  
  // Menampilkan nama hari berdasarkan nilai yang dikembalikan oleh rtc.now().dayOfTheWeek()
  // dayOfTheWeek() mengembalikan 0=Ahad, 1=Senin, ..., 6=Sabtu
  lcd.print (nameDay[now.dayOfTheWeek()]);
  
  // Menampilkan separator
  lcd.print (", ");
  
  // Menampilkan tanggal (hari ke-) dalam format dua digit
  printAngka (now.day());
  
  // Menampilkan separator
  lcd.print ("/");
  
  // Menampilkan bulan dalam format dua digit
  printAngka (now.month());
  
  // Menampilkan separator
  lcd.print ("/");
  
  // Menampilkan tahun
  printAngka (now.year());
  
  // Mengatur posisi kursor untuk menampilkan waktu (kolom 5, baris 1)
  lcd.setCursor(5,1);
  
  // Menampilkan jam dalam format dua digit
  printAngka (now.hour());
  
  // Menampilkan separator (koma di sini bertindak sebagai titik dua/pemisah waktu)
  lcd.print (","); 
  
  // Menampilkan menit dalam format dua digit
  printAngka (now.minute());
  
  // Menampilkan separator
  lcd.print (","); 
  
  // Menampilkan detik dalam format dua digit
  printAngka (now.second());
  
  // Menghasilkan nada (tone) pada pin 8 dengan frekuensi 1000 Hz selama 50 milidetik
  // Ini mungkin digunakan sebagai 'bunyi detik' atau indikasi waktu
  tone(8,1000,50);
  
  // Mengatur posisi kursor untuk menampilkan pesan tetap (kolom 2, baris 3)
  lcd.setCursor (2,3);
  
  // Menampilkan pesan tetap
  lcd.print (" SMP BQ Islamic BS Bogor ");


  // Menunda eksekusi selama 250 milidetik sebelum loop berulang
  // Delay yang singkat membuat tampilan jam lebih responsif
  delay(250);
}

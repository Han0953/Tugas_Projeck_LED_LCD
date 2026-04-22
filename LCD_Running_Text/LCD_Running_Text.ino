#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- KONFIGURASI ---)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Teks berjalan
String teksBerjalan = "         Semangat Kuliah di PVTE UMRI         ";

void setup() {
  lcd.init();        // Inisialisasi LCD
  lcd.backlight();   // Nyalain lampu latar 
  
  // Teks di baris atas
  lcd.setCursor(0, 0); 
  lcd.print("Kelompok Gacor");
  
  // Teks sebelum jalan
  lcd.setCursor(0, 1);
  lcd.print("Loading...");
  delay(2000); // Jeda 2 detik
}

void loop() {
  // Logic teks berjalan di baris bawah (baris ke-1)
  for (int i = 0; i < teksBerjalan.length() - 16; i++) {
    lcd.setCursor(0, 1); 
    lcd.print(teksBerjalan.substring(i, i + 16));
    
    delay(100); // Kecepatan lari teksnya. Kurangin angkanya kalau mau lebih ngebut
  }
}

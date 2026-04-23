#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- KONFIGURASI LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
String teksBerjalan = "         Semangat Kuliah di PVTE UMRI         ";
int indexTeks = 0; 

// --- KONFIGURASI LED ---
int pinAwal = 2;
int pinAkhir = 11;
int currentLED = 2; 
int arahLED = 1;    // 1 = maju ke kanan, -1 = mundur ke kiri

// --- TIMER MULTITASKING (ANTI DELAY-DELAY CLUB) ---
unsigned long waktuSblmLCD = 0;
unsigned long waktuSblmLED = 0;
int jedaLCD = 250; 
int jedaLED = 150;  

void setup() {
  // Setup LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PVTE UMRI!");

  // Setup LED
  for (int pin = pinAwal; pin <= pinAkhir; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  unsigned long waktuSkrg = millis();

  // ==========================================
  // TUGAS 1: URUSIN LCD TEKS BERJALAN
  // ==========================================
  if (waktuSkrg - waktuSblmLCD >= jedaLCD) {
    waktuSblmLCD = waktuSkrg; 

    lcd.setCursor(0, 1);
    lcd.print(teksBerjalan.substring(indexTeks, indexTeks + 16));

    indexTeks++;
    if (indexTeks > teksBerjalan.length() - 16) {
      indexTeks = 0; 
    }
  }

  // ==========================================
  // TUGAS 2: URUSIN 10 LED KNIGHT RIDER
  // ==========================================
  if (waktuSkrg - waktuSblmLED >= jedaLED) {
    waktuSblmLED = waktuSkrg; 

    // Matiin semua LED dulu 
    for (int pin = pinAwal; pin <= pinAkhir; pin++) {
      digitalWrite(pin, LOW);
    }

    // Nyalain LED giliran saat ini
    digitalWrite(currentLED, HIGH);

    // Siapin posisi LED buat giliran berikutnya
    currentLED += arahLED;

    // Logika pantulan: Kalo mentok, putar balik arahnya
    if (currentLED > pinAkhir) {
      currentLED = pinAkhir - 1; 
      arahLED = -1;              
    } else if (currentLED < pinAwal) {
      currentLED = pinAwal + 1;  
      arahLED = 1;               
    }
  }
}
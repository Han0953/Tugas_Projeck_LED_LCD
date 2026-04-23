#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- KONFIGURASI LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
String teksBerjalan = "         Semangat Kuliah di PVTE UMRI         ";
int indexTeks = 0; // Buat ngelacak teks udah jalan sampe mana

// --- KONFIGURASI LED ---
int pinAwal = 2;
int pinAkhir = 9;
int currentLED = 2; // LED mana yang lagi nyala
int arahLED = 1;    // 1 = maju ke kanan, -1 = mundur ke kiri

// --- TIMER MULTITASKING (PENGGANTI DELAY) ---
unsigned long waktuSblmLCD = 0;
unsigned long waktuSblmLED = 0;
int jedaLCD = 300; // Kecepatan jalan teks
int jedaLED = 250;  // Kecepatan jalan LED bolak-balik

void setup() {
  // Setup LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PVTE UMRI");

  // Setup LED
  for (int pin = pinAwal; pin <= pinAkhir; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Baca waktu (stopwatch) saat ini sejak Arduino nyala
  unsigned long waktuSkrg = millis();

  // LCD Running Text
 
  if (waktuSkrg - waktuSblmLCD >= jedaLCD) {
    waktuSblmLCD = waktuSkrg; // Reset stopwatch LCD

    lcd.setCursor(0, 1);
    lcd.print(teksBerjalan.substring(indexTeks, indexTeks + 16));

    indexTeks++;
    if (indexTeks > teksBerjalan.length() - 16) {
      indexTeks = 0; // Kalo udah mentok ujung, ulang dari awal
    }
  }

  // LED Running
  
  if (waktuSkrg - waktuSblmLED >= jedaLED) {
    waktuSblmLED = waktuSkrg; // Reset stopwatch LED

    // Matiin semua LED dulu biar gak nyala berbarengan
    for (int pin = pinAwal; pin <= pinAkhir; pin++) {
      digitalWrite(pin, LOW);
    }

    // Nyalain LED giliran saat ini
    digitalWrite(currentLED, HIGH);

    // Siapin posisi LED buat giliran berikutnya
    currentLED += arahLED;

    // Logika pantulan: Kalo mentok kanan/kiri, putar balik arahnya
    if (currentLED > pinAkhir) {
      currentLED = pinAkhir - 1; // Mundur selangkah
      arahLED = -1;              // Ganti gigi mundur
    } else if (currentLED < pinAwal) {
      currentLED = pinAwal + 1;  // Maju selangkah
      arahLED = 1;               // Ganti gigi maju
    }
  }
}
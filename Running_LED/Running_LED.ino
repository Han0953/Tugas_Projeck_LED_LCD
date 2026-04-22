// Kita gak pake ngetik satu-satu, kita deklarasiin pin awal dan akhir
int pinAwal = 2;
int pinAkhir = 11;
int waktuJeda = 350; // Kecepatan lari LED-nya (satuan milidetik). Makin kecil makin ngebut!

void setup() {
  // Looping buat ngatur pin D2 sampai D11 jadi OUTPUT semua
  // Anak teknik ngodingnya begini, sekali ngetik beres 10 pin 😎
  for (int pin = pinAwal; pin <= pinAkhir; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // --- EFEK LED BERJALAN MAJU (Kiri ke Kanan) ---
  for (int pin = pinAwal; pin <= pinAkhir; pin++) {
    digitalWrite(pin, HIGH);  // Nyalain LED
    delay(waktuJeda);         // Tunggu bentar biar matanya sempet lihat
    digitalWrite(pin, LOW);   // Matiin LED lagi sebelum pindah ke sebelah
  }

  // --- EFEK LED BERJALAN MUNDUR (Kanan ke Kiri) ---
  // Kalau gak mau efek mundur, hapus aja blok for yang bawah ini
  for (int pin = pinAkhir - 1; pin >= pinAwal + 1; pin--) {
    digitalWrite(pin, HIGH);
    delay(waktuJeda);
    digitalWrite(pin, LOW);
  }
}
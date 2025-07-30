# WiFi Gratis Prank

Sebuah proyek sederhana namun efektif untuk mengubah mikrokontroler ESP8266 menjadi sebuah *Access Point* WiFi palsu yang menjebak pengguna dengan halaman *captive portal* interaktif. Proyek ini sangat cocok untuk keisengan atau demonstrasi cara kerja *captive portal*.

Ketika seseorang terhubung ke jaringan **"WiFi Gratis"**, mereka akan dialihkan ke halaman login yang mensimulasikan proses koneksi secara meyakinkan, lengkap dengan perubahan status tombol dan efek suara.

> **Peringatan:** Proyek ini dibuat untuk tujuan edukasi dan hiburan. Penggunaan untuk aktivitas yang merugikan, ilegal, atau mengganggu orang lain sangat tidak dianjurkan. Gunakan dengan bijak dan bertanggung jawab.

## ✨ Fitur Utama

* **Jaringan WiFi Terbuka**: Membuat jaringan WiFi dengan nama (SSID) **"WiFi Gratis"** tanpa memerlukan kata sandi.
* **Captive Portal Otomatis**: Semua pengguna yang terhubung akan secara otomatis diarahkan ke halaman "autentikasi" saat mereka mencoba membuka browser.
* **Halaman Login Modern**: Antarmuka yang bersih dan meyakinkan, membuat pengguna tidak curiga.
* **Tombol Interaktif dengan Simulasi Status**:
    * **Hubungkan Sekarang**: Status awal tombol dengan animasi berdenyut (pulse).
    * **Menghubungkan...**: Tombol berubah warna menjadi kuning saat proses "koneksi" berlangsung.
    * **✓ Terhubung**: Tombol berubah warna menjadi hijau setelah "berhasil" terhubung.
* **Efek Suara Realistis**: Dilengkapi dengan suara koneksi yang diputar saat tombol ditekan untuk menambah kesan nyata.

## 🔧 Cara Kerja

Proyek ini memanfaatkan beberapa fitur inti dari ESP8266:

1.  **Mode Access Point (AP)**: ESP8266 tidak terhubung ke jaringan lain, melainkan membuat jaringannya sendiri (Access Point).
2.  **DNS Server**: Sebuah server DNS berjalan di ESP8266. Tugasnya adalah menangkap semua permintaan nama domain (misal: google.com, facebook.com) dan mengalihkannya ke alamat IP dari ESP8266 itu sendiri (192.168.4.1). Inilah yang menciptakan efek *captive portal*.
3.  **Web Server**: ESP8266 juga menjalankan web server sederhana pada port 80. Server ini bertugas menyajikan halaman HTML prank kepada pengguna yang dialihkan oleh DNS server.
4.  **Logika di Sisi Klien (JavaScript)**: File `audio_handler.js` yang disajikan bersama halaman HTML mengatur semua interaksi. Saat tombol "Hubungkan Sekarang" ditekan:
    * Audio `connect_sound.mp3` diputar.
    * Teks dan warna tombol diubah untuk mensimulasikan status koneksi.
    * Setelah simulasi berhasil, audio akan diputar berulang-ulang (*loop*) untuk memberi kesan bahwa koneksi sedang aktif.

## 🗂️ Struktur File Proyek

* **`WiFi.ino`**: Kode utama Arduino. Berisi konfigurasi AP, server DNS, web server, dan kode HTML untuk halaman login.
* **`/data/audio_handler.js`**: File JavaScript yang mengontrol logika interaktif di halaman login.
* **`/data/connect_sound.mp3`**: File audio yang diputar selama proses simulasi koneksi.
* **`/data/wifi.png`**: Ikon gambar WiFi yang ditampilkan di halaman login.

## 🛠️ Kebutuhan

### Perangkat Keras
* Mikrokontroler berbasis ESP8266 (NodeMCU, Wemos D1 Mini, dll.)

### Perangkat Lunak
* [Arduino IDE](https://www.arduino.cc/en/software)
* Driver USB untuk board ESP8266 Anda (CH340/CP2102).
* [ESP8266 Filesystem Uploader](https://github.com/esp8266/arduino-esp8266fs-plugin)

## ⚙️ Panduan Setup Lengkap

### 1. Konfigurasi Arduino IDE
* **Install Board ESP8266**:
    * Buka `File > Preferences`.
    * Di bagian `Additional Boards Manager URLs`, tambahkan URL ini:
        ```
        http://arduino.esp8266.com/stable/package_esp8266com_index.json
        ```
    * Buka `Tools > Board > Boards Manager...`, cari `esp8266`, dan instal paketnya.

### 2. Instal Filesystem Uploader
* Kunjungi repositori [ESP8266 Filesystem Uploader](https.://github.com/esp8266/arduino-esp8266fs-plugin).
* Ikuti petunjuk instalasi di sana. Setelah selesai, Anda akan melihat opsi baru di `Tools > ESP8266 Sketch Data Upload`.

### 3. Siapkan File untuk Diunggah
* Di dalam folder yang sama tempat Anda menyimpan `WiFi.ino`, buat sebuah folder baru bernama `data`.
* Masukkan file `audio_handler.js`, `connect_sound.mp3`, dan `wifi.png` ke dalam folder `data` tersebut.

    ```
    - WiFi_Prank/
      |- WiFi.ino
      |- data/
         |- audio_handler.js
         |- connect_sound.mp3
         |- wifi.png
    ```

### 4. Unggah File ke ESP8266
* Hubungkan ESP8266 Anda ke komputer.
* Di Arduino IDE, pilih board dan port yang benar pada menu `Tools`.
* **Unggah file sistem**: Klik `Tools > ESP8266 Sketch Data Upload`. Tunggu hingga proses selesai. Ini akan mengunggah semua file di dalam folder `data` ke memori SPIFFS di ESP8266.
* **Unggah kode utama**: Klik tombol **Upload** (panah ke kanan) untuk mengunggah sketch `WiFi.ino`.

### 5. Selesai!
* Buka Serial Monitor (`Tools > Serial Monitor`) dengan baud rate `115200` untuk melihat log. Jika semua berjalan lancar, Anda akan melihat pesan bahwa server telah dimulai dan captive portal siap.

## 🚀 Cara Menggunakan

1.  Nyalakan ESP8266 Anda (bisa menggunakan power bank agar portabel).
2.  Tempatkan di lokasi yang strategis.
3.  Gunakan ponsel atau laptop Anda untuk mencari jaringan WiFi. Anda akan menemukan jaringan terbuka bernama **"WiFi Gratis"**.
4.  Hubungkan ke jaringan tersebut. Browser Anda seharusnya akan membuka halaman login secara otomatis.
5.  Tekan tombol "Hubungkan Sekarang" dan nikmati hasilnya!
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "FS.h"

const char* ssid = "WiFi Gratis";
const char* password = "";

DNSServer dnsServer;
ESP8266WebServer server(80);
const byte DNS_PORT = 53;

const char htmlPage[] PROGMEM = R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>WiFi Gratis</title>
    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
      body {
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
          "Helvetica Neue", Arial, sans-serif;
        background-color: #f0f2f5; /* Latar belakang abu-abu muda yang bersih */
        color: #1c1e21; /* Warna teks gelap untuk kontras */
        min-height: 100vh;
        display: flex;
        align-items: center;
        justify-content: center;
        padding: 20px;
      }
      .card {
        background: #ffffff; /* Latar belakang putih solid */
        border-radius: 12px; /* Sudut yang sedikit membulat */
        padding: 40px;
        text-align: center;
        max-width: 360px;
        width: 100%;
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1); /* Bayangan yang lembut untuk kedalaman */
      }
      .wifi-image {
        width: 80px; /* Atur ukuran gambar Anda di sini */
        height: auto;
        margin: 0 auto 20px;
      }
      h1 {
        font-size: 24px;
        font-weight: 600;
        margin-bottom: 8px;
        color: #000000; /* Warna hijau tua yang profesional */
      }
      .subtitle {
        color: #606770; /* Warna abu-abu lembut untuk teks sekunder */
        font-size: 15px;
        margin-bottom: 30px;
      }
      .connect-btn {
        background-color: #ca3434; /* Warna utama hijau solid */
        border: none;
        padding: 14px 28px;
        border-radius: 8px;
        color: white;
        font-size: 16px;
        font-weight: 600;
        cursor: pointer;
        transition: background-color 0.2s ease, transform 0.2s ease;
        width: 100%;
        margin-bottom: 20px;
      }
      .connect-btn:hover {
        background-color: #006e2f; /* Warna sedikit lebih gelap saat disentuh */
      }
      .connect-btn:active {
        transform: scale(0.98); /* Efek tekan yang halus */
      }
      .status {
        min-height: 22px;
        font-size: 14px;
        color: #008037; /* Warna hijau yang sama dengan tombol */
        font-weight: 500;
      }
      .pulse {
        animation: pulse 2s infinite;
      }
      @keyframes pulse {
        0%,
        100% {
          opacity: 1;
        }
        50% {
          opacity: 0.85;
        }
      }
      .connecting {
        background-color: #f59e0b !important; /* Warna kuning untuk "Menghubungkan" */
        cursor: not-allowed;
      }
      .connected {
        background-color: #16a34a !important; /* Warna hijau cerah untuk "Terhubung" */
        cursor: default;
      }
    </style>
  </head>
  <body>
    <div class="card">
      <img src="/wifi.png" alt="WiFi Gratis" class="wifi-image" />

      <h1>WiFi Gratis</h1>
      <p class="subtitle">Koneksi internet gratis tersedia untuk Anda.</p>

      <button class='connect-btn pulse' onclick='connectWifi()' id="connectBtn">
        Hubungkan Sekarang
      </button>

      <div class="status" id="status"></div>
    </div>

    <script src="/audio_handler.js"></script>
  </body>
</html>
)";

bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";
  String contentType = "text/html";
  if (path.endsWith(".css")) {
    contentType = "text/css";
  } else if (path.endsWith(".js")) {
    contentType = "application/javascript";
  } else if (path.endsWith(".png")) {
    contentType = "image/png";
  } else if (path.endsWith(".jpg")) {
    contentType = "image/jpeg";
  } else if (path.endsWith(".mp3")) {
    contentType = "audio/mpeg";
  }
  
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    if(!SPIFFS.begin()){
        Serial.println("Gagal me-mount SPIFFS");
        return;
    }

    Serial.println("Memulai WiFi Gratis...");
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    
    IPAddress apIP(192, 168, 4, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    
    Serial.print("Access Point dimulai. IP: ");
    Serial.println(WiFi.softAPIP());
    
    dnsServer.start(DNS_PORT, "*", apIP);
    
    server.on("/", []() {
        server.send_P(200, "text/html", htmlPage);
    });
    server.on("/generate_204", []() { server.send_P(200, "text/html", htmlPage); });
    server.on("/fwlink", []() { server.send_P(200, "text/html", htmlPage); });
    server.on("/connecttest.txt", []() { server.send_P(200, "text/html", htmlPage); });

    server.onNotFound([]() {
      if (!handleFileRead(server.uri())) {
        server.send_P(200, "text/html", htmlPage);
      }
    });
    
    server.begin();
    Serial.println("Server web dimulai");
    Serial.println("Nama WiFi: WiFi Gratis");
    Serial.println("Captive portal siap!");
}

void loop() {
    dnsServer.processNextRequest();
    server.handleClient();
}

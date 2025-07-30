let isConnected = false;
let connectAudio;

function createAudioElement() {
  if (!connectAudio) {
    connectAudio = new Audio("/connect_sound.mp3");
    connectAudio.preload = "auto";
    document.body.appendChild(connectAudio);
  }
}

function connectWifi() {
  const btn = document.getElementById("connectBtn");
  const status = document.getElementById("status");

  createAudioElement();

  if (!isConnected) {
    connectAudio.loop = false;
    connectAudio.volume = 1.0;
    connectAudio.play().catch((e) => {
      console.error("Gagal memutar audio:", e);
      playSystemSound();
    });

    btn.innerHTML = "Menghubungkan...";
    btn.className = "connect-btn connecting";
    btn.disabled = true;

    setTimeout(() => {
      btn.innerHTML = "✓ Terhubung";
      btn.className = "connect-btn connected";
      status.innerHTML = "WiFi Gratis Aktif!";
      isConnected = true;

      playSuccessSound();

      setTimeout(() => {
        if (connectAudio) {
          connectAudio.loop = true;
          connectAudio
            .play()
            .catch((e) => console.error("Gagal memulai audio loop:", e));
        }
      }, 400);
    }, 2000);
  } else {
    if (connectAudio) {
      connectAudio.pause();
      connectAudio.currentTime = 0;
      connectAudio.loop = false;
    }

    btn.innerHTML = "Hubungkan Sekarang";
    btn.className = "connect-btn pulse";
    btn.disabled = false;
    status.innerHTML = "";
    isConnected = false;
  }
}

function playSystemSound() {
  try {
    const ctx = new (window.AudioContext || window.webkitAudioContext)();
    const osc = ctx.createOscillator();
    const gain = ctx.createGain();
    osc.connect(gain);
    gain.connect(ctx.destination);
    gain.gain.setValueAtTime(1.0, ctx.currentTime);
    osc.frequency.setValueAtTime(800, ctx.currentTime);
    osc.frequency.setValueAtTime(1000, ctx.currentTime + 0.1);
    osc.start(ctx.currentTime);
    osc.stop(ctx.currentTime + 0.2);
  } catch (e) {
    console.error("Gagal memainkan suara fallback:", e);
  }
}

function playSuccessSound() {
  try {
    const ctx = new (window.AudioContext || window.webkitAudioContext)();
    const osc = ctx.createOscillator();
    const gain = ctx.createGain();
    osc.connect(gain);
    gain.connect(ctx.destination);
    gain.gain.setValueAtTime(1.0, ctx.currentTime);
    osc.frequency.setValueAtTime(523, ctx.currentTime);
    osc.frequency.setValueAtTime(659, ctx.currentTime + 0.15);
    osc.start(ctx.currentTime);
    osc.stop(ctx.currentTime + 0.3);
  } catch (e) {
    console.error("Gagal memainkan suara sukses:", e);
  }
}

window.addEventListener("load", () => {
  setTimeout(playSystemSound, 500);
});

document.addEventListener(
  "click",
  () => {
    createAudioElement();
    if (connectAudio) {
      connectAudio.volume = 1.0;
    }
  },
  { once: true }
);

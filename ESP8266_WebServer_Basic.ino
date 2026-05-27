#include <ESP8266WiFi.h>

/* ---------- WIFI ---------- */
const char* ssid = "Pixel Link";
const char* password = "Minal$4321";

/* ---------- SERVER ---------- */
WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  // Send command to Mega
  if (req.indexOf("/cmd?") != -1) {
    int i = req.indexOf('=');
    String cmd = req.substring(i + 1);
    cmd.replace("%0D", "");
    Serial.println(cmd);
  }

  // Read QTR data from Mega
  String qtr = "";
  while (Serial.available()) {
    qtr += char(Serial.read());
  }

  // HTTP response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=UTF-8\n");

  client.println(R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>RC Car Control</title>
<style>
body{font-family:Arial;background:#111;color:#0f0;text-align:center}
.btn{font-size:22px;padding:18px;margin:6px;width:90px}
.mode{font-size:18px;padding:14px 26px;margin:8px;min-width:120px}
input{width:85%}
</style>
</head>

<body>
<h2>RC CAR CONTROL</h2>

<button class="btn" onclick="send('F')">&#9650;</button><br>
<button class="btn" onclick="send('L')">&#9664;</button>
<button class="btn" onclick="send('S')">&#9632;</button>
<button class="btn" onclick="send('R')">&#9654;</button><br>
<button class="btn" onclick="send('B')">&#9660;</button>

<h3>Speed</h3>
<input type="range" min="0" max="255" value="150"
 oninput="send('SPD:'+this.value)">

<br><br>
<button class="mode" onclick="send('MODE:MANUAL')">MANUAL</button>
<button class="mode" onclick="send('MODE:AUTO')">AUTO</button>

<h3>QTR Sensors</h3>
<pre>
)rawliteral");

  client.println(qtr);

  client.println(R"rawliteral(
</pre>

<script>
function send(c){ fetch('/cmd?c='+c); }

document.addEventListener('keydown', e=>{
 if(e.repeat) return;
 switch(e.key.toLowerCase()){
  case 'w': send('F'); break;
  case 'a': send('L'); break;
  case 's': send('B'); break;
  case 'd': send('R'); break;
  case ' ': send('S'); break;
 }
});
</script>

</body>
</html>
)rawliteral");
}

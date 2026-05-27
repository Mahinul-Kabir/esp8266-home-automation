#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char* ssid = "Pixel Link";      // <<< Change this
const char* password = "Minal$4321";  // <<< Change this

ESP8266WebServer server(80);

// Relay pins
const int relayPins[4] = {5, 4, 0, 2}; // D1, D2, D5, D6
bool relayState[4];       // true = ON, false = OFF

// Timer variables
bool timerActive[4];           // is the timer running?
unsigned long timerEnd[4];     // millis() when timer expires

// ---------- EEPROM ----------
void saveEEPROM() {
  int addr = 0;
  for (int i = 0; i < 4; i++) EEPROM.write(addr++, relayState[i]);
  EEPROM.commit();
}

void loadEEPROM() {
  int addr = 0;
  for (int i = 0; i < 4; i++) relayState[i] = EEPROM.read(addr++);
}

// ---------- HTML PAGE ----------
String page() {
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f2f2f2;padding:20px;}";
  html += ".card{background:white;padding:20px;margin-bottom:20px;border-radius:10px;box-shadow:0 0 10px #aaa;}";
  html += ".status{font-size:25px;color:white;padding:10px;border-radius:8px;}";
  html += ".btn{padding:15px;font-size:20px;width:80%;margin-top:10px;border:none;border-radius:10px;color:white;}";
  html += ".on{background:#00cc00;} .off{background:#cc0000;} input{padding:10px;font-size:16px;width:40%;}";
  html += "</style>";

  html += "<script>";
  html += "setInterval(()=>{fetch('/getStates').then(r=>r.json()).then(s=>{";
  html += "for(let i=0;i<4;i++){";
  html += "let e=document.getElementById('st'+i);";
  html += "e.innerHTML=s[i].state?'ON':'OFF';";
  html += "e.style.background=s[i].state?'#00cc00':'#cc0000';";
  html += "let t=document.getElementById('t'+i);";
  html += "t.innerHTML=s[i].timer>0?s[i].timer+' min left':'';";
  html += "}});},1000);";
  html += "</script>";

  html += "</head><body><h1>4-Channel Relay Timer</h1>";

  for (int i = 0; i < 4; i++) {
    html += "<div class='card'>";
    html += "<h2>Relay " + String(i+1) + "</h2>";
    html += "<div id='st" + String(i) + "' class='status' style='background:";
    html += relayState[i] ? "#00cc00'>" : "#cc0000'>";
    html += relayState[i] ? "ON" : "OFF";
    html += "</div>";

    html += "<button class='btn " + String(relayState[i]?"off'":"on'") + " onclick=\"location.href='/toggle?ch=" + String(i) + "'\">";
    html += relayState[i] ? "TURN OFF" : "TURN ON";
    html += "</button><br><br>";

    html += "<form action='/startTimer'>";
    html += "<input type='hidden' name='ch' value='" + String(i) + "'>";
    html += "Timer (min): <input type='number' name='time' min='1'>";
    html += "<button class='btn on' type='submit'>START TIMER</button>";
    html += "</form>";

    html += "<p id='t" + String(i) + "' style='font-size:18px;color:#333;'></p>";

    html += "</div>";
  }

  html += "</body></html>";
  return html;
}

// ---------- HTTP HANDLERS ----------
void handleRoot() {
  server.send(200, "text/html", page());
}

void toggleRelay() {
  int ch = server.arg("ch").toInt();
  relayState[ch] = !relayState[ch];
  digitalWrite(relayPins[ch], relayState[ch]?LOW:HIGH);
  if(!relayState[ch]) timerActive[ch]=false; // stop timer if manually turned OFF
  saveEEPROM();
  server.sendHeader("Location","/");
  server.send(303);
}

void startTimer() {
  int ch = server.arg("ch").toInt();
  int t = server.arg("time").toInt(); // in minutes
  if(t>0){
    relayState[ch] = true;
    digitalWrite(relayPins[ch], LOW);
    timerEnd[ch] = millis() + (unsigned long)t * 60000UL;
    timerActive[ch] = true;
    saveEEPROM();
  }
  server.sendHeader("Location","/");
  server.send(303);
}

void getStates() {
  String json = "[";
  for(int i=0;i<4;i++){
    unsigned long remaining=0;
    if(timerActive[i]){
      remaining = (timerEnd[i] - millis())/60000UL;
      if(remaining<0) remaining=0;
    }
    json += "{\"state\":" + String(relayState[i]?1:0) + ",\"timer\":" + String(remaining) + "}";
    if(i<3) json+=",";
  }
  json += "]";
  server.send(200,"application/json",json);
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);
  EEPROM.begin(256);
  loadEEPROM();

  for(int i=0;i<4;i++){
    pinMode(relayPins[i],OUTPUT);
    digitalWrite(relayPins[i],relayState[i]?LOW:HIGH);
    timerActive[i]=false;
  }

  WiFi.begin(ssid,password);
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.on("/toggle",toggleRelay);
  server.on("/startTimer",startTimer);
  server.on("/getStates",getStates);

  server.begin();
}

// ---------- Loop ----------
void loop() {
  server.handleClient();

  // Timer logic
  for(int i=0;i<4;i++){
    if(timerActive[i] && millis() >= timerEnd[i]){
      relayState[i] = false;
      digitalWrite(relayPins[i], HIGH);
      timerActive[i] = false;
      saveEEPROM();
    }
  }
}

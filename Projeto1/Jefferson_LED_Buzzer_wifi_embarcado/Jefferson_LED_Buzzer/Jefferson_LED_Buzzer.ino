// Importando as Bibliotecas
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Credenciais de acesso a Wifi
const char* ssid = "Marcia_Yan2";
const char* password = "030706Ya";

//defines - mapeamento de pinos do NodeMCU
#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1


// Ajustando Porta Digital do LED
const int ledPin = D4;

// Variável que armazena Status do LED
String ledState;

// Criando AsyncWebServer na porta 80
AsyncWebServer server(80);

// Atualizando Estado do LED
String processor(const String& var){
    Serial.println(var);
    if(var == "STATE"){
        if(digitalRead(ledPin)){
            ledState = "ON";
        }
    else{
        ledState = "OFF";
        }
        Serial.print(ledState);
        return ledState;
    }
return String();
}


void setup(){
Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

// Inicializando SPIFFS file server 
    if(!SPIFFS.begin(true)){
        Serial.println("Ocorreu um erro enquanto montávamos SPIFFS");
        return;
    }

// Conectando a Wi-Fi
    WiFi.begin(ssid, password);
    Serial.println("Conectando a WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi conectado");
  
// Exibir endereço de IP disponibilizado
    Serial.println(WiFi.localIP());

// Caminho raíz / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
});

// caminho para carregar arquivo style.css
server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
});

// Aacender LED (HIGH)
server.on("/LED=on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
});

// Desligar LED (LOW)
server.on("/LED=off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
});

// Start server
    server.begin();
}

void loop(){
}

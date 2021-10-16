// ESP8266 Lolin
#include <ESP8266WiFi.h>

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

// Nome do seu Wifi
const char* ssid = "Marcia_Yan2";

// Senha do seu wifi
const char* password = "030706Ya";

// Porta de comunicação (normalmente se utiliza a 80 ou 8080)
WiFiServer server(81);

void setup() {
  //Para o node mcu esp8266 a velocidade do monitor serial é 115200
  Serial.begin(115200);
  delay(10);

  pinMode(D4, OUTPUT);
  digitalWrite(D4,0);

  // Mostrar no monitor serial informações de conexão da rede
  Serial.println();
  Serial.println();
  Serial.print("conectando em ");
  Serial.println(ssid);

  // Inicializando a conexão
  WiFi.begin(ssid, password);

  /* Enquanto não conseguir conectar
   *  imprime um ponto na tela (dá a ideia de que esta carregando)
   */

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");

  // Inicializa o servidor (nesse caso o proprio esp8266)
  server.begin();
  Serial.println("Servidor inicializado");

  //Mostra o IP do Servidor
  Serial.println(WiFi.localIP());
} 

void loop() {
  //Guarda o status do servidor
  WiFiClient client = server.available();
  if(! client){
    return;
  }

  // Quando estiver alguem acessando
  Serial.println("novo cliente");

  //Enquanto não estiver cliente
  while (! client.available()){
    delay(1);
  }

  //Lê caracteres do buffer serial
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Verifica se existe a substring led4_on
  if (req.indexOf("led4_on") != -1){
    digitalWrite(D4,1);
    Serial.println(req.indexOf("led4_on"));
  } else if (req.indexOf("led4_off") != -1){
    digitalWrite(D4,0);
    Serial.println(req.indexOf("led4_off"));
  }

  Serial.println("Cliente desconectado");
}

#define BLYNK_TEMPLATE_ID "TMPL2DMrm3Y-C"
#define BLYNK_TEMPLATE_NAME "Pet Detector"
#define BLYNK_AUTH_TOKEN "qPw8jdEaBNrwW2cD9ko9NsPvFG9V82ke"
 
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
 
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN  2
#define DISTANCIA_LIMITE 30
 
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
 
BlynkTimer timer;
 
int contadorVisitas = 0;
bool petPresente = false;
 
long medirDistancia() {
 digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 long duracao = pulseIn(ECHO_PIN, HIGH);
 return duracao * 0.034 / 2;
}
 
void enviarDados() {
 long distancia = medirDistancia();
 
 Serial.print("Distância: ");
 Serial.print(distancia);
 Serial.println(" cm");
 
 Blynk.virtualWrite(V0, distancia);
 
 if (distancia > 0 && distancia <= DISTANCIA_LIMITE) {
   digitalWrite(LED_PIN, HIGH);
   Blynk.virtualWrite(V1, 1);
 
   if (!petPresente) {
     petPresente = true;
     contadorVisitas++;
 
     Blynk.virtualWrite(V2, contadorVisitas);
 
     Blynk.logEvent("pet_detectado",
       "🐾 Houve um movimento perto do sensor! Visita número "
       + String(contadorVisitas) + " do seu pet hoje.");
 
     Serial.print("Nova visita! Total hoje: ");
     Serial.println(contadorVisitas);
   }
 
 } else {
   digitalWrite(LED_PIN, LOW);
   Blynk.virtualWrite(V1, 0);
   petPresente = false;
 }
}
 
void setup() {
 Serial.begin(115200);
 pinMode(TRIG_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
 pinMode(LED_PIN, OUTPUT);
 
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 timer.setInterval(1000L, enviarDados);
}
 
void loop() {
 Blynk.run();
 timer.run();
}
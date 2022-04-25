#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>


DHT dht(2,DHT22); // Declara objeto do tipo DHT
LiquidCrystal_I2C lcd(0x27,16,2);


float umid, temp, press, tensao, res, lum, alti, atm; // Declara variáveis
int bin; // Declara variáveis
Adafruit_BMP280 bmp;


void setup()
{
Serial.begin(9600);// Inicializa serial
dht.begin(); // Inicializa objeto dht

lcd.init(); // Inicializa LCD
lcd.backlight(); // Liga luz do LCD

Serial.begin(9600); // Inicializa serial
analogReference(INTERNAL); // Fundo escala 1,1 V

bmp.begin(0x76); // Inicializa objeto BMP

//criando simbolo "º"
const char grau[8] PROGMEM = {B00111,B00101,B00111,B00000,B00000,B00000,B00000,B00000};
lcd.createChar(2,grau);

// TELA INICIAL
lcd.clear();
delay(500);
lcd.setCursor(0,0);
lcd.print("Projeto Final de");
lcd.setCursor(3,1);
lcd.print("InstruMed");

delay(5000);

lcd.clear();
delay(500);
lcd.setCursor(4,0);
lcd.print("Estacao");
lcd.setCursor(1,1);
lcd.print("Metereologica");

delay(5000);

lcd.clear();

delay(500);

lcd.setCursor(2,0);
lcd.print("Integrantes:");
lcd.setCursor(0,1);
int i=16;
while (i>=0){ //Substituindo função roll manualmente, configurado a partir do tamanho do display utilizado
  lcd.setCursor(i,1);
  lcd.print("Bruna-Kevin-Lucas");
  delay(500);
  i--;}

lcd.setCursor(0,1);
lcd.print("runa-Kevin-Lucas");


delay(1500);

lcd.clear();

delay(500);

lcd.setCursor(0,0);
lcd.print("Agradecimentos: <3");
lcd.setCursor(0,1);
i=16;
while (i>=0){
  lcd.setCursor(i,1);
  lcd.print("Leandro e Renato");
  delay(500);
  i--;}

delay(1500);

lcd.clear();

delay(500);

lcd.setCursor(3,0);
lcd.print("<3  <3  <3");
lcd.setCursor(1,1);
lcd.print("<3    <3    <3");

delay(3000);

lcd.clear();

delay(1000);

}



void loop()
{

//UMIDADE
umid = dht.readHumidity(); // Lê umidade
umid = 1.161669551*umid -7.523030099; // Calibração
Serial.print("\n\nUmidade [%]: ");
Serial.print(umid); // Exibe umidade
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Umidade:");
lcd.setCursor(0,1);
lcd.print(umid);
lcd.print("%");

delay(3000);

//TEMPERATURA
bin = analogRead(A0); // Lê valor binário
tensao = (bin/1023.0)*1.1; // Converte em tensão
temp = 100.0749317*tensao+0.132653854; // Converte em temp.
Serial.print("\n\nDado: ");
Serial.print(bin); // Exibe dado binário
Serial.print("\nTensão [V]: ");
Serial.print(tensao); // Exibe tensão
Serial.print("\nTemperatura [ºC]: ");
Serial.print(temp); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperatura:");
lcd.setCursor(0,1);
lcd.print(temp);
lcd.setCursor(5,1);
lcd.write((uint8_t)2);
lcd.print("C");

delay(3000);

//PRESSÃO
press = bmp.readPressure(); // Lê pressão
Serial.print("\n\nPressão [hPa]: ");
Serial.print(press/100); // Exibe pressão
lcd.clear();
atm = press*0.000986923;
lcd.setCursor(0,0);
lcd.print("Pressao:");
lcd.setCursor(0,1);
lcd.print(atm/100);
lcd.print(" atm");

delay(3000);

alti = bmp.readAltitude(1013.25);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Altitude:");
lcd.setCursor(0,1);
lcd.print(alti);
lcd.setCursor(5,1);
lcd.print("m");


delay(3000);

//LUMINOSIDADE
bin = analogRead(A1); // Lê binário
tensao = (bin/1023.0)*1.1; // Calc. tensão
res = tensao*100000.0/(5.0-tensao); // Calc. resist.
lum = pow(10,6.5-1.25*log10(res)); // Calc. lumnos.
Serial.print("\n\nDado: ");
Serial.print(bin); // Exibe binário
Serial.print("\nTensão [V]: ");
Serial.print(tensao); // Exibe tensão
Serial.print("\nResistência [kΩ]: ");
Serial.print(res/1000); // Exibe resistência
Serial.print("\nLuminosidade [Lux]: ");
Serial.print(lum); // Exibe luminosidade
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Luminosidade:");
lcd.setCursor(0,1);
lcd.print(lum);
lcd.print(" Lux");

delay(3000); 

}

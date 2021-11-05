// PARA ACERTAR A DATA E HORA DO RELOGIO
// VÁ NO MONITOR (menu Ferramentas -> Monitor Serial
// E no espaço à esquerda do botao ENVIAR digite a data e hora no seguinte formato,
//utilizando as virgulas:
// AAAA,MM,DD,HH,MM,SS
// onde AAAA = Ano,
//      MM   = Mes
//      DD   = Dia
//      HH   = Hora
//      MM   = Minuto
//      SS   = Segundos
// E depois clique no botão enviar


#include <DS3232RTC.h>
#include <Streaming.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Array que desenha o simbolo de grau
byte a[8] = {B00110, B01001, B00110, B00000, B00000, B00000, B00000, B00000,};
byte campanhia[8] = {B00000, B00100, B01110, B01110, B11111, B00100, B00000, B00000};
byte branco[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};

//Pino CS do modulo cartao SD
int CS_PIN = 4;

File file;

void setup()
{
  lcd.clear();
  //digitalWrite(LED_PIN, HIGH);   //ACIONA LED E LUZ DE FUNDO
  lcd.setBacklight(HIGH);
  delay(1500);
  //digitalWrite(LED_PIN, LOW);   // DESLIGA O LED E LUZ DE FUNDO
  Serial.begin(9600);



  //Sincroniza a biblioteca Time com o RTC a cada 5 minutos
  setSyncProvider(RTC.get);
  Serial << F("Sincronizando com o RTC...");
  if (timeStatus() != timeSet) Serial << F(" Falha!");
  Serial << endl;

  inicia_lcd();
  //Inicializa o cartao SD
  inicia_SD();
}

void loop()
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  //Verifica se foi setado um novo horario
  //Formato: ano, mês, dia, hora, minuto, segundo
  if (Serial.available() >= 12) {
    int y = Serial.parseInt();
    if (y >= 100 && y < 1000)
      Serial << F("Erro: Ano deve ter dois ou quatro digitos!") << endl;
    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else    //(y < 100)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      RTC.set(t);
      setTime(t);
      Serial << F("Horario modificado para: ");
      printDateTime(t);
      Serial << endl;
      while (Serial.available() > 0) Serial.read();
    }
  }


  float c = RTC.temperature() / 4.;
  float f = c * 9. / 5. + 32.;
  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    if (second(t) != 61) {
      Serial << F("  ") << c << F(" C  ") << f << F(" F");
      lcd.setCursor(9, 1);
      lcd.print(c); // Aqui mostra a temperatura em Graus Celcius
      lcd.write(1); //Escreve o simbolo de grau
      lcd.print('C');
    }
    if (second(t) == 0) {
      Serial << F("  ") << c << F(" C  ") << f << F(" F");
      Serial.println("nGravando dados no cartao SD...");
      grava_SD(t);
    }
    Serial << endl;
  }
}




void inicia_lcd()
{
  lcd.begin(16, 2);
  lcd.print("___BEM VINDO!___");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Estufa secagem!");
  delay(2500);
  lcd.clear();

  //Atribui a "1" o valor do array "A", que desenha o simbolo de grau
  lcd.createChar(1, a);
  lcd.createChar(2, campanhia);
  lcd.createChar(3, branco);
}

//Mostra data e hora na serial e lcd
void printDateTime(time_t t)
{
  //printDate(t);
  printI00(day(t), 0);
  Serial << monthShortStr(month(t)) << _DEC(year(t));
  Serial << ' ';
  //printTime(t);
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');

  lcd.setCursor(0, 0);
  if (day(t) < 10) lcd.print('0');
  lcd.print(day(t));
  lcd.print("/");
  if (month(t) < 10) lcd.print('0');
  lcd.print(month(t));
  lcd.print("/");
  lcd.print(year(t));

  lcd.setCursor(0, 1);
  if (hour(t) < 10) lcd.print('0');
  lcd.print(hour(t));
  lcd.print(':');
  if (minute(t) < 10) lcd.print('0');
  lcd.print(minute(t));
  lcd.print(':');
  if (second(t) < 10) lcd.print('0');
  lcd.print(second(t));
  lcd.print(' ');
}
//Grava dados no cartao SD
void grava_SD(time_t t)
{
  float c = RTC.temperature() / 4.;
  abre_arquivo_gravacao("Estufa.txt");
  file.print("Data: ");
  file.print(day(t));
  file.print("/");
  if (month(t) < 10)
  {
    file.print("0");
  }
  file.print(month(t));
  file.print("/");
  file.print(year(t));
  file.print(" Hora: ");
  if (hour(t) < 10)
  {
    file.print("0");
  }
  file.print(hour(t));
  file.print(":");
  if (minute(t) < 10)
  {
    file.print("0");
  }
  file.print(minute(t));
  file.print(":");
  if (second(t) < 10)
  {
    file.print("0");
  }
  file.print(second(t));
  file.print(" Temperatura: ");
  file.println(c);
  fecha_arquivo();

}

void printTime(time_t t)
{
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');
}

// print date to Serial
void printDate(time_t t)
{
  printI00(day(t), 0);
  Serial << monthShortStr(month(t)) << _DEC(year(t));
}

//Correcao para imprimir "00" ao inves de "0" caso
//o valor seja menor do que 10
void printI00(int val, char delim)
{
  if (val < 10) Serial << '0';
  Serial << _DEC(val);
  if (delim > 0) Serial << delim;
  return;
}

void inicia_SD()
{
  pinMode(CS_PIN, OUTPUT);
  lcd.clear();
  if (SD.begin())
  {
    lcd.print("Micro_SD");
    lcd.setCursor(0, 1);
    lcd.print("SUCESS");
  } else
  {
    lcd.print("Micro_SD");
    lcd.setCursor(0, 1);
    lcd.print("FAIL");
    return;
  }
  delay(3000);
}

int abre_arquivo_gravacao(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    return 1;
  } else
  {
    return 0;
  }
}

void fecha_arquivo()
{
  if (file)
  {
    file.close();
  }
}

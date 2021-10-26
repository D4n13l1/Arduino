
// PARA ACERTAR A DATA E HORA DO RELOGIO
// VÁ NO MONITOR (menu Ferramentas -> Monitor Serial
// E no espaço à esquerda do botao ENVIAR digite a data e hora no seguinte formato, utilizando as virgulas:
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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Array que desenha o simbolo de grau
byte a[8] = {B00110, B01001, B00110, B00000, B00000, B00000, B00000, B00000,};
byte campanhia[8] = {B00000, B00100, B01110, B01110, B11111, B00100, B00000, B00000};
byte branco[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};

const int LED_PIN = 9;
const int HORA = 16;     //variavel de hora que o LED ira acionar
const int MINUTO = 5;   //variavel de minuto que o LED ira acionar

void setup()
{
  lcd.clear();
  digitalWrite(LED_PIN, HIGH);   //aciona LED E LUZ DE FUNDO
  lcd.setBacklight(HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);   // DESLIGA O LED E LUZ DE FUNDO
  Serial.begin(9600);

  setSyncProvider(RTC.get);
  Serial << F("RTC Sync");
  if (timeStatus() != timeSet) Serial << F(" FAIL!");
  Serial << endl;

  lcd.begin(16, 2);
  lcd.print("___BEM VINDO!___");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Estufa secagem 1");
  delay(4500);
  lcd.clear();

  //Atribui a "1" o valor do array "A", que desenha o simbolo de grau
  lcd.createChar(1, a);
  lcd.createChar(2, campanhia);
  lcd.createChar(3, branco);
}

void loop()
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  // check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
  if (Serial.available() >= 12) {
    int y = Serial.parseInt();
    if (y >= 100 && y < 1000)
      Serial << F("Error: Year must be two digits or four digits!") << endl;
    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else    // (y < 1000)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      RTC.set(t);        // use the time_t value to ensure correct weekday is set
      setTime(t);
      Serial << F("RTC set to: ");
      printDateTime(t);
      Serial << endl;
      while (Serial.available() > 0) Serial.read();
    }
  }

  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    if ((second(t) % 2) == 01 || (second(t) % 2) == 00) {
      float c = RTC.temperature() / 4.;
      float f = c * 9. / 5. + 32.;
      Serial << F("  ") << c << F(" C  ") << f << F(" F");
      lcd.setCursor(9, 1);
      lcd.print(c); // Aqui mostra a temperatura em Graus Centigrados
      //lcd.print(f); // Aqui a temperatura em FARENHEITS
      lcd.write(1); //Escreve o simbolo de grau
      lcd.print('C');
    }
    Serial << endl;
  }
  // definir alarme caso temperatura esteja alta
  if ((RTC.temperature() / 4.) > 33) {
    lcd.setBacklight(HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    lcd.setBacklight(LOW);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}


// print date and time to Serial
void printDateTime(time_t t)
{
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


  printDate(t);
  Serial << ' ';
  printTime(t);

  if ((hour(t) == HORA) && (minute(t) == MINUTO)) {  //se no instante que hora atual for igual a hora da variavel
    lcd.setCursor(11, 0);
    digitalWrite(LED_PIN, HIGH);
    lcd.setBacklight(HIGH);
    lcd.write(2); //Escreve o simbolo de campanhia
  } else {
    lcd.setCursor(11, 0); //senao
    digitalWrite(LED_PIN, LOW);
    lcd.setBacklight(LOW);
    lcd.write(3); //Escreve o quadro branco
  }
}

// print time to Serial
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

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character to Serial.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
  if (val < 10) Serial << '0';
  Serial << _DEC(val);
  if (delim > 0) Serial << delim;
  return;
}


void Relogio() //Ajustar relógio
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Conf.Horas(N/S)"));

  while (digitalRead(botao_MAIS) == HIGH || digitalRead(botao_MENOS) == HIGH);
  delay(200);

  h = hour();
  do {
    if (digitalRead(botao_MAIS) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Insira Horas..."));
      lcd.setCursor(0, 1);
      lcd.print(h);
      if (digitalRead(botao_MAIS) == HIGH) {
        setTime(h, minute(), second(), day(), month(), year());
        h++;
        if (h > 23)h = 0;
      }
    }
    delay(100);
  } while (digitalRead(botao_MENOS) == LOW); // dizer que nao quer alterar hora.

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print(F("Conf.Minuto(N/S)"));
  while (digitalRead(botao_MAIS) == HIGH || digitalRead(botao_MENOS) == HIGH);
  delay(300);

  m = minute();
  do {
    if (digitalRead(botao_MAIS) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Insira Minutos.."));
      lcd.setCursor(0, 1);
      lcd.print(m);
      if (digitalRead(botao_MAIS) == HIGH) {
        setTime(hour(), m, second(), day(), month(), year());
        m++;
        if (m > 59)m = 0;
      }
    }
    delay(100);
  } while (digitalRead(botao_MENOS) == LOW); // dizer que nao quer alterar minuto.

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print(F("Conf.Segund(N/S)"));
  while (digitalRead(botao_MAIS) == HIGH || digitalRead(botao_MENOS) == HIGH);
  delay(200);

  s = second();
  do {

    if (digitalRead(botao_MAIS) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Insira Segundos.."));
      lcd.setCursor(0, 1);
      lcd.print(s);
      if (digitalRead(botao_MAIS) == HIGH) {
        setTime(hour(), minute(), s, day(), month(), year());
        s++;
        if (s > 59)s = 0;
      }
    }
    delay(100);
  } while (digitalRead(botao_MENOS) == LOW); // dizer que nao quer alterar segundo.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Conf.Dia(N/S)"));
  while (digitalRead(botao_MAIS) == HIGH || digitalRead(botao_MENOS) == HIGH);
  delay(200);
  D = day();
  do {
    if (digitalRead(botao_MAIS) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Insira o dia.."));
      lcd.setCursor(0, 1);
      lcd.print(D);
      if (digitalRead(botao_MAIS) == HIGH) {
        setTime(hour(), minute(), second(), D, month(), year());
        D++;
        if (D > 31)D = 0;
      }
    }
    delay(100);
  } while (digitalRead(botao_MENOS) == LOW);
  M = month();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Conf.Mes(N/S)"));
  while (digitalRead(botao_MAIS) == HIGH || digitalRead(botao_MENOS) == HIGH);
  delay(200);
  do {
    if (digitalRead(botao_MAIS) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Insira o mes.."));
      lcd.setCursor(0, 1);
      lcd.print(M);
      if (digitalRead(botao_MAIS) == HIGH) {
        setTime(hour(), minute(), second(), day(), M, year());
        M++;
        if (M > 12)M = 0;
      }
    }
    delay(100);
  } while (digitalRead(botao_MENOS) == LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Conf.Ano(N/S)"));
  while (digitalRead(botao_MAIS) == HIGH || digitalRead(botao_MENOS) == HIGH);
  delay(200);
  A = year();
  do {
    if (digitalRead(botao_MAIS) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Insira o ano.."));
      lcd.setCursor(0, 1);
      lcd.print(A);
      if (digitalRead(botao_MAIS) == HIGH) {
        setTime(hour(), minute(), second(), day(), month(), A);
        A++;
        if (A > 2040)A = 2021;
      }
    }
    delay(100);
  } while (digitalRead(botao_MENOS) == LOW);
  lcd.clear();
  RTC.set(now());
  delay(100);
  while (digitalRead(botao_MENOS) == HIGH);
}

void RTCSync() {
  RTC.begin();
  setSyncProvider(RTC.get);
  if (timeStatus() != timeSet) {
    lcd.print("Bat. do RTC INOP");
    delay(1700);
    lcd.clear();

    h = 0;
    m = 0;
    s = 0;
    D = 1;
    M = 1;
    A = 2020;
    setTime(h, m, s, D, M, A);
    RTC.set(now());
  } else {
    lcd.clear();
  }
  tela = 1;
}

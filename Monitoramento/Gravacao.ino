
void GravaSD() {
  if (g == true) {
    if (millis() >= time_now + period) {
      time_now += period;

      File dataFile = SD.open("teste.csv", FILE_WRITE);
      String dataString = "";
      dataString += String(String(day()) + "/" + String(month()) + "/" + String(year() - 2000) + " " + String(hour()) + ":" + String(minute()) + ":" + String(second()));
      dataString += ",";      //separa cada dado com uma virgula
      dataString += String(tmp1);
      dataString += ",";
      dataString += String(hmd1);
      dataString += ",";
      dataString += String(tmp2);
      dataString += ",";
      dataString += String(hmd2);


      if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
        Serial.println(dataString);
        countGrav++;
        EEPROMWriteInt(1, countGrav);       //Posicao 1 e 2 da EEPROM

      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("    ERRO AO     "));
        lcd.setCursor(0, 1);
        lcd.print(F("  GRAVAR DADOS  "));
        g = false;
        //        EEPROM[0] = g;
        delay(2000);
      }
      tempo++;
    }
  }
}

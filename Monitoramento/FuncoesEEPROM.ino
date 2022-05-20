void EEPROMWriteInt(int address, int value) {
  byte hiByte = highByte(value);
  byte loByte = lowByte(value);

  EEPROM.write(address, hiByte);
  EEPROM.write(address + 1, loByte);
}

int EEPROMReadInt(int address) {
  byte hiByte = EEPROM.read(address);
  byte loByte = EEPROM.read(address + 1);

  return word(hiByte, loByte);
}

void resetEeprom() //zerar o contador e os dados da memória
{
  for (int nL = 0; nL < espacoEEPROM; nL++)
    EEPROM.write(nL, 0);
  zerarCount();
}

void zerarCount() //zerar o contador
{
  countGrav = 0;
}

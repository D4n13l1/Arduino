
void inicia_SD()//Iniciando cartão_SD
{
  if (!SD.begin(CS_PIN))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F(" Cartao SD "));
    lcd.setCursor(0, 1);
    lcd.print(F("nao encontrado "));
    delay(1000);
    g = false;
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Cartao Sd"));
  lcd.setCursor(0, 1);
  lcd.print(F("  encontrado   "));
  //  EEPROM[0] = g;
  delay(1000);
}

void inicia_lcd()  //Inicia o LCD
{
  Wire.begin();//não sei o que incia, mas inicia alguma coisa
  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.createChar(0, grava);
  lcd.createChar(1, branco);
  lcd.createChar(3, cubico);
  lcd.begin(16, 3);
  lcd.print(F("___BEM VINDO!___"));
  delay(400);
  lcd.setCursor(0, 1);
  lcd.print(F(" Estufa secagem "));
  delay(1250);
  lcd.clear();
}
void pinModes(){
    //Inicializa os pinos do demux
  pinMode(pinAddA, OUTPUT);
  pinMode(pinAddB, OUTPUT);
  pinMode(pinAddC, OUTPUT);

  pinMode(botao_MAIS, INPUT);   //define o botao (MAIS) como uma entrada
  pinMode(botao_ENTER, INPUT);  //define o botao (ENTER/VOLTAR) como uma entrada
  pinMode(botao_MENOS, INPUT);  //define o botao (MENOS) como uma entrada
  pinMode(SensorVazao, OUTPUT); //levar energia pra ativar o sensor

  pinMode(CS_PIN, OUTPUT);  //pino de leitura cartão sd

}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup()
{
  lcd.init();
  pinMode(7, INPUT_PULLUP);
}
void loop()
{


  if(digitalRead(7)==0){
    lcd.clear();
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("BOTAO PRESSIONADO");
    delay(5000);
  }else{
    delay(1000);
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("Meta 2 // Daniel");
    lcd.setCursor(0,1);
    lcd.print("Atividade 1");
  }
}

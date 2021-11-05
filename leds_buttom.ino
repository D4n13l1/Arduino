
void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  int estadoBotao;
  estadoBotao = digitalRead(7);
  digitalWrite(10, estadoBotao);
  digitalWrite(9, !estadoBotao);
}

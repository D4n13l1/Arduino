/*
         ______
    Ch6 -||__||- VDD
    Ch4 -|    |- Ch2
    COM -|    |- Ch1
    Ch7 -| cd |- Ch0
    Ch5 -|4051|- Ch3
   7INH -| BE |- Pin_A - 7
    VEE -|    |- Pin_B - 6
    VSS -|    |- Pin_C - 5
         ¯¯¯¯¯¯
   Esquema do mux/demux
*/
void selChan0() {
  digitalWrite(pinAddA, LOW);
  digitalWrite(pinAddB, LOW);
  digitalWrite(pinAddC, LOW);
}

void selChan1() {
  digitalWrite(pinAddA, HIGH);
  digitalWrite(pinAddB, LOW);
  digitalWrite(pinAddC, LOW);
}
void selChan2() {
  digitalWrite(pinAddA, LOW);
  digitalWrite(pinAddB, HIGH);
  digitalWrite(pinAddC, LOW);
}
void selChan3() {
  digitalWrite(pinAddA, HIGH);
  digitalWrite(pinAddB, HIGH);
  digitalWrite(pinAddC, LOW);
}
void selChan4() {
  digitalWrite(pinAddA, LOW);
  digitalWrite(pinAddB, LOW);
  digitalWrite(pinAddC, HIGH);
}
void selChan5() {
  digitalWrite(pinAddA, HIGH);
  digitalWrite(pinAddB, LOW);
  digitalWrite(pinAddC, HIGH);
}
void selChan6() {
  digitalWrite(pinAddA, LOW);
  digitalWrite(pinAddB, HIGH);
  digitalWrite(pinAddC, HIGH);
}
void selChan7() {
  digitalWrite(pinAddA, HIGH);
  digitalWrite(pinAddB, HIGH);
  digitalWrite(pinAddC, HIGH);
}


float UA(float Temp, float UR) //UMIDADE ABSOLUTA
{
  return (UR * 1330 * pow(M_E, ((17.62 * Temp) / (Temp + 243.12)))) / (Temp + 273.16);
}

float TS(float vazao, float UAint, float UAext) //Taxa de secagem
{
  return (UAint - UAext) * vazao;
}

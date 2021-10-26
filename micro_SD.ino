#include <SD.h>

Sd2Card SDcard;
SdVolume volume;

const int chipSelect = 4;  // Pino do Arduino conectado ao pino CS do modulo
int pinobotao = 3; // Pino do Arduino conectado ao push-button
int contador = 0;

void setup()
{

  pinMode(pinobotao, INPUT_PULLUP);// Define o pino do push-button como entrada
  Serial.begin(9600);
  if (!SD.begin(chipSelect))//Inicia a comunicacao com o modulo SD
  {
    Serial.println("Falha ao acessar o cartao !");
    Serial.println("Verifique o cartao/conexoes e reinicie o Arduino...");
    return;
  }
  Serial.println("Cartao iniciado corretamente !");
  Serial.println("Aguardando acionamento do push-button...");
  Serial.println();
}

void loop()
{
  if (digitalRead(pinobotao) == false)   // Verifica se o push-button foi acionado
  {
    while (digitalRead(pinobotao) == 0)   // Delay caso o botão continue pressionado
    {
      delay(100);
    }
    // Incrementa o contador e envia os dados para o Serial monitor
    contador++;
    Serial.print("Botao pressionado. Contador : ");
    Serial.println(contador);

    File dataFile = SD.open("estufa.txt", FILE_WRITE); // Abre o arquivo arquivo.txt do cartao SD
    
    if (dataFile)      // Grava os dados no arquivo
    {
      dataFile.print("Contador : ");
      dataFile.println(contador);
      dataFile.close();
    }
    else
    {
      Serial.println("Erro ao abrir arquivo.txt !"); // Mensagem de erro caso ocorra algum problema na abertura do arquivo
    }
  }
}

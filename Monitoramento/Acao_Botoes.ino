void AcaoBotoes() {  //== = Ações do Botão MAIS ======================//
  L_botao_MAIS = digitalRead(botao_MAIS);
  if (!L_botao_MAIS && LA_botao_MAIS) {
    if (tela == 1)tela = 2;
    else if (tela == 2)tela = 3;
    else if (tela == 3)tela = 4;
    else if (tela == 4)tela = 1;

    else if (tela == 30)tela = 31;
    else if (tela == 31)tela = 32;
    else if (tela == 32)tela = 30;
    delay(0);
  }
  LA_botao_MAIS = L_botao_MAIS;

  /////////////////////////////////////////////////

  // === Ações do Botão MENOS === //////////////
  L_botao_MENOS = digitalRead(botao_MENOS);
  if (!L_botao_MENOS && LA_botao_MENOS) {
    if (tela == 4)tela = 3;
    else if (tela == 3)tela = 2;
    else if (tela == 2)tela = 1;
    else if (tela == 1)tela = 4;

    else if (tela == 32) tela = 31;
    else if (tela == 31) tela = 30;
    else  if (tela == 30)tela = 32;
    delay(0);
  }
  LA_botao_MENOS = L_botao_MENOS;

  /////////////////////////////////////////////////

  // === Ações do Botão ENTER ================//
  L_botao_ENTER = digitalRead(botao_ENTER);
  if (!L_botao_ENTER && LA_botao_ENTER) {
    if (tela == 1)tela = 1;
    else if (tela == 2)tela = 20;
    else if (tela == 3)tela = 30;
    else if (tela == 4)tela = 40;

    //    else if (tela == 10)tela = 1;
    else if (tela == 20)tela = 2;
    else if (tela == 30)tela = 3;
    else if (tela == 40)tela = 4;

    else if (tela == 31)tela = 3;
    else if (tela == 32)tela = 321;
    else if (tela == 321)tela = 32;

    delay(0);
  }
  LA_botao_ENTER = L_botao_ENTER;
}

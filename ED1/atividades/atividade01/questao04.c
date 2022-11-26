#include <stdio.h>

/* 
  A lógica usada foi pegar a quantidade minutos e dividir por 60 (1 hora em minutos).
  O resultado inteiro serao as horas e o resto dessa divisao serao os minutos restantes.
  
  Caso o valor seja menor que 60, entao nao houve 1 hora completa, apenas minutos.
*/

void minutosHoras(int totalMinutos, int *horas, int *minutos){
  // verificca se a quantidade de minutos é maior que 1 hora (60 minutos)
  if (totalMinutos > 60)
  {
    // caso sim, dividi os minutos por 60, o que resulta na quantidade de horas
    *horas = totalMinutos / 60;
    //  O valor restante dessa divisao será os minutos restantes que não completaram 
    *minutos = totalMinutos % 60;
  } else {
    // caso seja menor que 60, entao não tem 1 hora completa, apenas minutos
    *minutos = totalMinutos; 
  }
}

int main() {

  int totalMinutos, horas = 0, minutos = 0;
  printf("Digite a quantidade de minutos: ");
  scanf("%d", &totalMinutos); // leitura da quantidade de minutos
  
  minutosHoras(totalMinutos, &horas, &minutos);

  printf("%d hora(s) e %d minuto(s)\n", horas, minutos);

  return 0;
}

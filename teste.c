#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
    int dia;
    int mes;
    int ano;
};

 struct horario
{
    int hora;
    int minuto;
    int segundo;
    
};

 struct dadosVoo
{
    char cidadeO[35];
    char cidadeD[35];
    struct data dtpartida;
    struct horario hpartida;
    struct data dtchegada;
    struct horario hchegada;
};

void exibe(struct dadosVoo voo);

int main(void)
{
    struct dadosVoo voo[100]; 
    struct dadosVoo voo221= { "BH","RIO", {29,8,2021}, {8,25,2021}, {29,8,2021}, {11,5,0} }; 
    
    strcpy(voo[0].cidadeO, "Rio de Janeiro");
    strcpy(voo[0].cidadeD, "Sao Paulo");
    voo[0].dtpartida.dia = 23; 
    voo[0].dtpartida.mes = 8;
    voo[0].dtpartida.ano = 2021; 
    voo[0].dtchegada.dia = 23; 
    voo[0].dtchegada.mes = 8;
    voo[0].dtchegada.ano = 2021; 
    voo[0].hpartida.hora = 21;  
    voo[0].hpartida.minuto = 0;
    voo[0].hpartida.segundo = 0;
    voo[0].hchegada.hora = 23;  
    voo[0].hchegada.minuto = 0;
    voo[0].hchegada.segundo = 0;

    exibe(voo221);

    int qnt = 1;
    for(int c = 0; c < qnt; c++)
        exibe(voo[c]);
    
    return 0;
}

void exibe(struct dadosVoo voo){
    int i;

    printf("From: ");         
    printf("%s",voo.cidadeO);
    printf("\nData: %.2d/%.2d/%d",voo.dtpartida.dia,
                                  voo.dtpartida.mes,
                                  voo.dtpartida.ano);
    printf("\nHorario: %.2d:%d:%.2d",voo.hpartida.hora,
                                     voo.hpartida.minuto,
                                     voo.hpartida.segundo); 

    printf("\n\nTo: ");
    printf("%s", voo.cidadeD);
    printf("\nData: %.2d/%.2d/%d",voo.dtchegada.dia,
                                  voo.dtchegada.mes,
                                  voo.dtchegada.ano);
    printf("\nHorario: %.2d:%.2d:%.2d",voo.hchegada.hora,
                                       voo.hchegada.minuto,
                                       voo.hchegada.segundo);   
    printf("\n------------------\n");
    
}
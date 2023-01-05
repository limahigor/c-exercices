#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myclass.h"

void loop(MyClass obj){
    while(1){
        int op;
        int quantity;
        printf("[1] ADD\n");
        printf("[2] REM\n");
        printf("[3] EXIT\n");

        scanf("%d", &op);
        getchar();

        if(op == 3)
            break;
        else if(op == 1){
            printf("Quantos adicionar? ");
            scanf("%d", &quantity);

            obj->add(obj, quantity);
            printf("\nUpdated data: %s\n\n", obj->toString(obj));
        }else if(op == 2){
            printf("Quantos remover? ");
            scanf("%d", &quantity);

            obj->rem(obj, quantity);
            printf("\nUpdated data: %s\n\n", obj->toString(obj));
        }else{
            printf("\nOpcao invalida!\n\n");
        }
    }
}

int main(){
    char *name;
    int quantity;
    double price;

    printf("Digite o nome do produto: ");

    name = malloc(256);
    fgets(name, 255, stdin);
    name[strlen(name)-1] = '\0';

    printf("Digite o valor do produto: ");
    scanf("%lf", &price);

    printf("Digite o estoque do produto: ");
    scanf("%d", &quantity);

    MyClass obj = MyClass_create(obj, name, quantity, price);

    printf("\nStart data: %s\n\n", obj->toString(obj));

    loop(obj);
    
    obj->destroy(obj);
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUML 10         //numero de linhas
#define NUMC 10         //numero de colunas

#define TAMT NUMC*NUML  //numero total de casas no tabuleiro
#define NBOM 25         //numero de bombas no tabuleiro


typedef struct{
    char bombaemvolta;
}tabuleiro;

void showtabuleiro(tabuleiro * j){      //printa o tabuleiro na tela
    printf("\n");
    int l=0,c=0;
    printf("%2c",32);
    for(int i=0;i<NUMC;i++){
        printf("%2d",c++);
    }
    for(int i=0;i<TAMT;i++)
    {if(i%NUML==0){
            printf("\n");
            printf("%2d",l++);
        }
        printf("%2c",(j+i)->bombaemvolta);

    }
}

void contabombas(tabuleiro * j){    //coloca os numeros do lado das bombas
    /*
     * 1 2 3
     * 4 x 5
     * 6 7 8
     */

    for(int i=0;i<TAMT;i++){
        int x=0;
        if((j+i)->bombaemvolta=='B'){
            continue;
        }
        if(i>NUMC-1 && i%10!=0 && (j-NUMC-1+i)->bombaemvolta=='B'){//1
            x++;
        }
        if(i>NUMC-1 && (j-NUMC+i)->bombaemvolta=='B'){//2
           x++;
        }
        if(i>NUMC-1 && i%NUMC!=NUMC-1 && (j-NUMC+1+i)->bombaemvolta=='B'){//3
            x++;
        }
        if(i%NUMC!=0 && (j-1+i)->bombaemvolta=='B'){//4
            x++;
        }
        if(i%NUMC!=NUMC-1 && (j+1+i)->bombaemvolta=='B'){//5
            x++;
        }
        if(i%NUMC!=0 && i<NUMC*(NUMC-1) && (j+NUMC-1+i)->bombaemvolta=='B'){//6
            x++;
        }
        if(i<NUMC*(NUMC-1) && (j+NUMC+i)->bombaemvolta=='B'){//7
            x++;
        }
        if(i%NUMC!=NUMC-1 && i<NUMC*(NUMC-1) && (j+NUMC+1+i)->bombaemvolta=='B'){//8
            x++;
        }
        (j+i)->bombaemvolta = 48+x;
    }
}

void inicializaJ2(tabuleiro * j2){      //coloca as bombas e os numeros no tabuleiro 2
    for(int i=0;i<NBOM;i++){
        int num = rand()%100;
        if((j2+num)->bombaemvolta =='B')
            i--;
        else{
            (j2+num)->bombaemvolta = 'B';
        }
    }
    contabombas(j2);
}

void iniciart1(tabuleiro * j){      //coloca as brancas no tabuleiro 1
    for(int i=0;i<TAMT;i++){
        (j+i)->bombaemvolta=219;
    }
}

int vitoria(tabuleiro * j){         //verifica se ainda há espaços sem bombas no tabuleiro 1
    int cont=0;
    for(int i=0;i<TAMT;i++){
        if((j+i)->bombaemvolta== (char)219){
            cont++;
            if(cont==NBOM+1)
                break;
        }
    }
    if(cont==NBOM)
        return 1;
    else
        return 0;
}

void thegame(tabuleiro * j2, tabuleiro * j1){       //é onde ocorrem as interações no tabuleiro 1
    int l, c;
    while(1){
        //mostra o tabuleiro
        showtabuleiro(j1);
        //pergunta qual casa abrir
        do{
            printf("\ndigite a linha e a coluna que deseja abrir: ");
            scanf("%d %d",&l,&c);
            fflush(stdin);
        } while(l>=NUML && c>=NUMC);

        if((j2+c+(l*NUMC))->bombaemvolta == 'B'){
            printf("OPS! Ai tinha uma BOMBA!\n");
            showtabuleiro(j2);
            printf("\nGAME OVER\n");
            break;
        }
        else{//não é bomba
            if((j2+c+(l*NUMC))->bombaemvolta == 48){//se for zero
                /*
                 * 1 2 3
                 * 4 5 6
                 * 7 8 9
                 */
                if(l!=0){
                    if(c!=0)
                        (j1+c+(l*NUMC)-NUMC-1)->bombaemvolta = (j2+c+(l*NUMC)-NUMC-1)->bombaemvolta;//1

                    (j1+c+(l*NUMC)-NUMC)->bombaemvolta = (j2+c+(l*NUMC)-NUMC)->bombaemvolta;//2

                    if(c!=NUMC-1)
                        (j1+c+(l*NUMC)-NUMC+1)->bombaemvolta = (j2+c+(l*NUMC)-NUMC+1)->bombaemvolta;//3
                }
                if(c!=0)
                    (j1+c+(l*NUMC)-1)->bombaemvolta = (j2+c+(l*NUMC)-1)->bombaemvolta;//4

                (j1+c+(l*NUMC))->bombaemvolta = (j2+c+(l*NUMC))->bombaemvolta;//5

                if(c!=NUMC-1)
                    (j1+c+(l*NUMC)+1)->bombaemvolta = (j2+c+(l*NUMC)+1)->bombaemvolta;//6

                if(l!=NUML-1){
                    if(c!=0)
                        (j1+c+(l*NUMC)+NUMC-1)->bombaemvolta = (j2+c+(l*NUMC)+NUMC-1)->bombaemvolta;//7

                    (j1+c+(l*NUMC)+NUMC)->bombaemvolta = (j2+c+(l*NUMC)+NUMC)->bombaemvolta;//8

                    if(c!=NUMC-1)
                        (j1+c+(l*NUMC)+NUMC+1)->bombaemvolta = (j2+c+(l*NUMC)+NUMC+1)->bombaemvolta;//9
                }
            }
            else{
                (j1+c+(l*NUMC))->bombaemvolta = (j2+c+(l*NUMC))->bombaemvolta;
            }
        }
        if(vitoria(j1)==1){
            printf("PARABENS, VOCE VENCEU O JOGO!\n");
            printf("sua jogada\n");
            showtabuleiro(j1);
            printf("\n\ntodas as bombas\n");
            showtabuleiro(j2);
            printf("VOCE VENCEU!\n");
            break;
        }
    }
}

int main(){
    srand(time(NULL));
    tabuleiro * j1 = malloc( TAMT * sizeof(tabuleiro)); //apresentado ao usuario
    tabuleiro * j2 = malloc( TAMT * sizeof(tabuleiro)); //contem as informações
    if(j1==NULL || j2==NULL){
        printf("nao deu certo na alocacao\n");
        exit(1);
    }

    int escolha;
    while(1){
        inicializaJ2(j2);
        iniciart1(j1);

        thegame(j2, j1);

        printf("\nDeseja jogar novamente? [1]sim/[2]nao");
        scanf("%d",&escolha);
        if(escolha==2)
            break;
    }
    free(j2);
    free(j1);
    return 0;
}

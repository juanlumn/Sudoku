#include <stdlib.h>
#include <conio.h> 
#include <stdio.h>
#include <time.h>

#define NCOL 9
#define NFIL 9

//Function random1
void random1 (int &n_veces){
    n_veces=9+rand()%12;
    return;
}

//Function random2
void random2 (int &num){
        num=(rand()%9)+1;
    return;
}


//Function to order the table
void orden(int tablero[NFIL][NCOL]){                   
    
    int i,x,z,filas=0,columnas=0,raya=0;
    
    printf("|");
    for (i=0;i<NFIL;i++){
        for(x=0;x<NCOL;x++){
            if (columnas==3){
                printf("|");
                columnas=0;
                filas++;
            }
            if (filas==3){
                filas=0;
                raya++;
                printf("\n|");
            }         
            if (raya==3){
                raya=0;
                for (z=0;z<20;z++){
                    printf("-");
                }
                printf("|");
                printf("\n|");
            }
            if (tablero[x][i]==0){
                printf(" *");
            }
            else{
                printf(" %d",tablero[x][i]);
            }
            columnas++;
        }
    }
    printf("|\n");
    for (z=0;z<22;z++){
        printf("-");
    }
    return;
}

//Function to check the matches
bool comprobar(int tablero[NCOL][NFIL],int comp_num,int columna,int fila){

    int i,x;
    bool coincidencia=0;
        
    for (i=0;i<NCOL;i++){
        for (x=0;x<NFIL;x++){
            if (tablero[i][x]==comp_num) {
                if (columna/3==i/3 && fila/3==x/3){
                    coincidencia=1;
                }
                if(columna==i || fila==x){
                    coincidencia=1;
                }               
            }
        }
    }
    return(coincidencia);
}

//Startup Screen 1
void pantalla_inicio1(int tablero[NCOL][NFIL]){

    int i,col,fil,num,n_veces;
    bool coincidencia=0;
   n_veces=9+rand()%25;
    i=0;
    //while n_veces
    while(i<n_veces){
        //Choose a random number
        random2(num);
        //Choose a random row and column between 0 and 8
        col=rand()%NCOL;
        fil=rand()%NFIL;
        //Call comprobar and saves the result in coincidencia
        coincidencia=comprobar(tablero,num,col,fil);
        
        if (coincidencia==0){
            //Puts in the table a random number
            tablero[col][fil]=num;
            i++;
        }
    }
    return;
}

//Matriz function
void matriz(int tablero[NCOL][NFIL]){

    int i,x;

    for (i=0;i<NCOL;i++){
        for(x=0;x<NFIL;x++){
            tablero[i][x]=0;
        }
    }
    pantalla_inicio1(tablero);
    return;
}


void sudoku(void){
    
    int i;
    
    for (i=0;i<8;i++){
        printf(">");
    }
    printf("SUDOKU");
    for (i=0;i<8;i++){
        printf("<");
    }
    printf("\n");
    return;
}

//Menu
void menu(int &numero){
    
    int i;
    
    printf("\n\nGAME MENU.\n");
    for (i=0;i<14;i++){
        printf("-");
    }
    printf("\n1.PLAY.");
    printf("\n2.DELETE BOX.");
    printf("\n3.CLEAR THE PANEL.");
    printf("\n4.NEW PANEL.");
    printf("\n5.SOLVE PANEL.");
    printf("\n6.EXIT");
    printf("\n\nCHOOSE AN OPTION <1-6>:");
    scanf("%d",&numero);
    return;
}

void posicion(int &columna,int &fila,int numero,int tablero[NCOL][NFIL]){
    
    bool contador=0;
    
    do{
        if (numero==1&&contador==1){
            contador=0;
            printf("\nPOSITION ALREADY OCCUPIED,PRESS ANY KEY AND CHOOSE ANOTHER.\n");
            getche();
        }
        do{
            printf("\nCHOOSE THE COLUMN <1-9>:");
            scanf("%d",&columna);
        }while(columna<1||columna>9);
    
        do{
            printf("\nCHOOSE THE ROW <1-9>:");
            scanf("%d",&fila);
        }while(fila<1||fila>9);
        contador=1;
    }while (tablero[columna-1][fila-1]!=0);
    
    return;
}

//Function to choose a number to play
void tirar(int tablero[NCOL][NFIL],int numero){
    int columna,fila;
    
    int coincidencia=0,comp_num=0;
    
    posicion(columna,fila,numero,tablero);
    
    do{
        printf("\nCHOOSE THE NUMBER <1-9>:");  
        scanf("%d",&comp_num);
    }while (comp_num<1||comp_num>9);
    
    coincidencia=comprobar(tablero,comp_num,columna-1,fila-1);
    
    if (coincidencia==1){
        printf("\nINCORRECT NUMBER,PRESS ANY KEY AND KEEP PLAYING.");
        getche();
    }else{
        tablero[columna-1][fila-1]=comp_num; 
    }
    return;
}

//Function to delete an introduced number
void borrar(int tablero[NCOL][NFIL],int tablero_reserva[NCOL][NFIL]){
    int columna,fila;

    posicion(columna,fila,0,tablero);
    
    if (tablero[columna-1][fila-1]!=tablero_reserva[columna-1][fila-1]){
        tablero[columna-1][fila-1]=0;
    }else{
        printf("\nYOU CAN'T DELETE THIS,PRESS ANY KEY AND KEEP PLAYING.");
        getche();
    }
    return;
}

//Function to delete all introduced numbers
void borrar_todo(int tablero[NCOL][NFIL],int tablero_reserva[NCOL][NFIL]){
    
    int i,x;
    
    for(i=0;i<NCOL;i++){
        for (x=0;x<NFIL;x++){
            tablero[i][x]=0;
            tablero[i][x]=tablero_reserva[i][x];
        }
    }
    
    return;
}

//Function when you win/lose
int final(int tablero[NCOL][NFIL],int numero){

    int i,x;
    int contador=0;
    
    for (i=0;i<NCOL;i++){
        for (x=0;x<NFIL;x++){
            if (tablero[i][x]==0){
                contador=1;
            }
        }
    }

    if(contador==0){
        if (numero==0){
            printf("\nCONGRATULATIONS,YOU WIN.");
            getche();
        }
        if (numero==1){
            printf("\nYOU LOSE.\n");
            printf("\nTHE ANSWER IS:\n");
            for (i=0;i<22;i++){
                printf("-");
            }
        }
    }
    
    return (contador);
}


//Recursive function which auto-solves the SUDOKU
void resolver(int tablero[NCOL][NFIL],int columna,int fila,int &contador){
    
    int i=0,x,z,fin=0;
    bool coincidencia;

if (contador==0){
    if (tablero[columna][fila]==0){
        for (i=1;i<10;i++){
            coincidencia=comprobar(tablero,i,columna,fila);
            if (coincidencia==0){
                tablero[columna][fila]=i;
                resolver(tablero,columna,fila,contador);
            }
        }
        tablero[columna][fila]=0;
    }else{
        columna++;
        if (columna==9){
            columna=0;
            fila++;
            if (fila==9){
                contador++;
                system("cls");
                final(tablero,1);
                printf("\n");
                orden(tablero);
                printf("\nPRESS A KEY.");
            }
        }
        if(fila!=9) resolver(tablero,columna,fila,contador);
    }
}
    return;
}

//Aux function
void auxiliar(int tablero[NCOL][NFIL],int tablero_reserva[NCOL][NFIL]){
    
    int i,x;
    
    for(i=0;i<NCOL;i++){
        for(x=0;x<NFIL;x++){
            tablero_reserva[i][x]=tablero[i][x];
        }
    }
    
    return;
}

//Initial screen
void pantalla_inicio(int tablero[NCOL][NFIL],int tablero_reserva[NCOL][NFIL]){
    matriz(tablero);
    auxiliar(tablero,tablero_reserva);
    return;
}

//Function to choose an option
void opcion(int numero,int tablero[NCOL][NFIL],int tablero_reserva[NCOL][NFIL]){
    int contador=0;
    switch (numero){
        case 1:
            tirar(tablero,numero);
            break;
        case 2:
            borrar(tablero,tablero_reserva);
            break;
        case 3:
            borrar_todo(tablero,tablero_reserva);
            break;
        case 4:
            pantalla_inicio(tablero,tablero_reserva);
            break;
        case 5:
            printf("SOLVING, PLEASE WAIT.\n");
            resolver(tablero,0,0,contador);
            if (contador==0){
                printf("SORRY, THIS BOARD HASN'T ANSWER.");
                printf("PRESS ANY KEY.");
            }
            getche();
            break;
    }
    
    return;
}

void principal(void){
    
    int tablero[NCOL][NFIL],tablero_reserva[NCOL][NFIL];
    int numero=0;
    //Sets the rand 
    srand(time(0));

    pantalla_inicio(tablero,tablero_reserva);

    while (numero!=6){
        sudoku();
        orden(tablero);
        menu(numero);
        opcion(numero,tablero,tablero_reserva);
        final(tablero,0);
        system ("cls");
    }
    return;
}

int main (void){
    principal();
    return (0);
}

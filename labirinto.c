#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //para alterar cores

#define CORREDOR 000
#define PAREDE 001
#define GRAMA 002


#define PORTA 010
#define CHAVE 020
#define MONSTRO 030
#define ESPADA 040
#define VIDA 050
                    
/*
#define ACIMA 72
#define ABAIXO 80
#define DIREITA 77           DEFINIÇÕES QUE NAO USAMOS, SOMENTE COMO GUIA.
#define ESQUERDA 75
#define ESC 27
*/

/*  DOS
  Largura: 100
  Altura: 80
*/


     //variaveis globais
     HANDLE  hConsole;//para cor
     int i,j,direcao=0,linha=0,coluna=1,vida=6,chave=0,esp=0,vidamenu=3,espmenu=0;       
     char E,S,sim[3]; 
     char lab[25][75]={//matriz do labirinto
   001,'E',001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,
   001,000,001,020,002,020,002,020,002,001,000,000,000,000,000,000,000,000,001,001,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,002,002,002,001,000,000,000,000,000,000,000,000,000,030,000,000,000,020,001,                                                                            
   001,000,001,000,000,000,000,000,000,001,000,000,001,001,001,001,001,000,001,001,000,001,000,001,000,000,000,000,000,000,000,000,000,000,000,001,000,001,001,001,001,001,001,001,001,000,000,000,000,000,000,000,000,000,000,001,002,050,002,001,001,001,000,000,000,000,000,000,000,001,001,001,001,001,001,                                                                                                                                                         
   001,000,001,000,001,001,001,001,000,001,000,000,001,000,000,000,001,000,001,001,000,001,000,001,000,000,000,000,000,000,000,000,000,000,000,001,000,000,000,001,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,001,002,000,002,002,002,001,000,000,000,000,000,000,001,001,000,000,000,000,001,                                                                            
   001,000,001,000,001,001,000,001,000,001,000,000,001,001,001,001,001,000,001,001,000,001,000,001,000,000,000,000,000,000,000,000,000,000,000,001,001,001,000,001,000,000,000,000,001,001,001,001,001,001,000,000,001,000,000,010,000,000,000,000,000,000,000,000,000,000,000,000,001,000,000,000,000,000,001,                                                                                                   
   001,000,001,000,010,010,000,001,000,001,000,000,000,010,000,001,000,000,000,000,000,001,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,000,000,000,001,000,000,001,001,000,001,002,002,002,002,002,000,000,000,000,000,000,000,000,000,000,000,000,002,001,                                                                                                                                        
   001,000,001,000,001,001,000,001,010,001,001,001,001,001,000,001,001,001,001,001,001,001,000,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,000,001,001,001,001,001,001,001,001,001,000,001,000,000,001,001,001,001,001,001,000,000,002,000,001,001,001,001,001,001,001,001,001,001,001,001,001,
   001,000,001,020,050,001,000,000,000,010,010,010,000,030,020,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,000,000,001,000,000,000,000,000,000,000,001,000,001,001,001,001,000,000,000,001,001,000,000,002,000,001,000,000,000,000,000,000,001,000,000,000,000,001,
   001,000,001,020,002,001,001,001,010,001,001,001,001,001,001,001,010,001,000,000,000,002,002,002,002,002,000,000,000,001,000,000,001,001,001,001,000,001,001,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,001,010,001,001,000,000,001,000,000,001,000,000,000,000,001,                                                                                                                                        
   001,000,001,001,001,001,000,000,000,001,040,001,000,000,000,000,000,001,000,000,000,000,002,000,050,000,000,000,000,001,000,000,001,000,030,000,000,001,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,000,001,001,001,001,000,000,050,000,000,000,000,001,                                                                                                                                        
   001,000,000,000,020,000,000,000,000,001,000,001,000,000,000,040,000,001,000,000,000,001,001,001,001,000,000,000,000,001,000,000,001,000,001,001,001,001,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,002,000,000,000,000,000,001,000,000,000,000,000,001,000,000,001,000,000,000,000,001,                                                                                                                                       
   001,001,001,001,001,001,001,001,000,001,000,001,000,000,000,001,001,001,000,001,001,001,000,000,001,000,001,001,001,001,000,000,001,000,001,000,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,002,000,000,000,000,000,001,000,000,000,000,000,001,000,000,001,000,000,000,000,001,                                                                                                                                        
   001,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,000,000,000,001,000,001,001,000,001,000,000,001,000,000,001,000,001,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,002,000,000,000,000,000,001,000,000,000,000,000,030,000,002,002,000,000,000,000,001,                                                                                                                                        
   001,000,000,000,002,002,050,002,002,001,000,001,000,000,000,001,000,001,000,001,000,001,000,000,001,000,001,000,000,001,000,000,001,000,001,000,000,000,000,000,000,001,020,000,000,000,000,000,000,000,000,000,000,000,002,000,000,000,000,000,001,001,001,001,001,001,001,001,001,001,000,000,000,000,001,                                                                                                                                        
   001,000,001,001,001,001,010,001,001,001,000,001,000,000,000,001,000,001,001,001,000,001,001,000,001,001,001,000,000,000,000,000,001,000,001,000,000,000,000,000,001,050,000,000,000,000,000,000,000,000,000,000,000,000,002,000,000,000,000,000,000,000,000,001,010,000,000,000,000,001,000,000,000,000,001,                                                                                                                                        
   001,000,020,000,000,000,000,000,000,001,000,001,030,002,001,001,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,001,040,001,000,000,000,000,000,001,001,001,001,001,001,001,001,000,000,000,000,000,000,002,000,000,000,000,000,000,000,000,001,000,001,001,001,000,001,000,000,000,000,001,                                                                                                                                        
   001,001,001,001,001,001,001,001,000,001,000,001,020,000,002,001,000,000,001,000,000,000,000,001,001,001,000,000,000,000,001,001,001,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,002,000,000,000,000,000,000,000,000,001,000,001,020,001,000,001,000,000,000,000,001,                                                                                                                                        
   001,000,000,000,000,000,000,000,000,001,000,001,000,000,050,001,000,000,001,000,001,001,001,000,000,010,000,000,000,000,001,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,002,002,002,002,002,000,000,000,000,001,000,001,050,001,030,001,000,002,002,002,001,                                                                                                                                        
   001,000,001,001,001,001,001,001,001,001,000,001,000,000,001,001,000,000,001,000,001,001,000,000,001,010,001,000,000,000,001,000,001,001,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,001,000,001,010,001,000,000,020,002,001,                                                                                                                                        
   001,000,000,000,000,000,000,000,000,001,000,001,000,000,001,001,000,000,000,000,001,000,000,000,001,001,001,000,000,000,001,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,002,002,001,                                                                                                                                        
   001,001,001,001,001,001,001,001,000,001,000,001,010,001,001,001,001,001,001,050,001,000,000,000,001,001,001,001,001,001,001,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,000,002,001,                                                                                                                                        
   001,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,001,001,001,000,000,001,001,000,000,030,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,000,002,001,                                                                                                                                        
   001,000,001,001,001,001,001,001,001,001,000,001,000,000,000,000,000,000,000,001,001,001,002,001,000,000,001,001,001,001,001,001,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,001,000,000,000,000,000,000,000,002,001,                                                                                                                                       
   001,000,000,000,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,001,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,001,010,001,000,000,000,000,002,002,002,002,001,                                                                                                                                          
   001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,'S',001,001,001,001,001,001,001,001,001,001,
   };       
    
   
        
    int instrucoes[5][9]={//matriz de instruções
        2,6,6,6,6,6,6,6,3,
        1,0,0,0,30,0,0,0,1,
        1,0,0,0,0,0,0,0,1,
        1,0,17,0,31,0,16,0,1,
        4,6,6,6,6,6,6,6,5};
                                                              
    
    void instruc(void){//função para desenhar matris de instruções
         
         for(i=0;i<5;i++){
                          printf("\t\t\t\t ");
                          for(j=0;j<9;j++){
                                           hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//mudar cor
                                           SetConsoleTextAttribute(hConsole, 11);//mudar cor
                                           if(instrucoes[i][j]==PAREDE)printf("%c",186);//imprime um caractere especifico para parede
                                           if(instrucoes[i][j]==CORREDOR)printf(" ");
                                           if(instrucoes[i][j]==30)printf("%c",30);
                                           if(instrucoes[i][j]==17)printf("%c",17);
                                           if(instrucoes[i][j]==31)printf("%c",31);
                                           if(instrucoes[i][j]==16)printf("%c",16);
                                           if(instrucoes[i][j]==2)printf("%c",201);
                                           if(instrucoes[i][j]==3)printf("%c",187);
                                           if(instrucoes[i][j]==4)printf("%c",200);
                                           if(instrucoes[i][j]==5)printf("%c",188);
                                           if(instrucoes[i][j]==6)printf("%c",205);
                                           }                                       
                                           printf("\n");
                                           
                          }
                          
                          }//fim funcao instruc
         
   void labirinto(void){//função para desenhar o labirinto
   
   for(i=0;i<25;i++){
                     printf("\t");
                     for(j=0;j<75;j++){
                                       if(lab[linha][coluna]==CHAVE)lab[linha][coluna]=000;//faz com que as cheves sumam quando pegas
                                       if(lab[linha][coluna]==VIDA)lab[linha][coluna]=002;//troca a vida por grama 
                                       if(lab[linha][coluna]==ESPADA)lab[linha][coluna]=000;//troca espada por caminho 
                                       if(lab[linha][coluna]==PORTA)lab[linha][coluna]=001;//ao atravessar uma porta ela se torna parede                                                                                                                                                
                                       if(i==linha&&j==coluna){
                                                               hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//mudar cor
                                                               SetConsoleTextAttribute(hConsole, 10);//mudar cor
                                                               printf("%c",258);
                                                               continue;//O comando continue se parece com o comando break, mas a diferença é que ele apenas ignora o resto do bloco de dados de um loop e continua o for.
                                                               }                                                                    
                                       if(lab[i][j]==PAREDE){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 14);
                                                        printf("%c",219);
                                                        }
                                       if(lab[i][j]==CORREDOR)printf("%c",0);                                                        
                                       if(lab[i][j]==GRAMA){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 10);
                                                        printf("%c",177);
                                                        }
                                       if(lab[i][j]==PORTA){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 11);
                                                        printf("%c",219);
                                                        }
                                       if(lab[i][j]==CHAVE){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 11);
                                                        printf("%c",261);
                                                        }
                                       if(lab[i][j]==VIDA){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 10);
                                                        printf("%c",177);
                                                        }
                                       if(lab[i][j]==ESPADA){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 15);
                                                        printf("%c",197);
                                                        }
                                       if(lab[i][j]==MONSTRO){
                                                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                        SetConsoleTextAttribute(hConsole, 12);
                                                        printf("%c",1);
                                                        }                                        
                                       if(lab[i][j]=='E')printf("%c",31);
                                       if(lab[i][j]=='S')printf("%c",30);                                       
                                       }//fim for J
                     printf("\n");
                     }//fim for I                 
}//fim função labirinto

int main(int argc, char *argv[])
{    
  while(lab[linha][coluna]!='S'){  
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//mudar cor
  SetConsoleTextAttribute(hConsole, 10);//mudar cor
  printf("\n\n\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c LABIRINTO OF ZELDA %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n\n",175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174,174);  
  printf("\tVidas: %d\n",vidamenu);
  printf("\tChaves: %d\n",chave);
  printf("\tEspada: %d\n\n",espmenu); //aparece a quantidade de espadas
  labirinto();
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//mudar cor
  SetConsoleTextAttribute(hConsole, 11);//mudar cor
  printf("\n\n\t\t\t\tINSTRU%cOES\n",128);
  printf("\t\t  Utilize as setas do teclado como guia\n\n");
  instruc(); 
  printf("\n\t\t\tDefinicoes:\n");
  printf("\t\t\t\t%c - Chave\n",261);
  printf("\t\t\t\t%c - Monstro\n",1);
  printf("\t\t\t\t%c - Espada\n",197); 
  printf("\t\t\t\t%c - Porta\n\n",219);
  printf("\t\t\tPara Reiniciar Pressione R\n");
  printf("\t\t\tImportante: Ao atravessar uma porta ela se transforma em parede!\n");
  printf("\t\t\tDica: As vezes a grama esconde tesouros!!!\n"); 
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//mudar cor
  SetConsoleTextAttribute(hConsole, 15);//mudar cor  
  printf("\n\n\t\t\tPressione Esc para sair\n\n");  
  direcao=getch();
   
  switch(direcao){
                  case 77:coluna++;//caso seta direita pressionada pula para proxima coluna
                                   /*se for parede porta sem chave grama ou entrada vc nao pode passar,volta a posição anterior*/
                          if(lab[linha][coluna]==1||lab[linha][coluna]==010&&chave==0||lab[linha][coluna]==2||lab[linha][coluna]=='E')coluna--;                                          
                          break;
                  case 80:linha++;//caso seta baixo pressionada
                          if(lab[linha][coluna]==1||lab[linha][coluna]==010&&chave==0||lab[linha][coluna]==2||lab[linha][coluna]=='E')linha--;                          
                          break;
                  case 75:coluna--;//caso seta esquerda pressionada
                          if(lab[linha][coluna]==1||lab[linha][coluna]==010&&chave==0||lab[linha][coluna]==2||lab[linha][coluna]=='E')coluna++;                                                 
                          break;
                  case 72:linha--;//caso cima pressionada
                          if(lab[linha][coluna]==1||lab[linha][coluna]==010&&chave==0||lab[linha][coluna]==2||lab[linha][coluna]=='E')linha++;                                                 
                          break;
                  case 27:exit(0);//caso esc seja pressionado, o programa fecha
                  
                  case 'r': //serve para fazer o restart
                            system("cls");
                            system("labirinto.exe");
                            break;
                  case 'R': //serve para fazer o restart com o Caps Lock ativado
                            system("cls");
                            system("labirinto.exe");
                            break;
                  
                  default: ;break;//se a pessoa apertar qualquer outra tecla nao definida o programa nao faz nada, simplesmente redesenha os quadros                          
                  }//fim switch
  if(lab[linha][coluna]==CHAVE){//se vc estiver em cima da chave                             
                             chave++;                             
                             printf("\a");                                                     
                             }
  if(lab[linha][coluna]==PORTA&&chave>0){//caso passe pela porta
                                      printf("\a");
                                      chave--;                                      
                                      }
  if(lab[linha][coluna]==VIDA){//caso vc pegue uma vida
                               printf("\a");
                               vida=vida+2;
                               vidamenu=vida;
                               vidamenu=vidamenu/2;//o valor real da vida e de 2pts mas so e mostrado 1pt, pois o monstro tira 2pts de vida por passagem
                               }
  if(lab[linha][coluna]==ESPADA){//caso pegue uma espada
                                 printf("\a");
                                 esp=esp+2;
                                 if(esp%2==0)espmenu++;
                                 }
  if(lab[linha][coluna]==MONSTRO&&esp==0){//se vc passar por um monstro sem espada
                                          printf("\a\a\a");
                                          vida--;                                          
                                          if(vida%2==0)vidamenu--;//so diminui a vida no menu quando se perder 2pts                                          
                                          }
  if(lab[linha][coluna]==MONSTRO&&esp>0){
                                          printf("\a");
                                          esp--;
                                          if(esp%2==0)espmenu--;
                                          }
  if(vida==-1){            
            system("cls");
            for(i=0;i<900;i++){
                    printf("GAME OVER! ");                    
                    }
                    printf("\n\n\n\t\t\t Pressione Qualquer Tecla Para Continuar");
                    getch();
            system("cls");
            system("labirinto.exe");
            }  
  system("cls");//limpar tela

}//fim while 

printf("\a\a\a");//se o labirinto for concluido
for(i=0;i<400;i++){
                   system("color f0");
                   printf("PARABENS, VOCE VENCEU!!!!!\t ");
                  }

  getch();//substitui o system("pause"); (sem mensagem 'press qlqer tecla p cont..')	
  return 0;
}

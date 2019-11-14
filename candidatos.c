#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>    // setlocale
#define MAXCHAR 1000
#define FALSE   0      // constante falsa
#define TRUE   !FALSE  // constante verdadeira


/***********************************************/ 
/* Defini��o dos Registros                     */
/***********************************************/ 
typedef struct {          // registro 
       int  codigo;       
	   int  n;
	   int  fatbal;
} INFORMACAO;
       
typedef struct arv {
       INFORMACAO info;   // dados do registro
       struct arv* subd;  // ponteiro para o nodo da direita
       struct arv* sube;  // ponteiro para o nodo da esquerda
} ARVORE; 


/***********************************************/ 
/* Defini��o das Fun��es                       */
/***********************************************/
void    entrada_dados   ( ARVORE* aux ); // leitura dos dados de entrada
void    imprime_ARVORE  ( ARVORE* aux ); // visualiza��o da �rvore em tela, todos os candidatos
void    cria_ARVORE     ( ARVORE** r );  // inicializa �rvore com NULL
void    insere_candidato( ARVORE** r, int cod ); // inclui um novo candidato na �rvore
ARVORE* remove_candidato( ARVORE *p, int cod ); //remove candidato
ARVORE* busca_recursivo ( ARVORE *p, int cod ); // buscar um candidato
ARVORE* descubra_candidato ( ARVORE *p, int cod ); // descubra o  candidato
void 	carregar_questoes (char filename);
void    salvar_questao   ( ARVORE* p );


void cria_ARVORE( ARVORE** r ){
    *r = NULL; // arvore criada, raiz nao aponta
}

void entrada_dados( ARVORE* aux )
{ 
/*  printf( "\n\n C�digo: %d", aux->info.codigo ); */  
    aux->subd = NULL;    // n�o aponta
    aux->sube = NULL;    // n�o aponta

}

void imprime_ARVORE( ARVORE* aux ){    
     
    if( aux != NULL ){              // verifica se a raiz � diferente de vazio
        printf( "\n C�digo.....: %d", aux->info.codigo );
        printf( "\n Altura.....: %d", aux->info.n );
        printf( "\n Fatbal.....: %d", aux->info.fatbal );        
		getchar();
        printf( "\n >> sube" );
        imprime_ARVORE( aux->sube ); // recursivo, segue pelo caminho da esquerda
        printf( "\n >> subd" );
        imprime_ARVORE( aux->subd ); // recursivo, segue pelo caminho da direita
    }
    else
       printf("\n �rvore vazia!");
}

void insere( ARVORE** r ){
    ARVORE* p;      // ponteiro auxiliar
    ARVORE* a;      // ponteiro auxiliar para anterior de p
    int cod, achou; // cod = dado de entrada; achou = informa se c�digo j� existe na estrutura

    printf("\n Digite o novo c�digo: ");
    scanf("%d", &cod);
    
    p = *r;                            // posiciona ponteiro auxiliar
    achou = busca( cod, &a, &p );      // verifica se c�digo a ser inserido j� existe na �rvore
    if( !achou ){                      // se n�o achou o c�digo, insere
         ARVORE* no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em mem�ria

         if( no != NULL ){             // se conseguiu alocar mem�ria, insere
                 no->info.codigo = cod;// preenche o novo registro com o c�digo j� informado
                 entrada_dados( no );  // entrada do usu�rio
                 if( *r == NULL )      // verifica se a �rvore esta vazia
                     *r = no;          // o registro sera o primeiro, atualiza a raiz
                 else 
                      if ( no->info.codigo > a->info.codigo )
                           a->subd = no; // insere a direita do registro folha
                      else
                           a->sube = no; // insere a esquerda do registro folha
         } // fim if( no != NULL )
    } // fim if( !achou )
    else
        printf( "\n Registro j� existe!" );
}

int busca( int cod, ARVORE** a, ARVORE** p ){
   int achou = FALSE;                // achou = indica se encontrou o c�digo na estrutura
   
   *a = NULL;                        // ponteiro auxiliar para o anterior
   while( ( *p != NULL ) && ( !achou ) )
           if ( (*p)->info.codigo == cod ){
		   		// veririfica se encontrou o c�digo
                achou = TRUE;        // encontrou a matricula na estrutura

		   } 
           else {
                *a = *p;             // posiciona ponteiro auxiliar no anterior de p
                if( (*p)->info.codigo > cod )
                    *p = (*p)->sube; // anda com o ponteiro p para a esquerda, pois o c�digo procurada e menor
                else
                    *p = (*p)->subd; // anda com o ponteiro p para a direita, pois o c�digo procurada e maior 
           } // fim if ((*p)->info.codigo == cod)
    
   return achou; 
}


ARVORE* busca_recursivo( ARVORE *p, int cod ){
//	if( p == NULL || p->info.codigo == cod )
   if(p->info.codigo == cod )
       	printf("achou!!!");
   else{
       if( p->info.codigo > cod )
            return busca_recursivo( p->sube, cod ); // anda com o ponteiro p para a esquerda, pois o c�digo procurada � menor
       else
            return busca_recursivo( p->subd, cod ); // anda com o ponteiro p para a direita, pois o c�digo procurada � maior 
   } 
   
}






int main(int argc, char *argv[]) {
	
	char op;      
	setlocale(LC_ALL, "Portuguese");
	//Resultado das quest�es
	int pontos = 25;
	
	//Cria �rvore
	ARVORE* r, *p; 
//	cria_ARVORE( &r );
//	insere( &r );
//	insere( &r );  
//	insere( &r );      
//	busca_recursivo(r, 666);
//	
//	while(1){
//		 printf( "\n /-----------------------------------------------------/" ); 
//         printf( "\n Programa de advinhar candidato - Menu                " );
//         printf( "\n [1] Cria ARVORE                                      " );
//         printf( "\n [2] Insere candidato                                 " );
//         printf( "\n [3] Remove candidato                                 " );
//         printf( "\n [4] Imprime ARVORE de candidatos                     " );
//		 printf( "\n [5] Descubra seu candidato                           " );          
//		 printf( "\n [6] Para sair do programa                            " );         
//         printf( "\n /---------------------------------------------------/" );      
//         printf( "\n Opcao: " );
//         
//         op = getche(); // tecla de op��o do menu
//         
//          switch( op ) {
//           case '1':    
//                   cria_ARVORE( &r );
//                   break;
//                                
//           case '2':   
//                   insere( &r );    
//                   break;
//                      
//           case '3':   
//                 
//                   break;
//           
//           case '4':   
//                  
//                   break;                   
//                                                         
//           case '5':   
//                    break;  
//                   
//           case '6':                                               
//                  
//                   break; 
//				                      
//           case '7':                                              
//                   exit( 1 ); 
//                   break;                
//                   
//           default : 
//                   printf( "\n Digite uma opcao: " );
//                   break;
//        } 
//        
//        
//        fflush( stdin ); // limpa buffer do teclado, funciona junto com entrada de dados
//        getchar();       // parada da tela
//        
//        printf( "\n" );
//	}
//	
//	
	

    
    
    
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "demon.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);

	
	
	
	return 0;
}

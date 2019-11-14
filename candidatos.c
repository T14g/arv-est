#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>    // setlocale
#define MAXCHAR 1000
#define FALSE   0      // constante falsa
#define TRUE   !FALSE  // constante verdadeira


/***********************************************/ 
/* Definição dos Registros                     */
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
/* Definição das Funções                       */
/***********************************************/
void    entrada_dados   ( ARVORE* aux ); // leitura dos dados de entrada
void    imprime_ARVORE  ( ARVORE* aux ); // visualização da árvore em tela, todos os candidatos
void    cria_ARVORE     ( ARVORE** r );  // inicializa árvore com NULL
void    insere_candidato( ARVORE** r, int cod ); // inclui um novo candidato na árvore
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
/*  printf( "\n\n Código: %d", aux->info.codigo ); */  
    aux->subd = NULL;    // não aponta
    aux->sube = NULL;    // não aponta

}

void imprime_ARVORE( ARVORE* aux ){    
     
    if( aux != NULL ){              // verifica se a raiz é diferente de vazio
        printf( "\n Código.....: %d", aux->info.codigo );
        printf( "\n Altura.....: %d", aux->info.n );
        printf( "\n Fatbal.....: %d", aux->info.fatbal );        
		getchar();
        printf( "\n >> sube" );
        imprime_ARVORE( aux->sube ); // recursivo, segue pelo caminho da esquerda
        printf( "\n >> subd" );
        imprime_ARVORE( aux->subd ); // recursivo, segue pelo caminho da direita
    }
    else
       printf("\n Árvore vazia!");
}

void insere( ARVORE** r ){
    ARVORE* p;      // ponteiro auxiliar
    ARVORE* a;      // ponteiro auxiliar para anterior de p
    int cod, achou; // cod = dado de entrada; achou = informa se código já existe na estrutura

    printf("\n Digite o novo código: ");
    scanf("%d", &cod);
    
    p = *r;                            // posiciona ponteiro auxiliar
    achou = busca( cod, &a, &p );      // verifica se código a ser inserido já existe na árvore
    if( !achou ){                      // se não achou o código, insere
         ARVORE* no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em memória

         if( no != NULL ){             // se conseguiu alocar memória, insere
                 no->info.codigo = cod;// preenche o novo registro com o código já informado
                 entrada_dados( no );  // entrada do usuário
                 if( *r == NULL )      // verifica se a árvore esta vazia
                     *r = no;          // o registro sera o primeiro, atualiza a raiz
                 else 
                      if ( no->info.codigo > a->info.codigo )
                           a->subd = no; // insere a direita do registro folha
                      else
                           a->sube = no; // insere a esquerda do registro folha
         } // fim if( no != NULL )
    } // fim if( !achou )
    else
        printf( "\n Registro já existe!" );
}

int busca( int cod, ARVORE** a, ARVORE** p ){
   int achou = FALSE;                // achou = indica se encontrou o código na estrutura
   
   *a = NULL;                        // ponteiro auxiliar para o anterior
   while( ( *p != NULL ) && ( !achou ) )
           if ( (*p)->info.codigo == cod ){
		   		// veririfica se encontrou o código
                achou = TRUE;        // encontrou a matricula na estrutura

		   } 
           else {
                *a = *p;             // posiciona ponteiro auxiliar no anterior de p
                if( (*p)->info.codigo > cod )
                    *p = (*p)->sube; // anda com o ponteiro p para a esquerda, pois o código procurada e menor
                else
                    *p = (*p)->subd; // anda com o ponteiro p para a direita, pois o código procurada e maior 
           } // fim if ((*p)->info.codigo == cod)
    
   return achou; 
}


ARVORE* busca_recursivo( ARVORE *p, int cod ){
//	if( p == NULL || p->info.codigo == cod )
   if(p->info.codigo == cod )
       	printf("achou!!!");
   else{
       if( p->info.codigo > cod )
            return busca_recursivo( p->sube, cod ); // anda com o ponteiro p para a esquerda, pois o código procurada é menor
       else
            return busca_recursivo( p->subd, cod ); // anda com o ponteiro p para a direita, pois o código procurada é maior 
   } 
   
}






int main(int argc, char *argv[]) {
	
	char op;      
	setlocale(LC_ALL, "Portuguese");
	//Resultado das questões
	int pontos = 25;
	
	//Cria árvore
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
//         op = getche(); // tecla de opção do menu
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

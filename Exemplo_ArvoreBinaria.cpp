/***********************************************/ 
/* �rvores Bin�rias                            */
/* objetivo: registro de c�digos               */
/* programador: Daniela Bagatini               */
/* criado em: 08/11/2017                       */
/* data da �ltima altera��o: 06/06/2018        */
/***********************************************/ 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>    // setlocale

#define FALSE   0      // constante falsa
#define TRUE   !FALSE  // constante verdadeira


/***********************************************/ 
/* Defini��o dos Registros                     */
/***********************************************/ 
typedef struct {          // registro 
       int  codigo;       
	   int  altura;
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
void    imprime_ARVORE  ( ARVORE* aux ); // visualiza��o da �rvore em tela, todos os registros
void    cria_ARVORE     ( ARVORE** r );  // inicializa �rvore com NULL
void    insere          ( ARVORE** r );  // inclui um novo registro na �rvore, sempre na folha
int     busca           ( int matricula, ARVORE** a, ARVORE** p ); // procura na �rvore um c�digo
void    sucessor        ( ARVORE* p, ARVORE** q, ARVORE** b ); // procura registro posterior de um c�digo
void    antecessor      ( ARVORE* p, ARVORE** q, ARVORE** b ); // procura registro anterior de um c�digo
void    remove          ( ARVORE** r );  // exclui um regitro por c�digo
void    insere_recursivo( ARVORE** r, int cod ); // inclui um novo registro na �rvore
ARVORE* busca_recursivo ( ARVORE *p, int cod );  
ARVORE* remove_recursivo( ARVORE *p, int cod );
//ARVORE* menor_valor     ( ARVORE *p );
void    calcula_altura  ( ARVORE **r );
int     altura_arvore   ( ARVORE *p );     // informa a altura da �rvore
void verifica_balanceamento( ARVORE **r ); // verifica balanceamento da �rvore
void rotacao_direita ( ARVORE **p );
void rotacao_esquerda( ARVORE **p );       
       
/***********************************************/ 
/* Programa Principal                          */
/***********************************************/
int main( void )
{
    char op;       // op��o do menu                               
    ARVORE* r, *p; // declara��o da ARVORE, vari�vel do tipo ARVORE = ARVORE de ponteiros
    int cod, fatbal= 0, altura_esq=0, altura_dir=0,;
    
    setlocale(LC_ALL, "Portuguese");
    cria_ARVORE( &r );
    while( 1 ){
         printf( "\n /---------------------------------------------------/" ); 
         printf( "\n Programa de registros - Menu                         " );
         printf( "\n [1] Cria ARVORE                                      " );
         printf( "\n [2] Insere                                           " );
         printf( "\n [3] Remove                                           " );
         printf( "\n [4] Imprime                                          " );         
         printf( "\n [5] Insere recursivo                                 " );
         printf( "\n [6] Busca recursivo                                  " );         
         printf( "\n [7] Remove recursivo                                 " );          
         printf( "\n [8] Menor valor                                      " ); 
		 printf( "\n [9] Para sair do programa                            " );         
         printf( "\n /---------------------------------------------------/" );      
         printf( "\n Opcao: " );
         op = getche(); // tecla de op��o do menu

        switch( op ) {
           case '1':   // rotina cria ARVORE       
                   cria_ARVORE( &r );
                   break;
                                
           case '2':   // rotina inclui nodo no final da ARVORE (folha)
                   insere( &r );    
                   break;
                      
           case '3':   // rotina exclui nodo da ARVORE
                   remove( &r );
                   break;
           
           case '4':   // rotina imprime nodos da ARVORE
                   imprime_ARVORE( r );
                   break;                   
                                                         
           case '5':   // rotina recursiva do inclui nodo da ARVORE
                   printf("\n Digite o novo codigo: ");
                   scanf("%d", &cod);
                   insere_recursivo( &r, cod );
                   calcula_altura( &r );        // calcula e armazena a altura de cada n�
                   verifica_balanceamento( &r );// verifica balanceamento da �rvore
                   break; 
                   
           case '6':  // rotina recursiva que busca um registro da ARVORE                                                
                   printf("\n Buscar o codigo: ");
                   scanf("%d", &cod);
                   p= busca_recursivo( r, cod );
                   if( p != NULL )
                       printf("\n Codigo: %d", p->info.codigo);   
                   break; 

           case '7':  // rotina recursiva que busca um registro da ARVORE                                                
                   printf("\n Remove codigo: ");
                   scanf("%d", &cod);
                   p= remove_recursivo( r, cod );
				   calcula_altura( &r ); 
                   break;
                   
           case '8':  // rotina recursiva que busca um registro da ARVORE                                                
                   //p= menor_valor( r );
                   if( p != NULL )
                       printf("\n Codigo: %d", p->info.codigo);
                   break;
				                      
           case '9':  // t�rmino do programa                                                 
                   exit( 1 ); 
                   break;                
                   
           default : 
                   printf( "\n Digite uma opcao!" );
                   break;
        } // switch( op )
        
        fflush( stdin ); // limpa buffer do teclado, funciona junto com entrada de dados
        getchar();       // parada da tela
        
        printf( "\n" );
     } // fim do while( 1 )
     
 return 0;
} // fim do programa principal



/************************************************ 
 * entrada_dados                                *
 * objetivo: rotina para ler dados              *
 * entrada : nodo (ponteiro para o novo espaco) *
 * sa�da   : nodo com dados                      *
 ************************************************/
void entrada_dados( ARVORE* aux )
{ 
/*  printf( "\n\n C�digo: %d", aux->info.codigo ); */  
    aux->subd = NULL;    // n�o aponta
    aux->sube = NULL;    // n�o aponta

}



/*************************************************
 * imprime_ARVORE                                *
 * objetivo: rotina para imprimir dados          *
 * entrada : ARVORE                              *
 * sa�da   : dados em tela                       *
 *************************************************/ 
void imprime_ARVORE( ARVORE* aux ){    
     
    if( aux != NULL ){              // verifica se a raiz � diferente de vazio
        printf( "\n C�digo.....: %d", aux->info.codigo );
        printf( "\n Altura.....: %d", aux->info.altura );
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


/*************************************************
 * menor_valor                                   *
 * objetivo: rotina para encontrar menor valor   *
 * entrada : ARVORE                              *
 * sa�da   : endere�o do menor                   *
 *************************************************/ 
ARVORE* menor_valor( ARVORE* aux ){    
    //ARVORE *p; 
    if( aux != NULL ){            // verifica se a raiz � diferente de vazio
        //p= aux;
        menor_valor( aux->subd ); // recursivo, segue pelo caminho da direita
    }
    else
       return( aux );
}


/************************************************
 * cria_ARVORE                                   *
 * objetivo: rotina para inicializar a ARVORE    *
 * entrada : nenhuma                             *
 * sa�da   : NULL (inicializa ARVORE)            *
 ************************************************/ 
void cria_ARVORE( ARVORE** r ){
    *r = NULL; // arvore criada, raiz nao aponta
}



/************************************************* 
 * insere                                        *
 * objetivo: rotina para inserir no fim da ARVORE*
 * entrada : ARVORE                              *
 * sa�da   : ARVORE com mais um registro         *
 *************************************************/ 
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



/************************************************ 
 * busca                                        *
 * objetivo: achar nodo                         *
 * entrada : ARVORE e c�digo a ser exclu�do     *
 * sa�da   : posicao ou NULL (n�o encontrou)    *
 ************************************************/ 
int busca( int cod, ARVORE** a, ARVORE** p ){
   int achou = FALSE;                // achou = indica se encontrou o c�digo na estrutura
   
   *a = NULL;                        // ponteiro auxiliar para o anterior
   while( ( *p != NULL ) && ( !achou ) )
           if ( (*p)->info.codigo == cod ) // veririfica se encontrou o c�digo
                achou = TRUE;        // encontrou a matricula na estrutura
           else {
                *a = *p;             // posiciona ponteiro auxiliar no anterior de p
                if( (*p)->info.codigo > cod )
                    *p = (*p)->sube; // anda com o ponteiro p para a esquerda, pois o c�digo procurada e menor
                else
                    *p = (*p)->subd; // anda com o ponteiro p para a direita, pois o c�digo procurada e maior 
           } // fim if ((*p)->info.codigo == cod)
    
   return achou; 
}



/*************************************************** 
 * remove                                          *
 * objetivo: rotina para excluir nodo da ARVORE    *
 * entrada : ARVORE                                *
 * sa�da   : ARVORE                                *
 ***************************************************/ 
void remove( ARVORE** r ){
    ARVORE* p;    // ponteiro auxiliar
    ARVORE* q;    // ponteiro auxiliar
    ARVORE* b;    // ponteiro auxiliar
    ARVORE* a;    // ponteiro auxiliar para anterior
    int cod, achou; // cod = dado de entrada; achou = informa se c�digo j� existe na estrutura
    
    if ( *r == NULL )
         printf("\n Arvore vazia!");
    else
       {    
        printf("\n Codigo de referencia: ");
        fflush( stdin ); // limpa buffer do teclado e faz a entrada de dados
        scanf( "%d", &cod ); 

        p = *r;      // posiciona ponteiro auxiliar
        achou = busca( cod, &a, &p ); // verifica se c�digo a ser inserida j� existe na �rvore
        if( achou ){ // se achou o c�digo, remove
            if((( p->sube != NULL ) && ( p->subd != NULL )) || (( p->subd != NULL ) && ( p->sube == NULL ))){
                 sucessor( p, &q, &b );
                 p->info= q->info; // substitui o c�digo 
                 a= b;             // ponteiros auxiliares s�o posicionados na sub�rvore 
                 p= q;
                 
                 if( p->sube != NULL ) // ajusta subarvore
                     b= p->sube;
                 else
                     b= p->subd;
     
                 if( p->info.codigo >= a->info.codigo )
                     a->subd= b;
                 else
                     a->sube= b;
            } 
            
            else 
               if(( p->subd == NULL ) && ( p->sube != NULL )){
                    antecessor( p, &q, &b );
                    p->info= q->info; // substitui o c�digo
                    a= b;             // ponteiros auxiliares s�o posicionados na sub�rvore 
                    p= q;

                    if( p->subd != NULL ) // ajusta subarvore
                        b= p->subd;
                    else
                        b= p->sube;
     
                    if( p->info.codigo >= a->info.codigo )
                        a->sube= b;
                    else
                        a->subd= b;
               }  
               else
                  if(( p->subd == NULL ) && ( p->sube == NULL ))
                       if( p == *r ) // remove a raiz quando n�o tem filhos
                           *r= NULL;
                       else      
                           if( p->info.codigo >= a->info.codigo )
                               a->subd= NULL;
                           else
                               a->sube= NULL;
                
            free( p ); // remove registro que substituiu o exclu�do
       }
   }
}


/*************************************************** 
 * sucessor                                        *
 * objetivo: rotina para descobrir nodos filhos    *
 * entrada : ARVORE, ponteiros auxiliares q e b    *
 * sa�da   : ponteiros auxiliares q e b            *
 ***************************************************/ 
void sucessor( ARVORE* p, ARVORE** q, ARVORE** b ){
 *b= p;
 *q= p->subd;
 while( (*q)->sube != NULL ){ // caminha pela esquerda at� encontrar folha
         *b= *q;              // atualiza ponteiro para guardar endere�o do pai
         *q= (*q)->sube;      // caminha para a esquerda
 }
}
 
 
 
/*************************************************** 
 * antecessor                                      *
 * objetivo: rotina para descobrir nodos filhos    *
 * entrada : ARVORE, ponteiros auxiliares q e b    *
 * sa�da   : ponteiros auxiliares q e b            *
 ***************************************************/ 
void antecessor( ARVORE* p, ARVORE** q, ARVORE** b ){
 *b= p;
 *q= p->sube;
 while( (*q)->subd != NULL ){ // caminha pela direita at� encontrar folha
         *b= *q;              // atualiza ponteiro para guardar endere�o do pai
         *q= (*q)->subd;      // caminha para a direita
 }
}         



/************************************************* 
 * insere_recursivo                              *
 * objetivo: rotina para inserir no fim da ARVORE*
 * entrada : ARVORE e cod                        *
 * sa�da   : ARVORE com mais um registro         *
 *************************************************/ 
void insere_recursivo( ARVORE** p, int cod ){
   if( *p == NULL ){                                     // se n�o achou o c�digo, insere
         ARVORE* no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em mem�ria
         no->info.codigo= cod;  
         no->subd= NULL;                                 // inicializa sub�rvore da direita
         no->sube= NULL;								 // inicializa sub�rvore da esquerda
         *p= no;                                         // anterior aponta para novo registro
         printf( "\n Registro inserido!" );   
   }else{
         if( (*p)->info.codigo > cod )                   // verifica se c�digo a ser inserido � menor que o valor do registro para qual o p aponta
              insere_recursivo( &(*p)->sube, cod );      // anda com o ponteiro p para a esquerda, pois o c�digo procurado � menor
         else
              if( (*p)->info.codigo < cod )              // verifica se c�digo a ser inserido � maior que o valor do registro para qual o p aponta
                   insere_recursivo( &(*p)->subd, cod ); // anda com o ponteiro p para a direita, pois o c�digo procurado � maior 
              else
                 printf( "\n Registro j� existe!" );    
		 }			    
} // desempilha



/***************************************************
 * busca_recursivo                                 *
 * objetivo: rotina para buscar registro por c�digo*
 * entrada : ARVORE e cod                          *
 * sa�da   : ARVORE com mais um registro           *
 ***************************************************/ 
ARVORE* busca_recursivo( ARVORE *p, int cod ){
   if( p == NULL || p->info.codigo == cod )
       return p; 
   else{
       if( p->info.codigo > cod )
            return busca_recursivo( p->sube, cod ); // anda com o ponteiro p para a esquerda, pois o c�digo procurada � menor
       else
            return busca_recursivo( p->subd, cod ); // anda com o ponteiro p para a direita, pois o c�digo procurada � maior 
   } 
   
    if( *p == NULL || (*p)->info.codigo == cod ){
    	printf("achou!!!");
	}
}


/****************************************************
 * remove_recursivo                                 *
 * objetivo: rotina para remover registro por c�digo*
 * entrada : ARVORE e cod                           *
 * sa�da   : ARVORE com registro removido           *
 ****************************************************/ 
ARVORE* remove_recursivo( ARVORE *p, int cod ){
	 if( p == NULL )
	     return NULL;
	 else 
	     if( p->info.codigo > cod )     // procura o c�digo pela esquerda
			 p->sube= remove_recursivo( p->sube, cod );
         else
		     if( p->info.codigo < cod ) // procura o c�digo pela esquerda
				 p->subd= remove_recursivo( p->subd, cod );
			 else{                      // achou o n� e este n�o tem filhos
				 if( p->sube == NULL && p->subd == NULL ){
					 free( p );
					 p= NULL;
				 }else                  // achou o n� e este tem filho � direita
					 if( p->sube == NULL ){
						 ARVORE* aux= p;
						 p= p->subd;
						 free( aux );
					 }else              // achou o n� e este tem filho � esquerda
					     if( p->subd == NULL ){
							 ARVORE* aux= p;
							 p= p->sube;
							 free( aux );
						 }else{         // achou o n� e este tem os dois filhos
							 ARVORE* aux2 = p->sube;     // procura o maior da esquerda
							 while( aux2->subd != NULL )  
							 		aux2= aux2->subd;
							 p->info= aux2->info;        // troca as informa��es
							 aux2->info.codigo= cod;
							 p->sube= remove_recursivo( p->sube, cod );
						 }
			 }
 return p;
}


/****************************************************
 * calcula_altura                                   *
 * objetivo: rotina para calcular a altura da �rvore*
 * entrada : ARVORE                                 *
 * sa�da   : ARVORE com campo altura atualizado     *
 ****************************************************/ 
void calcula_altura( ARVORE **r ){
	ARVORE *aux= *r;                            // ponteiro auxiliar para percorrer a �rvore
    
    if( aux != NULL ){                          // verifica se a raiz � diferente de NULL
        aux->info.altura= altura_arvore( aux ); // verifica a altura do n�
        aux->info.fatbal= ( altura_arvore( aux->subd ) + 1 ) - ( altura_arvore( aux->sube ) + 1 ); // calcula fator de balanceamento (fatbal) do n�
        //printf("\n Cod:%i  A:%i  Fatbal:%i  \n", aux->info.codigo, aux->info.altura, fatbal);
   	    calcula_altura( &aux->subd );          // recursivo, segue pelo caminho da direita do n�
        calcula_altura( &aux->sube );          // recursivo, segue pelo caminho da esquerda do n�
    }
}


/****************************************************
 * verifica_balanceamento                           *
 * objetivo: rotina para calcular o balancemaneto   *
 * entrada : ARVORE                                 *
 * sa�da   : ARVORE balanceada                      *
 ****************************************************/ 
void verifica_balanceamento( ARVORE **r ){
	ARVORE *aux= *r;                                // cria ponteiro auxiliar para percorrer a �rvore
    printf("\n chama");
    if( aux != NULL ){                              // verifica se ponteiro � diferente de NULL
		if( aux->info.fatbal >= 2 && ( aux->subd->info.fatbal != 2 && aux->subd->info.fatbal != -2 ) ){ // verifica fator de balanceamento no n� pai e filho, se n� pai for maior do que 1, a rota��o ser� � esquerda 
	        if( aux->subd->info.fatbal < 0 ){       // se sinal do fatbal do n� filho for negativo, realiza rota��o dupla				
	            rotacao_direita( &aux->subd );	    // rota��o esquerda - dupla
		        rotacao_esquerda( &aux );
			}else                                   // se sinal do fatbal do n� filho for positivo, realiza rota��o simples
    			rotacao_esquerda( &aux );
	    }else
            if( aux->info.fatbal <= -2 && ( aux->sube->info.fatbal != 2 && aux->sube->info.fatbal != -2 ) ){ // verifica fator de balanceamento no n� pai e filho, se n� pai for menor do que 1, a rota��o ser� � direita
		        if( aux->sube->info.fatbal > 0 ){   // se sinal do fatbal do n� filho for positvo, realiza rota��o dupla  
		            rotacao_esquerda( &aux->sube ); // rota��o direita - dupla	  
			        rotacao_direita( &aux );
				}else 
	    			rotacao_direita( &aux );        // se sinal do fatbal do n� filho for positivo, realiza rota��o simples
			}else{
					verifica_balanceamento( &aux->sube ); // continua verificando balanceamento � esquerda
					verifica_balanceamento( &aux->subd ); // continua verificando balanceamento � direita 	
			}
		calcula_altura( &aux );	                    // atualiza a altura dos n�s da �rvore ap�s rota��o
   }
   *r= aux;                                         // atualiza a raiz ap�s rota��o
}

/****************************************************
 * altura_arvore                                    *
 * objetivo: rotina para calcular a altura da �rvore*
 * entrada : ARVORE                                 *
 * sa�da   : altura                                 *
 ****************************************************/ 
int altura_arvore( ARVORE *p ){
	 int altura_esq, altura_dir;
	 if( p == NULL  )                           // finaliza o percurso
	     return -1;
     else{
          altura_dir= altura_arvore( p->subd ); // percorre � direita
	 	  altura_esq= altura_arvore( p->sube ); // percorre � esquerda
          if( altura_dir > altura_esq )         // se altura da direita maior, soma mais um n�vel � direita
              return altura_dir + 1;
          else                                  // se altura da esquerda maior, soma mais um n�vel � esquerda
              return altura_esq + 1;		      
     }
}


/****************************************************
 * rotacao_direita                                  *
 * objetivo: rotina para rotacionar �rvore          *
 * entrada : ARVORE                                 *
 * sa�da   : ARVORE rotacionada                     *
 ****************************************************/ 
void rotacao_direita( ARVORE **p ){
	 ARVORE *aux;
	 if( *p != NULL ){                            // percurso at� NULL
	 	  aux= (*p)->sube;                        // aponta � esquerda
		  (*p)->sube= aux->subd;                  // n� filho � direita  
		  aux->subd= *p;                          // raiz passa a ser n� filho
		  *p= aux;                                // aux passa ser a nova raiz
     }
}


/****************************************************
 * rotacao_esquerda                                 *
 * objetivo: rotina para rotacionar �rvore          *
 * entrada : ARVORE                                 *
 * sa�da   : ARVORE rotacionada                     *
 ****************************************************/ 
void rotacao_esquerda( ARVORE **p ){
	 ARVORE *aux;
	 if( *p != NULL ){                            // percurso at� NULL
	 	  aux= (*p)->subd;                        // ponteiro auxiliar � posicionado no n� filho da direita
		  (*p)->subd= aux->sube;                  // ajusta apontamento, ponteiro direito pai aponta para ponteiro esquerdo do filho
		  aux->sube= *p;                          // ponteiro � esquerda no filho aponta para n� pai
		  *p= aux;                                // reposiciona p
     }
}

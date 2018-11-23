  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "tabela.h"

  int definirAtributos(FILE *arquivo);
  int escreverAtributos(char *nome, Atributo *atributo);  



  void criarTabela(){
      FILE *ptr_arq; //Ponteiro do arquivo
      char *nome_tabela;
      nome_tabela = (char *) malloc (20*sizeof(char));
      printf("Digite o nome da sua tabela: ");
      getchar();
      fscanf(stdin, "%s", nome_tabela);
      strcat(nome_tabela,".txt");

      //criando o arquivo com o nome da tabela
    ptr_arq = fopen(nome_tabela, "w+");
    if(ptr_arq==NULL){    
      printf("Erro de criacao");
    }
    else{
      if(definirAtributos(ptr_arq)>=0){
        printf("Tabela criada com sucesso!\n");              
      }else{
        printf("Houve um erro ao tentar criar a tabela!\n");
      }   
    }
    free(nome_tabela);
    fclose(ptr_arq);
  }

  int definirAtributos(FILE *tabela){
    char *nome;
    nome = (char*) calloc (20, sizeof(char));
    int coluna_counter=1,option, string_size;  
    Atributo *ptr_att = (Atributo*) calloc(1,sizeof(Atributo));   
    if(ptr_att==NULL){
      printf("Erro de memória!\n");
      return (-1);
    }
    else {    
      printf("---------COLUNAS DA TABELA----------\n");
      //CHAVE PRIMARIA
            printf("(%d) Digite o nome da chave primária: ", coluna_counter);
            fscanf(stdin, "%s", nome);            
            fprintf(tabela, "[%s (%s)]\n", nome, "int");
            coluna_counter++;
            //FIM DO PROCESSO DA CHAVE PRIMARIA            
            //Lembrete, sempre a chave primária será a primeira coluna, por definição nossa
      do{
        //definindo as colunas da tabela  
        printf("(%d) Digite o tipo da coluna : \n1-CHAR | 2-INT | 3-FLOAT | 4-DOUBLE | 5-STRING | 0-FIM\n", coluna_counter);      
        scanf("%d", &option);
        if(option!=0){ 
          printf("(%d) Digite o nome da coluna (max 20 caracteres): \n", coluna_counter);
          fscanf(stdin, "%s", nome);   
          if(verificaColunas(tabela, nome) == 0){
            //coluna ainda n existe
            switch(option){          
              case 1:            
                (ptr_att)->nome=nome;
                (ptr_att)->tipo= "char";                
                break;
              case 2:
                (ptr_att)->nome=nome;
                (ptr_att)->tipo="int";                
                break;
              case 3:
                (ptr_att)->nome=nome;
                (ptr_att)->tipo="float";                
                break;
              case 4:
                (ptr_att)->nome = nome;
                (ptr_att)->tipo = "double";                
                break;
              case 5:
                (ptr_att)->nome=nome;
                (ptr_att)->tipo="string";
                printf("Digite o tamanho da string que desejas: ");
                getchar();
                scanf("%d", &string_size);                
                break; 
              default:
                printf("Digite um valor válido!\n");            
            } 
            int length= strlen(ptr_att->nome);
            fprintf(tabela, "[%s (%s)]\n",ptr_att->nome, ptr_att->tipo); 
            coluna_counter++;
          }else{
            printf("Já existe uma coluna com esse nome!\n");
          }      
        }
      }while(option != 0);       
    }
    free(ptr_att);
    free(nome);
    return 0;
  }

  int verificaColunas(FILE *tabela, char *nome){
      int count = 0, k = 0;        
      char buffer[256];   
      int qnt_colunas = contarColunas(tabela, '[');        
      char **linhas = (char**) calloc(qnt_colunas, sizeof(char*));
      if(linhas == NULL){
        fprintf(stderr, "Erro1");
        return -1;
      }else{ 
        fseek(tabela,0, SEEK_SET);        
        while (fgets(buffer,256, tabela)) 
        {                         
          linhas[count] = (char*) calloc(20, sizeof(char));
          if(linhas[count] == NULL){
            fprintf(stderr, "Erro");
            return -1;
          }else{            
            //armazena cada linha de colunas da tabela em um vetor
            strcpy(linhas[count],buffer);
          }
          count++;
        }
      }
      for(int j = 0; j<count; j++){
        if(strstr(linhas[j], nome) != NULL){
          return 1;
          //nome já existe existe
        }
      }      
      return 0;          
  }

int contarColunas(FILE* tabela, char separador){
    int colunas = 0, ch = 0;
    while(!feof(tabela))
      {
        ch = fgetc(tabela);
        if(ch == separador)
        {
          colunas++;
        }
      }
      return colunas;
}

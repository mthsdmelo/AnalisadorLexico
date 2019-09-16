#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ID 0

char palavras_reservadas[22][10] = {
"break"
,"case"
,"char"
,"continue"
,"default"
,"do"
,"double"
,"else"
,"float"
,"for"
,"if"
,"int"
,"long"
,"return"
,"short"
,"sizeof"
,"struct"
,"switch"
,"typedef"
,"unsigned"
,"void"
,"while" };

#define ADD 23            // +
#define SUB 24            // -
#define MUL 25            // *
#define DIV 26            // /
#define IGUAL 27          // =
#define OR 28             // ||
#define AND 29            // &&
#define ADD_ADD 30        // ++
#define SUB_SUB 31        // --
#define ADD_IGUAL 32      // +=
#define MUL_IGUAL 33      // *=
#define DIV_IGUAL 34      // /=
#define SUB_IGUAL 35      // -=
#define IGUAL_IGUAL 36    // ==
#define MAIOR 37          // >
#define MENOR 38          // <
#define MAIOR_IGUAL 39    // >=
#define MENOR_IGUAL 40    // <=


#define PONTO_VIRGULA 41  // ;
#define O_COLCHETE 42     // [
#define C_COLCLETE 43     // ]
#define VIRGULA 44        // ,
#define O_PARENTESES 45   // (
#define C_PARENTESES 46   // )
#define ASPAS_D 47        // "
#define ASPAS_S 48        // '
#define O_CHAVE 49        // {
#define C_CHAVE 50        // }
#define DOIS_PONTOS 51    // :

void gera_token_palava(char palavra[],int x,int y,FILE *arq){
  int i;
  for(i=0;i<22;i++){
    if(strcmp(palavra,palavras_reservadas[i])==0){
      fprintf(arq,"%d,%d,%d\n",i+1,y,x);
      return;
    }
  }
  fprintf(arq,"%s,%d,%d,%d\n",palavra,ID,y,x);
  return;
}
void gera_token_separador(char c,int x,int y,FILE *arq){
  switch(c){
    case ';':
      fprintf(arq,"%d,%d,%d\n",PONTO_VIRGULA,y,x);
      break;
    case '[':
      fprintf(arq,"%d,%d,%d\n", O_COLCHETE,y,x);
      break;
    case ']':
      fprintf(arq,"%d,%d,%d\n",C_COLCLETE,y,x);
      break;
    case ',':
      fprintf(arq,"%d,%d,%d\n",VIRGULA,y,x);
      break;
    case '(':
      fprintf(arq,"%d,%d,%d\n",O_PARENTESES,y,x);
      break;
    case ')':
      fprintf(arq,"%d,%d,%d\n",C_PARENTESES,y,x);
      break;
    case '\"':
      fprintf(arq,"%d,%d,%d\n",ASPAS_D,y,x);
      break;
    case '\'':
      fprintf(arq,"%d,%d,%d\n",ASPAS_S,y,x);
      break;
    case '{':
      fprintf(arq,"%d,%d,%d\n",O_CHAVE,y,x);
      break;
    case '}':
      fprintf(arq,"%d,%d,%d\n",C_CHAVE,y,x);
      break;
    case ':':
      fprintf(arq,"%d,%d,%d\n",DOIS_PONTOS,y,x);
      break;
  }
}
void gera_token_numero(char numero[],int x,int y,FILE *arq){
      fprintf(arq,"_%s,%d,%d\n",numero,y,x);
}
void gera_token_operador(char c[],int x,int y,FILE *arq){
  if(strcmp(c,"+")==0){
    fprintf(arq,"%d,%d,%d\n",ADD,y,x);
  }
  else if(strcmp(c,"-")==0){
    fprintf(arq,"%d,%d,%d\n",SUB,y,x);
  }
  else if(strcmp(c,"*")==0){
    fprintf(arq,"%d,%d,%d\n",MUL,y,x);
  }
  else if(strcmp(c,"/")==0){
    fprintf(arq,"%d,%d,%d\n",DIV,y,x);
  }
  else if(strcmp(c,"=")==0){
    fprintf(arq,"%d,%d,%d\n",IGUAL,y,x);
  }
  else if(strcmp(c,"||")==0){
    fprintf(arq,"%d,%d,%d\n",OR,y,x);
  }
  else if(strcmp(c,"&&")==0){
    fprintf(arq,"%d,%d,%d\n",AND,y,x);
  }
  else if(strcmp(c,"++")==0){
    fprintf(arq,"%d,%d,%d\n",ADD_ADD,y,x);
  }
  else if(strcmp(c,"--")==0){
    fprintf(arq,"%d,%d,%d\n",SUB_SUB,y,x);
  }
  else if(strcmp(c,"+=")==0){
    fprintf(arq,"%d,%d,%d\n",ADD_IGUAL,y,x);
  }
  else if(strcmp(c,"*=")==0){
    fprintf(arq,"%d,%d,%d\n",MUL_IGUAL,y,x);
  }
  else if(strcmp(c,"/=")==0){
    fprintf(arq,"%d,%d,%d\n",DIV_IGUAL,y,x);
  }
  else if(strcmp(c,"-=")==0){
    fprintf(arq,"%d,%d,%d\n",SUB_IGUAL,y,x);
  }
  else if(strcmp(c,"==")==0){
    fprintf(arq,"%d,%d,%d\n",IGUAL_IGUAL,y,x);
  }
  else if(strcmp(c,">")==0){
    fprintf(arq,"%d,%d,%d\n",MAIOR,y,x);
  }
  else if(strcmp(c,"<")==0){
    fprintf(arq,"%d,%d,%d\n",MENOR,y,x);
  }
  else if(strcmp(c,">=")==0){
    fprintf(arq,"%d,%d,%d\n",MAIOR_IGUAL,y,x);
  }
  else if(strcmp(c,"<=")==0){
    fprintf(arq,"%d,%d,%d\n",MENOR_IGUAL,y,x);
  }
  return;
}

void gera_token_literal(char str[],FILE *arq){
  fprintf(arq,"\"%s\"\n",str);
}

int main(int argc, char *argv[]){
    FILE *arq = fopen(argv[1],"r");
    FILE *erros = fopen("logErros.txt","w");
    FILE *lista_tokens = fopen("lista_tokens.txt","w");
    int x=0,y=0,i;
    char palavra[31];
    char numero[32];
    char c=fgetc(arq);
    char literal[200];
    char operador[3];
    while(1){
//-----------------------Palavras (reservadas ou nao)-------------------------------------
      if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c=='_'||c=='$'){
        for(i=0;(c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_'||c=='$';i++){
          palavra[i]=c;
          c = fgetc(arq);
          x++;
        }
        palavra[i]='\0';
        gera_token_palava(palavra,x,y,lista_tokens);
      }
//-----------------------Numeros-------------------------------------
      else if(c>='0'&&c<='9'){
        i=0;
        if(c=='0'){
          numero[i]=c;
          c = fgetc(arq);
          x++;
          i++;
          if(c=='x'){
            numero[i]=c;
            for(;(c>='0'&&c<='9')||(c>='a'&&c<='f');i++){
              numero[i]=c;
              c = fgetc(arq);
              x++;
            }
          }
        }
        for(;(c>='0'&&c<='9')||c=='.';i++){
          numero[i]=c;
          c = fgetc(arq);
          x++;
        }
       numero[i]='\0';
       gera_token_numero (numero,x,y,lista_tokens);
      }
      else if(c=='.'){
        i=2;
        numero[0]='0';
        numero[1]='.';
        c = fgetc(arq);
        for(;(c>='0'&&c<='9');i++){
          numero[i]=c;
          c = fgetc(arq);
          x++;
        }
        numero[i]='\0';
        gera_token_numero (numero,x,y,lista_tokens);
      }
//-----------------------Literais-------------------------------------
      else if(c=='\''){
        gera_token_separador(c,x,y,lista_tokens);
        c=fgetc(arq);
        x++;
        for(i=0;i<200;i++){
          if(c=='\''){
            break;
          }
          literal[i] = c;
          c=fgetc(arq);
          x++;
        }
        literal[i]='\0';
        gera_token_literal(literal,lista_tokens);
        gera_token_separador(c,x,y,lista_tokens);
        c = fgetc(arq);
        x++;
      }
      else if(c=='\"'){
        gera_token_separador(c,x,y,lista_tokens);
        c=fgetc(arq);
        x++;
        for(i=0;i<200;i++){
          if(c=='\"'){
            break;
          }
          literal[i] = c;
          c=fgetc(arq);
          x++;
        }
        literal[i]='\0';
        gera_token_literal(literal,lista_tokens);
        gera_token_separador(c,x,y,lista_tokens);
        c = fgetc(arq);
        x++;
      }
//------------------------Comentarios-----------------------------------
      else if(c=='/'){
        c=fgetc(arq);
        x++;
        if(c=='/'){
          while(1){
            c=fgetc(arq);
            x++;
              if(c=='\n'){
                x=0;y++;
                c=fgetc(arq);
                break;
              }
          }
        }
        else if(c=='*'){
          c=fgetc(arq);
          if(c=='\n'){
            x=0;
            y++;
          }
          else x++;
          while(1){
            if(c=='*'){
              c=fgetc(arq);
              if(c=='\n'){
                x=0;
                y++;
              }
              else x++;

              if(c=='/'){
                break;
              }
              else continue;
            }
            c=fgetc(arq);
            if(c=='\n'){
              x=0;
              y++;
            }
            else x++;
          }
        }
        else if(c=='='){
          gera_token_operador("/=",x,y,lista_tokens);
        }
        else
          gera_token_operador("/",x,y,lista_tokens);
      }
//---------------------------Separadores--------------------------
      else if(c==';'||c=='['||c==']'||c==','||c=='('||c==')'||c=='{'||c=='}'||c==':'){
        gera_token_separador(c,x,y,lista_tokens);
        c=fgetc(arq);
        x++;
      }
//---------------------------Operadores----------------------------
      else if(c=='*'||c=='+'||c=='-'||c=='='||c=='<'||c=='>'){
        operador[0]=c;
        c = fgetc(arq);
        x++;
        if(c=='='){
          operador[1]=c;
          c = fgetc(arq);
          x++;
        }
        else if(operador[0]=='+' && c=='+'){
          operador[1]=c;
          c = fgetc(arq);
          x++;
        }
        else if(operador[0]=='-' && c=='-'){
          operador[1]=c;
          c = fgetc(arq);
          x++;
        }
        else {
          operador[1]='\0';
        }
        operador[2]='\0';
        gera_token_operador(operador,x-1,y,lista_tokens);
      }
      else if(c=='|'||c=='&'){
        operador[0]=c;
        c = fgetc(arq);
        x++;
        if(operador[0]=='|' && c=='|'){
          operador[1]=c;
          c = fgetc(arq);
          x++;
          operador[2]='\0';
          gera_token_operador(operador,x-1,y,lista_tokens);
        }
        else if(operador[0]=='&' && c=='&'){
          operador[1]=c;
          c = fgetc(arq);
          x++;
          operador[2]='\0';
          gera_token_operador(operador,x-1,y,lista_tokens);
        }
        else {
          fprintf(erros,"Erro lexico linha: %d, coluna: %d.\n",y,x);
        }
      }
      else if(c=='\n'){
        c = fgetc(arq);
        x=0;
        y++;
      }
      else if(c==EOF){
       break;
      }
      else if(c==' '){
        c = fgetc(arq);
        x++;
      }
      else {
        fprintf(erros,"Simbolo %c nao reconhecido, linha: %d, coluna: %d.\n",c,y,x);
        c = fgetc(arq);
        x++;
      }
    }

}

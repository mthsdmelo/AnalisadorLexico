# Analisador Léxico
 Analisador Léxico criado para a disciplina de Compiladores da Universidade Federal de São João del Rei. 
## Compilação
  ```
  make
  ```
## Execução
  ```
  ./compilar arquivo
  ```
  Onde arquivo corresponde ao arquivo de entrada do analisador 
  
## Saída
  Após a execução a lista de token do codigo analizado é armazenada no arquivo lista_tokens.txt já os erros são armazenados no arquivo logErros.txt
  
## Formato lista de tonken
  ### Identificadores
  ```
  Nome_identificador,0,linha,coluna
  ```
  ### Palavras reservadas(Incluindo operadores e separadores)
  ```
  Id_palavra_reservada,linha,coluna
  ```
  ### Literais
  ```
  "Este eh um literal"
  ```
  ### Numeros
  ```
  _numero,linha,coluna
  ```
## Exemplo de execução
  Executando o seguinte código, presente no arquivo teste.c:
  ```
  int main(){
  int i,j;
  for (i = 0; i < 20 ;i++)
    {
      j+=i;
    }
    return 0;
  }
  ```
  Obtivemos a seguinte lista de tokens:
  ```
  12,0,3
  main,0,0,8
  45,0,8
  46,0,9
  49,0,10
  12,1,5
  i,0,1,7
  44,1,7
  j,0,1,9
  41,1,9
  10,2,5
  45,2,6
  i,0,2,8
  27,2,9
  _0,2,12
  41,2,12
  i,0,2,15
  38,2,16
  _20,2,20
  41,2,21
  i,0,2,23
  30,2,24
  46,2,25
  49,3,4
  j,0,4,7
  32,4,8
  i,0,4,10
  41,4,10
  50,5,4
  14,6,10
  _0,6,12
  41,6,12
  50,7,0
  ```

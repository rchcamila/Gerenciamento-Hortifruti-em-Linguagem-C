#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "administrativo.h"
#include "menu.h"

#define MAX_USERS 100
#define NOME_MAX 40
#define USERNAME_LENGTH 20 //Tamanho máximo do usuario
#define PASSWORD_LENGTH 20 //Tamanho máximo da senha

typedef struct{
    char pais[NOME_MAX];
    char uf[3];
    char cidade[NOME_MAX];
    char bairro[NOME_MAX];
    char rua[NOME_MAX];
}endereco;

typedef struct{
    char nome[NOME_MAX];
    int idade;
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    endereco end;
}funcionario; funcionario f[MAX_USERS];

int idUser = -1;
int quantidadeFunc = -1;

char *removeSpaces(char *str){
    int i, j = 0;
    for(i = 0; str[i] != '\0'; i++){
        if(str[i] != ' '){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void lerFuncionarios(funcionario func[MAX_USERS]){
    FILE *bd_funcionarios = fopen("banco_dados/funcionarios.csv", "r");
    FILE *bd_end_funcionarios = fopen("banco_dados/end_funcionarios.csv", "r");
    if(!bd_funcionarios){
        printf("Não há funcionários cadastrados\n");
        return 0;
    }
    char buffer_funcionario[1024]; //buffer para armazenar dados da linha
    char buffer_endereco[1024];
    char *data;

    //Lê as primeira linha para pular
    fgets(buffer_funcionario, sizeof(buffer_funcionario), bd_funcionarios);
    fgets(buffer_endereco, sizeof(buffer_endereco), bd_end_funcionarios);

    int i = 0; //contará a quantidade de funcionários

    //Lê o resto das linhas
    while(fgets(buffer_funcionario, sizeof(buffer_funcionario), bd_funcionarios)){ //Confere se ainda tem dados nas linhas

        //Nome
        data = strtok(buffer_funcionario, ",");
        strcpy(func[i].nome, data);

        //Idade
        data = strtok(NULL, ",");
        func[i].idade = atoi(data);

        //Usuário
        data = strtok(NULL, ",");
        strcpy(func[i].username, data);

        //Senha
        data = strtok(NULL, ",");
        strcpy(func[i].password, data);

        //Lê os endereços
        fgets(buffer_endereco, sizeof(buffer_endereco), bd_end_funcionarios);

        //País
        data = strtok(buffer_endereco, ","); //Lê o primeiro dado até a ","
        strcpy(func[i].end.pais, data);

        //UF
        data = strtok(NULL, ","); //Lê o dado seguinte até a ","
        strcpy(func[i].end.uf, data);

        //Cidade
        data = strtok(NULL, ",");
        strcpy(func[i].end.cidade, data);

        //Bairro
        data = strtok(NULL, ",");
        strcpy(func[i].end.bairro, data);

        //Rua
        data = strtok(NULL, ",");
        strcpy(func[i].end.rua, data);
        i++;
    }
    //fecha o arquivo
    fclose(bd_funcionarios);
    fclose(bd_end_funcionarios);

    quantidadeFunc = i;
}

void rotinaAdministrativo(int id){
    idUser = id;
    lerFuncionarios(f);
    if(quantidadeFunc > 0){
        printf("Quantidade de funcionários cadastrados: %d\n",quantidadeFunc);
    }

    printf("==============================================\n");

    while(1){
        int opcao = 0;
        printf("Escolha uma opção:\n");
        printf("1 - Funcionários\n"); //Aqui o usuário poderá escolher entre cadastrar, alterar ou remover um funcionario
        printf("2 - Fornecedores\n"); //Aqui o usuário poderá escolher entre cadastrar, alterar ou remover um fornecedor
        printf("3 - Retornar ao menu anterior\n");

        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            //alterarFuncionario();
            limpar_tela();
            alterarFuncionario();
            break;
        case 2:
            //cadastrarFornecedor();
            limpar_tela();
            printf("Rotina não implementada\n");
            break;
        case 3:
            menu(idUser);
            break;
        default:
            limpar_tela();
            printf("Opção não encontrada, pressione ENTER para retornar\n");
            getchar();
            getchar();
            limpar_tela();
            break;
        }
    }
}

void alterarFuncionario(){
    int opcao = 0;
    printf("Escolha uma opção:\n");
    printf("1 - Cadastrar funcionário\n");
    printf("2 - Listar funcionários\n");
    printf("3 - Alterar cadastro de funcionário\n");
    printf("4 - Remover cadastro de funcionário\n");
    printf("5 - Cancelar\n");

    scanf("%d", &opcao);

    switch (opcao){
    case 1:
        cadastrarFuncionario();
        limpar_tela();
        break;
    case 2:
        limpar_tela();
        lerFuncionarios(f);
        listarFuncionarios();
        alterarFuncionario();
        break;
    case 3:
        printf("teste");
        break;
    case 4:
        printf("teste");
        break;
    default:
        printf("teste");
        limpar_tela();
    }
}

void listarFuncionarios(){
    int i;
    printf("==============================================\n");
    printf("ID\t-\tNome\t-\tPaís\n");
    printf("==============================================\n");
    for(i = 0; i < quantidadeFunc; i++){
        printf("%d - %s\t%s\n",i,f[i].nome,f[i].end.pais);
    }
    printf("Pressione ENTER para voltar");
    getchar();
    getchar();
    limpar_tela();
}

void cadastrarFuncionario(){
    funcionario novo_funcionario;

    printf("Seja Bem-Vindo a rotina de cadastro de funcionário\n\n");
    printf("NOME (MAX 40 CARACTERES): ");
    scanf(" %39[^\n]", novo_funcionario.nome);
    printf("IDADE: ");
    scanf(" %d", &novo_funcionario.idade);
    printf("USERNAME (MAX 20 CARACTERES): ");
    scanf(" %19[^\n]", novo_funcionario.username);
    printf("PASSWORD (MAX 20 CARACTERES): ");
    scanf(" %19[^\n]", novo_funcionario.password);
    printf("PAÍS (MAX 40 CARACTERES): ");
    scanf(" %39[^\n]", novo_funcionario.end.pais);
    printf("UF (MAX 2 CARACTERES): ");
    scanf(" %2[^\n]", novo_funcionario.end.uf);
    printf("CIDADE (MAX 40 CARACTERES): ");
    scanf(" %39[^\n]", novo_funcionario.end.cidade);
    printf("BAIRRO (MAX 40 CARACTERES): ");
    scanf(" %39[^\n]", novo_funcionario.end.bairro);
    printf("RUA (MAX 40 CARACTERES): ");
    scanf(" %39[^\n]", novo_funcionario.end.rua);


    FILE *bd_funcionarios = fopen("banco_dados/funcionarios.csv", "a+");
    FILE *bd_end_funcionarios = fopen("banco_dados/end_funcionarios.csv", "a+");

    if(!bd_funcionarios| !bd_end_funcionarios){
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }
    else
    {
        fseek(bd_funcionarios, 0, SEEK_END); //Coloca o ponteiro no final do arquivo;
        int size = ftell(bd_funcionarios); //Define o tamanho da tabela baseado na posição do ponteiro;
        if(size == 0){ //Caso o tamanho da tabela = 0;
            printf("file is empty");
            fprintf(bd_funcionarios, "NOME,IDADE,USUARIO,SENHA\n"); //Escreve cabeçalho na tabela;
            fprintf(bd_end_funcionarios, "PAIS,UF,CIDADE,BAIRRO,RUA\n");
        }
    }
    fprintf(bd_funcionarios, "%s,%i,%s,%s,\n",
            novo_funcionario.nome,
            novo_funcionario.idade,
            novo_funcionario.username,
            novo_funcionario.password);
    fprintf(bd_end_funcionarios, "%s,%s,%s,%s,%s,\n",
            novo_funcionario.end.pais,
            novo_funcionario.end.uf,
            novo_funcionario.end.cidade,
            novo_funcionario.end.bairro,
            novo_funcionario.end.rua);
    fclose(bd_funcionarios);
    fclose(bd_end_funcionarios);
}

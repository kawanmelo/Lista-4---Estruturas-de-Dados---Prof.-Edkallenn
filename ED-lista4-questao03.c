#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
** Função : Receber dados e utiliza-los para definir os membros de uma variável da estrutura perfil_saude.
** Autor : Kawan Melo - 3º período turma F 2024.1
** Data : 25.05.2024
** Observações: Null
*/

#define expectativaM 73
#define expectativaF 80

typedef struct {
    short int dia;
    short int mes;
    int ano;
} Data;

typedef struct {
    char nome[80];
    char sexo[2];
    Data data_de_nascimento;
    float altura;
    float peso;
} Perfil_saude;

// Getters
char* get_nome(Perfil_saude *perfil) {
    return perfil->nome;
}

char* get_sexo(Perfil_saude *perfil) {
    return perfil->sexo;
}

Data get_data_de_nascimento(Perfil_saude *perfil) {
    return perfil->data_de_nascimento;
}

float get_altura(Perfil_saude *perfil) {
    return perfil->altura;
}

float get_peso(Perfil_saude *perfil) {
    return perfil->peso;
}

// Setters
void set_nome(Perfil_saude *perfil, char *nome) {
    strncpy(perfil->nome, nome, 80);
}

void set_sexo(Perfil_saude *perfil, char *sexo) {
    strncpy(perfil->sexo, sexo, 2);
}

void set_data_de_nascimento(Perfil_saude *perfil, short int dia, short int mes, int ano) {
    perfil->data_de_nascimento.dia = dia;
    perfil->data_de_nascimento.mes = mes;
    perfil->data_de_nascimento.ano = ano;
}

void set_altura(Perfil_saude *perfil, float altura) {
    perfil->altura = altura;
}

void set_peso(Perfil_saude *perfil, float peso) {
    perfil->peso = peso;
}

//  função para calcular a idade. 
int calcula_idade(Perfil_saude *perfil){
  //  recebe o ano da data atual
  time_t agora = time(NULL);
  struct tm *local = localtime(&agora);
  int ano_atual = local->tm_year + 1900;
  //  retorna a diferença entre o ano da data atual e o ano de nascimento
  int idade = ano_atual - perfil->data_de_nascimento.ano; 
  return idade;
}

// Função para calcular a frequência cardíaca máxima
int calcula_fcmax(Perfil_saude *perfil) {
    int idade = calcula_idade(perfil);
    return (strcmp(perfil->sexo, "m") == 0) ? 220 - idade : 226 - idade;
}

// Função para calcular a frequência cardíaca ideal
float calcula_fcideal(Perfil_saude *perfil) {
    int fcmax = calcula_fcmax(perfil);
    return fcmax * 0.7;
}

// Função para calcular o IMC
float calcula_imc(Perfil_saude *perfil) {
    return perfil->peso / (perfil->altura * perfil->altura);
}

// Função para calcular a expectativa de vida
int calcula_expectativa_vida(Perfil_saude *perfil) {
    int idade = calcula_idade(perfil);
    int expectativa = (strcmp(perfil->sexo, "m") == 0) ? expectativaM : expectativaF;
    return expectativa - idade;
}

// Função para exibir a tabela de valores do IMC
void exibe_tabela_imc() {
    printf("\nTabela de Valores do IMC:\n");
    printf("Menor que 18.5: Abaixo do peso\n");
    printf("Entre 18.5 e 24.9: Peso normal\n");
    printf("Entre 25 e 29.9: Sobrepeso\n");
    printf("Entre 30 e 34.9: Obesidade grau 1\n");
    printf("Entre 35 e 39.9: Obesidade grau 2\n");
    printf("40 ou maior: Obesidade grau 3\n");
}

int main() {
    int n;
    printf("Informe o número de perfis de saúde: ");
    scanf("%d", &n);
    getchar(); // Consumir o '\n' deixado pelo scanf

    Perfil_saude *perfis = malloc(sizeof(Perfil_saude) * n);

    for (int i = 0; i < n; i++) {
        char nome[80];
        char sexo[2];
        short int dia, mes;
        int ano;
        float altura, peso;

        printf("\nInforme os dados para o perfil %d:\n", i + 1);

        printf("Nome: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remover o '\n' final

        printf("Sexo (m/f): ");
        fgets(sexo, sizeof(sexo), stdin);
        sexo[strcspn(sexo, "\n")] = '\0'; // Remover o '\n' final

        printf("Data de Nascimento (dia.mes.ano): ");
        scanf("%hd.%hd.%d", &dia, &mes, &ano);
        getchar(); // Consumir o '\n' deixado pelo scanf

        printf("Altura (em metros): ");
        scanf("%f", &altura);
        getchar(); // Consumir o '\n' deixado pelo scanf

        printf("Peso (em kg): ");
        scanf("%f", &peso);
        getchar(); // Consumir o '\n' deixado pelo scanf

        set_nome(&perfis[i], nome);
        set_sexo(&perfis[i], sexo);
        set_data_de_nascimento(&perfis[i], dia, mes, ano);
        set_altura(&perfis[i], altura);
        set_peso(&perfis[i], peso);
    }

    for (int i = 0; i < n; i++) {
        printf("\nInformações do perfil %d:\n", i + 1);
        printf("Nome: %s\n", get_nome(&perfis[i]));
        printf("Sexo: %s\n", get_sexo(&perfis[i]));
        Data data = get_data_de_nascimento(&perfis[i]);
        printf("Data de Nascimento: %02d/%02d/%04d\n", data.dia, data.mes, data.ano);
        printf("Altura: %.2f metros\n", get_altura(&perfis[i]));
        printf("Peso: %.2f kg\n", get_peso(&perfis[i]));

        int idade = calcula_idade(&perfis[i]);
        float imc = calcula_imc(&perfis[i]);
        int fcmax = calcula_fcmax(&perfis[i]);
        float fcideal = calcula_fcideal(&perfis[i]);
        int expectativa = calcula_expectativa_vida(&perfis[i]);

        printf("Idade: %d anos\n", idade);
        printf("IMC: %.2f\n", imc);
        printf("Frequência Cardíaca Máxima: %d bpm\n", fcmax);
        printf("Frequência Cardíaca Ideal: %.2f bpm\n", fcideal);
        printf("Expectativa de Vida: %d anos restantes\n", expectativa);
    }

    exibe_tabela_imc();

    free(perfis);
    return 0;
}
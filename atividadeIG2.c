// Matricula: 202412638
// Nome: Eduarda de Campos Geraldo
// Email: eduarda.202412638@unilasalle.edu.br

// O que eu fiz no código: desenvolvi o código sozinha, com pesquisa e ajuda dos slides da aula e apoio do chatgpt para entender como implementar melhor as funções solicitadas.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// estrutura de aluno
    
typedef struct {
    int matricula;
    float g1;
    float g2;
    float media;
} Aluno;

// estrutura de pilha

typedef struct {
    Aluno *dados;
    int topo;
    int capacidade;
} Pilha;

int empty(Pilha *p) {
    return p->topo == -1;
}

int full(Pilha *p) {
    return p->topo == p->capacidade - 1;
}

int push(Pilha *p, Aluno a) {
    if (full(p)) {
        printf("Pilha cheia. (Não é possível empilhar mais alunos)\n");
        return 0;
    }
    p->topo++;
    p->dados[p->topo] = a;
    return 1;
}

Aluno pop(Pilha *p) {
    Aluno vazio = {-1, 0, 0, 0};
    if (empty(p)) {
        printf("Pilha vazia. (Não há alunos para desempilhar)\n");
        return vazio;
    }
    return p->dados[p->topo--];
}

void buscarMatricula(Pilha *p, int matriculaBusca) {
    if (empty(p)) {
        printf("Pilha vazia.\n");
        return;
    }

    int encontrado = FALSE;
    for (int i = p->topo; i >= 0; i--) {
        if (p->dados[i].matricula == matriculaBusca) {
            printf("Aluno encontrado:\n");
            printf("Matrícula: %d\n", p->dados[i].matricula);
            printf("G1: %.2f, G2: %.2f, Média: %.2f\n", p->dados[i].g1, p->dados[i].g2, p->dados[i].media);
            encontrado = TRUE;
            break;
        }
    }

    if (!encontrado)
        printf("Aluno com matrícula %d não encontrado.\n", matriculaBusca);
}

// estrutura de função para ler a nota com vírgula, e não só com ponto

float lervirgula() {
    char entrada[50];
    scanf("%s", entrada);

    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] == ',') {
            entrada[i] = '.';
        }
    }

    return atof(entrada);
}

// estrutura principal do código

int main() {
    Pilha p;
    int capacidade;

    printf("Digite a quantidade máxima de alunos: ");
    scanf("%d", &capacidade);

    p.dados = (Aluno *) malloc(capacidade * sizeof(Aluno));
    p.topo = -1;
    p.capacidade = capacidade;

    int opcao;
    do {
        printf("\n1 - Empilhar aluno\n2 - Desempilhar aluno\n3 - Buscar por matrícula\n4 - Listar alunos\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Aluno a;
            printf("Digite a matrícula: ");
            scanf("%d", &a.matricula);
            printf("Digite a nota da G1: ");
            a.g1 = lervirgula();
            printf("Digite a nota da G2: ");
            a.g2 = lervirgula();
            a.media = (a.g1 + a.g2) / 2;

            if (push(&p, a)) {
                printf("Aluno empilhado com média %.2f.\n", a.media);
            }

        } else if (opcao == 2) {
            Aluno removido = pop(&p);
            if (removido.matricula != -1) {
                printf("Aluno desempilhado:\n");
                printf("Matrícula: %d, G1: %.2f, G2: %.2f, Média: %.2f\n",
                       removido.matricula, removido.g1, removido.g2, removido.media);
            }

        } else if (opcao == 3) {
            int mat;
            printf("Digite a matrícula: ");
            scanf("%d", &mat);
            buscarMatricula(&p, mat);

        } else if (opcao == 4) {
            if (empty(&p)) {
                printf("A pilha está vazia.\n");
            } else {
                printf("\nLista de alunos na pilha:\n");
                for (int i = p.topo; i >= 0; i--) {
                    printf("Matrícula: %d, G1: %.2f, G2: %.2f, Média: %.2f\n",
                           p.dados[i].matricula, p.dados[i].g1, p.dados[i].g2, p.dados[i].media);
                }
            }
        }

    } while (opcao != 0);

// retorno
    
    free(p.dados);
    return 0;
}

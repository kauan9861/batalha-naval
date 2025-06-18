#include <stdio.h>

#define TAM_TAB 10
#define TAM_HAB 5

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para posicionar navios (3 blocos)
void posicionarNavios(int tabuleiro[TAM_TAB][TAM_TAB]) {
    // Navio horizontal
    int l1 = 1, c1 = 2;
    for (int i = 0; i < 3; i++) {
        tabuleiro[l1][c1 + i] = 3;
    }

    // Navio vertical
    int l2 = 4, c2 = 6;
    for (int i = 0; i < 3; i++) {
        tabuleiro[l2 + i][c2] = 3;
    }

    // Navio diagonal ↘
    int l3 = 0, c3 = 0;
    for (int i = 0; i < 3; i++) {
        tabuleiro[l3 + i][c3 + i] = 3;
    }

    // Navio diagonal ↙
    int l4 = 6, c4 = 9;
    for (int i = 0; i < 3; i++) {
        tabuleiro[l4 + i][c4 - i] = 3;
    }
}

// Função para criar habilidade CONE (↧)
void criarCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i >= j - 2 && i >= 2 - j) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar habilidade CRUZ (+)
void criarCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar habilidade OCTAEDRO (◆)
void criarOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linha = origem_linha - 2 + i;
            int coluna = origem_coluna - 2 + j;

            // Garante que está dentro dos limites
            if (linha >= 0 && linha < TAM_TAB && coluna >= 0 && coluna < TAM_TAB) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }
}

// Mostra o tabuleiro no console
void mostrarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\nTABULEIRO FINAL:\n\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");  // água
            else if (tabuleiro[i][j] == 3)
                printf("# ");  // navio
            else if (tabuleiro[i][j] == 5)
                printf("* ");  // habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades em posições diferentes
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone em (2,2)
    aplicarHabilidade(tabuleiro, cruz, 7, 2);       // Cruz em (7,2)
    aplicarHabilidade(tabuleiro, octaedro, 5, 5);   // Octaedro em (5,5)

    mostrarTabuleiro(tabuleiro);

    return 0;
}

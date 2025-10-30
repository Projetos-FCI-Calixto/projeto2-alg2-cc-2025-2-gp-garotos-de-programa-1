#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WIDTH 1024
#define MAX_HEIGHT 768

// Função para exibir o help
void show_help() {
    printf("Uso: ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binárias dadas em arquivos PBM ou por dados informados manualmente.\n");
    printf("Argumentos:\n");
    printf("  -?, --help   : apresenta essa orientação na tela.\n");
    printf("  -m, --manual : ativa o modo de entrada manual, em que o usuário fornece todos os dados da imagem informando-os através do teclado.\n");
    printf("  -f, --file   : considera a imagem representada no arquivo PBM (Portable Bitmap).\n");
}

// Função para ler arquivo PBM e retornar a matriz de pixels
int** read_pbm(const char* filename, int* width, int* height) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo %s\n", filename);
        return NULL;
    }

    char magic[3];
    if (fscanf(fp, "%2s", magic) != 1 || strcmp(magic, "P1") != 0) {
        fprintf(stderr, "Erro: arquivo não é um PBM válido (magic number P1 esperado)\n");
        fclose(fp);
        return NULL;
    }

    // Ignorar comentários (linhas começando com #)
    int ch;
    while ((ch = fgetc(fp)) == '#') {
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    }
    ungetc(ch, fp);  // Devolver o último caractere lido

    // Ler largura e altura
    if (fscanf(fp, "%d %d", width, height) != 2) {
        fprintf(stderr, "Erro: não foi possível ler largura e altura\n");
        fclose(fp);
        return NULL;
    }

    if (*width <= 0 || *height <= 0 || *width > MAX_WIDTH || *height > MAX_HEIGHT) {
        fprintf(stderr, "Erro: dimensões inválidas (máx: %dx%d)\n", MAX_WIDTH, MAX_HEIGHT);
        fclose(fp);
        return NULL;
    }

    // Alocar matriz
    int** image = (int**)malloc(*height * sizeof(int*));
    if (!image) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < *height; i++) {
        image[i] = (int*)malloc(*width * sizeof(int));
        if (!image[i]) {
            fprintf(stderr, "Erro: falha na alocação de memória\n");
            for (int j = 0; j < i; j++) free(image[j]);
            free(image);
            fclose(fp);
            return NULL;
        }
    }

    // Ler pixels (0 ou 1)
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            if (fscanf(fp, "%d", &image[i][j]) != 1) {
                fprintf(stderr, "Erro: falha ao ler pixels\n");
                for (int k = 0; k < *height; k++) free(image[k]);
                free(image);
                fclose(fp);
                return NULL;
            }
            if (image[i][j] != 0 && image[i][j] != 1) {
                fprintf(stderr, "Erro: pixel deve ser 0 ou 1\n");
                for (int k = 0; k < *height; k++) free(image[k]);
                free(image);
                fclose(fp);
                return NULL;
            }
        }
    }

    fclose(fp);
    return image;
}

// Função para entrada manual de dados
int** read_manual(int* width, int* height) {
    printf("Digite a largura e altura da imagem (separados por espaço): ");
    if (scanf("%d %d", width, height) != 2) {
        fprintf(stderr, "Erro: entrada inválida para largura e altura\n");
        return NULL;
    }

    if (*width <= 0 || *height <= 0 || *width > MAX_WIDTH || *height > MAX_HEIGHT) {
        fprintf(stderr, "Erro: dimensões inválidas (máx: %dx%d)\n", MAX_WIDTH, MAX_HEIGHT);
        return NULL;
    }

    // Alocar matriz
    int** image = (int**)malloc(*height * sizeof(int*));
    if (!image) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        return NULL;
    }
    for (int i = 0; i < *height; i++) {
        image[i] = (int*)malloc(*width * sizeof(int));
        if (!image[i]) {
            fprintf(stderr, "Erro: falha na alocação de memória\n");
            for (int j = 0; j < i; j++) free(image[j]);
            free(image);
            return NULL;
        }
    }

    printf("Digite os pixels linha por linha (0 para branco, 1 para preto):\n");
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            if (scanf("%d", &image[i][j]) != 1) {
                fprintf(stderr, "Erro: falha ao ler pixel\n");
                for (int k = 0; k < *height; k++) free(image[k]);
                free(image);
                return NULL;
            }
            if (image[i][j] != 0 && image[i][j] != 1) {
                fprintf(stderr, "Erro: pixel deve ser 0 ou 1\n");
                for (int k = 0; k < *height; k++) free(image[k]);
                free(image);
                return NULL;
            }
        }
    }

    return image;
}

// Função recursiva para codificar a imagem (placeholder - você deve implementar)
char* encode(int** image, int x1, int y1, int x2, int y2) {
    // TODO: Implementar a lógica recursiva de codificação
    // Retornar uma string alocada dinamicamente com o código (P, B ou X + sub-códigos)
    // Lembre-se de verificar se a subimagem é uniforme (todos 0 ou todos 1)
    // Se não, dividir em 4 quadrantes e concatenar os códigos
    // Usar malloc para strings e strcat para concatenação
    // Exemplo básico (não funcional):
    // if (uniforme) return strdup("P") ou "B";
    // else return "X" + encode(q1) + encode(q2) + encode(q3) + encode(q4);
    return NULL;  // Placeholder
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        show_help();
        return 0;
    }

    int** image = NULL;
    int width, height;
    char* code = NULL;

    if (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--help") == 0) {
        show_help();
    } else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--manual") == 0) {
        image = read_manual(&width, &height);
        if (image) {
            code = encode(image, 0, 0, width - 1, height - 1);
        }
    } else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Erro: nome do arquivo não informado\n");
            return 1;
        }
        image = read_pbm(argv[2], &width, &height);
        if (image) {
            code = encode(image, 0, 0, width - 1, height - 1);
        }
    } else {
        fprintf(stderr, "Argumento inválido\n");
        show_help();
        return 1;
    }

    if (code) {
        printf("%s\n", code);
        free(code);
    }

    // Liberar memória da imagem
    if (image) {
        for (int i = 0; i < height; i++) {
            free(image[i]);
        }
        free(image);
    }

    return 0;
}

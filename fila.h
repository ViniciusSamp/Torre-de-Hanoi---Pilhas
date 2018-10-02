typedef struct node Node;
struct node {
    char str[50];
    Node *proximo;
};

typedef struct fila Fila;
struct fila {
    int tamanho;
    Node *inicio;
    Node *fim;
};

Fila *criaFila();
void enfileira(Fila *fila, char *str);
void desenfileirar(Fila *fila);
void printar(Fila *fila);
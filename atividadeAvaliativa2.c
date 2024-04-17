#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float X;
    float Y;
} Ponto;

double areaTriangulo(Ponto A, Ponto B, Ponto C){
    double det = ((A.X * B.Y) + (B.X * C.Y) + (C.X * A.Y)) - ((A.Y * B.X) + (B.Y * C.X) + (C.Y * A.X));
    printf("\nDeterminante = %.2lf\n", fabs(det));
    return fabs(det) / 2.0;
}

void CalcularAreaPoligono(char* arquivo){
    FILE* f;
    int numVertices;
    Ponto* vertices;
    double areaTotal = 0.0;

    f = fopen(arquivo, "r");
    if(f == NULL){
        printf("Arquivo nao encontrado!");
        exit(1);
    }

    fscanf(f, "%d", &numVertices);
    
    vertices = (Ponto*)malloc(numVertices * sizeof(Ponto));

    for(int i = 0; i < numVertices; i++){
        fscanf(f, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    fclose(f);

    if(numVertices == 3){
        areaTotal = areaTriangulo(vertices[0], vertices[1], vertices[2]);
    } else {
        for(int i = 2; i < numVertices; i++){
            areaTotal += areaTriangulo(vertices[0], vertices[i-1], vertices[i]);
        }
    }

    printf("A area do poligono eh: %.2f\n", areaTotal);

    free(vertices);
}

int main() {
    CalcularAreaPoligono("../poligono.txt");
    return 0;
}
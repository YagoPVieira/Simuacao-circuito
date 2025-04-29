#include <math.h>
#include "lm35_filter.h"
#include <stdio.h>

double obterDadoSensor(int linha) {
    FILE* arquivo = fopen("../data.txt", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo\n");
        return -1;
    }
    
    char buffer[256];
    double valor_tempo, valor_temperatura;
    
    for (int contador = 0; contador < linha; contador++) {
        if (fgets(buffer, sizeof(buffer), arquivo) == NULL) {
            printf("Falha ao ler a linha %d\n", linha);
            fclose(arquivo);
            return -1;
        }
    }
    
    if (sscanf(buffer, "%lf %lf", &valor_tempo, &valor_temperatura) != 2) {
        printf("Falha ao analisar o formato da linha\n");
        fclose(arquivo);
        return -1;
    }
    
    fclose(arquivo);
    return valor_temperatura;
}

int main(void) {
    EstadoFiltro filtro;
    inicializar_filtro(&filtro);
    
    for (int contador = 0; contador < 100; ++contador) {
        const double leitura_bruta = obterDadoSensor(1);
        const double leitura_filtrada = aplicar_filtro(&filtro, leitura_bruta);
        printf("%.32f\n", leitura_filtrada);
    }
    
    return 0;
}
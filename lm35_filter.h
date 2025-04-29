#ifndef SENSOR_TEMPERATURA_FILTRO_H
#define SENSOR_TEMPERATURA_FILTRO_H

#define COEF_B0  2.46193251e-06
#define COEF_B1  4.92386501e-06
#define COEF_B2  2.46193251e-06
#define COEF_A1  -1.99555712
#define COEF_A2  0.99556697
typedef struct {
    double entrada_anterior;
    double entrada_anterior2;
    double saida_anterior;
    double saida_anterior2;
} EstadoFiltro;

static void inicializar_filtro(EstadoFiltro* estado) {
    estado->entrada_anterior = 0.0;
    estado->entrada_anterior2 = 0.0;
    estado->saida_anterior = 0.0;
    estado->saida_anterior2 = 0.0;
}

static double aplicar_filtro(EstadoFiltro* estado, double entrada) {
    const double saida = COEF_B0 * entrada + 
                         COEF_B1 * estado->entrada_anterior + 
                         COEF_B2 * estado->entrada_anterior2 -
                         COEF_A1 * estado->saida_anterior - 
                         COEF_A2 * estado->saida_anterior2;
    
    estado->entrada_anterior2 = estado->entrada_anterior;
    estado->entrada_anterior = entrada;
    estado->saida_anterior2 = estado->saida_anterior;
    estado->saida_anterior = saida;
    
    return saida;
}

#endif 
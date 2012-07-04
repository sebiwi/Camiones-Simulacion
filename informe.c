#include <stdio.h>
#include <stdlib.h>
#include "set.h"

void reporte_gral(var_grales parametros){

	FILE *AR;
	var_grales aux = parametros;
	
	AR = fopen("Informe.txt","w+");
	fprintf(AR, "\nSimulador de camiones autonomos!\n--------------------------------\n\n1-.    Parametros de Simulacion\n");
	fprintf(AR, "\n    Semilla ingresada para el generador de numeros aleatorios:\n\t%d\n",aux->idum);
	fprintf(AR, "    Camiones Totales ingresados:\n\t%d\n",aux->cam);
	fprintf(AR, "    Tiempo de Simulacion:\n\t%e\n",aux->termino);
	fprintf(AR, "    Media de tiempo entre fallas de los camiones ingresado:\n\t%e [minutos]\n",aux->media_camion);
	fprintf(AR, "    Media de tiempo de reparacion de camion ingresado:\n\t%e [minutos]\n",aux->media_repcamion);
	fprintf(AR, "    Media de tiempo de reparacion de pala ingresado:\n\t%e [minutos]\n",aux->media_pala);

	fprintf(AR,"\n\n2-.    Resultados Finales\n");
	fprintf(AR,"\n    Cantidad de material extraido:\n\t%e [tons]\n",aux->toneladas);
	fprintf(AR,"    Rendimiento final:\n\t%e [Ton/Hora]\n",(aux->toneladas)/((aux->current)/60) );

	

	fclose(AR);
}

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

void estadisticas_camion(pcamion lista) {
	FILE *AR;
	pcamion aux = lista;

	AR = fopen("Informe.txt","a");
	fprintf(AR, "\n3-.    Detalle de camiones al finalizar simulacion\n");
	while (aux->next != NULL)
	{	
		fprintf(AR, "\tID de Camion: %d\n", aux->id);
		fprintf(AR, "\tToneladas extraidas: %e\n", aux->toneladas_camion);
		fprintf(AR, "\tTiempo de partida: %e\n",aux->start);
		fprintf(AR, "\tTiempo de funcionamiento: %e [minutos]\n", aux->tiempo_funcionamiento);
		if (aux->motor == 1)
			fprintf(AR, "\tEstado del motor: Funcionando\n");
		else 
			fprintf(AR, "\tEstado del motor: En reparacion\n");

		switch (aux->carga){
			case 0:
				fprintf(AR, "\tUbicacion: Hacia faena (s/carga)\n\n");
				break;
			case 1:
				fprintf(AR, "\tUbicacion: Hacia planta (c/carga)\n\n");
				break;
			case 2:
				fprintf(AR, "\tUbicacion: En faena, en proceso de carga de material\n\n");
				break;
			case 3:
				fprintf(AR, "\tUbicacion: En planta, en proceso de descarga del material\n\n");
				break;
			default:
				break;
		}
		aux=aux->next;
	}	

	
	fclose(AR);
}

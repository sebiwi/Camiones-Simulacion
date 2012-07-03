#ifndef LIST_H
#define LIST_H

typedef struct protocamion   //Prototipo de camión
{	int id, direccion, senal, motor, velocidad, carga;   //Direccion es 1 para ida, 0 para vuelta, los demas valores son 1 para Ok, y 0 para No.
	double tiempo, tiempo_funcionamiento, toneladas_camion, tiempo_trayecto;
	struct protocamion *next, *falla;
	} camion, *pcamion;

pcamion creacamion(int id, double tiempo, double termino, long *idum, double media_repcamion); //Constructor de camión

pcamion insertarenorden(pcamion lista, pcamion camion); //Insertar ordenadamente

pcamion insertaralinicio(pcamion lista, pcamion camion);

pcamion insertaralfinal(pcamion lista,pcamion camion);

pcamion eliminarcamion(pcamion lista);

pcamion seleccionarminimo(pcamion A, pcamion B, pcamion C, pcamion D, pcamion E, pcamion F, pcamion G, pcamion H, pcamion I);


#endif

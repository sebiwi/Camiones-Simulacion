#ifndef LIST_H
#define LIST_H

typedef struct protocamion   //Prototipo de camión
{	int id, direccion, senal, motor, velocidad, carga;   //Direccion es 1 para ida, 0 para vuelta, los demas valores son 1 para Ok, y 0 para No.
	//valores de carga 0 hacia faena, 1 hacia planta, 2 en faena, 3 en planta,
	double tiempo, tiempo_funcionamiento, toneladas_camion, tiempo_trayecto, start;
	struct protocamion *next, *falla;
	} camion, *pcamion;

typedef struct struct_var
{	double current,termino,toneladas,media_camion,media_repcamion,media_pala;
	int idum;
	int cam;		//total de camiones
} var,*var_grales;

pcamion creacamion(int id, double tiempo, double termino, long *idum, double media_repcamion); //Constructor de camión

pcamion insertarenorden(pcamion lista, pcamion camion); //Insertar ordenadamente

pcamion insertaralinicio(pcamion lista, pcamion camion);

pcamion insertaralfinal(pcamion lista,pcamion camion);

pcamion eliminarcamion(pcamion lista);

pcamion seleccionarminimo(pcamion A, pcamion B, pcamion C, pcamion D, pcamion E, pcamion F, pcamion G, pcamion H, pcamion I);

var_grales crea_var();

#endif

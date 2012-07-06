#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

#include "list.h"
#include "set.h"
#include "list.h"

double ran(long *idum) {

    int j;
    long k;
    static long iy=0;
    static long iv[NTAB];
    double temp;

    if (*idum <= 0 || !iy)
    {

            if (-(*idum) < 1) *idum=1; /*Be sure to prevent idum = 0*/
            else *idum = -(*idum);
            for (j=NTAB+7;j>=0;j--)		/*Load the shu.e table (after 8 warm-ups)*/
            {
                    k=(*idum)/IQ;
                    *idum=IA*(*idum-k*IQ)-IR*k;
                    if (*idum < 0)
                    *idum += IM;
                    if (j < NTAB)
                    iv[j] = *idum;
            }
            iy=iv[0];
    }
    k=(*idum)/IQ;					/*Start here when not initializing.*/
    *idum=IA*(*idum-k*IQ)-IR*k;
    if (*idum < 0) *idum += IM;
    j=iy/NDIV;
    iy=iv[j];
    iv[j] = *idum;
    if ((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}

void inicializar(){
}

int set() {
	int ingresando=1, temp_int, carga_ocupada=0;
	double current=0, termino, toneladas=0,temp_tiempo,temp_double,media_pala,media_camion, media_repcamion;
	long idum = -275920;
	pcamion listainicio=NULL,listacargado=NULL,listadescarga=NULL,listamotor=NULL,listainterferencia=NULL,listatrayecto=NULL, listacarga=NULL, listapala=NULL, temp=NULL, listatermino=NULL, aux=NULL;
	var_grales parametros=crea_var();		//crea e inicializa parametros para utilizacion en generacion de reporte

	printf("Simulador de camiones autonomos!\n");
	printf("Ingrese semilla distinta de 0 para el generador de numeros aleatorios:\n");
	scanf("%d",&idum);
	parametros->idum = idum;
	printf("Ingrese media de tiempo entre fallas de los camiones [Default: 1472[min]]\n");
	scanf("%lf",&media_camion);
	parametros->media_camion = (double)media_camion;
	printf("Ingrese media de tiempo de reparacion de camion [Default: 360[min]]\n");
	scanf("%lf",&media_repcamion);
	parametros->media_repcamion = (double)media_repcamion;
	printf("Ingrese media de tiempo de reparacion de palas [Default: 105[min]]\n");
	scanf("%lf",&media_pala);	
	parametros->media_pala =  (double)media_pala;
	printf("Ingrese tiempo de simulacion [Minutos]\n");
	scanf("%lf",&termino);
	parametros->termino = (double)termino;
	listatermino=insertarenorden(listatermino,creacamion(314159,termino,0,NULL,0));
	
	while(ingresando==1){
		printf("\nIngrese id del camion a insertar\n");
		scanf("%d",&temp_int);
		printf("\nIngrese tiempo de partida del camion\n");
		scanf("%lf",&temp_tiempo);
		listainicio=insertarenorden(listainicio,creacamion(temp_int,temp_tiempo,termino,&idum,media_repcamion));
		parametros->cam += 1;
		printf("\nInsertar otro camion? (1=si, 2=no)\n");
		scanf("%d",&ingresando);
		}
	

	while(current<termino){
		if(carga_ocupada)temp=seleccionarminimo(listainicio,listacargado,listadescarga,listatrayecto,listamotor,listainterferencia,NULL,listapala,listatermino);
		else temp=seleccionarminimo(listainicio,listacargado,listadescarga,listatrayecto,listamotor,listainterferencia,listacarga,NULL,listatermino);
		current+=(temp->tiempo-current);

		if(temp==listainicio){  temp->direccion=1;
					temp->senal=1;
					temp->motor=1;          //Variables de estado
					temp->velocidad=1;
					temp->carga=0;			
					printf("Camion %d parte hacia faena en t=%e\n",temp->id,temp->tiempo);
					
					while(current>temp->falla->tiempo)temp->falla=temp->falla->next;
					
					if(temp->tiempo+10>temp->falla->tiempo){
							temp->tiempo+=((temp->falla->tiempo)-current);
							temp->tiempo_funcionamiento+=((temp->falla->tiempo)-current);
							temp->tiempo_trayecto=((temp->falla->tiempo)-current);            

							printf("Camion %d sufre falla motor en t=%e\n",temp->id,temp->tiempo);
							listainicio=eliminarcamion(listainicio);
							temp->next=NULL;
							temp->motor=0;
							temp->velocidad=0;
							listamotor=insertarenorden(listamotor,temp);
							continue;
							}
									  
					/*if(temp_int<40){
							printf("Camion  %d sufre interferencia en t=%e\n",temp->id,temp->tiempo);
							temp->tiempo+=5;
							listainicio=eliminarcamion(listainicio);
							temp->next=NULL;
							temp->senal=0;
							temp->velocidad=0;
							listainterferencia=insertarenorden(listainterferencia,temp);
							continue;
							}*/
				  
					temp->tiempo+=10;
					temp->tiempo_funcionamiento+=10;
					printf("Llega camion %d a cola de carga en t=%e\n",temp->id,temp->tiempo);
					listainicio=eliminarcamion(listainicio);
					temp->next=NULL;
					temp->velocidad=0;
					listacarga=insertarenorden(listacarga,temp);
					continue;
					}
		

		if(temp==listamotor){
					temp->tiempo+=(-media_repcamion*log(ran(&idum)));//tiempo de reparacion (variable)
					temp->tiempo_funcionamiento += (temp->tiempo - temp->tiempo_funcionamiento);
					printf("Camion %d es reparado en t=%e\n",temp->id,temp->tiempo);
					listamotor=eliminarcamion(listamotor);
					temp->next=NULL;
					temp->motor=1;
					temp->velocidad=1;
					listatrayecto=insertarenorden(listatrayecto,temp);
					continue;
					}

		if(temp==listainterferencia){
					printf("Camion %d deja de sufrir interferencia en t=%e\n",temp->id,temp->tiempo);
					temp->tiempo+=5;
					temp->tiempo_funcionamiento+=5;
					listainterferencia=eliminarcamion(listainterferencia);
					temp->next=NULL;
					temp->senal=1;
					temp->velocidad=1;
					listatrayecto=insertarenorden(listatrayecto,temp);
					continue;
					}

		if(temp==listatrayecto){ 
					while(current>temp->falla->tiempo)temp->falla=temp->falla->next;
			
					if(temp->tiempo+(10-temp->tiempo_trayecto)>temp->falla->tiempo){
							temp->tiempo_trayecto+=((temp->falla->tiempo)-current); 
							temp->tiempo+=((temp->falla->tiempo)-current);
							temp->tiempo_funcionamiento+=((temp->falla->tiempo)-current);

							printf("Camion  %d sufre falla motor en t=%e\n",temp->id,temp->tiempo);
							listatrayecto=eliminarcamion(listatrayecto);
							temp->next=NULL;
							temp->motor=0;
							temp->velocidad=0;
							listamotor=insertarenorden(listamotor,temp);
							continue;
							}
					/*  
					if(temp_int<40){
							printf("Camion  %d sufre interferencia en t=%e\n",temp->id,temp->tiempo);
							temp->tiempo+=5;
							listatrayecto=eliminarcamion(listatrayecto);
							temp->next=NULL;
							temp->senal=0;
							temp->velocidad=0;
							listainterferencia=insertarenorden(listainterferencia,temp);
							continue;
							}	*/			  
					if(temp->direccion==1){	
							temp->tiempo+=(10-temp->tiempo_trayecto);
							temp->tiempo_funcionamiento+=(10-temp->tiempo_trayecto);
							printf("Llega camion %d a cola de carga en t=%e\n",temp->id,temp->tiempo);
							listatrayecto=eliminarcamion(listatrayecto);
							temp->next=NULL;
							temp->velocidad=0;
							listacarga=insertarenorden(listacarga,temp);
							continue;
							}
					if(temp->direccion==0){
							temp->tiempo+=(10-temp->tiempo_trayecto);
							temp->tiempo_funcionamiento+=(10-temp->tiempo_trayecto);
							printf("Llega camion %d a descarga en t=%e\n",temp->id,temp->tiempo);
							listatrayecto=eliminarcamion(listatrayecto);
							temp->next=NULL;
							temp->velocidad=0;
							listadescarga=insertarenorden(listadescarga,temp);
							continue;
							}
					}

		if(temp==listacarga){	
					temp_double=ran(&idum);
					carga_ocupada=1;
					temp->carga=2;
					temp->tiempo_trayecto=0;			//resetea valor de tiempo de trayecto
				    	
					printf("Camion %d se empieza a cargar en t=%e\n",temp->id,temp->tiempo);

					if(temp_double<0.40625){ 
							printf("Falla de pala mientras se carga camion  %d\n",temp->id);

							temp->tiempo+=(-media_pala* log(ran(&idum)));
							temp->tiempo_funcionamiento += (temp->tiempo - temp->tiempo_funcionamiento);
							listacarga=eliminarcamion(listacarga);
							temp->next=NULL;
							listapala=insertarenorden(listapala,temp);
							continue;
							}
						
					else  {	
						printf("Camion %d se esta cargando sin problemas en t=%e\n",temp->id,temp->tiempo);
						temp->tiempo+=10;
						temp->tiempo_funcionamiento+=10;
						listacarga=eliminarcamion(listacarga);
						temp->next=NULL;
						listacargado=insertarenorden(listacargado,temp);
						continue;
						}
				}

		if(temp==listapala){ 
					printf("Pala es arreglada en t= %e\n",temp->tiempo);
					temp->tiempo+=0.5;
					temp->tiempo_funcionamiento += 0.5;
					listapala=eliminarcamion(listapala);
					temp->next=NULL;
					listacarga=insertaralinicio(listacarga,temp);
					carga_ocupada=0;
			}

		if(temp==listacargado){ 
					temp->direccion=0;
					temp->carga=1;
					temp->velocidad=1;
					temp_double=ran(&idum);
					carga_ocupada=0;			
					if(listacarga!=NULL){	listacarga->tiempo=temp->tiempo+0.5;
								listacarga->tiempo_funcionamiento+=0.5;
								}
					printf("Camion  %d se ha terminado de cargar, vuelve a planta en t=%e\n",temp->id,temp->tiempo);
							
			
					while(current>temp->falla->tiempo)temp->falla=temp->falla->next;
					
					if(temp->tiempo+10>temp->falla->tiempo){
							temp->tiempo_trayecto=((temp->falla->tiempo)-current);
							temp->tiempo+=((temp->falla->tiempo)-current);
							temp->tiempo_funcionamiento+=((temp->falla->tiempo)-current);

							printf("Camion  %d sufre falla motor en t=%e\n",temp->id,temp->tiempo);
							//temp->tiempo+=5;
							listacargado=eliminarcamion(listacargado);
							temp->next=NULL;
							temp->motor=0;
							temp->velocidad=0;
							temp->tiempo_trayecto=0;
							listamotor=insertarenorden(listamotor,temp);
							continue;
							}
					/*				  
					if(temp_int<40){
							printf("Camion  %d sufre interferencia en t=%e\n",temp->id,temp->tiempo);
							temp->tiempo+=5;
							listacargado=eliminarcamion(listacargado);
					
					temp->next=NULL;
							temp->senal=0;
							temp->velocidad=0;
							listainterferencia=insertarenorden(listainterferencia,temp);
							continue;
							}*/
				  
					temp->tiempo+=10;
					temp->tiempo_funcionamiento+=10;
					listacargado=eliminarcamion(listacargado);
					temp->next=NULL;
					listadescarga=insertarenorden(listadescarga,temp);
					continue;
					}
			
		if(temp==listadescarga){
					printf("Camion %d descarga en t=%e\n",temp->id,temp->tiempo);
					temp->tiempo+=10;
					temp->tiempo_funcionamiento+=10;
					temp->toneladas_camion+=5;
					listadescarga=eliminarcamion(listadescarga);
					temp->next=NULL;
					temp->carga=3; 
					listainicio=insertarenorden(listainicio,temp);
					toneladas+=5;
					continue;
					}
		
		if(temp==listatermino){
					printf("Tiempo limite de simulacion alcanzado.(t=%e)\n",temp->tiempo);
					if(listainicio!=NULL) aux = insertarenorden(aux,listainicio);
					if(listacargado!=NULL) aux = insertarenorden(aux,listacargado);
					if(listadescarga!=NULL)  aux = insertarenorden(aux,listadescarga);
					if(listatrayecto!=NULL)  aux = insertarenorden(aux,listatrayecto);
					if(listamotor!=NULL)  aux = insertarenorden(aux,listamotor);
					if(listainterferencia!=NULL) aux = insertarenorden(aux,listainterferencia);
					if(listacarga!=NULL) aux = insertarenorden(aux,listacarga);
					if(listapala!=NULL) aux = insertarenorden(aux,listapala);
					if(listatermino!=NULL) aux = insertarenorden(aux,listatermino);
					
					continue;
					}
		}
	printf("Se extrajeron %e toneladas en %e minutos\n",toneladas, termino);
	printf("El rendimiento final es: %e [Ton/Hora]\n",toneladas/(current/60));
	parametros->toneladas = toneladas;
	parametros->current = current;

	reporte_gral(parametros);
	printf("\nReporte generado (Informe.txt).\nSimulacion finalizada\n");
	estadisticas_camion(aux);

	return 0;
}

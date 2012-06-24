#include <stdio.h>
#include <stdlib.h> 

#include "list.h"
#include "set.h"

void randomize() //Empieza el generador de numeros aleatorios usando como semilla el tiempo
{
	time_t tim;
	time(&tim);
	srand(tim);
}

int randomABi(int A, int B){//Obtiene un numero aleatorio dentro del intervalo [A,B]
	return((int)((double) rand()/RAND_MAX*(B+1-A)+A));
}

void inicializar(){
}

int set() {
randomize();
	int ingresando=1, temp_int, carga_ocupada=0;
	double current=0, termino, toneladas=0,temp_tiempo;
	pcamion listainicio=NULL,listacargado=NULL,listadescarga=NULL,listamotor=NULL,listainterferencia=NULL,listatrayecto=NULL, listacarga=NULL, listapala=NULL, temp=NULL, listatermino=NULL;
	FILE *f=fopen("probabilidades.txt","r");
 
    	if(f==NULL){
		printf("No hay archivo con probabilidades de falla");
        	return 1;}
 
    	double probabilidades_camiones[18];        
 
    	for(temp_int = 0; temp_int < 18; temp_int++) {
        	fscanf(f, "%lf",&probabilidades_camiones[temp_int]);
        	//printf("%lf\n",probabilidades_camiones[temp_int]);
 	    }
 
 	   close(f);
 

	printf("Simulador de camiones autonomos!\n");
	printf("Ingrese tiempo de simulacion [Minutos]\n");
	scanf("%lf",&termino);
	listatermino=insertarenorden(listatermino,creacamion(314159,termino));
	
	while(ingresando==1){
		printf("\nIngrese id del camion a insertar\n");
		scanf("%d",&temp_int);
		printf("\nIngrese tiempo de partida del camion\n");
		scanf("%lf",&temp_tiempo);
		listainicio=insertarenorden(listainicio,creacamion(temp_int,temp_tiempo));
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
 					temp_int=randomABi(0,100);			
					printf("Camion %d parte hacia faena en t=%e\n",temp->id,temp->tiempo);

					if(temp_int<probabilidades_camiones[((temp->id)-1)%18]){
							temp->tiempo_trayecto=randomABi(1,99)/10; 			//tiempo en el que falla, suponiendo que en 10 min llega a faena
							temp->tiempo+=temp->tiempo_trayecto;
							temp->tiempo_funcionamiento+=temp->tiempo_trayecto;            

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
					temp->tiempo+=5;		//tiempo de reparacion (fijo)
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
					listainterferencia=eliminarcamion(listainterferencia);
					temp->next=NULL;
					temp->senal=1;
					temp->velocidad=1;
					listatrayecto=insertarenorden(listatrayecto,temp);
					continue;
					}

		if(temp==listatrayecto){  
					temp_int=randomABi(0,100);
			
					if(temp_int<probabilidades_camiones[((temp->id)-1)%18]){
							temp->tiempo_trayecto=randomABi(0,(10-temp->tiempo_trayecto)*10)/10; //define tiempo en el que falla durante el trayecto
							temp->tiempo+=temp->tiempo_trayecto;
							temp->tiempo_funcionamiento+=temp->tiempo_trayecto;

							printf("Camion  %d sufre falla motor en t=%e\n",temp->id,temp->tiempo);
							//temp->tiempo+=5;
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
							temp->tiempo_funcionamiento+=10;
							printf("Llega camion %d a cola de carga en t=%e\n",temp->id,temp->tiempo);
							listatrayecto=eliminarcamion(listatrayecto);
							temp->next=NULL;
							temp->velocidad=0;
							listacarga=insertarenorden(listacarga,temp);
							continue;
							}
					if(temp->direccion==0){
							temp->tiempo+=(10-temp->tiempo_trayecto);
							temp->tiempo_funcionamiento+=10;
							printf("Llega camion %d a descarga en t=%e\n",temp->id,temp->tiempo);
							listatrayecto=eliminarcamion(listatrayecto);
							temp->next=NULL;
							temp->velocidad=0;
							listadescarga=insertarenorden(listadescarga,temp);
							continue;
							}
					}

		if(temp==listacarga){	
					temp_int=randomABi(0,100);
					carga_ocupada=1;
					temp->tiempo_trayecto=0;			//resetea valor de tiempo de trayecto
				    	
					printf("Camion %d se empieza a cargar en t=%e\n",temp->id,temp->tiempo);

					if(temp_int<20){ 
							printf("Falla de pala mientras se carga camion  %d\n",temp->id);
							temp->tiempo+=10;
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
					listapala=eliminarcamion(listapala);
					temp->next=NULL;
					listacarga=insertaralinicio(listacarga,temp);
					carga_ocupada=0;
			}

		if(temp==listacargado){ 
					temp->direccion=0;
					temp->carga=1;
					temp->velocidad=1;
					temp_int=randomABi(0,100);
					carga_ocupada=0;			//??
					if(listacarga!=NULL){	listacarga->tiempo=temp->tiempo+0.5;
								listacarga->tiempo_funcionamiento+=0.5;
								}
					printf("Camion  %d se ha terminado de cargar, vuelve a planta en t=%e\n",temp->id,temp->tiempo);
							
			

					if(temp_int<probabilidades_camiones[((temp->id)-1)%18]){
							temp->tiempo_trayecto=randomABi(0,99)/10;
							temp->tiempo+=temp->tiempo_trayecto;
							temp->tiempo_funcionamiento+=temp->tiempo_trayecto;

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
					temp->carga=0; //conceptual
					listainicio=insertarenorden(listainicio,temp);
					toneladas+=5;
					continue;
					}
		
		if(temp==listatermino){
					printf("Tiempo limite de simulacion alcanzado.(t=%e)\n",temp->tiempo);
					continue;
					}
		}
	printf("Se extrageron %e toneladas en %e minutos\n",toneladas, termino);
	printf("El rendimiento final es: %e [Ton/Hora]\n",toneladas/(current/60));

	return 0;
}

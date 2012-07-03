#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
#include "set.h"

pcamion creacamion(int id, double tiempo, double termino, long *idum, double media_repcamion) //Constructor de camión
{
	pcamion pc=NULL;
	double temp= tiempo;

	if((pc=(pcamion) malloc(sizeof(camion))) ==NULL) exit(0);
	else
	{	pc->id=id;
		pc->tiempo=tiempo;
		pc->next=NULL;

		while(temp<termino){	
					temp+=(-media_repcamion*log(ran(idum)));
					pc->falla=insertarenorden(pc->falla,creacamion(0,temp,0,NULL,0));
					
					}		

		pc->tiempo_funcionamiento=0;
		pc->toneladas_camion=0;
		pc->tiempo_trayecto=0;
	}
	return pc;
}

pcamion insertarenorden(pcamion lista, pcamion camion) //Insertar en orden
{
	pcamion temp=lista;

	if(lista==NULL){
			lista=camion;
			return lista;
			}
	else

        if(lista->tiempo>camion->tiempo){
					 camion->next=lista;
					 lista=camion;
					 return lista;
					}


		else{	
			while(temp->next !=NULL && temp->tiempo<camion->tiempo) temp=temp->next;
			camion->next=temp->next;
			temp->next=camion;
		    return lista;
		
	    }
}

pcamion insertaralfinal(pcamion lista, pcamion camion)
{
	if(lista==NULL){
			lista=camion;
			return lista;
			}

	else{		
			while(lista->next!=NULL) lista=lista->next; 
			lista->next=camion;
			return lista;
	    }

}

pcamion insertaralinicio(pcamion lista, pcamion camion)
{
	if(lista==NULL){
			lista=camion;
			return lista;
			}

	else {			
			camion->next=lista;
			lista=camion;
			return lista;
		}
}

pcamion eliminarcamion(pcamion lista)//Elimina el minimo de una lista
{	
	pcamion tmp=NULL;
	if(lista==NULL) return NULL;
	
	else

		if(lista->next==NULL) {
			lista=NULL;
			return lista;
		}

		else
			{
			//tmp=lista;
			lista=lista->next;	
			//free(tmp);
			return lista;
			}
}

pcamion seleccionarminimo(pcamion A, pcamion B, pcamion C, pcamion D, pcamion E, pcamion F, pcamion G, pcamion H, pcamion I)
{	double tA, tB, tC, tD, tE, tF, tG, tH, tI, min;
	pcamion t;

	if(A!=NULL)	tA = A->tiempo; 
		else	tA = 10000000000;
	
	if(B!=NULL)	tB = B->tiempo;
		else	tB = 10000000000;
	
	if(C!=NULL)	tC = C->tiempo;
		else	tC = 10000000000;
	
	if(D!=NULL)	tD = D->tiempo;
		else	tD = 10000000000;

	if(E!=NULL)	tE = E->tiempo;
		else	tE = 10000000000;

	if(F!=NULL)	tF = F->tiempo;
		else	tF = 10000000000;
		
	if(G!=NULL)	tG = G->tiempo;
		else	tG = 10000000000;
	
	if(H!=NULL)	tH = H->tiempo;
		else	tH = 10000000000;
	
	if(I!=NULL)	tI = I->tiempo;
		else	tI = 10000000000;
	
	min = tA;
	if(min>tB) min = tB;
	if(min>tC) min = tC;
	if(min>tD) min = tD;
	if(min>tE) min = tE;
	if(min>tF) min = tF;
	if(min>tG) min = tG;
	if(min>tH) min = tH;
	if(min>tI) min = tI;
	
	if(A!=NULL && min==A->tiempo) return A;
	if(B!=NULL && min==B->tiempo) return B;
	if(C!=NULL && min==C->tiempo) return C;
	if(D!=NULL && min==D->tiempo) return D;
	if(E!=NULL && min==E->tiempo) return E;
	if(F!=NULL && min==F->tiempo) return F;
	if(G!=NULL && min==G->tiempo) return G;
	if(H!=NULL && min==H->tiempo) return H;
	if(I!=NULL && min==I->tiempo) return I;


}


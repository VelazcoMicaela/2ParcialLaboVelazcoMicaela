#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "LinkedList.h"
#include "employee.h"
#include "Controller.h"



ePais* employee_new()
{
	ePais* aux;

	aux= (ePais*) malloc (sizeof(ePais));
	if(aux!=NULL)
	{
		aux->id=0;
		strcpy( aux->pais, " ");
		aux->vac2dosis=0;
		aux->vac1dosis=0;
		aux->sinVacunar=0;
	}

	return aux;
}

ePais* employee_newParametros(char* idStr,char* paisStr,char* vac1dosisStr, char* vac2dosisStr, char* sinVacunarStr)
{
	ePais* aux;

	aux=employee_new();

	if(aux!=NULL && idStr!=NULL && paisStr!=NULL && vac1dosisStr!=NULL && vac2dosisStr!=NULL)
	{
		if(!(employee_setId(aux, atoi(idStr))==0 &&
			employee_setPais(aux, paisStr)==0 &&
			employee_setVac1dosisStr(aux, atoi(vac1dosisStr))==0 &&
			employee_setVac2dosisStr(aux, atoi(vac2dosisStr))==0 &&
			employee_setSinVacunarStr(aux, atoi(sinVacunarStr))==0))
		{
			free(aux);
			aux=NULL;
		}
	}

	return aux;
}

////// EMPIEZAN SET ///////

int employee_setId(ePais* this,int id)
{
	int error=-1;

	if(this!=NULL && id>0 && id<2000)
	{
		this->id=id;
		error=0;
	}

	return error;
}

int employee_setPais(ePais* this,char* pais)
{
	int error=-1;


	if(this!=NULL && strlen(pais)<100 && strlen(pais)>1 )

	{
		strcpy( this->pais, pais);
		error=0;
	}

	return error;
}

int employee_setVac1dosisStr(ePais* this,int vac1dosisStr)
{
	int error=-1;

	if(this!=NULL && vac1dosisStr<=60 && vac1dosisStr>=0)
	{
		this->vac1dosis =vac1dosisStr;
		error=0;
	}

	return error;
}

int employee_setVac2dosisStr(ePais* this,int vac2dosisStr)
{
	int error=-1;

	if(this!=NULL && vac2dosisStr<=40 && vac2dosisStr>=0)
	{
		this->vac2dosis=vac2dosisStr;
		error=0;
	}

	return error;
}

int employee_setSinVacunarStr(ePais* this,int sinVacunarStr)
{
	int error=-1;

	if(this!=NULL && sinVacunarStr<=100 && sinVacunarStr>=0)
	{
		this->sinVacunar=sinVacunarStr;
		error=0;
	}

	return error;
}

/////////////// EMPIEZAN GET////////////

int employee_getId(ePais* this,int* id)
{
	int error=-1;

	if(this!=NULL && id!=NULL)
	{
		*id= this->id;
		error=0;
	}

	return error;
}

int employee_getPais(ePais* this,char* pais)
{
	int error=-1;

	if(this!=NULL && pais!=NULL)
	{
		strcpy(pais, this->pais);
		error=0;
	}

	return error;
}

int employee_getVac1dosisStr(ePais* this,int* vac1dosis)
{
	int error=-1;

	if(this!=NULL && vac1dosis!=NULL)
	{
		*vac1dosis= this->vac1dosis;
		error=0;
	}

	return error;
}

int employee_getVac2dosisStr(ePais* this,int* vac2dosis)
{
	int error=-1;

	if(this!=NULL && vac2dosis!=NULL)
	{
		*vac2dosis= this->vac2dosis;
		error=0;
	}

	return error;
}

int employee_getSinVacunarStr(ePais* this,int* sinVacunar)
{
	int error=-1;

	if(this!=NULL && sinVacunar!=NULL)
	{
		*sinVacunar= this->sinVacunar;
		error=0;
	}

	return error;
}

int employee_mostrarEmpleado(ePais* unPais)
{
	int error=-1;
	int id;
	char pais[128];
	int vac1dosis;
	int vac2dosis;
	int sinVacunar;

	if(unPais!=NULL)
	{
		if(employee_getId(unPais, &id)==0 &&
			employee_getPais(unPais, pais)==0 &&
			employee_getVac1dosisStr(unPais, &vac1dosis)==0 &&
			employee_getVac2dosisStr(unPais,&vac2dosis)==0 &&
			employee_getSinVacunarStr(unPais,&sinVacunar)==0)
		{
			printf("%4d %10s   %2d %2d %2d\n", id, pais, vac1dosis,vac2dosis,sinVacunar);
		}

		error=0;
	}
    return error;
}

int employee_buscarMayorId(LinkedList* pArrayListEmployee, int* id)
{
	int error=-1;
	ePais* aux;
	int mayor=0;
	int i;

	if(pArrayListEmployee!=NULL && id!=NULL)// tam>=0 &&
	{
		for(i=0; i<ll_len(pArrayListEmployee); i++)
		{
			aux=(ePais*)ll_get(pArrayListEmployee, i);
			if(i==0 || aux->id > mayor)
			{
				mayor=aux->id;
			}
		}

		*id=mayor+1;
		error=0;
	}

	return error;
}



///////////// comparaciones ////////////

int employee_cmp1Dosis(void* a, void* b)
{
	int error=0;

	ePais* unPais1;
	ePais* unPais2;

	if(a!=NULL && b!=NULL)
	{
		unPais1= (ePais*) a;
		unPais2= (ePais*) b;

		if(unPais1->vac1dosis > unPais2->vac1dosis)
		{
			error=1;
		}
		else if(unPais1->vac1dosis < unPais2->vac1dosis)
		{
			error=-1;
		}
	}
	return error;
}

int employee_cmp2Dosis(void* a, void* b)
{
	int error=0;

	ePais* unPais1;
	ePais* unPais2;

	if(a!=NULL && b!=NULL)
	{
		unPais1= (ePais*) a;
		unPais2= (ePais*) b;

		if(unPais1->vac2dosis > unPais2->vac2dosis)
		{
			error=1;
		}
		else if(unPais1->vac2dosis < unPais2->vac2dosis)
		{
			error=-1;
		}
	}
	return error;
}

int employee_sinVacunar(void* a, void* b)
{
	int error=0;

	ePais* unPais1;
	ePais* unPais2;

	if(a!=NULL && b!=NULL)
	{
		unPais1= (ePais*) a;
		unPais2= (ePais*) b;

		if(unPais1->sinVacunar > unPais2->sinVacunar)
		{
			error=1;
		}
		else if(unPais1->sinVacunar < unPais2->sinVacunar)
		{
			error=-1;
		}

	}
	return error;
}

///////////// FILTROS ////////////

/** \brief aparezcan países cuya población este vacunada con dos dosis en un porcentaje mayor al 30%
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int employee_FilterPais2Dosis(void* a)
{
	int error=0;

	ePais* unPais;

	if(a!=NULL)
	{
		unPais= (ePais*) a;

		if(unPais->vac2dosis > 30)
		{
			error=1;
		}
	}
	return error;
}


int employee_FilterMayorVacunados(void* a)
{
	int error=0;
	int num1;
	int num2;
	int totalVacunados;

	ePais* unPais;

	if(a!=NULL)
	{
		unPais= (ePais*) a;

		num1=unPais->vac1dosis;
		num2=unPais->vac2dosis;
		totalVacunados= num1+num2;

		if(unPais->sinVacunar > totalVacunados)
		{
			error=1;
		}
	}
	return error;
}

///////////// ASIGNACION ALEATORIOS ////////////
int employee_numAleatorio(int mayor, int menor)
{
	int num;

	num= rand()% (mayor-menor+1)+menor;

	return num;
}

int employee_paisAsignacionVac1dosis(void* a)
{
	int error=0;
	int num;

	ePais* unPais;

	if(a!=NULL)
	{
		unPais= (ePais*) a;
		num=employee_numAleatorio(60, 1);

		if(num>=1 && num<=60)
		{
			unPais->vac1dosis=num;
			error=1;
		}
	}
	return error;
}

int employee_paisAsignacionVac2dosis(void* a)
{
	int error=0;
	int num;

	ePais* unPais;

	if(a!=NULL)
	{
		unPais= (ePais*) a;
		num=employee_numAleatorio(40, 1);

		if(num>=1 && num<=40)
		{
			unPais->vac2dosis=num;
			error=1;
		}
	}
	return error;
}

int employee_paisAsignacionSinVacunar(void* a)
{
	int error=0;
	int num1;
	int num2;
	int numResultado;

	ePais* unPais;

	if(a!=NULL)
	{
		unPais= (ePais*) a;

		num1=unPais->vac1dosis;
		num2=unPais->vac2dosis;
		numResultado= num1+num2;
		numResultado=100-numResultado;

		if(numResultado>=0 && numResultado<=100)
		{
			unPais->sinVacunar=numResultado;
			error=1;
		}
	}
	return error;
}


int menuErrores(int retorno, char* errorNegativo,  char* error0, char* error1, char* error2, char* error3, char* error4, char* error5)
{
	int error=-1;

	if(errorNegativo!=NULL&& error0!=NULL&& error1!=NULL&& error2!=NULL&& error3!=NULL&& error4!=NULL&& error5!=NULL)
	{
		switch(retorno)
		{
			case -1:
				printf("%s",errorNegativo);
				break;

			case 0:
				printf("%s",error0);
				break;

			case 1:
				printf("%s",error1);
				break;

			case 2:
				printf("%s",error2);;
				break;

			case 3:
				printf("%s",error3);
				break;

			case 4:
				printf("%s",error4);
				break;

			case 5:
				printf("%s",error5);
				break;
		}

		error=0;
	}

	return error;
}

char* ingresarPath(char* path)
{
	if(path!=NULL)
	{
		printf("Ingrese Path_  \n");
		fflush(stdin);
		gets(path);

	}

	return path;
}



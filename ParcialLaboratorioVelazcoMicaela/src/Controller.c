#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee, int* idNext)
{
	int flag=-1;
	int idAux;
	FILE* f;
	char confirmacion;

	if(path!=NULL && pArrayListEmployee!=NULL && idNext!=NULL)
	{
		f= fopen(path, "r");

		if(f!=NULL)
		{
			if(ll_isEmpty(pArrayListEmployee)==1 && utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n')==0)
			{
				if(confirmacion!='s')
				{
					flag=5;
				}
			}
			if(ll_isEmpty(pArrayListEmployee)==0 || confirmacion=='s')
			{
				ll_clear(pArrayListEmployee);
				flag=parser_EmployeeFromText(f, pArrayListEmployee);

				if(employee_buscarMayorId(pArrayListEmployee,&idAux)==0)
				{
					*idNext=idAux;
				}
			}

		}
		else
		{
			flag=4;
		}
	}

	fclose(f);

    return flag;
}

/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee, int* idNext)
{
	int error=-1;
	int idAux;
	FILE* f;
	char confirmacion;

	if(path!=NULL && pArrayListEmployee!=NULL && idNext!=NULL)
	{
		f= fopen(path,"rb");
		if(f!=NULL)
		{
			if(ll_isEmpty(pArrayListEmployee)==1 && utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n')==0)
			{
				if(confirmacion!='s')
				{
					error=5;
				}
			}
			if(ll_isEmpty(pArrayListEmployee)==0 || confirmacion=='s')
			{
				ll_clear(pArrayListEmployee);
				error=parser_EmployeeFromBinary(f, pArrayListEmployee);
				if(employee_buscarMayorId(pArrayListEmployee,&idAux)==0)
				{
					*idNext=idAux;
				}
			}
		}
		else
		{
			error=3;//no se pudo abrir
		}
	}

	fclose(f);
    return error;
}





/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	int tam;
	ePais* aux=NULL;

	tam= ll_len(pArrayListEmployee);

	if(pArrayListEmployee!=NULL && tam>0)
	{
		printf("\n  id pais vac1dosis vac2dosis sinVacunar\n");

		for(int i=0; i<tam; i++)
		{
			aux=(ePais*) ll_get(pArrayListEmployee, i);
			employee_mostrarEmpleado(aux);

		}
		aux=NULL;
		error=0;
	}

    return error;
}

/** \brief asigna valores a los campos
 * \param pArrayListEmployee LinkedList*
 * \return int
 */

int controller_MapEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	int opcion;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumeroEnteroConIntentos(&opcion, "Asignar valor:\n 1- vac1dosis\n 2- vac2dosis\n 3-sinVacunar ", "ERROR ingrese entre 1-3", 1, 3, 5)==0)
		{
			switch (opcion)
			{
				case 1:
					printf("vac1dosis");
					pArrayListEmployee=ll_map(pArrayListEmployee, employee_paisAsignacionVac1dosis);
					break;

				case 2:
					printf("vac2dosis");
					pArrayListEmployee=ll_map(pArrayListEmployee, employee_paisAsignacionVac2dosis);
					break;

				case 3:
					printf("sinVacunar");
					pArrayListEmployee=ll_map(pArrayListEmployee, employee_paisAsignacionSinVacunar);
					break;
			}
		}
		error=0;
	}
	return error;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	int opcion;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumeroEnteroConIntentos(&opcion, "\nOrdenar por\n 1-Vacunado 1 dosis Ascendente\n 2-Vacunado 1 dosis  Descendente\n "
				"3-Vacunado 2 dosis  Ascendente\n 4-Vacunado 2 dosis  Descendente\n "
				"5-Sin Vacunar Ascendente\n 6-Sin Vacunar Descendente", "ERROR ingrese 1-6 ", 1, 6, 5)==0)
		{
			switch (opcion)
			{
				case 1:
					printf("Vacunado 1 dosis Ascendente");
					error=ll_sort(pArrayListEmployee, employee_cmp1Dosis, 1);
					break;

				case 2:
					printf("Vacunado 1 dosis Descendente");
					error=ll_sort(pArrayListEmployee, employee_cmp1Dosis, 0);
					break;

				case 3:
					printf("Vacunado 2 dosis Ascendente");
					error=ll_sort(pArrayListEmployee, employee_cmp2Dosis, 1);
					break;

				case 4:
					printf("Vacunado 2 dosis Descendente");
					error=ll_sort(pArrayListEmployee, employee_cmp2Dosis, 0);
					break;

				case 5:
					printf("Sin Vacunar Ascendente");
					error=ll_sort(pArrayListEmployee, employee_sinVacunar, 1);
					break;

				case 6:
					printf("Sin Vacunar Descendente");
					error=ll_sort(pArrayListEmployee, employee_sinVacunar, 0);
					break;
			}
		}
		error=0;
	}
	return error;
}

/** \brief generar un archivo igual al original, pero donde solo
aparezcan países cuya población este vacunada con dos dosis en un porcentaje mayor al 30%
 * \param pArrayListEmployee LinkedList*
 * \return int
 */

int controller_filterEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	LinkedList* listaFiltrada=NULL;

	if(pArrayListEmployee!=NULL)
	{
		listaFiltrada=ll_filter(pArrayListEmployee, employee_FilterPais2Dosis);
		controller_ListEmployee(listaFiltrada);

		error=0;
	}
	return error;
}


/** \brief : Informar el nombre del país o países con el mayor porcentaje de no
vacunados. Y cuál es ese número
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_filterHorno(LinkedList* pArrayListEmployee)
{
	int error=-1;
	LinkedList* listaFiltrada=NULL;

	if(pArrayListEmployee!=NULL)
	{
		listaFiltrada=ll_filter(pArrayListEmployee, employee_FilterMayorVacunados);
		controller_ListEmployee(listaFiltrada);

		error=0;
	}
	return error;
}



/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int error=-1;
	FILE* f;
	int tam;
	ePais* aux=NULL;
	char confirmacion='s';

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		f= fopen(path, "r");
		if(f!=NULL)
		{
			utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n');
		}

		fclose(f);

		if(confirmacion=='s')
		{
			f= fopen(path, "w");

			if(f!=NULL)
			{
				fprintf(f,"Id,Nombre,HorasTrabajadas,Sueldo\n");

				tam= ll_len(pArrayListEmployee);

				for(int i=0; i<tam; i++)
				{
					aux=(ePais*) ll_get(pArrayListEmployee, i);
					if(aux!=NULL)
					{
						fprintf(f,"%d,%s,%d,%d,%d\n",
									aux->id,
									aux->pais,
									aux->vac1dosis,
									aux->vac2dosis,
									aux->sinVacunar
									);
						aux=NULL;
					}
					else
					{
						error=1;// hubo problema en el fprintf
						break;
					}
				}
			}
			else
			{
				error=2; // hubo problema en abrir el archivo
			}
			error=0;
		}
		else
		{
			error=3; // cancelacion de sobreescribir
		}
	}

	fclose(f);

    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int error=-1;
	int tam;
	ePais* aux=NULL;
	FILE* f;
	char confirmacion='s';

	tam=ll_len(pArrayListEmployee);

	if(path!=NULL && pArrayListEmployee!=NULL && tam>0)
	{
		f= fopen(path, "rb");
		if(f!=NULL)
		{
			utn_getCaracterCorroboraDosCarac(&confirmacion, "ALERTA base con empleados cargados. Sobreescribir s/n", "ERROR ingrese s/n", 's', 'n');

		}

		fclose(f);
		if(confirmacion=='s')
		{
			f= fopen(path, "wb");
			if(f!=NULL)
			{
				for(int i=0; i<tam; i++)
				{
					aux=(ePais*) ll_get(pArrayListEmployee, i);
					if(aux!=NULL)
					{
						if(fwrite(aux, sizeof(ePais),1,f)<1)
						{
							error=1;// hubo un problema en el guardado
							break;
						}
						else
						{
							error=0;
						}
					}
					else
					{
						error=2;// hubo un problema en cargar el empleado
						break;
					}
				}
			}
		}
		else
		{
			error=3;
		}
	}
fclose(f);
    return error;
}


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

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int* id)
{
	int error=-1;
	Employee* aux=NULL;

	if(pArrayListEmployee!=NULL && id!=NULL)
	{
		printf("\nid %d\n", *id);
		aux= employee_new();

		if(aux!=NULL &&
			utn_getString(aux->nombre, "Ingrese nombre ", "ERROR ingrese solo letras ", 5)==0 &&
			utn_getNumeroEnteroConIntentos(&aux->horasTrabajadas, "Ingrese las horas trabajadas entre 50-500 ",
					"ERROR reingrese las horas trabajadas entre 50-500 ", 50, 500, 5)==0 &&
			utn_getNumeroEnteroConIntentos(&aux->sueldo, "Ingrese sueldo entre 1000-1000000 ",
					"ERROR reingrese sueldo entre 1000-1000000 ", 1000, 1000000, 5)==0)
		{
			aux->id= *id;

			if(ll_add(pArrayListEmployee, aux)==0)
			{
				*id=*id+1;
				aux=NULL;
				error=0;
			}
		}
	}

    return error;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)// ll_set
{
	int error=-1;
	Employee* aux=NULL;
	int indice;

	if(pArrayListEmployee!=NULL)
	{

		aux=employee_pedirIdyMostrar(pArrayListEmployee, &indice);

		if(aux!=NULL)
		{
			error=employee_menuModificar(aux);
		}
		else
		{
			error=2;
		}
		aux=NULL;
	}
    return error;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee, LinkedList* pArrayListEmployeeBaja)
{
	int error=-1;
	Employee* aux=NULL;
	int indice;
	int opcion;

	if(pArrayListEmployee!=NULL && pArrayListEmployeeBaja)
	{
		aux=employee_pedirIdyMostrar(pArrayListEmployee, &indice);

		if(aux!=NULL && indice>=0)
		{
			if(utn_getNumeroEnteroConIntentos(&opcion, "Desea:\n 1-Eliminar de la lista\n 2-Remover y agregar en la lista de empleados de baja\n", "ERROR, ingrese 1-2", 1, 2, 5)==0)
			{
				if(opcion==2)
				{
					aux= ll_pop(pArrayListEmployee, indice);
					ll_add(pArrayListEmployeeBaja, aux);
					error=0;

				}
				else
				{
					ll_remove(pArrayListEmployee, indice);
					error=0;

				}
			}
			aux=NULL;
		}
		else
		{
			error=2;
		}
	}
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
	Employee* aux=NULL;

	tam= ll_len(pArrayListEmployee);

	if(pArrayListEmployee!=NULL && tam>0)
	{
		printf("\n  Id HsTrb Sueldo Nombre\n");

		for(int i=0; i<tam; i++)
		{
			aux=(Employee*) ll_get(pArrayListEmployee, i);
			employee_mostrarEmpleado(aux);

		}
		aux=NULL;
		error=0;
	}

    return error;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int error=-1;
	int opcion;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumeroEnteroConIntentos(&opcion, "\nOrdenar por\n 1-Nombre Ascendente\n 2-Nombre Descendente\n "
				"3-Hs Trabajadas Ascendente\n 4-Hs Trabajadas Descendente\n "
				"5-Sueldo Ascendente\n 6-Sueldo Descendente", "ERROR ingrese 1-7 ", 1, 7, 5)==0)
		{
			switch (opcion)
			{
				case 1:
					printf("Nombre Ascendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpNombre, 1);
					break;

				case 2:
					printf("Nombre Descendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpNombre, 0);
					break;

				case 3:
					printf("Hs Trabajadas Ascendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpHsTrab, 1);
					break;

				case 4:
					printf("Hs Trabajadas Descendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpHsTrab, 0);
					break;

				case 5:
					printf("Sueldo Ascendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpSueldo, 1);
					break;

				case 6:
					printf("Sueldo Descendente");
					error=ll_sort(pArrayListEmployee, employee_empleadoCmpSueldo, 0);
					break;
			}
		}
		error=0;
	}
	return error;
}

/** \brief Reincorpora un empleado dado de baja en la lista activa
 *
 * \param pArrayListEmployee LinkedList*
 * \param pArrayListEmployeeBaja LinkedList*
 * \return int
 *
 */
int controller_ReincorporacionEmpleado(LinkedList* pArrayListEmployee, LinkedList* pArrayListEmployeeBaja)// ll_set
{
	int error=-1;
	Employee* auxAReincorporar=NULL;
	Employee* auxEmpPrev=NULL;
	int indiceBaja;
	char confirmacion;
	int indiceInsertar;

	if(pArrayListEmployee!=NULL&& pArrayListEmployeeBaja!=NULL)
	{
		auxAReincorporar=employee_pedirIdyMostrar(pArrayListEmployeeBaja, &indiceBaja);//recupero el indice del empleado a reincorporar

		if(auxAReincorporar!=NULL && ll_contains(pArrayListEmployee, auxAReincorporar)==0)
		{
			if(utn_getCaracterCorroboraDosCarac(&confirmacion, "Desea reactivar empleado? s-n", "ERROR ingrese s-n", 's', 'n')==0)
			{
				if( confirmacion=='s') // muesttra lista de altas donde quiere q reincorpore
				{
					printf("\n*** Antes de que empleado desea que este***");
					auxEmpPrev=employee_pedirIdyMostrar(pArrayListEmployee, &indiceInsertar);// busco el empleado previo
					//employee_buscarId(pArrayListEmployee, ll_len(pArrayListEmployee), indiceInsertar);
					if(auxEmpPrev!=NULL)
					{
						indiceInsertar=ll_indexOf(pArrayListEmployee, auxEmpPrev);
						if(indiceInsertar>-1)
						{
							ll_push(pArrayListEmployee, indiceInsertar, auxAReincorporar);
							ll_remove(pArrayListEmployeeBaja, indiceBaja);
							error=0;
						}
					}
				}
			}
			else
			{
				error=1;
			}
		}
		else
		{
			error=2;
		}
		auxAReincorporar=NULL;
		auxEmpPrev=NULL;
	}
    return error;
}

int controller_CrearSublista(LinkedList* pArrayListEmployee)// ll_set
{
	int error=-1;
	int idMayor;
	int idInicio;
	int idFinal;
	Employee* empInicio;
	Employee* empFinal;
	LinkedList* pArrayListEmployeeNew=NULL;

	if(pArrayListEmployee!=NULL)
	{
		employee_buscarMayorId(pArrayListEmployee, &idMayor);
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getNumeroEnteroConIntentos(&idInicio, "Ingrese desde que id ","ERROR id no valido" , 0, idMayor, 5)==0 &&
			utn_getNumeroEnteroConIntentos(&idFinal, "Ingrese hasta que id ","ERROR id no valido" , 0, idMayor, 5)==0 )
		{
			empInicio= employee_buscarId(pArrayListEmployee, ll_len(pArrayListEmployee), idInicio);
			empFinal= employee_buscarId(pArrayListEmployee, ll_len(pArrayListEmployee), idFinal);

			if(empInicio!=NULL && empFinal!=NULL)
			{
				idInicio=ll_indexOf(pArrayListEmployee, empInicio);
				idFinal=ll_indexOf(pArrayListEmployee, empFinal);

				if(idInicio>-1 && idFinal>-1)
				{
					pArrayListEmployeeNew= ll_subList(pArrayListEmployee, idInicio, idFinal);
					if(ll_containsAll(pArrayListEmployee, pArrayListEmployeeNew)==1)//verificacion de exito
					{
						controller_ListEmployee(pArrayListEmployeeNew);
						error=0;
					}

				}
			}
			else
			{
				error=2;
			}
		}
		else
		{
			error=1;
		}
	}

	return error;
}

int controller_Clone(LinkedList* pArrayListEmployee)
{
	int error=-1;
	char confirmacion;
	LinkedList* pArrayListEmployeeNew;

	if(pArrayListEmployee!=NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getCaracterCorroboraDosCarac(&confirmacion, "Seguro que desea clonar la lista? s-n ", "ERROR ingrese s-n", 's', 'n')==0)
		{
			pArrayListEmployeeNew=ll_clone(pArrayListEmployee);
			if(ll_containsAll(pArrayListEmployee, pArrayListEmployeeNew)==1)//verificacion de exito
			{
				printf("Lista clonada\n");
				controller_ListEmployee(pArrayListEmployeeNew);
				error=0;
			}
		}
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
	Employee* aux=NULL;
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
					aux=(Employee*) ll_get(pArrayListEmployee, i);
					if(aux!=NULL)
					{
						fprintf(f,"%d,%s,%d,%d\n",
									aux->id,
									aux->nombre,
									aux->horasTrabajadas,
									aux->sueldo);
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
	Employee* aux=NULL;
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
					aux=(Employee*) ll_get(pArrayListEmployee, i);
					if(aux!=NULL)
					{
						if(fwrite(aux, sizeof(Employee),1,f)<1)
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


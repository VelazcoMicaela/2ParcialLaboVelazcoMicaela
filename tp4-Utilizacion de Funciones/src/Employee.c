#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "LinkedList.h"
#include "employee.h"
#include "Controller.h"



Employee* employee_new()
{
	Employee* aux;

	aux= (Employee*) malloc (sizeof(Employee));
	if(aux!=NULL)
	{
		aux->id=0;
		strcpy( aux->nombre, " ");
		aux->horasTrabajadas=0;
		aux->sueldo=0;
	}

	return aux;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* aux;

	aux=employee_new();

	if(aux!=NULL && idStr!=NULL && nombreStr!=NULL && horasTrabajadasStr!=NULL && sueldoStr!=NULL)
	{
		if(!(employee_setId(aux, atoi(idStr))==0 &&
			employee_setNombre(aux, nombreStr)==0 &&
			employee_setHorasTrabajadas(aux, atoi(horasTrabajadasStr))==0 &&
			employee_setSueldo(aux, atoi(sueldoStr))==0))
		{
			free(aux);
			aux=NULL;
		}
	}

	return aux;
}

////// EMPIEZAN SET ///////

int employee_setId(Employee* this,int id)
{
	int error=-1;

	if(this!=NULL && id>0 && id<2000)
	{
		this->id=id;
		error=0;
	}

	return error;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int error=-1;


	if(this!=NULL && strlen(nombre)<100 && strlen(nombre)>1 )

	{
		strcpy( this->nombre, nombre);
		error=0;
	}

	return error;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int error=-1;

	if(this!=NULL && horasTrabajadas>50 && horasTrabajadas<500)
	{
		this->horasTrabajadas=horasTrabajadas;
		error=0;
	}

	return error;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int error=-1;

	if(this!=NULL && sueldo>1000 && sueldo<1000000)
	{
		this->sueldo=sueldo;
		error=0;
	}

	return error;
}

/////////////// EMPIEZAN GET////////////

int employee_getId(Employee* this,int* id)
{
	int error=-1;

	if(this!=NULL && id!=NULL)
	{
		*id= this->id;
		error=0;
	}

	return error;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int error=-1;

	if(this!=NULL && nombre!=NULL)
	{
		strcpy(nombre, this->nombre);
		error=0;
	}

	return error;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int error=-1;

	if(this!=NULL && horasTrabajadas!=NULL)
	{
		*horasTrabajadas= this->horasTrabajadas;
		error=0;
	}

	return error;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int error=-1;

	if(this!=NULL && sueldo!=NULL)
	{
		*sueldo= this->sueldo;
		error=0;
	}

	return error;
}

int employee_mostrarEmpleado(Employee* emp)
{
	int error=-1;
	int id;
	char nombre[128];
	int horasTrabajadas;
	int sueldo;

	if(emp!=NULL)
	{
		if(employee_getId(emp, &id)==0 &&
			employee_getNombre(emp, nombre)==0 &&
			employee_getHorasTrabajadas(emp, &horasTrabajadas)==0 &&
			employee_getSueldo(emp,&sueldo)==0)
		{
			printf("%4d %3d   %5d %s\n", id, horasTrabajadas, sueldo,nombre);
		}

		error=0;
	}
    return error;
}

int employee_buscarMayorId(LinkedList* pArrayListEmployee, int* id)
{
	int error=-1;
	Employee* aux;
	int mayor=0;
	int i;

	//tam=ll_len(pArrayListEmployee);

	if(pArrayListEmployee!=NULL && id!=NULL)// tam>=0 &&
	{
		for(i=0; i<ll_len(pArrayListEmployee); i++)
		{
			aux=(Employee*)ll_get(pArrayListEmployee, i);
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

void employee_employee_delete()
{
	//free(array);
}


///////////// comparaciones ////////////

int employee_empleadoCmpSueldo(void* a, void* b)
{
	int error=0;

	Employee* emp1;
	Employee* emp2;

	if(a!=NULL && b!=NULL)
	{
		emp1= (Employee*) a;
		emp2= (Employee*) b;

		if(emp1->sueldo > emp2->sueldo)
		{
			error=1;
		}
		else if(emp1->sueldo < emp2->sueldo)
		{
			error=-1;
		}
	}
	return error;
}

int employee_empleadoCmpHsTrab(void* a, void* b)
{
	int error=0;

	Employee* emp1;
	Employee* emp2;

	if(a!=NULL && b!=NULL)
	{
		emp1= (Employee*) a;
		emp2= (Employee*) b;

		if(emp1->horasTrabajadas > emp2->horasTrabajadas)
		{
			error=1;
		}
		else if(emp1->horasTrabajadas < emp2->horasTrabajadas)
		{
			error=-1;
		}
	}
	return error;
}

int employee_empleadoCmpNombre(void* a, void* b)
{
	int error=0;

	Employee* emp1;
	Employee* emp2;

	if(a!=NULL && b!=NULL)
	{
		emp1= (Employee*) a;
		emp2= (Employee*) b;

		error=strcmp(emp1->nombre , emp2->nombre);

	}
	return error;
}

Employee* employee_buscarId(LinkedList* pArrayListEmployee, int tam, int id)
{
	Employee* aux=NULL;

	if(pArrayListEmployee!=NULL && tam>0 && id>0 )
	{
		for(int i=0; i<tam; i++)
		{
			aux=(Employee*) ll_get(pArrayListEmployee, i);

			if(aux->id==id && aux!=NULL)
			{
				break;
			}
			else
			{
				aux=NULL;
			}
		}
	}

	return aux;
}

int employee_menuModificar(Employee* empleado)
{
	int opcion;
	char salir;
	int error=-1;
	char guardar;
	char nombre[20];
	int horasTrab;
	int sueldo;


	if(empleado!=NULL)
	{
		do
		{
			if(utn_getNumeroEnteroConIntentos(&opcion, "Modificar \n 1-Nombre\n 2-Horas trabajadas\n 3-Sueldo\n 4-Salir  ",
							"ERROR reingrese una opcion ", 0, 4, 5)==0)
			{
				error=1;
				switch(opcion)
				{
					case 1:
						printf("Modificar Nombre\n");
						if(utn_getString(nombre, "Ingrese nombre ", "ERROR ingrese solo letras ", 5)==0)
						{
							printf("%s\n", nombre);
							utn_getCaracterCorroboraDosCarac(&guardar,"Guardar los cambios s/n", "ERROR ingrese s/n", 's', 'n');
							if(guardar=='s')
							{
								strcpy(empleado->nombre,nombre);
								error=0;
							}
						}
						break;

					case 2:
						printf("Modificar Horas Trabajadas\n");
						if(utn_getNumeroEnteroConIntentos(&horasTrab, "Ingrese las horas trabajadas ",
								"ERROR reingrese las horas trabajadas entre 0-1000 ", 0, 1000, 5)==0)
						{
							printf("%d\n", horasTrab);
							utn_getCaracterCorroboraDosCarac(&guardar,"Guardar los cambios s/n", "ERROR ingrese s/n", 's', 'n');
							if(guardar=='s')
							{
								empleado->horasTrabajadas=horasTrab;
								error=0;
							}
						}
						break;

					case 3:
						printf("Modificar Sueldo\n");
						if(utn_getNumeroEnteroConIntentos(&sueldo, "Ingrese sueldo ",
								"ERROR reingrese sueldo entre 10-1000000 ", 10, 1000000, 5)==0)
						{
							printf("%d\n", sueldo);
							utn_getCaracterCorroboraDosCarac(&guardar,"Guardar los cambios s/n", "ERROR ingrese s/n", 's', 'n');
							if(guardar=='s')
							{
								empleado->sueldo=sueldo;
								error=0;
							}
						}
						break;

					case 4:
						printf("Salir\n");
						utn_getCaracterCorroboraDosCarac(&salir, " s/n", "ERROR ingrese s/n", 's', 'n');
						error=0;
						break;
				}

			}
		}while(opcion!=4);
	}

	return error;
}

Employee* employee_pedirIdyMostrar(LinkedList* pArrayListEmployee, int* indice)
{
	int tam;
	Employee* aux=NULL;
	int id;
	int idRaiz;

	if(pArrayListEmployee!=NULL && indice!=NULL)
	{
		employee_buscarMayorId(pArrayListEmployee, &idRaiz);

		if(controller_ListEmployee(pArrayListEmployee)==0 &&
				utn_getNumeroEnteroConIntentos(&id, "Ingrese el id del empleado ",
				"ERROR reingrese id ", 0, idRaiz, 5)==0)
		{
			tam= ll_len(pArrayListEmployee);

			aux= employee_buscarId(pArrayListEmployee, tam, id);
			if(aux!=NULL)
			{
				employee_mostrarEmpleado(aux);
				*indice=ll_indexOf(pArrayListEmployee, aux);
			}
		}
	}

	return aux;
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



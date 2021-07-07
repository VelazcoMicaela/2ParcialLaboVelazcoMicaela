#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int cant;
	ePais* aux;
	int flag=-1;
	char buffer[5][1000];

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);//lectura fantasma
		while(!feof(pFile))
		{
			cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
			if(cant==5)
			{
				aux=employee_newParametros(buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);

				if(aux!=NULL)
				{

					if(ll_add(pArrayListEmployee, aux)==0)
					{
						aux=NULL;
						flag=0;
					}
					else
					{
						flag=1;//hubo un problema para cargar el empleado
						break;
					}
				}
				else
				{
					flag=2;//hubo un problema en el parseo
					break;
				}
			}
			else
			{
				flag=3;// hubo un problema con el levantar datos
				break;
			}
		}
	}

    return flag;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int error=-1;
	ePais* aux=NULL;
	int cant;
	int i=0;

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		while(!feof(pFile))
		{
			aux= employee_new();

			if(aux!=NULL)
			{
				cant= fread(aux,sizeof(ePais),1,pFile);
				if(cant==1)
				{
					if(ll_add(pArrayListEmployee, aux)==0)
					{
						aux=NULL;
						error=0;
					}
				}


			}
			else
			{
				error=2;// no se pudo conseguir lugar
				break;
			}
			i++;

		}
	}

    return error;
}



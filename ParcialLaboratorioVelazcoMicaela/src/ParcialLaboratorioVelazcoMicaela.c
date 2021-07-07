/*
 ============================================================================
 Name        : ParcialLaboratorioVelazcoMicaela.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);

	////// TIME INICIALIZADO ////
	srand(time(NULL));

	int opcion;
	char salir;
	int error;
	int idNext=1;
	char path[50];

	LinkedList* listaEmpleados = ll_newLinkedList();

	/*/////// ALEATORIO //////////////
	/// HAY Q INCLUIR TIME.H
	int num;
	int max=200;
	int min=50;
	printf("\n");
	num= rand()% (max-min+1)+min;
	printf("%d\n", num);
	////////////////////*/

	if(listaEmpleados!=NULL)
	{
	   do{
		   if(utn_getNumeroEnteroConIntentos(&opcion, "\nIngrese una opcion\n 1-Cargar modo texto\n 2-Cargas modo binario\n "
				   "3-Imprimir lista\n 4-Asignar estadísticas\n 5-Filtrar por países exitosos\n 6-Filtrar por países en el horno\n "
				   "7-Ordenar por nivel de vacunación\n 8- Mostrar más castigado\n 9-Guardar modo texto\n 10-Guardar modo binario\n 11-Salir",
				   "ERROR ingrese una opcion entre 1-11 ", 1, 11, 5)==0)
		   {
				switch(opcion)
				{
					case 1:
						printf("\nCargar datos (modo texto)\n");//utilizacion de ll_IsEmpty, ll_clear
						ingresarPath(path);

						error=controller_loadFromText(path,listaEmpleados, &idNext);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados cargados exitosamente\n", "ERROR hubo un problema para cargar el empleado\n",
											"ERROR hubo un problema en el parseo\n", "ERROR hubo un problema con el levantar datos\n", "ERROR hubo problema al abrir\n",
											"Datos no sobreescritos\n");
						break;

					case 2:
						printf(" Cargar datos (modo binario)\n");//utilizacion de ll_IsEmpty, ll_clear
						ingresarPath(path);
						error=controller_loadFromBinary(path,listaEmpleados,  &idNext);
						menuErrores(error, "ERROR hubo un problema\n", "Empleados cargados exitosamente\n", "ERROR hubo un problema para cargar el empleado\n",
											"ERROR hubo un problema en el parseo\n", "ERROR hubo un problema con el levantar datos\n", "ERROR hubo problema al abrir\n",
											"Datos no sobreescritos\n");
						break;

					case 3:
						printf(" Listar de empleados activos");// ll_len ll_get

						if(controller_ListEmployee(listaEmpleados)==0)
						{
							printf("listar exitoso\n");
						}
						break;

					case 4:
						printf(" Asignar estadísticas\n");
						if(controller_MapEmployee(listaEmpleados)==0)
						{
							controller_ListEmployee(listaEmpleados);
							printf("Asignados exitosamente\n");
						}

						break;

					case 5:
						printf(" Filtrar por países exitosos\n");
						if(controller_filterEmployee(listaEmpleados)==0)
						{
							printf("Filtrado exitosamente\n");
						}

						break;

					case 6:
						printf(" Filtrar por países en el horno\n");
						if(controller_filterHorno(listaEmpleados)==0)
						{
							printf("Filtrado exitosamente\n");
						}
					break;

					case 7:
						printf(" Ordenar por nivel de vacunación\n");
						if(controller_sortEmployee(listaEmpleados)==0)
						{
							controller_ListEmployee(listaEmpleados);
							printf("Oredenados exitosamente\n");
						}

						break;

					case 8:
						printf(" Mostrar más castigado\n");
						/*if(controller_sortEmployee(listaEmpleados)==0)
						{
							controller_ListEmployee(listaEmpleados);
							printf("Oredenados exitosamente\n");
						}*/

						break;



					case 9:
						printf(" Guardar datos (modo texto)\n");
						ingresarPath(path);
						error=controller_saveAsText(path, listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados guardados exitosamente\n", "ERROR hubo problema en el fprintf\n",
											"ERROR hubo problema en abrir el archivo\n", "Archivo no guardado. Datos no sobreescritos", " ", " ");
						break;

					case 10:
						printf(" Guardar datos (modo binario)\n");
						ingresarPath(path);
						error=controller_saveAsBinary(path, listaEmpleados);
						menuErrores(error, "ERROR hubo un problema\n", "Empleados guardados exitosamente\n", "ERROR hubo problema en el guardado\n",
											"ERROR hubo problema en abrir el archivo\n", "Archivo no guardado. Datos no sobreescritos", " ", " ");
						break;

					case 11:
						printf(" Salir\n");
						if(utn_getCaracterCorroboraDosCarac(&salir, "Desea salir? S/N\n", "ERROR Ingrese S para salir o N para quedarse", 's', 'n')==0)
						{
							if(salir=='s')
							{
								printf("Hasta luego\n");
							}
						}
						break;
				}
		   }

		}while(salir !='s');
	}

   ll_deleteLinkedList(listaEmpleados);
	return EXIT_SUCCESS;
}

/*
 ============================================================================
 Name        : linkedListTP4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);
	int opcion;
	char salir;
	int error;
	int idNext=1;
	char path[50];

	LinkedList* listaEmpleados = ll_newLinkedList();
	LinkedList* listaEmpleadosBaja = ll_newLinkedList();


	if(listaEmpleados!=NULL && listaEmpleadosBaja!=NULL)
	{
	   do{
		   if(utn_getNumeroEnteroConIntentos(&opcion, "\nIngrese una opcion\n 1-Cargar modo texto\n 2-Cargas modo binario\n "
				   "3-Alta\n 4-Modificacion\n 5-Baja\n 6-Listar\n 7-Ordenar\n 8-Inserta un empleado dado de baja en la lista de activos\n "
				   "9-Pasa a nueva lista un rango de empleados \n 10-Clonar lista\n"
				   " 11-Guardar modo texto\n 12-Guardar modo binario\n 13-Salir",
				   "ERROR ingrese una opcion entre 1-13 ", 1, 13, 5)==0)
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
						printf(" Alta de empleado\n");// ll_add
						if(controller_addEmployee(listaEmpleados,&idNext)==0)
						{
							printf("Alta exitosa\n");
							controller_ListEmployee(listaEmpleados);
						}

						break;

					case 4:
						printf(" Modificar empleado\n");
						error=controller_editEmployee(listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados modificado exitosamente\n", "Modificacion cancelada\n",
														"ERROR no existe empleado con ese id\n", " ", " ", " ");
						break;

					case 5:
						printf(" Baja de empleado\n");// pop delate
						error=controller_removeEmployee(listaEmpleados, listaEmpleadosBaja);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados dado de baja exitosamente\n", "Baja cancelada\n",
											"ERROR no existe empleado con ese id\n", " ", " ", " ");
						break;

					case 6:
						printf(" Listar de empleados activos");// ll_len ll_get

						if(controller_ListEmployee(listaEmpleados)==0)
						{
							printf("listar exitoso\n");
						}
						printf("\nEmpleados dados de baja");
						if(controller_ListEmployee(listaEmpleadosBaja)==0)
						{
							printf("listar exitoso\n");
						}

						break;

					case 7:
						printf(" Ordenar de empleado\n");
						if(controller_sortEmployee(listaEmpleados)==0)
						{
							controller_ListEmployee(listaEmpleados);
							printf("Oredenados exitosamente\n");
						}

						break;

					case 8:////PUSH indexOf Contain
						printf(" Reincorpora un empleado dado de baja en la lista de activos \n");

						error=controller_ReincorporacionEmpleado(listaEmpleados, listaEmpleadosBaja);

						menuErrores(error, "ERROR hubo un problema\n", "Empleado reactivado exitosamente\n", "reactivacion cancelada\n",
						"ERROR no existe empleado con ese id o ya se encuentra activo\n", " ", " ", " ");


						break;

					case 9:////SUblist
						printf(" Pasa a nueva lista un rango de empleados \n");
						error=controller_CrearSublista(listaEmpleados);
						menuErrores(error, "ERROR hubo un problema\n",  "Sublista exitosa\n", "Id empleado no existe",  " Empleados no validos",  " ",  " ",  " ");

						break;

					case 10:////CLONE
						printf(" Clonar lista \n");
						if(controller_Clone(listaEmpleados)==0)
						{
							printf("Clonada exitosamente\n");
						}

						break;

					case 11:
						printf(" Guardar datos (modo texto)\n");
						ingresarPath(path);
						error=controller_saveAsText(path, listaEmpleados);

						menuErrores(error, "ERROR hubo un problema\n", "Empleados guardados exitosamente\n", "ERROR hubo problema en el fprintf\n",
											"ERROR hubo problema en abrir el archivo\n", "Archivo no guardado. Datos no sobreescritos", " ", " ");
						break;

					case 12:
						printf(" Guardar datos (modo binario)\n");
						ingresarPath(path);
						error=controller_saveAsBinary(path, listaEmpleados);
						menuErrores(error, "ERROR hubo un problema\n", "Empleados guardados exitosamente\n", "ERROR hubo problema en el guardado\n",
											"ERROR hubo problema en abrir el archivo\n", "Archivo no guardado. Datos no sobreescritos", " ", " ");
						break;

					case 13:
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
   ll_deleteLinkedList(listaEmpleadosBaja);
	return EXIT_SUCCESS;
}

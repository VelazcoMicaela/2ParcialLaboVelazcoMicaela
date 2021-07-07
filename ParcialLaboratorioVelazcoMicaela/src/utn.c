/*
 * UTN.c
 *
 *  Created on: 13 abr. 2021
 *      Author: Asus
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utn.h"

int utn_getNumeroEnteroConIntentos(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int bufferInt;
	int error=-1;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
	{
		for(int i=0;i<=reintentos;i++)
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt)==1)
			{
				if(bufferInt>=minimo && bufferInt<=maximo)
				{
					*pResultado=bufferInt;
					error=0;
					break;
				}
				else
				{
					printf("Le quedan %d intentos\n",reintentos-i);
					printf("%s",mensajeError);
				}
			}
			else
			{
				printf("Le quedan %d intentos\n",reintentos-i);
				printf("%s",mensajeError);
			}
			fflush(stdin);
		}
	}
	return error;
}

int utn_getNumeroEntero(int* pResultado, char* mensaje, char* mensajeError)
{
	int bufferInt;
	int error=-1;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL)
	{
		printf("%s", mensaje);
		error=getInt(&bufferInt);

		if(error==1)
		{
			*pResultado=bufferInt;
			error=1;
		}

		while(error<0)
		{
			printf("%s",mensajeError);
			error=getInt(&bufferInt);
			*pResultado=bufferInt;
		}
		fflush(stdin);
	}
	return error;
}

int getInt(int* pResultado)
{
	char buffer[64];
	int ret=-1;

	if(myGet(buffer,sizeof(buffer))==0 && esNumerica(buffer))
	{
		*pResultado=atoi(buffer);
		ret=1;
	}
	return ret;
}

int esNumerica(char* cadena)
{
	int i=0;
	int retorno=-1;

	if(cadena!=NULL && strlen(cadena)>0)
	{
		while(cadena[i] !='\0')
		{
			if(cadena[i]<'0'||cadena[i]>'9')
			{
				retorno=0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

int myGet(char* cadena, int longitud)
{
	int error=-1;
	if(cadena!=NULL && longitud>0 && fgets(cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1]=='\n')
		{
			cadena[strlen(cadena)-1] = '\0';
		}
		error=0;
	}
	return error;
}

int esCaracter(char* cadena)
{
	int i=0;
	int retorno=-1;

	if(cadena!=NULL && strlen(cadena)>0)
	{
		while(cadena[i] !='\0')
		{
			cadena[i]=tolower(cadena[i]);
			if(cadena[i]<'a'||cadena[i]>'z')
			{
				retorno=0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

int getChar(char* pResultado)
{
	char buffer[120];
	int ret=-1;

	scanf("%s",buffer);
	if(esCaracter(buffer))
	{
		*pResultado=*buffer;
		ret=1;
	}
	return ret;
}

int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
	char bufferchar;
	int error=-1;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
	{
		for(int i=0;i<=reintentos;i++)
		{
			printf("%s", mensaje);

			if(getChar(&bufferchar)==1 && bufferchar>=minimo && bufferchar<=maximo)
			{
				*pResultado=bufferchar;
				error=0;
				break;
			}
			printf("Le quedan %d intentos\n",reintentos-i);
			printf("%s",mensajeError);

			fflush(stdin);
		}
	}
	return error;
}

int utn_getCaracterCorroboraDosCarac(char* pResultado, char* mensaje, char* mensajeError, char validar1, char validar2)
{
	char bufferChar;
	int error=-1;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && validar1!=validar2)
	{
		printf("%s", mensaje);
		error=getChar(&bufferChar);

		while(error!=0)
		{
			if(bufferChar==validar1 || bufferChar==validar2)
			{
				*pResultado=bufferChar;
				error=0;
			}
			else
			{
				while(bufferChar!=validar1 && bufferChar!=validar2)
				{
					printf("%s", mensajeError);
					error=getChar(&bufferChar);

					*pResultado=bufferChar;
					error=0;
				}
			}
		}
		fflush(stdin);
	}
	return error;
}


int utn_getString(char* pResultado, char* mensaje, char* mensajeError, int reintentos)
{
	char bufferchar[120];
	int error=-1;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && reintentos>=0)
	{
		printf("%s", mensaje);

		for(int i=0;i<=reintentos;i++)
		{
			scanf("%s",bufferchar);
			fflush(stdin);
			if(esCaracter(bufferchar))
			{
				bufferchar[0]=toupper(bufferchar[0]);
				strcpy(pResultado,bufferchar);
				error=0;
				break;
			}
			printf("Le quedan %d intentos\n",reintentos-i);
			printf("%s",mensajeError);
		}
	}
	return error;
}

int getFloat(float* pResultado)
{
	char buffer[64];
	int ret=-1;

	if(myGet(buffer,sizeof(buffer))==0 && esFlotante(buffer))
	{
		*pResultado=atof(buffer);
		ret=0;
	}

	return ret;
}

int esFlotante(char* cadena)
{
	int i=0;
	int retorno=-1;
	int bandera=0;

	if(cadena!=NULL && strlen(cadena)>0)
	{
		while(cadena[i] !='\0')
		{
			if(cadena[i]<'0'||cadena[i]>'9')
			{
				if(cadena[i]=='.')
				{
					bandera++;
					if(bandera>1)
					{
						retorno=0;
						break;
					}
				}
				else
				{
					if(i==0)
					{
						if(cadena[i]!='-'&& cadena[i]!='+')
						{
							retorno=0;
							break;
						}
					}
					else
					{
						retorno=0;
						break;
					}
				}
			}
			i++;
		}
	}
	return retorno;
}

int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float bufferFloat;
	int error=-1;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
	{
		for(int i=0;i<=reintentos;i++)
		{
			printf("%s", mensaje);
			if(getFloat(&bufferFloat)==0)
			{
				if(bufferFloat>=minimo && bufferFloat<=maximo)
				{
					*pResultado=bufferFloat;
					error=0;
					break;
				}
			}
			else
			{
				printf("Le quedan %d intentos\n",reintentos-i);
				printf("%s",mensajeError);
			}
		}
		fflush(stdin);
	}

	return error;
}


int mostrarArrayInt(int* pArray, int len)
{
	int error=-1;
	int i;

	if(pArray!=NULL&&len>=0)
	{
		error=0;
		for(i=0;i<len;i++)
		{
			printf("indice %d  - valor %d\n",i,pArray[i]);
		}
	}

	return error;
}

int ordenarArrayInt(int* pArray, int len)
{
	int error=-1;
	int aux;

	if(pArray!=NULL&&len>=0)
	{
		for(int i=0; i<len-1; i++)
		{
			for(int j=i+1; j<len; j++)
			{
				if(pArray[i]>pArray[j])
				{
					aux=pArray[i];
					pArray[i]=pArray[j];
					pArray[j]=aux;
					//printf("*****%d*****\n",aux);
				}
			}

		}
		error=0;
	}


	return error;
}




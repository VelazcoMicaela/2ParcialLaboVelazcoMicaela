/*
 * utn.h
 *
 *  Created on: 13 abr. 2021
 *      Author: Asus
 */

#ifndef UTN_H_
#define UTN_H_

/*\brief toma enteros y corrobora dentro de un rango
 *\ param pResultado puntero donde se guarde el resultado
 *\ param mensaje puntero con mensaje
 *\param mensajeError puntero con mensaje de error
 *\param minimo valor minimo para corroborar
 *\param maximo valor maximo para corroborar
 *\param reintentos cantidad de reintentos a realizar
 *\return 0 ok -1error
 *
 */
int utn_getNumeroEnteroConIntentos(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

/*\brief toma el dato numerico
 *\ param cadena devuelve la cadena corroborada
 *\return 0 ok -1error
 */
int getInt(int* pResultado);

/*\brief verifica si es un numero lo ingresado
 *\ param cadena devuelve la cadena corroborada
 *\return 0 ok -1error
 */
int esNumerica(char* cadena);

/*\brief toma enteros
 *\ param pResultado puntero donde se guarde el resultado
 *\ param mensaje puntero con mensaje
 *\param mensajeError puntero con mensaje de error
 *\return 1 ok -1error
 *
 */
int utn_getNumeroEntero(int* pResultado, char* mensaje, char* mensajeError);

/*brief toma de datos
 * param cadena donde se guardan lo ingresado
 * param longitud largo de la cadena
 * return 0 ok -1error
 */
int myGet(char* cadena, int longitud);

/*\brief corrobora q haya un solo punto, admite signos + y - en el primer indice
 *\ param cadena devuelve la cadena corroborada
 *\return 0 ok -1error
 */
int esFlotante(char* cadena);

/*\brief toma el dato flotante
 *\ param cadena devuelve la cadena corroborada
 *\return 0 ok -1error
 */
int getFloat(float* pResultado);

/*\brief toma flotantes y corrobora dentro de un rango
 *\ param pResultado puntero donde se guarde el resultado
 *\ param mensaje puntero con mensaje
 *\param mensajeError puntero con mensaje de error
 *\param minimo valor minimo para corroborar
 *\param maximo valor maximo para corroborar
 *\param reintentos cantidad de reintentos a realizar
 *\return 0 ok -1error
 *
 */
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);

/*\brief verifica si es una letra lo ingresado
 *\ param cadena devuelve la cadena corroborada
 *\return 0 ok -1error
 */
int esCaracter(char* cadena);

/*\brief toma caracteres y corrobora si es alfabetico
 *\ param pResultado puntero donde se guarde el resultado
 *\ param mensaje puntero con mensaje
 *\param mensajeError puntero con mensaje de error
 *\param minimo valor minimo para corroborar
 *\param maximo valor maximo para corroborar
 *\param reintentos cantidad de reintentos a realizar
 *\return 0 ok -1error
 *
 */
int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);

/*brief corrobora caracter de salida del bucle
 *\param pResultado puntero donde se guarde el resultado
 *\param mensaje puntero con mensaje
 *\param mensajeError puntero con mensaje de error
 *\param validar1 caracter a validar
 *\param validar2 caracter a validar
 *\return 0 ok -1error
 */
int utn_getCaracterCorroboraDosCarac(char* pResultado, char* mensaje, char* mensajeError, char validar1, char validar2);

/*\brief toma string y corrobora si es alfabetico
 *\ param pResultado puntero donde se guarde el resultado
 *\ param mensaje puntero con mensaje
 *\param mensajeError puntero con mensaje de error
 *\param reintentos cantidad de reintentos a realizar
 *\return 0 ok -1error
*/
int utn_getString(char* pResultado, char* mensaje, char* mensajeError, int reintentos);

/*brief Imprime un array de enteros
 *\param pArray puntero donde se guarde lo ordenado
 *\param len largo del array
 *\return 0 ok -1error
 */
int mostrarArrayInt(int* pArray, int len);

/*brief Ordena un array de enteros
 *\param pArray puntero donde se guarde lo ordenado
 *\param len largo del array
 *\return 0 ok -1error
 */
int ordenarArrayInt(int* pArray, int len);
#endif /* UTN_H_ */

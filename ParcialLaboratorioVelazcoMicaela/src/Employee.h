#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char pais[128];
    int vac1dosis;
    int vac2dosis;
    int sinVacunar;
}ePais;

ePais* employee_new();
ePais* employee_newParametros(char* idStr,char* paisStr,char* vac1dosisStr, char* vac2dosisStr, char* sinVacunarStr);
void employee_delete();

int employee_setId(ePais* this,int id);
int employee_getId(ePais* this,int* id);

int employee_setPais(ePais* this,char* pais);
int employee_getPais(ePais* this,char* pais);

int employee_setVac1dosisStr(ePais* this,int vac1dosisStr);
int employee_getVac1dosisStr(ePais* this,int* vac1dosi);

int employee_setVac2dosisStr(ePais* this,int vac2dosisStr);
int employee_getVac2dosisStr(ePais* this,int* vac2dosis);

int employee_setSinVacunarStr(ePais* this,int sinVacunarStr);
int employee_getSinVacunarStr(ePais* this,int* sinVacunar);

int employee_mostrarEmpleado(ePais* emp);
int employee_buscarMayorId(LinkedList* pArrayListEmployee, int* id);

ePais* employee_buscarId(LinkedList* pArrayListEmployee, int tam, int id);

int employee_menuModificar(ePais* empleado);
ePais* employee_pedirIdyMostrar(LinkedList* pArrayListEmployee, int* indice);

int employee_cmp1Dosis(void* a, void* b);
int employee_cmp2Dosis(void* a, void* b);
int employee_sinVacunar(void* a, void* b);

int employee_FilterPais2Dosis(void* a);
int employee_FilterMayorVacunados(void* a);

int employee_numAleatorio(int mayor, int menor);
int employee_paisAsignacionVac1dosis(void* a);
int employee_paisAsignacionVac2dosis(void* a);
int employee_paisAsignacionSinVacunar(void* a);

int menuErrores(int retorno, char* errorNegativo, char* error0, char* error1, char* error2, char* error3, char* error4, char* error5);
char* ingresarPath(char* path);

#endif // employee_H_INCLUDED

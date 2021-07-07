#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_mostrarEmpleado(Employee* emp);
int employee_buscarMayorId(LinkedList* pArrayListEmployee, int* id);

Employee* employee_buscarId(LinkedList* pArrayListEmployee, int tam, int id);

int employee_menuModificar(Employee* empleado);
Employee* employee_pedirIdyMostrar(LinkedList* pArrayListEmployee, int* indice);

int employee_empleadoCmpSueldo(void* a, void* b);
int employee_empleadoCmpHsTrab(void* a, void* b);
int employee_empleadoCmpNombre(void* a, void* b);

int menuErrores(int retorno, char* errorNegativo, char* error0, char* error1, char* error2, char* error3, char* error4, char* error5);
char* ingresarPath(char* path);

#endif // employee_H_INCLUDED

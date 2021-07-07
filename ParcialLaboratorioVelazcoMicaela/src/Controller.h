int controller_loadFromText(char* path , LinkedList* pArrayListEmployee,int* idNext);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee, int* idNext);
int controller_addEmployee(LinkedList* pArrayListEmployee, int* id);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee, LinkedList* pArrayListEmployeeBaja);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_MapEmployee(LinkedList* pArrayListEmployee);
int controller_filterEmployee(LinkedList* pArrayListEmployee);
int controller_filterHorno(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);



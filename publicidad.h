


int publicidad_init(ePublicidad* array, int tam);
int publicidad_alta(ePublicidad* array,int tam, int idpantalla);
int publicidad_modificacion(ePublicidad* array,int tam, char* cuit, int id);
int publicidad_baja(ePublicidad* array,int tam, char* cuit, int id);
int publicidad_mostrar(ePublicidad* array,int tam, ePantalla* array2, int tam2, char* cuit);
int publicidad_ordenar(ePublicidad* array,int tam, int orden);
int publicidad_buscar(ePublicidad* array,int tam, char* cuit, int id);
int publicidad_baja_pantalla(ePublicidad* array,int tam, int id);


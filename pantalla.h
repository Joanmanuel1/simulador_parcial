
typedef struct
{
    int   id;
    char  nombre[51];
    char  direccion[51];
    float precio;
    int   tipo;
    int   isEmpty;
}ePantalla;

typedef struct
{
    char  cuit[12];
    char  archivo[13];
    int   idpantalla;
    int   dias;
    int   isEmpty;
}ePublicidad;

int pantalla_init(ePantalla* array, int tam);
int pantalla_alta(ePantalla* array,int tam);
int pantalla_modificacion(ePantalla* array,int tam, int id);
int pantalla_baja(ePantalla* array,int tam, int id, ePublicidad* array2, int tam2);
int pantalla_ordenar(ePantalla* array,int tam, int orden);
int pantalla_buscarPorId(ePantalla* array,int tam, int id);

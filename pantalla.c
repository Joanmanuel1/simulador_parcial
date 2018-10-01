#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantalla.h"
#include "publicidad.h"
#include "utn.h"

int buscarLugarLibre(ePantalla* array,int tam);
static int proximoId();

/**
 * \brief Inicializa el array de pantallas
 * \param array de pantallas
 * \param cantidad de elementos
 * \return codigo de retorno
*/
int pantalla_init(ePantalla* array, int tam)
{
    int retorno = -1;
    int i;
    if(tam > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0; i<tam; i++)
        {
            array[i].isEmpty = 0;
        }
    }
    return retorno;
}
/**
 * \brief Busca lugar libre en array de pantallas
 * \param array de pantallas
 * \param cantidad de elementos
 * \return codigo de retorno
*/
int buscarLugarLibre(ePantalla* array,int tam)
{
    int retorno = -1;
    int i;
    if(tam > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 0)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief Alta de una pantalla en el array, solicita datos de la pantalla
 * \param array de pantallas
 * \param cantidad de elementos
 * \return codigo de retorno
*/
int pantalla_alta(ePantalla* array,int tam)
{
    int retorno = -1;

    int   id;
    char  nombre[50];
    char  direccion[50];
    float precio;
    int   tipo;

    int indice = buscarLugarLibre(array,tam);

    system("cls");
    printf("Alta de pantalla\n\n");

    if(tam > 0 && array != NULL)
    {
        retorno = -2;

        if(indice >= 0)
        {
            id = proximoId();
            retorno = -3;
            if(!getValidString("Nombre Pantalla  : ","Dato ingresado erroneo\n","Overflow", nombre,50,2))
            {
            if(!getValidString("Direccion        : ","Dato ingresado erroneo\n","Overflow", direccion,50,2))
                {
             if(!getValidFloat("Precio           : ","Dato ingresado erroneo\n",&precio,1,99999,2))
                    {
               if(!getValidInt("Tipo: 1-LED/2-LCD: ","Dato ingresado erroneo\n",&tipo,1,2,2))
                        {
                            retorno = 0;
                            strcpy(array[indice].nombre,nombre);
                            strcpy(array[indice].direccion,direccion);
                            array[indice].precio=precio;
                            array[indice].tipo=tipo;
                            array[indice].id = id;
                            array[indice].isEmpty = 1;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

/**
 * \brief Modificacion de una pantalla en el array, solicita datos de la pantalla
 * \param array de pantallas
 * \param cantidad de elementos
 * \param id de la pantalla a modificar
 * \return codigo de retorno
*/
int pantalla_modificacion(ePantalla* array,int tam, int id)
{
    int retorno = -1;

    char  nombre[50];
    char  direccion[50];
    float precio;
    int   tipo;
    system("cls");
    printf("Modificacion de pantalla\n\n");

    int indice = pantalla_buscarPorId(array,tam,id);
    if(indice >= 0)
    {
            retorno = -2;
            if(!getValidString("Nombre Pantalla  : ","Dato ingresado erroneo\n","Overflow", nombre,50,2))
            {
            if(!getValidString("Direccion        : ","Dato ingresado erroneo\n","Overflow", direccion,50,2))
              {
            if(!getValidFloat("Precio            : ","Dato ingresado erroneo\n",&precio,1,99999,2))
                    {
              if(!getValidInt("Tipo: 1-LED/2-LCD : ","Dato ingresado erroneo\n",&tipo,1,2,2))
                    {
                        retorno = 0;
                        strcpy(array[indice].nombre,nombre);
                        strcpy(array[indice].direccion,direccion);
                        array[indice].precio=precio;
                        array[indice].tipo=tipo;
                    }
                }
            }
        }
    }
  return retorno;
}

/**
 * \brief Baja de una pantalla y sus publicaciones
 * \param array de pantallas
 * \param cantidad de pantallas
 * \param id de la pantalla a dar de baja
 * \param array de publicaciones
 * \param cantidad de publicaciones
 * \return codigo de retorno
*/
int pantalla_baja(ePantalla* array,int tam, int id, ePublicidad* array2, int tam2)
{

    int retorno = -1;
    int indice;
    indice = pantalla_buscarPorId(array,tam,id);
    if(indice >= 0)
    {
        retorno = 0;
        array[indice].isEmpty = 0;
       // da de baja las publicaciones que incluyan esta pantalla
        publicidad_baja_pantalla(array2, tam2, id);
    }
    return retorno;
}

/**
 * \brief ordena array de pantallas
 * \param array de pantallas
 * \param cantidad de pantallas
 * \param orden 0-asc 1-desc
 * \return codigo de retorno
*/
int pantalla_ordenar(ePantalla* array,int tam, int orden)
{
    int retorno = -1;
    int flagSwap;
    int i;
    ePantalla auxiliar;

    if(tam > 0 && array != NULL)
    {
        retorno = 0;
        do
        {
            flagSwap = 0;
            for(i=0; i<tam-1; i++)
            {
                if(array[i].isEmpty == 1 && array[i+1].isEmpty == 1 )
                {
                    if((strcmp(array[i].nombre,array[i+1].nombre) > 0 && !orden) || (strcmp(array[i].nombre,array[i+1].nombre) < 0 && orden)) //<------------
                    {
                        auxiliar = array[i];
                        array[i] = array[i+1];
                        array[i+1] = auxiliar;
                        flagSwap = 1;
                    }
                }
            }
        }
        while(flagSwap);
    }

    return retorno;
}

/**
 * \brief busca pantalla por id
 * \param array de pantallas
 * \param cantidad de pantallas
 * \param id de la pantalla
 * \return codigo de retorno
*/
int pantalla_buscarPorId(ePantalla* array,int tam, int id)
{
    int retorno = -1;
    int i;
    if(array > 0 && array != NULL)
    {
        retorno = -2;

        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1 && array[i].id == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief calcula proximo id de pantalla
 * \return proximo id
*/
static int proximoId()
{
    static int ultimoId = 0;
    ultimoId++;
    return ultimoId;
}
/**
 *\brief Lista todas las pantallas o una pantalla segun id recibido por parametro
 *\param  array de pantallas
 *\param  cantidad de pantallas
 *\return  codigo de retorno
*/
int pantalla_mostrar(ePantalla* array,int tam, int id, int todo)
{
    int retorno = -1;
    int i;
    char tipop[10];

    printf("============================================================== \n");
    printf("Id  Nombre        Direccion        Precio          Tipo        \n");
    printf("============================================================== ");


    if(tam > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1)
            {
                if(todo==1 || array[i].id==id) {
                    if(array[i].tipo==1) { strcpy(tipop, "LCD"); }
                    if(array[i].tipo==2) { strcpy(tipop, "LED"); }
                   // Id pantalla Nombre Direccion Precio Tipo
                    printf("\n %3d  %-15s %-15s  %10.2f      %1d  %-5s", array[i].id, array[i].nombre, array[i].direccion, array[i].precio, array[i].tipo, tipop);
                }

            }
        }
    }
    printf("\n");
    return retorno;
}


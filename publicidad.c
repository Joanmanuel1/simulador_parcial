#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantalla.h"
#include "publicidad.h"
#include "informes.h"
#include "utn.h"

static int buscarLugarLibre2(ePublicidad* array,int tam);

/**
 *\brief Inicializa el array de publicidades
 *\param Array de publicidades
 *\param cantidad de publicidades
 *\param Retorno
*/
int publicidad_init(ePublicidad* array, int tam)
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
 * \brief Busca un lugar libre en array de publicidades
 * \param  Array de publicidades
 * \param  cantidad de publicidades
 * \return  Retorno
*/
static int buscarLugarLibre2(ePublicidad* array,int tam)
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
 * \param Alta de una publicidad, solicita los datos de la publicacion
 * \param Array de publicidades
 * \param cantidad de publicidades
 * \param Ide de la pantalla donde se publicara
 * \return Retorno
*/
int publicidad_alta(ePublicidad* array,int tam, int idpantalla)
{
    int retorno = -1;

    char cuit[12];
    char  archivo[51];
    int   dias;

    int indice = buscarLugarLibre2(array,tam);
    if(tam > 0 && array != NULL)
    {
        retorno = -2;
        if(indice >= 0)
        {
            retorno = -3;
            if(!getValidDni("Cuit                   : ","Dato ingresado erroneo\n","El CUIT supera los 11 caracteres\n", cuit,2))
            {
         if(!getValidString("Archivo a publicar     : ","Dato ingresado erroneo\n","Overflow", archivo,50,2))
                {
            if(!getValidInt("Dias de la publicacion : ","Dato ingresado erroneo\n",&dias,1,31,2))
                    {
                            retorno = 0;
                            strcpy(array[indice].cuit,cuit);
                            strcpy(array[indice].archivo,archivo);
                            array[indice].dias=dias;
                            array[indice].idpantalla=idpantalla;
                            array[indice].isEmpty = 1;
                    }
                }
            }
        }
    }
    return retorno;
}

/**
 * \brief Modifica dias de la publicacion para el cuit/id pantalla
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Cuit del cliente
 * \param Id de la pantalla
 * \return retorno
*/
int publicidad_modificacion(ePublicidad* array,int tam, char* cuit, int id)
{
    int retorno = -1;
    int   dias;

    int indice = publicidad_buscar(array, tam, cuit, id);
    if(indice >= 0)
    {
            retorno = -2;
            if(!getValidInt("Dias             : ","Dato ingresado erroneo\n",&dias,1,31,2))
            {
                retorno = 0;
                array[indice].dias=dias;
            }
    }
   return retorno;
}

/**
 * \brief Baja de la publicacion para el cuit/id pantalla
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Cuit del cliente
 * \param id de la pantalla
 * \return retorno
*/
int publicidad_baja(ePublicidad* array,int tam, char* cuit, int id)
{
    int retorno = -1;

    int indice = publicidad_buscar(array, tam, cuit, id);
    if(indice >= 0)
    {
           retorno = 0;
           array[indice].isEmpty = 0;
    }
    return retorno;
}

/**
 * \brief Lista publicaciones
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Array de pantallas
 * \param Cantidad de pantallas
 * \return retorno
*/
int publicidad_mostrar(ePublicidad* array,int tam, ePantalla* array2, int tam2, char* cuit)
{
    int retorno = -1;
    int i;
    int i2;
    printf("=====================================================\n");
    printf("\nCuit         Archivo    Dias     Nombre          id\n");
    printf("=====================================================");

    if(tam > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1)
            {
               if(strcmp(array[i].cuit,cuit)==0) {
                i2=pantalla_buscarPorId(array2,tam2, array[i].idpantalla);
                // cuit archivo dias pantalla id
                printf("\n%-11s  %-12s  %2d  %-15s %3d ",array[i].cuit, array[i].archivo, array[i].dias, array2[i2].nombre, array2[i2].id);
              }
            }
        }
    }
    printf("\n");
    return retorno;

}

/**
 * \brief ordena array de publicaciones
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param orden 0-asc 1-desc
 * \return retorno
*/
int publicidad_ordenar(ePublicidad* array,int tam, int orden)
{
    int retorno = -1;
    int flagSwap;
    int i;
    ePublicidad auxiliar;

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
                    if((strcmp(array[i].cuit, array[i+1].cuit)> 0 && !orden) || (strcmp(array[i].cuit, array[i+1].cuit) < 0 && orden)) //<------------
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
 * \brief Busca la publicidad por Cuit/id pantalla
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Cuit del cliente
 * \param id de pantalla
 * \return retorno
*/
int publicidad_buscar(ePublicidad* array,int tam, char* cuit, int id)
{
    int retorno = -1;
    int i;
    if(array > 0 && array != NULL)
    {
        retorno = -2;

        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1  && strcmp(array[i].cuit,cuit)==0 && array[i].idpantalla == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief Da de baja las publicaciones con la pantalla recibida por parametro
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param id de la pantalla
 * \return retorno
*/
int publicidad_baja_pantalla(ePublicidad* array,int tam, int id)
{
    int retorno = -1;
    int i;
    for(i=0; i<tam; i++)
    {
        if(array[i].isEmpty == 1)
        {
            if(array[i].idpantalla == id)
            {
                array[i].isEmpty = 0;
            }
        }
    }
    return retorno;
}


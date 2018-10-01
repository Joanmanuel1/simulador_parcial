#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantalla.h"
#include "publicidad.h"
#include "utn.h"


/**
 * \brief Se listan las contrataciones indicando nombre de la pantalla, nombre de video, cantidad de días y cuit de cliente.
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Array de pantallas
 * \param Cantidad de pantallas
 * \return retorno
*/

int publicidad_mostrarcontrataciones(ePublicidad* array,int tam, ePantalla* array2,int tam2)
{
    int retorno = -1;
    int i;
    int i2;
    printf("====================================================\n");
    printf("Pantalla         Archivo     Dias  Cuit             \n");
    printf("====================================================");

    if(tam > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1)
            {
               i2=pantalla_buscarPorId(array2,tam2, array[i].idpantalla);
               // Pantalla         Archivo     Dias  Cuit
               printf("\n%-15s %-15s %2d %-12s ", array2[i2].nombre, array[i].archivo, array[i].dias, array[i].cuit);
            }
        }
    }
    printf("\n");
    return retorno;

}

/**
 * \brief Lista facturacion de  un cliente y se deberá listar el importe a pagar por cada contratación
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Array de pantallas
 * \param Cantidad de pantallas
 * \param Cuit del cliente
 * \return retorno
*/
int publicidad_mostrarfacturacion(ePublicidad* array,int tam, ePantalla* array2,int tam2, char* cuit)
{
    int retorno = -1;
    int i;
    int i2;
    float importe;
    printf("======================================================================== \n");
    printf("Cuit         Archivo    Dias     Id  Pantalla            Importe         \n");
    printf("========================================================================");
    if(tam > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1)
            {
                if(strcmp(array[i].cuit,cuit)==0)
                {
                   i2=pantalla_buscarPorId(array2,tam2, array[i].idpantalla);
                   importe=array2[i2].precio * array[i].dias;  // calcula precio de publicacion * cantidad de dias publicados
                   printf("\n%-11s %-15s %2d  %3d  %-15s %10.2f",array[i].cuit, array[i].archivo, array[i].dias, array[i].idpantalla, array2[i2].nombre, importe);
                }
            }
        }
    }
    printf("\n");
    return retorno;

}


/**
 * \brief Lista cada cliente con cantidad de contrataciones e importe a pagar por cada una y calcula Cliente con importe más alto a facturar
 * \param Array de publicaciones
 * \param Cantidad de publicaciones
 * \param Array de pantallas
 * \param Cantidad de pantallas
 * \return retorno
*/

int publicidad_informe(ePublicidad* array,int tam, ePantalla* array2,int tam2)
{

    int retorno = -1;
    int i;
    int i2;
    float importe=0;
    float maximporte=0;
    char maxcuit[12];

    if(tam > 0 && array != NULL)
    {

        retorno = 0;
        printf("========================================================== \n");
        printf("Cuit           Contrataciones      Total a pagar           \n");
        printf("========================================================== ");
        for(i=0; i<tam; i++)
        {
            if(array[i].isEmpty == 1)
            {
               i2=pantalla_buscarPorId(array2,tam2, array[i].idpantalla);
               importe=array2[i2].precio * array[i].dias;  // calcula precio de publicacion * cantidad de dias publicados
               // Cuit           Contrataciones      Total a pagar
               printf("\n%-11s %3d %10.2f ", array[i].cuit, array[i].dias, importe);
               if(importe > maximporte) {
                   maximporte=importe;
                   strcpy(maxcuit, array[i].cuit);
               }
            }
        }
        printf("\n\nCliente con maxima facturacion: %11s \nTotal facturado: %10.2f", maxcuit, maximporte);
        printf("\n");
    }
    return retorno;
}

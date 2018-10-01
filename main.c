#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "utn.h"
#include "pantalla.h"
#include "publicidad.h"
#include "informes.h"

#define LCD  1
#define LED  2
#define MAX_PANTALLAS 100
#define MAX_PUBLICACIONES 1000

int MenuSistema();

/**
 *    Este programa permite comercializar espacios publicitarios, los cuales estarán integrados
 *    por dos tipos de dispositivos:
 *
 *        1. Pantallas LCD - Ubicados en paseos comerciales
 *        2. Pantallas Gigantes Led - Ubicadas en la vía pública
 *
 *    En el sistema existen pantallas del tipo Led o LCD , las cuales se registran mediante
 *    nombre, dirección y precio de la publicidad en dicha pantalla por cada día de publicación.
 *
 *    La plataforma permite vender a un cliente la publicación de un video publicitario en una
 *    pantalla determinada.
 *
 *    Menu:
 *
 *    1) Alta de pantalla: Se solicita al usuario los datos de la pantalla, para que el sistema
 *    pueda funcionar se deberá generar un ID único para cada pantalla.
 *
 *    2) Modificar datos de pantalla: Se ingresa el ID de la pantalla, permitiendo modificar sus
 *    datos.
 *
 *    3) Baja de pantalla: Se ingresa el ID de la pantalla, se eliminará la pantalla junto con todas
 *    las contrataciones de publicidad para esta pantalla.
 *
 *    4) Contratar una publicidad: Se listaran todas las pantallas y se le pedirá al usuario que
 *    elija la pantalla donde se quiere publicar, ingresando su ID. Luego se pedirán los datos
 *    asociados a la publicidad: auxiliarCuit del cliente, cantidad de días que dura la publicación y
 *    nombre del archivo de video (p.ej. Video1.avi).
 *
 *    5) Modificar condiciones de publicación: Se pedirá que se ingrese el auxiliarCuit del cliente y se
 *    listaran todas las pantallas de video que el cliente tiene contratadas mostrando todos sus
 *    campos. Luego de ingresar el ID de la pantalla, se permitirá modificar la cantidad de días
 *    contratados para la misma.
 *
 *    6) Cancelar contratación: Se pedirá que se ingrese el auxiliarCuit del cliente y se listaran todas las
 *    pantallas de video que el cliente tiene contratadas mostrando todos sus campos. Luego
 *    ingresar el ID de la pantalla de la cual se quiere cancelar la contratación.
 *
 *    7) Consulta facturación: Se deberá ingresar el auxiliarCuit del cliente y se deberá listar el importe
 *    a pagar por cada contratación.
 *
 *    8) Listar contrataciones: Se deberán listar las contrataciones indicando nombre de la
 *    pantalla, nombre de video, cantidad de días y auxiliarCuit de cliente.
 *
 *    9) Listar pantallas: Se deberán listar las pantallas existentes indicando todos sus campos.
 *
 *    10) Informes:
 *      1. Lista de cada cliente con cantidad de contrataciones e importe a pagar por cada una.
 *      2. Cliente con importe más alto a facturar (si hay más de uno indicar el primero)
 *
*/

int main()
{
    int   menu;
    int   auxiliarId;
    char  auxiliarCuit[12];
    int   ret;

    ePantalla arrayPantallas[MAX_PANTALLAS];
    ePublicidad arrayPublicidad[MAX_PUBLICACIONES];

    pantalla_init(arrayPantallas, MAX_PANTALLAS);
    publicidad_init(arrayPublicidad, MAX_PUBLICACIONES);


    do
    {
        menu=MenuSistema();
        switch (menu)
             {
            // alta de pantalla
            case 1:
                system("cls");
                printf("Alta de pantalla\n\n");
                pantalla_alta(arrayPantallas, MAX_PANTALLAS);
                break;
            // Modificar pantalla

            case 2:
                system("cls");
                printf("Modificacion de pantalla\n\n");
                getValidInt("\nID pantalla     : ","\nnumero invalido\n",&auxiliarId,1,MAX_PANTALLAS,2);
                ret=pantalla_modificacion(arrayPantallas, MAX_PANTALLAS, auxiliarId);
                if(ret!=0) {
                    printf("\nId de pantalla no existe\n");
                }
                break;

            // Baja de pantalla
            case 3:
                system("cls");
                printf("Baja de pantalla\n\n");
                getValidInt("\nID pantalla  :  ","\nnumero invalido\n",&auxiliarId,1,MAX_PANTALLAS,2);
                ret=pantalla_baja(arrayPantallas, MAX_PANTALLAS, auxiliarId, arrayPublicidad, MAX_PUBLICACIONES);
                if(ret!=0) {
                    printf("\nId de pantalla no existe\n");
                }
                break;

            // contratar publicidad
            case 4:
                system("cls");
                printf("Alta de publicidad\n\n");
                ret=pantalla_mostrar(arrayPantallas, MAX_PANTALLAS, 0, 1);
                if(ret==0) {
                    getValidInt("\nID pantalla            : ","\nnumero invalido\n",&auxiliarId,0,MAX_PANTALLAS,2);
                    if(pantalla_buscarPorId(arrayPantallas,MAX_PANTALLAS,auxiliarId)>=0)
                    {
                        ret=publicidad_alta(arrayPublicidad, MAX_PUBLICACIONES, auxiliarId);
                        if(ret!=0) {
                            printf("\nNo se pudo realizar la publicacion de la pantalla\n");
                        }
                    }
                    else
                    {
                         printf("\nLa pantalla ingresada no existe\n");
                    }
                }
                else
                {
                    printf("\nNo hay pantallas para publicaciones\n");
                }
                break;

            // Modificar condiciones
            case 5:
                system("cls");
                printf("Modificar condiciones\n\n");
                getValidDni("\nCuit             : ","Dato ingresado erroneo\n","El CUIT supera los 11 caracteres\n", auxiliarCuit,2);
                ret=publicidad_mostrar(arrayPublicidad, MAX_PUBLICACIONES, arrayPantallas, MAX_PANTALLAS, auxiliarCuit);
                getValidInt("\nID pantalla      : ","\nnumero invalido\n",&auxiliarId,0,MAX_PANTALLAS,2);
                if(publicidad_buscar(arrayPublicidad, MAX_PUBLICACIONES, auxiliarCuit, auxiliarId)>=0) {
                  ret=publicidad_modificacion(arrayPublicidad,MAX_PUBLICACIONES, auxiliarCuit, auxiliarId);
                }
                else
                {
                  printf("\nEl cliente no publicaciones\n");
                }
                break;

            // cancelar contratacion
            case 6:
                system("cls");
                printf("Cancelar contratacion\n\n");
                getValidDni("\nCuit              : ","Dato ingresado erroneo\n","El CUIT supera los 11 caracteres\n", auxiliarCuit,2);
                ret=publicidad_mostrar(arrayPublicidad, MAX_PUBLICACIONES, arrayPantallas, MAX_PANTALLAS, auxiliarCuit);
                getValidInt("\nID pantalla       : ","\nnumero invalido\n",&auxiliarId,0,MAX_PANTALLAS,2);
                if(publicidad_buscar(arrayPublicidad, MAX_PUBLICACIONES, auxiliarCuit, auxiliarId)>=0) {
                  ret=publicidad_baja(arrayPublicidad,MAX_PUBLICACIONES, auxiliarCuit, auxiliarId);
                }
                else
                {
                  printf("\nEl cliente no publicaciones\n");
                }
                break;

            // Consultar facturacion
            case 7:
                system("cls");
                printf("Consulta facturacion\n\n");
                getValidDni("\nCuit : ","Dato ingresado erroneo\n","El CUIT supera los 11 caracteres\n", auxiliarCuit,2);
                ret=publicidad_mostrarfacturacion(arrayPublicidad, MAX_PUBLICACIONES, arrayPantallas, MAX_PANTALLAS, auxiliarCuit);
                if(ret!=0) {
                    printf("\nEl Cliente no tiene pantallas publicadas\n");
                }
                break;


            // listar contrataciones
            case 8:
                system("cls");
                printf("Contrataciones\n\n");
                publicidad_mostrarcontrataciones(arrayPublicidad, MAX_PUBLICACIONES, arrayPantallas, MAX_PANTALLAS);
                break;

            // listar pantallas
            case 9:
                system("cls");
                printf("Pantallas\n\n");
                pantalla_ordenar(arrayPantallas, MAX_PANTALLAS,0);  // ordena pantallas por nombre
                ret=pantalla_mostrar(arrayPantallas,MAX_PANTALLAS, 0, 1);  // muestra todas las pantallas
                if(ret!=0) {
                    printf("\nNo hay pantallas para listar\n");
                }
                break;

            // informes
            case 10:
                system("cls");
                printf("Informe\n\n");
                publicidad_ordenar(arrayPublicidad,MAX_PUBLICACIONES,0);
                publicidad_informe(arrayPublicidad,MAX_PUBLICACIONES, arrayPantallas, MAX_PANTALLAS);
                break;
        }
        printf("\n\n");
        system("pause");
        system("cls");
    }while(menu != 11);

    return 0;
}

int MenuSistema() {
    int menu=0;

        printf(" 1- Alta de pantalla\n");
        printf(" 2- Modificar datos de pantalla\n");
        printf(" 3- Borrar Pantalla\n");
        printf(" 4- Contratar publicidad\n");
        printf(" 5- Modificar condiciones de publicacion\n");
        printf(" 6- Cancelar contratacion\n");
        printf(" 7- Consultar Facturacion\n");
        printf(" 8- Listar contrataciones\n");
        printf(" 9- Listar pantallas\n");
        printf("10- Informar\n");
        printf("11- Salir\n");
        getValidInt("\nIngrese opcion:","Opcion ingresada incorrecta\n",&menu,1,11,2);
        return menu;
}


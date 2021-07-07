#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "paises.h"
#include "LinkedList.h"

/****************************************************
    Menu:
1) Cargar archivo: Se pedir� el nombre del archivo y se cargar� en un linkedlist los elementos del mismo.
2) Imprimir lista: Se imprimir� por pantalla la tabla con los datos de los pa�ses.
3) Asignar estad�sticas: Se deber� hacer uso de la funci�n map. la cual recibir� el linkedlist y
 una funci�n que asignar� a cada pa�s un valor de vacunados con una dosis (entre 1% y 60%),
  vacunados con dos dosis (entre 1% y 40%), ambos asignados de manera aleatoria y porcentaje sin
   vacunar que ser� lo que falte para el 100%.
4) Filtrar por pa�ses exitosos: Se deber� generar un archivo igual al original, pero donde
solo aparezcan pa�ses cuya poblaci�n este vacunada con dos dosis en un porcentaje mayor al 30%.
5) Filtrar por pa�ses en el horno: Se deber� generar un archivo igual al original, pero donde
solo aparezcan pa�ses donde la cantidad de no vacunados sea mayor a la de vacunados.
6) Ordenar por nivel de vacunaci�n: Se deber� mostrar por pantalla un listado de los pa�ses
ordenados por cantidad de vacunados con 1 dosis.
7) Mostrar m�s castigado: Informar el nombre del pa�s o pa�ses con el mayor porcentaje de no vacunados. Y
*****************************************************/






int menu();

int main()
{
    int option = 0;
    char path[128];
    srand(time(NULL));
    LinkedList* listaPaises = ll_newLinkedList();
    LinkedList* listaMapeados = NULL;
    LinkedList* listaFiltrada = NULL;
    do{
        system("cls");
        option = menu();
        switch(option)
        {
            case 1:
                printf("Ingrese Path_");
               fflush(stdin);
               gets(path);
                if(loadFromText(path,listaPaises))
                {
                    printf("Datos cargados con exito!\n");
                }else{
                printf("No se pudieron cargar los datos\n");
                }
                system("pause");
                break;
                case 2:
                    mostrarPaises(listaPaises);
                   system("pause");
                break;
                case 3:
                listaMapeados = ll_map(listaPaises,cargarEstadisticas);
                if(listaMapeados!=NULL)
                {
                    printf("Se cargo de manera exitosa!\n");
                }
                   system("pause");
                break;
                case 4:
                    listaFiltrada =ll_filter(listaPaises,paisesExitosos);
                    mostrarPaises(listaFiltrada);
                    if(guardarArchivoTexto("exitoso.csv",listaFiltrada))
                    {
                        printf("Guardados con exito\n");
                    }
                    system("pause");
                break;
                case 5:
                    listaFiltrada = ll_filter(listaPaises,paisesHorno);
                    mostrarPaises(listaFiltrada);
                    if(guardarArchivoTexto("horno.csv",listaFiltrada))
                    {
                        printf("Guardados con exito\n");
                    }
                    system("pause");
                break;
                case 6:
                    ll_sort(listaPaises,paisesCmpVac1,1);
                    system("pause");
                break;
                case 7:
                    mostrarMasCastigados(listaPaises);
                    system("pause");
                break;
                case 8:
                    ll_deleteLinkedList(listaPaises);
                    ll_deleteLinkedList(listaMapeados);
                    ll_deleteLinkedList(listaFiltrada);
                break;

        }
    }while(option != 8);
    return 0;
}

int menu()
{
     int opcion;
    printf("\t\t***Menu Vacunados***\n\n");
    printf("1. Cargar archivo.\n");
    printf("2. Imprimir lista\n");
    printf("3. Asignar estadisticas\n");
    printf("4. Filtrar por paises exitosos\n");
    printf("5. Filtrar por paises en el horno\n");
    printf("6. Ordenar por nivel de vacunacion\n");
    printf("7. Mostrar mas castigado\n");
    printf("8. Salir\n");
    printf("Ingrese Opcion: ");
    scanf("%d", &opcion);
    while(opcion<0 || opcion>8)
    {
        fflush(stdin);
        printf("Opcion invalida: ");
        scanf("%d", &opcion);
    }
    printf("\n\n");
    return opcion;
}

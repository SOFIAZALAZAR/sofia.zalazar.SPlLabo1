#include "LinkedList.h"


#ifndef PAISES_H_INCLUDED
#define PAISES_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int vac1dosis;
    int vac2dosis;
    int sinVacunar;
}ePais;


#endif // PAISES_H_INCLUDED
ePais* newPais();

ePais* newPaisParam(char* id, char* nombre, char* vac1dosis, char* vac2dosis,char* sinVacunar);
void destroyPais(ePais* p);
// funciones seter
int paisSetId(ePais* e, int id);
int paisSetNombre(ePais*e, char* nombre);
int paisSet1dosis(ePais* e, int vac1dosis);
int paisSet2dosis(ePais* e,int vac2dosis);
int paisSetSinVac(ePais* e,int sinVacunar);
//funciones geter
int paisGetId(ePais* e, int* pId);
int paisGetNombre(ePais*e, char* pNombre);
int paisGet1dosis(ePais* e, int* p1dosis);
int paisGet2dosis(ePais* e,int* p2dosis);
int paisGetSinVac(ePais* e,int* pSinVac);

int mostrarPaises(LinkedList* lista);
int mostrarPais(ePais* p);

int loadFromText(char* path , LinkedList* pArrayPaises);

void* cargarEstadisticas(void*p);
int paisesExitosos(void* p);
int paisesHorno(void* p);
int paisesCmpVac1(void* a,void* b);

int mostrarMasCastigados(LinkedList* lista);
int guardarArchivoTexto(char* path, LinkedList* lista);

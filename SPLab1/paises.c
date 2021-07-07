#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paises.h"
#include "LinkedList.h"


ePais* newPais()
{

    ePais* nuevoPais = (ePais*) malloc(sizeof(ePais));
    if(nuevoPais != NULL)
    {
        nuevoPais->id =0;
        strcpy(nuevoPais->nombre," ");
        nuevoPais->vac1dosis= 0;
        nuevoPais->vac2dosis = 0;
        nuevoPais->sinVacunar = 0;
    }
    return nuevoPais;
}

ePais* newPaisParam(char* id, char* nombre, char* vac1dosis, char* vac2dosis,char* sinVacunar)
{
    ePais* nuevoPais = newPais();
    if(nuevoPais != NULL)
    {
        if(!(paisSetId(nuevoPais,atoi(id))&&
                paisSetNombre(nuevoPais,nombre)&&
                paisSet1dosis(nuevoPais,atoi(vac1dosis))&&
                paisSet2dosis(nuevoPais,atoi(vac2dosis))&&
            paisSetSinVac(nuevoPais,atoi(sinVacunar)))
          )
        {
            destroyPais(nuevoPais);
            nuevoPais = NULL;
        }

    }

    return nuevoPais;

}
void destroyPais(ePais* p)
{
    free(p);
}
// funciones seter
int paisSetId(ePais* e, int id)
{
    int todoOk = 0;
    if(e!=NULL && id>0)
    {
        e->id = id;
        todoOk = 1;
    }

    return todoOk;

}
int paisSetNombre(ePais*e, char* nombre)
{
    int todoOk = 0;
    if(e!=NULL && nombre!=NULL && strlen(nombre)<128)
    {
        strcpy(e->nombre,nombre);
        todoOk = 1;
    }

    return todoOk;
}
int paisSet1dosis(ePais* e, int vac1dosis)
 {
     int todoOk = 0;
    if(e!=NULL && vac1dosis>=0 && vac1dosis<=60)
    {
        e->vac1dosis = vac1dosis;
        todoOk = 1;
    }

    return todoOk;
 }
int paisSet2dosis(ePais* e,int vac2dosis)
{
     int todoOk = 0;
    if(e!=NULL && vac2dosis>=0 && vac2dosis<=40)
    {
        e->vac2dosis = vac2dosis;
        todoOk = 1;
    }

    return todoOk;
}
int paisSetSinVac(ePais* e,int sinVacunar)
{
    int todoOk = 0;
    if(e!=NULL && sinVacunar>=0 && sinVacunar<=100)
    {
        e->sinVacunar = sinVacunar;
        todoOk = 1;
    }

    return todoOk;
}
//funciones geter
int paisGetId(ePais* e, int* pId)
{
  int todoOk =0;

    if(e!=NULL && pId !=NULL)
    {
        *pId = e->id;
        todoOk = 1;

    }
    return todoOk;
}
int paisGetNombre(ePais*e, char* pNombre)
{
    int todoOk=0;
    if(e!=NULL && pNombre != NULL)
    {
        strcpy(pNombre,e->nombre);
        todoOk = 1;
    }
    return todoOk;

}
int paisGet1dosis(ePais* e, int* p1dosis)
{
  int todoOk =0;

    if(e!=NULL && p1dosis !=NULL)
    {
        *p1dosis = e->vac1dosis;
        todoOk = 1;

    }
    return todoOk;

}
int paisGet2dosis(ePais* e,int* p2dosis)
{
 int todoOk =0;

    if(e!=NULL && p2dosis !=NULL)
    {
        *p2dosis = e->vac2dosis;
        todoOk = 1;

    }
    return todoOk;
}
int paisGetSinVac(ePais* e,int* pSinVac)
{
   int todoOk =0;

    if(e!=NULL && pSinVac !=NULL)
    {
        *pSinVac = e->sinVacunar;
        todoOk = 1;

    }
    return todoOk;
}
int mostrarPaises(LinkedList* lista)
{

    int todoOk = 0;
    ePais* auxPais = NULL;
    if(lista != NULL)
    {
        printf(" id | nombre | vac1dosis | vac2dosis | sinVacunar\n");
        for(int i=0; i<ll_len(lista); i++)
        {
         auxPais =(ePais*)ll_get(lista,i);
         mostrarPais(auxPais);
        }
        printf("\n\n");
        todoOk = 1;
    }

    return todoOk;
}
int mostrarPais(ePais* p)
{

    int todoOk = 0;
    int id;
    char nombre[20];
    int vac1dosis;
    int vac2dosis;
    int sinVacunar;
    if(p!=NULL
            &&  paisGetId(p,&id)
            && paisGetNombre(p,nombre)
            && paisGet1dosis(p, &vac1dosis)
            && paisGet2dosis(p,&vac2dosis)
            && paisGetSinVac(p,&sinVacunar)
      )
    {
        printf("%d %10s     %d     %d      %d\n"
               ,p->id
               ,p->nombre
               ,p->vac1dosis
               ,p->vac2dosis
               ,p->sinVacunar);
        todoOk = 1;
    }
    return todoOk;


}


int loadFromText(char* path , LinkedList* pArrayPaises)
{
    int todoOk =0;
    char buffer[5][100];
    int cant;
    ePais* auxPais = NULL;
    if(path!=NULL && pArrayPaises!=NULL)
    {
        FILE* f = fopen(path, "r");
        if(f == NULL)
        {
            printf("no se pudo abrir el archivo");
            exit(1);
        }
      todoOk = 1;
     fscanf(f,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3],buffer[4]);
     while(!feof(f))
    {
      cant = fscanf(f,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3],buffer[4]);
      if(cant ==5)
      {
        auxPais = newPaisParam( buffer[0], buffer[1], buffer[2], buffer[3],buffer[4]);
        if(auxPais!=NULL)
        {
          ll_add(pArrayPaises,auxPais);
        }else{
            destroyPais(auxPais);
            ll_deleteLinkedList(pArrayPaises);
            todoOk = 0;
            break;
        }
      }
    }
            fclose(f);


    }

    return todoOk;
}

void* cargarEstadisticas(void*p)
{
  void* aux = NULL;
 ePais* auxP= NULL;
  int sinVac = 100;
  int doc1;
  int doc2;
  int min = 1;
  int max1 = 60;
 int max2 = 40;
  if(p!=NULL)
  {
      auxP = (ePais*)p;
      if(auxP!=NULL)
      {
        doc1 = rand() % (max1 - min + 1) + min;
      paisSet1dosis(auxP,doc1);
      doc2 = rand() % (max2 - min + 1) + min;
      paisSet2dosis(auxP,doc2);
      sinVac = sinVac - auxP->vac1dosis - auxP->vac2dosis;
      paisSetSinVac(auxP,sinVac);
      aux = auxP;
      }

  }

   return aux;
}

int paisesExitosos(void* p)
{
    int todoOk=0;
    ePais* aux = NULL;
    if(p!=NULL)
    {
        aux = (ePais*)p;
        if(aux->vac2dosis >=30)
        {
            todoOk = 1;
        }
    }
    return todoOk;
}
int paisesHorno(void* p)
{
    int todoOk=0;
    ePais* aux = NULL;
    if(p!=NULL)
    {
        aux = (ePais*)p;
        if(aux->sinVacunar > (aux->vac2dosis + aux->vac1dosis))
        {
            todoOk = 1;
        }
    }
    return todoOk;
}

int paisesCmpVac1(void* a,void* b)
{
    int retorno=0;
    ePais* pais1;
    ePais* pais2;
    if(a!=NULL && b!=NULL)
    {
        pais1 = (ePais*) a;
        pais2 = (ePais*) b;

        if(pais1->vac1dosis > pais2->vac1dosis)
        {
            retorno=1;
        }
        else if(pais1->vac1dosis < pais2->vac1dosis)
        {
            retorno= -1;
        }
    }
    return retorno;
}

int mostrarMasCastigados(LinkedList* lista)
{
   int todoOk=0;
   ePais* aux=NULL;
   int cant = 0;
   if(lista!=NULL)
   {
       for(int i=0; i<ll_len(lista);i++)
       {
          aux = (ePais*)ll_get(lista,i);
          if(aux->sinVacunar > 50)
          {
              mostrarPais(aux);
              cant++;
          }
       }
       todoOk=1;
       printf("Cantidad: %d\n",cant);

   }
    return todoOk;
}

int guardarArchivoTexto(char* path, LinkedList* lista)
{
    int todoOk=0;
    char confirma;
    int cant;
    ePais* aux=NULL;
    if(path!=NULL && lista!=NULL)
    {
        FILE* f;
        if((f=fopen(path,"r"))!=NULL)
        {
            printf("Cuidado se van a sobreescribir los datos\n");
            printf("Desea continuar?: \n");
            fflush(stdin);
            scanf("%c", &confirma);
        }
        if(f==NULL || confirma == 's')
        {
            f = fopen(path,"w");
            if(f == NULL)
            {
                printf("No se pudo abrir el archivo\n");
                exit(1);
            }
            fprintf(f,"id, nombre, vac1dosis, vac2dosis, sinVacunar\n");
            for(int i=0; i<ll_len(lista); i++)
            {
                aux = (ePais*)ll_get(lista,i);
                cant = fprintf(f,"%d,%s,%d,%d,%d\n"
                               ,aux->id
                               ,aux->nombre
                               ,aux->vac1dosis
                               ,aux->vac2dosis
                               ,aux->sinVacunar
                              );
                if(cant !=0)
                {
                    todoOk = 1;
                }

            }

        }
           fclose(f);
 }
        return todoOk;
}

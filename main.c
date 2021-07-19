#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define archivo "pedidos.bin"

typedef struct
{
    char material[20];
    float peso;

}cajon;

typedef struct
{
   float pesoIngresado;
   struct nodoVagon * sig;

}nodoVagon;

typedef struct
{
   int nroTren;
   char categoria[20];
   nodoVagon * listaVagones;

}tren;

typedef struct
{
  char ciudad[20];
  char categoria[20];
  float cantidad;

}Pedido;

nodoVagon * inicLista();
nodoVagon * crearNodoVagon(float peso);
nodoVagon * agregarAlPpio(nodoVagon * lista, nodoVagon * nuevoNodo);
cajon cargarCajon();
int cargarArrgleDeTrenes(tren ADT[]);
int buscarMaterial(tren ADT[], int validos, char aBuscar[]);
nodoVagon * cargarVagones(nodoVagon * lista, cajon nuevo);
int agregarTren(tren ADT[], int validos, cajon nuevo);
int cargarCelda(tren ADT[], int validos, cajon nuevo);
float controlarPeso(nodoVagon * lista);
void imprimirCelda(tren ADT[], int poss);
float pesoPorCategoria(tren ADT[], int validos);
void porcentajeCategoria(tren ADT[], int validos);
void trenMenorCarga(tren ADT[], int validos);
nodoVagon * borrarNodo(nodoVagon * lista, float peso);
nodoVagon * descargarMateriaPrima(nodoVagon * lista, float cantPedida);
void entregarPedidos (tren ADT[], int validos);
nodoVagon * eliminarVagonesVacios(nodoVagon * lista);

int main()
{
    tren ADT[6];

    int validos = cargarArrgleDeTrenes(ADT);

    printf("\nPeso por categoria:\n\n");

    pesoPorCategoria(ADT, validos);

    system("pause");
    system("cls");

    printf("\nPorcentaje:\n\n");

    porcentajeCategoria(ADT, validos);

    system("pause");
    system("cls");

    trenMenorCarga(ADT, validos);

    system("pause");
    system("cls");

    entregarPedidos(ADT, validos);

    return 0;
}

nodoVagon * inicLista()///Inciso 1
{
    return NULL;
}

nodoVagon * crearNodoVagon(float peso)///Inciso 1
{
    nodoVagon * nuevoNodo = (nodoVagon*)malloc(sizeof(nodoVagon));

    nuevoNodo->pesoIngresado = peso;

    nuevoNodo->sig = NULL;

    return nuevoNodo;
}

nodoVagon * agregarAlPpio(nodoVagon * lista, nodoVagon * nuevoNodo)///Inciso 1
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }else
    {
        nuevoNodo->sig = lista;

        lista = nuevoNodo;
    }

    return lista;
}

cajon cargarCajon()///Inciso 1
{
    cajon aux;

    int opcion;

    do
    {
        printf("\nSeleccione el material del cajon:\n\n");
        printf("\t1 - comestible\n");
        printf("\t2 - madera\n");
        printf("\t3 - metal\n");
        printf("\t4 - plastico\n");
        printf("\t5 - vidrio\n");

        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:

            strcpy(aux.material, "Comestible");
            break;

        case 2:

            strcpy(aux.material, "Madera");
            break;
        case 3:

            strcpy(aux.material, "Metal");
            break;
        case 4:

            strcpy(aux.material, "Plastico");
            break;
        case 5:

            strcpy(aux.material, "Vidrio");
            break;
        default:

            printf("\nopcion no valida\n\n");
            break;
        }

    }
    while(opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5);

    printf("\nIngrese el peso que lleva el cajon:\n\n");
    scanf("%f", &aux.peso);

    return aux;

}

int cargarArrgleDeTrenes(tren ADT[])///Inciso 1
{
    int validos = 0;

    char control = 's';

    while(control == 's' || control == 'S')
    {
        cajon nuevo = cargarCajon();

        validos = cargarCelda(ADT, validos, nuevo);

        printf("\nSeguir cargando? (s / n)\n\n");
        fflush(stdin);
        scanf("%c", &control);

        system("cls");
    }

    return validos;
}

int buscarMaterial(tren ADT[], int validos, char aBuscar[])///Inciso 1
{
    int rta = -1;

    for (int i = 0; i<validos; i++)
    {
        if(strcmpi(ADT[i].categoria, aBuscar) == 0)
        {
            rta = i;
        }
    }

    return rta;
}

nodoVagon * cargarVagones(nodoVagon * lista, cajon nuevo)///Inciso 1
{
    if(controlarPeso(lista) < 1400)
    {
        if(nuevo.peso <= 200 && controlarPeso(lista) + nuevo.peso <= 1400)
        {
            nodoVagon * nuevoNodo = crearNodoVagon(nuevo.peso);

            lista = agregarAlPpio(lista, nuevoNodo);
        }
        else
        {
            if(controlarPeso(lista) + 200 <= 1400)
            {
                nodoVagon * nuevoNodo = crearNodoVagon(200);

                lista = agregarAlPpio(lista, nuevoNodo);

                nuevo.peso -= 200;

                lista = cargarVagones(lista, nuevo);
            }
        }

        return lista;
    }
}

int agregarTren(tren ADT[], int validos, cajon nuevo)///Inciso 1
{
    ADT[validos].nroTren = validos + 1;

    strcpy(ADT[validos].categoria, nuevo.material);

    ADT[validos].listaVagones = inicLista();

    validos++;

    return validos;
}

float controlarPeso(nodoVagon * lista)///Inciso 1
{
    nodoVagon * aux = lista;

    float peso = 0;

    while(aux != NULL)
    {
        peso += aux->pesoIngresado;
        aux = aux->sig;
    }

    return peso;
}

int cargarCelda(tren ADT[], int validos, cajon nuevo) ///Inciso 1
{
    int poss = buscarMaterial(ADT, validos, nuevo.material);

    if(poss == -1)
    {
        validos = agregarTren(ADT, validos, nuevo);

        poss = validos - 1;
    }

    ADT[poss].listaVagones = cargarVagones(ADT[poss].listaVagones, nuevo);

    return validos;
}

void imprimirCelda(tren ADT[], int poss) /// Inciso 2
{
    float peso = controlarPeso(ADT[poss].listaVagones);

    printf("\n----------------\n");
    printf("Nro Tren: %d\n", ADT[poss].nroTren);
    printf("Categoria: %s\n", ADT[poss].categoria);
    printf("Peso: %.2f kg", peso);
    printf("\n----------------\n");
}

float pesoPorCategoria(tren ADT[], int validos) /// Inciso 2
{
    for(int i = 0; i < validos; i++)
    {
        imprimirCelda(ADT, i);
    }
}

void porcentajeCategoria(tren ADT[], int validos)/// Inciso 2
{
    char categoria[20];

    float pesoCategoria;

    int opcion;

    do
    {
        printf("\nSeleccione la categoria:\n\n");
        printf("\t1 - comestible\n");
        printf("\t2 - madera\n");
        printf("\t3 - metal\n");
        printf("\t4 - plastico\n");
        printf("\t5 - vidrio\n");

        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:

            strcpy(categoria, "Comestible");
            break;

        case 2:

            strcpy(categoria, "Madera");
            break;
        case 3:

            strcpy(categoria, "Metal");
            break;
        case 4:

            strcpy(categoria, "Plastico");
            break;
        case 5:

            strcpy(categoria, "Vidrio");
            break;
        default:

            printf("\nopcion no valida\n\n");
            break;
        }

    }
    while(opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5);

    int flag = -1;

    for(int i = 0; i < validos; i++)
    {
        if(strcmpi(ADT[i].categoria, categoria) == 0)
        {
             pesoCategoria = controlarPeso(ADT[i].listaVagones);
             flag = 1;
        }
    }

    system("cls");

    if(flag == 1)
    {
        float rta = (pesoCategoria * 100) / 1400;

        printf("\nEl porcentaje de peso en esa categoria es de: %.2f%% !!\n\n", rta);

    }else
    {
        printf("\nNo hay tren con esa categoria!!\n\n");
    }

}

void trenMenorCarga(tren ADT[], int validos)/// Inciso 2
{
    int poss;

    float menor = 1500, actual;

    for(int i = 0; i<validos; i++)
    {
        actual = controlarPeso(ADT[i].listaVagones);

        if(actual < menor)
        {
            menor = actual;
            poss = i;
        }
    }

     printf("\nEl tren con menor carga de peso es el de %s!!\n\n", ADT[poss].categoria);

}

nodoVagon * borrarNodo(nodoVagon * lista, float peso) ///Inciso 3
{
    nodoVagon * aux;
    nodoVagon * anterior;

    if(lista != NULL && lista->pesoIngresado <= peso)
    {
        aux = lista;
        lista = lista->sig;
        free(aux);

    }
    else
    {
        aux = lista;

        while(aux != NULL && aux->pesoIngresado > peso)
        {
            anterior = aux;
            aux = aux->sig;
        }

        if(aux != NULL)
        {
            anterior->sig = aux->sig;
            free(aux);
        }
    }

    return lista;
}

nodoVagon * descargarMateriaPrima(nodoVagon * lista, float cantPedida)///Inciso 3
{
    nodoVagon * aux = lista;

    if(cantPedida > 0 && aux != NULL)
    {
        if(cantPedida <= 200)
        {
            cantPedida -= aux->pesoIngresado;

            if(aux->pesoIngresado < cantPedida)
            {
                 aux->pesoIngresado = 0;
                 aux = descargarMateriaPrima(aux->sig, cantPedida);
            }else
            {
                aux->pesoIngresado -= cantPedida;
            }
        }else
        {
            cantPedida -= aux->pesoIngresado;
            aux->pesoIngresado = 0;

            aux = descargarMateriaPrima(aux->sig, cantPedida);
        }
    }

    return lista;
}

void entregarPedidos (tren ADT[], int validos)///Inciso 3
{
    Pedido aux;

    int poss;

    float pesoTotal;

    FILE * archi = fopen(archivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(Pedido), 1, archi) > 0)
        {
            poss = buscarMaterial(ADT, validos, aux.categoria);

            if(poss != -1)
            {
                ADT[poss].listaVagones = descargarMateriaPrima(ADT[poss].listaVagones, aux.cantidad);

                printf("\nEntrega a la ciudad de %s realizada\n\n", aux.ciudad);

            }else
            {
                printf("\nNo se cuenta con la materia prima que solicida la ciudad de %s!!\n\n", aux.ciudad);
            }

            ADT[poss].listaVagones = eliminarVagonesVacios(ADT[poss].listaVagones);

            printf("\nVagones vacios eliminados!!\n\n");
        }

        fclose(archi);
    }
}

nodoVagon * eliminarVagonesVacios(nodoVagon * lista)///Inciso 3
{
    nodoVagon * aux = lista;

    while(aux != NULL)
    {
        aux = borrarNodo(aux, 0);
        aux = aux->sig;
    }

    return lista;
}

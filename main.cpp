#include <iostream>
#include <stdlib.h>

using namespace std;

// Nodo de la pila
struct nodopila
{
    char dato;
    struct nodopila *enlace;
};

// Prototipos
void push(struct nodopila **top, char valor);
char pop(struct nodopila **top);
char verTope(struct nodopila *top);
int prioridad(char operador);

int main()
{
    struct nodopila *top = NULL;
    char expresion[100];

    cout << "Ingrese una operacion en notacion infija: ";
    cin.getline(expresion, 100);

    return 0;
}

// Inserta un dato en la pila
void push(struct nodopila **top, char valor)
{
    struct nodopila *nuevo;

    nuevo = (struct nodopila *) malloc(sizeof(struct nodopila));

    if(nuevo != NULL)
    {
        (*nuevo).dato = valor;
        (*nuevo).enlace = *top;
        *top = nuevo;
    }
}

// Elimina el dato del tope
char pop(struct nodopila **top)
{
    struct nodopila *temp;
    char valor;

    if(*top == NULL)
    {
        return '\0';
    }

    temp = *top;
    valor = (*temp).dato;
    *top = (**top).enlace;
    free(temp);

    return valor;
}

// Devuelve el dato del tope
char verTope(struct nodopila *top)
{
    if(top == NULL)
    {
        return '\0';
    }

    return (*top).dato;
}

// Prioridad de operadores
int prioridad(char operador)
{
    if(operador == '+' || operador == '-')
    {
        return 1;
    }

    if(operador == '*' || operador == '/')
    {
        return 2;
    }

    return 0;
}
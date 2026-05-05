#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <conio.h>

using namespace std;

// Pila para operadores
struct nodopilachar
{
    char dato;
    struct nodopilachar *enlace;
};

// Prototipos
void pushChar(struct nodopilachar **top, char valor);
char popChar(struct nodopilachar **top);
char verTopeChar(struct nodopilachar *top);

int prioridad(char operador);
int esNumero(char c);
int esOperador(char c);

void pasarAPosfija(char infija[], char posfija[]);

int main()
{
    char infija[100];
    char posfija[100];
    int opcion;

    do
    {
        system("CLS");

        cout << "       PROYECTO DE PILAS" << endl;
        cout << "1. Ingresar operacion" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if(opcion == 1)
        {
            system("CLS");

            cout << "Ingrese una operacion en notacion infija: ";
            cin.getline(infija, 100);

            pasarAPosfija(infija, posfija);

            cout << endl;
            cout << "Operacion en posfija: " << posfija << endl;

            cout << endl;
            cout << "Presione una tecla para volver al menu...";
            getch();
        }

    }while(opcion != 2);

    return 0;
}

// Inserta en pila
void pushChar(struct nodopilachar **top, char valor)
{
    struct nodopilachar *nuevo;

    nuevo = (struct nodopilachar *) malloc(sizeof(struct nodopilachar));

    if(nuevo != NULL)
    {
        (*nuevo).dato = valor;
        (*nuevo).enlace = *top;
        *top = nuevo;
    }
}

// Elimina del tope
char popChar(struct nodopilachar **top)
{
    struct nodopilachar *temp;
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

// Mira el tope
char verTopeChar(struct nodopilachar *top)
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

// Verifica numero
int esNumero(char c)
{
    if(c >= '0' && c <= '9')
    {
        return 1;
    }

    return 0;
}

// Verifica operador
int esOperador(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }

    return 0;
}

// Convierte infija a posfija
void pasarAPosfija(char infija[], char posfija[])
{
    struct nodopilachar *top = NULL;
    int i, j;

    j = 0;

    for(i = 0; infija[i] != '\0'; i++)
    {
        if(infija[i] == ' ')
        {
            continue;
        }

        // Multiplicacion implicita
        if(i > 0 && infija[i] == '(' && esNumero(infija[i - 1]) == 1)
        {
            while(top != NULL &&
                  verTopeChar(top) != '(' &&
                  prioridad(verTopeChar(top)) >= prioridad('*'))
            {
                posfija[j] = popChar(&top);
                j++;
                posfija[j] = ' ';
                j++;
            }

            pushChar(&top, '*');
        }

        // Numero directo a salida
        if(esNumero(infija[i]) == 1)
        {
            posfija[j] = infija[i];
            j++;
            posfija[j] = ' ';
            j++;
        }

        // Parentesis que abre
        else if(infija[i] == '(')
        {
            pushChar(&top, infija[i]);
        }

        // Parentesis que cierra
        else if(infija[i] == ')')
        {
            while(top != NULL && verTopeChar(top) != '(')
            {
                posfija[j] = popChar(&top);
                j++;
                posfija[j] = ' ';
                j++;
            }

            popChar(&top);
        }

        // Operadores
        else if(esOperador(infija[i]) == 1)
        {
            while(top != NULL &&
                  verTopeChar(top) != '(' &&
                  prioridad(verTopeChar(top)) >= prioridad(infija[i]))
            {
                posfija[j] = popChar(&top);
                j++;
                posfija[j] = ' ';
                j++;
            }

            pushChar(&top, infija[i]);
        }
    }

    // Vaciar la pila
    while(top != NULL)
    {
        posfija[j] = popChar(&top);
        j++;
        posfija[j] = ' ';
        j++;
    }

    posfija[j] = '\0';
}
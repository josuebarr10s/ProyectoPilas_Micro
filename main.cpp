#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <conio.h>

using namespace std;

// Pila para guardar operadores y parentesis
struct nodopilachar
{
    char dato;
    struct nodopilachar *enlace;
};

// Pila para guardar numeros y resultados
struct nodopilanum
{
    int dato;
    struct nodopilanum *enlace;
};

// Prototipos
void pushChar(struct nodopilachar **top, char valor);
char popChar(struct nodopilachar **top);
char verTopeChar(struct nodopilachar *top);

void pushNum(struct nodopilanum **top, int valor);
int popNum(struct nodopilanum **top);

int prioridad(char operador);
int esNumero(char c);
int esOperador(char c);

void pasarAPosfija(char infija[], char posfija[]);
int resolverPosfija(char posfija[]);

int main()
{
    char infija[100];
    char posfija[100];
    int resultado;
    int opcion;

    do
    {
        system("CLS");

        cout << "PROYECTO DE PILAS" << endl;
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

            // Se convierte la expresion ingresada a posfija
            pasarAPosfija(infija, posfija);

            cout << endl;
            cout << "Operacion en posfija: " << posfija << endl;

            // Se resuelve la expresion posfija
            resultado = resolverPosfija(posfija);

            cout << "Resultado: " << resultado << endl;

            cout << endl;
            cout << "Presione una tecla para volver al menu...";
            getch();
        }

    }while(opcion != 2);

    return 0;
}

// Pila de caracteres

void pushChar(struct nodopilachar **top, char valor)
{
    struct nodopilachar *nuevo;

    // Se reserva memoria para un nuevo nodo
    nuevo = (struct nodopilachar *) malloc(sizeof(struct nodopilachar));

    if(nuevo != NULL)
    {
        (*nuevo).dato = valor;
        (*nuevo).enlace = *top;
        *top = nuevo;
    }
}

char popChar(struct nodopilachar **top)
{
    struct nodopilachar *temp;
    char valor;

    if(*top == NULL)
    {
        return '\0';
    }

    // Se guarda el nodo del tope para eliminarlo
    temp = *top;
    valor = (*temp).dato;
    *top = (**top).enlace;

    free(temp);

    return valor;
}

char verTopeChar(struct nodopilachar *top)
{
    if(top == NULL)
    {
        return '\0';
    }
    else
    {
        return (*top).dato;
    }
}

// Pila de numeros

void pushNum(struct nodopilanum **top, int valor)
{
    struct nodopilanum *nuevo;

    // Se crea un nodo para guardar el numero
    nuevo = (struct nodopilanum *) malloc(sizeof(struct nodopilanum));

    if(nuevo != NULL)
    {
        (*nuevo).dato = valor;
        (*nuevo).enlace = *top;
        *top = nuevo;
    }
}

int popNum(struct nodopilanum **top)
{
    struct nodopilanum *temp;
    int valor;

    if(*top == NULL)
    {
        return 0;
    }

    // Se toma el valor del tope y se elimina
    temp = *top;
    valor = (*temp).dato;
    *top = (**top).enlace;

    free(temp);

    return valor;
}

// Funciones auxiliares

int prioridad(char operador)
{
    // Suma y resta tienen menor prioridad
    if(operador == '+' || operador == '-')
    {
        return 1;
    }

    // Multiplicacion y division tienen mayor prioridad
    if(operador == '*' || operador == '/')
    {
        return 2;
    }

    return 0;
}

int esNumero(char c)
{
    if(c >= '0' && c <= '9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int esOperador(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Conversion de infija a posfija

void pasarAPosfija(char infija[], char posfija[])
{
    struct nodopilachar *top = NULL;
    int i, j;

    j = 0;

    // Se recorre la expresion caracter por caracter
    for(i = 0; infija[i] != '\0'; i++)
    {
        if(infija[i] == ' ')
        {
            continue;
        }

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

        if(i > 0 && esNumero(infija[i]) == 1 && infija[i - 1] == ')')
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

        // Los numeros pasan directo a la salida
        if(esNumero(infija[i]) == 1)
        {
            posfija[j] = infija[i];
            j++;
            posfija[j] = ' ';
            j++;
        }

        // El parentesis que abre se guarda en la pila
        else if(infija[i] == '(')
        {
            pushChar(&top, infija[i]);
        }

        // Al cerrar parentesis se sacan operadores hasta encontrar (
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

        // Se comparan operadores segun su prioridad
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

    // Se vacia la pila al terminar la expresion
    while(top != NULL)
    {
        posfija[j] = popChar(&top);
        j++;
        posfija[j] = ' ';
        j++;
    }

    posfija[j] = '\0';
}

// Evaluacion de expresion posfija

int resolverPosfija(char posfija[])
{
    struct nodopilanum *top = NULL;
    int i;
    int num1, num2, resultado;

    // Se recorre la expresion posfija
    for(i = 0; posfija[i] != '\0'; i++)
    {
        if(posfija[i] == ' ')
        {
            continue;
        }

        // Si es numero, se guarda en la pila
        if(esNumero(posfija[i]) == 1)
        {
            pushNum(&top, posfija[i] - '0');
        }

        // Si es operador, se sacan dos numeros y se opera
        else if(esOperador(posfija[i]) == 1)
        {
            num1 = popNum(&top);
            num2 = popNum(&top);

            if(posfija[i] == '+')
            {
                resultado = num2 + num1;
            }
            else if(posfija[i] == '-')
            {
                resultado = num2 - num1;
            }
            else if(posfija[i] == '*')
            {
                resultado = num2 * num1;
            }
            else if(posfija[i] == '/')
            {
                resultado = num2 / num1;
            }

            // El resultado vuelve a la pila
            pushNum(&top, resultado);
        }
    }

    // Resultado final
    return popNum(&top);
}
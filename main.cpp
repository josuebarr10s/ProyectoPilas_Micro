#include <iostream>
#include <stdlib.h>

using namespace std;

// Nodo para la pila
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
int esNumero(char c);
int esOperador(char c);

void convertirPosfija(char infija[], char posfija[]);

int main()
{
    char infija[100];
    char posfija[100];

    cout << "Ingrese una operacion en notacion infija: ";
    cin.getline(infija, 100);

    convertirPosfija(infija, posfija);

    cout << endl;
    cout << "Notacion posfija: " << posfija << endl;

    // Pendiente: evaluar la expresion posfija usando otra pila

    return 0;
}

// Inserta en la pila
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

// Elimina 
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

// Mira
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

// Valida numeros de una cifra
int esNumero(char c)
{
    if(c >= '0' && c <= '9')
    {
        return 1;
    }

    return 0;
}

// Valida operadores
int esOperador(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }

    return 0;
}

// Convierte infija a posfija
void convertirPosfija(char infija[], char posfija[])
{
    struct nodopila *top = NULL;
    int i, j;

    j = 0;

    for(i = 0; infija[i] != '\0'; i++)
    {
        if(infija[i] == ' ')
        {
            continue;
        }

    
        if(i > 0 && infija[i] == '(' && esNumero(infija[i - 1]) == 1)
        {
            while(top != NULL &&
                  verTope(top) != '(' &&
                  prioridad(verTope(top)) >= prioridad('*'))
            {
                posfija[j] = pop(&top);
                j++;
                posfija[j] = ' ';
                j++;
            }

            push(&top, '*');
        }

        // Numero directo a salida
        if(esNumero(infija[i]) == 1)
        {
            posfija[j] = infija[i];
            j++;
            posfija[j] = ' ';
            j++;
        }

        // Parentesis de apertura
        else if(infija[i] == '(')
        {
            push(&top, infija[i]);
        }

        // Parentesis de cierre
        else if(infija[i] == ')')
        {
            while(top != NULL && verTope(top) != '(')
            {
                posfija[j] = pop(&top);
                j++;
                posfija[j] = ' ';
                j++;
            }

            pop(&top);
        }

        // Operadores
        else if(esOperador(infija[i]) == 1)
        {
            while(top != NULL &&
                  verTope(top) != '(' &&
                  prioridad(verTope(top)) >= prioridad(infija[i]))
            {
                posfija[j] = pop(&top);
                j++;
                posfija[j] = ' ';
                j++;
            }

            push(&top, infija[i]);
        }
    }

    // Vaciar operadores restantes
    while(top != NULL)
    {
        posfija[j] = pop(&top);
        j++;
        posfija[j] = ' ';
        j++;
    }

    posfija[j] = '\0';
}
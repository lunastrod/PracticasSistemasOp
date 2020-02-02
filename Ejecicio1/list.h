enum{
  tagSize=255
};

typedef struct Coor Coor;
struct Coor{
  int x;
  int y;
  char tag[tagSize];
};

typedef struct Node Node;
struct Node;

typedef struct List List;
struct List;

typedef struct Stack Stack;
struct Stack;

typedef struct Queue Queue;
struct Queue;





List * newList(void);
void deleteList(List * l);
void printList(List *l);

int isEmpty(List * l);//preguntar si una lista está vacía
int size(List * l);//preguntar el número de elementos de la lista
Coor * first(List * l);//determinar el primer elemento (o la "cabeza") de una lista
Coor * last(List * l);//determinar el último elemento (o la "cola") de una lista

void addLeft(List * l, Coor c);//agregar una entidad al inicio de una lista
void addRight(List * l, Coor c);//agregar una entidad al final de una lista

Coor * searchXY(List * l, int x, int y);//preguntar si una coordenada está en la lista pasando sus dos componentes (x,y),  y si es así, conseguir el puntero a la misma (si hay varias, la primera de la lista)
Coor * searchTag(List * l, char tag[]);//preguntar si una coordenada está en la lista pasando su etiqueta, y si es así, conseguir el puntero a la misma (si hay varias, la primera de la lista)
void erase(List * l, Coor * c);//eliminar una coordenada de la lista pasando su puntero



Stack * newStack();
void deleteStack(Stack * s);
void printStack(Stack * s);

void push(Stack * s, Coor c);
Coor pop(Stack * s);



Queue * newQueue();
void deleteQueue(Queue * q);
void printQueue(Queue * q);

void enqueue(Queue * q, Coor c);
Coor dequeue(Queue * q);

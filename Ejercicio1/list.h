enum{
  tagSize=255
};

typedef struct Coor Coor;
struct Coor{
  int x;
  int y;
  char tag[tagSize];
};

typedef struct List List;
typedef struct Stack Stack;
typedef struct Queue Queue;

Coor * newcoor(int x, int y, char * tag);
void deletecoor(Coor * c);
void printcoor(Coor * c);


List * newlist(void);
void deletelist(List * l);
void printlist(List *l);

int isempty(List * l);//preguntar si una lista está vacía
int size(List * l);//preguntar el número de elementos de la lista
Coor * firstcoor(List * l);//determinar el primer elemento (o la "cabeza") de una lista
Coor * lastcoor(List * l);//determinar el último elemento (o la "cola") de una lista

void addstartlist(List * l, Coor * c);//agregar una entidad al inicio de una lista
void addendlist(List * l, Coor * c);//agregar una entidad al final de una lista

Coor * searchxy(List * l, int x, int y);//preguntar si una coordenada está en la lista pasando sus dos componentes (x,y),  y si es así, conseguir el puntero a la misma (si hay varias, la primera de la lista)
Coor * searchtag(List * l, char * tag);//preguntar si una coordenada está en la lista pasando su etiqueta, y si es así, conseguir el puntero a la misma (si hay varias, la primera de la lista)
void erasecoor(List * l, Coor * c);//eliminar una coordenada de la lista pasando su puntero



Stack * newstack();
void deletestack(Stack * s);
void printstack(Stack * s);

void push(Stack * s, Coor * c);
Coor * pop(Stack * s);



Queue * newqueue();
void deletequeue(Queue * q);
void printqueue(Queue * q);

void enqueue(Queue * q, Coor * c);
Coor * dequeue(Queue * q);

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
struct Node{
  Coor data;
  Node* next;
  Node* prev;
};

typedef struct List List;
struct List{
  int size;
  Node* head;
  Node* tail;
};

List newList(void);//crear una lista vacía
void delete(List l);//destruir la lista

char isEmpty(List l);//preguntar si una lista está vacía
int size(List l);//preguntar el número de elementos de la lista

void addLeft(List l);//agregar una entidad al inicio de una lista
void addRight(List l);//agregar una entidad al final de una lista

void first(List l);//determinar el primer elemento (o la "cabeza") de una lista
void last(List l);//determinar el último elemento (o la "cola") de una lista

Coor searchXY(List l, int x, int y);//preguntar si una coordenada está en la lista pasando sus dos componentes (x,y),  y si es así, conseguir el puntero a la misma (si hay varias, la primera de la lista)
Coor searchTag(List l, char *tag[]);//preguntar si una coordenada está en la lista pasando su etiqueta, y si es así, conseguir el puntero a la misma (si hay varias, la primera de la lista)
void erase(List l, Coor* c);//eliminar una coordenada de la lista pasando su puntero

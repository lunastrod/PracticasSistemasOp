
typedef struct Coor Coor;
struct Coor{
  int x;
  int y;
  char tag[];
};

typedef struct Node Node;
struct Node{
  Coor data;
  Node next;
  Node prev;
};

void holaMundo();

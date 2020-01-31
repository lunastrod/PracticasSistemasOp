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
  Node* first;
  Node* last;
};


void holaMundo();

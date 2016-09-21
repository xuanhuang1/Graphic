#include <stdlib.h>
#include <stdio.h>


struct node { 
  int type;
  void* num; 
  struct node *next; 
}; 
typedef struct node Node; 
// typedef Node *Nodeptr;  

typedef struct _integer {
  int data;
} Integer;

typedef struct _double {
  double data;
} Double;

Integer *make_int(int x){
  Integer *newN; 
  if ( (newN = (Integer *) malloc( sizeof(Integer) ) )!= 0) { 
    newN->data =  x; 
  } 
  else { 
    printf("Out of memory!\n"); 
    exit(0); 
  } 
  return newN;
}
Double *make_double(double x){
  Double *newN; 
  if ( (newN = (Double *) malloc( sizeof(Double) ) )!= 0) { 
    newN->data =  x; 
  } 
  else { 
    printf("Out of memory!\n"); 
    exit(0); 
  } 
  return newN;
}


Node *head = 0;  
Node *tail = 0; 

Node *makenode (int tp, void* x) { 
  Node *newN; 
  if ( (newN = (Node *) malloc( sizeof(Node) ) )!= 0) { 
    newN->num =  x; 
    newN-> next = 0; 
    newN->type = tp;
  } 
  else { 
    printf("Out of memory!\n"); 
    exit(0); 
  } 
  return newN; 
} 

void add (Node *p) { 
  if (head == 0) { 
    head = p; 
    tail = p; 
  } 
  else { 
    tail->next = p; 
    tail = p; 
  } 
}

/*void delete (Node *p) { 
  Node *tmp, *prev; 
  if ((p == head) && (p == tail)) {
    head = tail = 0; 
  }
  else if (p == head) {
    head = p->next; 
  }
  else { 
    for(tmp=head, prev=0; tmp!=p; prev=tmp, tmp=tmp->next);
      if (p == tail) 
        tail = prev; 
      prev->next = p->next; 
    }
}*/

void print() { 
  Node *tmp; 
  for (tmp = head; tmp != 0; tmp = tmp->next) {
    if(tmp->type == 1){
      printf("%d ", ((Integer*)tmp->num)->data); 
    }else{
      printf("%f ", ((Double*)tmp->num)->data); 
    }
  }
  printf("\n"); 
}

int main() { 
  Node *tmp; 
  int i; 
  for (i = 0; i < 10; i++) { 
    Integer* ip = make_int(i);
    tmp = makenode(1, ip); 
    add(tmp); 
  } 
  for (i = 0; i < 10; i++) { 
    Double* kp = make_double(i+0.5);
    tmp = makenode(0, kp);
    add(tmp); 
  } 
  print(); 
} 
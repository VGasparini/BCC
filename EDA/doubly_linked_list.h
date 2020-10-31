#define MALLOC(a) (a *) malloc ( sizeof(a) )

struct Node{
   int num;
   struct node *next;
   struct node *prev;
};
typedef struct Node node;

 node *begin;
 node *end;

void push(int num);
void show();
void show_element();
node *find(int num);
void del(node *d);


void push ( int num ){
    node *nw = MALLOC (  node );
    node *actual;

   nw->num = num;

   if ( !begin ){
     nw->next = NULL;
     nw->prev  = NULL;

     begin = nw;
     end = nw;
    return ;
   }

   actual = begin;
   end->next = nw;
   nw->next = NULL;
   nw->prev = end;
   end = nw;
   return ;
}

void show (){
  node *actual = begin;

   while ( actual ){
      printf ( "%d ", actual->num );
      actual = actual->next;
   }
   return ;
}

void show_element ( int size, int pos ){
    node *actual = begin;
   int cont=0;
   pos>0 ? pos=pos : (pos=(size+pos+1));
   while ( actual ){
      cont++;
      if(cont==pos) printf("%d",actual->num);
      actual = actual->next;
   }
   return ;
}

node *find ( int num ){
    node *actual = begin;

   while ( actual ){
      if ( actual->num == num)
         return actual;
      else
         actual = actual->next;
   }
   return NULL;
 }

void del (  node *d ){
   if ( !d ) return ;

   if ( d->next && d->prev ){
      d->prev->next = d->next;
      d->next->prev = d->prev;

      free ( d );
      return ;
   }

   if ( d == begin ){
      begin = d->next;
      begin->prev = NULL;

      free ( d );
      return ;
   }

   if ( d == end ){
      end = d->prev;
      end->next = NULL;

      free ( d );
      return ;
   }
}

typedef struct tree{
  int num;
  struct tree* sad;
  struct tree* sae;
} Tree;

Tree* createTree(){
  return NULL;
}

int treeIsEmpty(Tree* t){
  return t == NULL;
}

void showTree(Tree* t){
  if(!treeIsEmpty(t)){
    printf("%d ", t->num);
    showTree(t->sae);
    showTree(t->sad);
  }
}

void insertTree(Tree** t, int num){
  if(*t == NULL){
    *t = (Tree*)malloc(sizeof(Tree));
    (*t)->sae = NULL;
    (*t)->sad = NULL;
    (*t)->num = num;
  } else {
    if(num < (*t)->num){
      insertTree(&(*t)->sae, num);
    }
    if(num > (*t)->num){
      insertTree(&(*t)->sad, num);
    }
  }
}

int isInTree(Tree* t, int num){
  if(treeIsEmpty(t)){
    return 0;
  }
  printf("%d",t->num);
  return t->num==num || isInTree(t->sae, num) || isInTree(t->sad, num);
}

int search (Tree* t, int num){ //showing path
    if (t == NULL) return 0;
    else if (t->num == num) return 1;
    if (t->num > num){
      printf("%d ",t->num);
       return busca (t->sae, num);
     }
    else{
      printf("%d ",t->num);
       return busca (t->sad, num);
     }
}

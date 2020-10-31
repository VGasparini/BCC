struct Node{
	int num;
	struct Node *prox;
	int tam;
};
typedef struct Node node;

void ini(node *LISTA);
void push(node *LISTA,int pos,int temp);
void push_back(node *LISTA,int temp);
void push_begin(node *LISTA,int temp);
void show(node *LISTA);
void clean(node *LISTA);
int empty(node *LISTA);
node *pop_begin(node *LISTA);
node *pop_back(node *LISTA);
node *pop(node *LISTA,int pos);
void bubbleSort(node *start);
void swap(node *a, node *b);
int search(node *LISTA, int key);
int max(node *LISTA);
int min(node *LISTA);
void search_qt(node *LISTA, int key);
void avanca(node *LISTA, int key);

void ini(node *LISTA){
	LISTA->prox = NULL;
	LISTA->tam=0;
}

int empty(node *LISTA){
	if(LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

node *aloca(){
	node *novo=(node *) malloc(sizeof(node));
	return novo;
}


void push_back(node *LISTA,int temp){
	node *novo=aloca();
	novo->num = temp;
	novo->prox = NULL;

	if(empty(LISTA))
		LISTA->prox=novo;
	else{
		node *tmp = LISTA->prox;

		while(tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	LISTA->tam++;
}

void push_begin(node *LISTA,int temp){
	node *novo=aloca();
	novo->num = temp;
	node *oldHead = LISTA->prox;

	LISTA->prox = novo;
	novo->prox = oldHead;

	LISTA->tam++;
}

void show(node *LISTA){
	if(empty(LISTA)){
		printf("-1\n");
		return ;
	}

	node *tmp;
	tmp = LISTA->prox;
	while( tmp != NULL){
		printf("%d", tmp->num);
		tmp = tmp->prox;
		if(tmp == NULL) return;
	else printf(" ");
	}
}

void mapping(node *LISTA,char op, int n){
	if(empty(LISTA)){
		printf("-1\n");
		return ;
	}
	node *tmp;
	tmp = LISTA->prox;
	switch (op) {
		case '+':
			while( tmp != NULL){
				tmp->num+=n;
			tmp = tmp->prox;
			if(tmp == NULL) break;
			}
		break;
		case '*':
			while( tmp != NULL){
				tmp->num*=n;
			tmp = tmp->prox;
			if(tmp == NULL) break;
			}
		break;
	}
	show(LISTA);
}

void mapping2(node *LISTA,char op, int n){
	node *auxi = (node *) malloc(sizeof(node));
	ini(auxi);
	if(empty(LISTA)){
		printf("-1\n");
		return ;
	}
	node *tmp;
	tmp = LISTA->prox;
	switch (op) {
		case '>':
			while( tmp != NULL){
				if(tmp->num > n) push_back(auxi,tmp->num);
				tmp = tmp->prox;
			if(tmp == NULL) break;
			}
		break;
		case '<':
			while( tmp != NULL){
				if(tmp->num < n) push_back(auxi,tmp->num);
				tmp = tmp->prox;
			if(tmp == NULL) break;
			}
		break;
	}
	show(auxi);
}

void clean(node *LISTA){
	if(!empty(LISTA)){
		node *proxNode,
			  *atual;

		atual = LISTA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void push(node *LISTA,int pos,int temp){
	int count;
	if(pos>0 && pos <= LISTA->tam){
		if(pos==1)
			push_begin(LISTA,temp);
		else{
			node *atual = LISTA->prox,
				 *anterior=LISTA;
			node *novo=aloca();
			novo->num = temp;

			for(count=1 ; count < pos ; count++){
					anterior=atual;
					atual=atual->prox;
			}
			anterior->prox=novo;
			novo->prox = atual;
			LISTA->tam++;
		}

	}else printf("Elemento invalido\n\n");
}

node *pop_begin(node *LISTA){
	if(LISTA->prox == NULL){
		printf("Lista vazia!\n");
		return NULL;
	}else{
		node *tmp = LISTA->prox;
		LISTA->prox = tmp->prox;
		LISTA->tam--;
		return tmp;
	}

}

node *pop_back(node *LISTA){
	if(LISTA->prox == NULL){
		printf("Lista vazia!\n\n");
		return NULL;
	}else{
		node *ultimo = LISTA->prox,
			 *penultimo = LISTA;

		while(ultimo->prox != NULL){
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}

		penultimo->prox = NULL;
		LISTA->tam--;
		return ultimo;
	}
}

node *pop(node *LISTA,int pos){
	int count;
	if(pos>0 && pos <= LISTA->tam){
		if(pos==1)
			return pop_begin(LISTA);
		else{
			node *atual = LISTA->prox,
				 *anterior=LISTA;

			for(count=1 ; count < pos ; count++){
				anterior=atual;
				atual=atual->prox;
			}

		anterior->prox=atual->prox;
		LISTA->tam--;
		return atual;
		}

	}else{
		printf("Elemento invalido\n");
		return NULL;
	}
}

void bubbleSort(node *LISTA){
    int swapped, i;
    node *atual;
    node *anterior = NULL;

    if (empty(LISTA)) return;

    do{
        swapped = 0;
        atual = LISTA;

        while (atual->prox != anterior)
        {
            if (atual->num > atual->prox->num)
            {
                swap(atual, atual->prox);
                swapped = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    }
    while (swapped);
}

void swap(node *a, node *b){
    int temp = a->num;
    a->num = b->num;
    b->num = temp;
}

int search(node *LISTA, int key){
    while (LISTA != NULL){
        if (LISTA->num == key) return 1;
        LISTA = LISTA->prox;
    }
		return 0;
}

int remove_intruso(node *LISTA){
	node *aux = (node *) malloc(sizeof(node));
    while (LISTA != NULL){
		if(search(LISTA,LISTA->num) && !search(aux,LISTA->num)) push_back(aux,LISTA->num);
        LISTA = LISTA->prox;
    }
	show(aux);
}

void avanca(node *LISTA, int key){
	node *atual;
    node *anterior = NULL;
	while (LISTA != NULL){
		atual = LISTA;
        if (atual->num == key) swap(atual, anterior);
        anterior = atual;
		LISTA = LISTA->prox;
    }
	show(LISTA);
}

void search_qt(node *LISTA, int key){
	node *auxi = (node *) malloc(sizeof(node));
	int pos=0;
	ini(auxi);
    while (LISTA != NULL){
        if (LISTA->num == key) push_back(auxi,pos);
        LISTA = LISTA->prox;
		pos++;
    }
	show(auxi);
}

int max(node *LISTA){
	int m;
    while (LISTA != NULL){
        if (LISTA->num >= m) m = LISTA->num;
        LISTA = LISTA->prox;
    }
		return m;
}

int min(node *LISTA){
	int m;
    while (LISTA != NULL){
        if (LISTA->num <= m) m = LISTA->num;
        LISTA = LISTA->prox;
    }
		return m;
}

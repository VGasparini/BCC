 /*
 ################################################
 #   Autor: Vinicius Gasparini
 #   Nome: Algoritmo Greedy de Prim usando FibonacciHeap
 #   Implementação FibonnaciHeap por Nitin Sharma
 ################################################
 */

#include <bits/stdc++.h>
#define MAX 100000;
using namespace std;


struct fnode{			            //node structure for a fibonacci heap
	int value;                      //to be used to check for the priority
    int id;			                //id of the node	
	fnode* child;		            //to point to the child
	bool cas;			            //cascading cut check
	fnode* left;		            //to point to next node
	fnode* right;		            //to point to previous node
	int post;			            //an extra variable to maintain post for applying prim's
};	


struct node{				        //node structure for simple adjacency scheme
    int id;				            //stroring node id
	int w;				            //weight of the node b/w id and its parent in adj list	
    struct node* next;		        // to point to the next neighnour of parent 
};

struct adjlist{					    //sturcure for the nodes in main chian of adj list
	int id;					        //to store id of nodes	
    struct adjlist *next; 	        //to point to next node in the main chian of adj list
	struct node* next2; 		    //to point to its neighbour since it's a 2d chain
};


adjlist* head = new adjlist;		//will point to the chain of nodes in adj list
fnode* fhead = new fnode;			//point the min elment in fibonacci heap
int gvertex;					    //global vertex to store number of vertices 
int gcall=0;					    //it's basically a counter to count number of time removemin is called in fib heap


void initheap();			        //initializing the fib heap circular linked list
int removemin();			        //called to return the minimum element pointed by fhead in fib heap
void prim();			        //this is the main call to rum prim's using f-scheme
int getw(int i,int j,adjlist*& head);			//this returns the weight in  the s-scheme, arugument provide are nodes id and pointer to the head to the chian of node id's in adj list
void add(int a,int b,int c,adjlist*& head);				//this will add node c as neibhour of node a with weight of a-b = c in the s-scheme
void init();										//this is called to populate cicular linked list created in initheap() with the edge lenght in accordance to prim's algorithm
void random(int n,int e);			//to generate a random data file connecting a connected graph with n nodes and e edges which will be used as input

void initheap(){
	fnode* fcurrent;    
	fcurrent = fhead;   //fcurrent initially pointing to the head of the doubly circular linked list in the fb heap
	for(int i=0;i<gvertex;i++){  //initializing the fp heap nodes circular linked list
		
			if(i==0){    //case when populating node with id 0
			 	fnode* temp = new fnode;
				fcurrent->value=MAX;
				fcurrent->cas = false;
				fcurrent->id=i;
				fcurrent->child=NULL;
				fcurrent->right=temp;
				fcurrent->left = NULL;
				fcurrent->post=MAX;
				temp->left = fcurrent;
				fcurrent=temp;
				temp=NULL;	
			}
			else if(i!=0 && i!=gvertex-1){    //case when populating intermediate nodes
				fnode* temp = new fnode;
				fcurrent->value=MAX;
				fcurrent->cas = false;
				fcurrent->id=i;
				fcurrent->child=NULL;
				fcurrent->post=MAX;
				fcurrent->right=temp;
				temp->left = fcurrent;
				fcurrent=temp;
				temp=NULL;
			}else{						//case when populating node with id gvertex-1 or last node
				fcurrent->value=MAX;
				fcurrent->cas = false;
				fcurrent->id=i;
				fcurrent->post=MAX;
				fcurrent->child=NULL;
				fcurrent->right=fhead;
				fhead->left = fcurrent;
			}
	}	
}

int removemin(){
	fnode* temp1;
	fnode* currentmin;
	temp1 = fhead;
	currentmin = fhead;				//storing current minimum to delete it in future
	int store;								//storing the current minimun which is nothing but the edge wegiht of next edge to be added in the mst 
	store = fhead ->value;		//storing minvalue before this node is deleted
	int nodes = gvertex-gcall;
	int min = INT_MAX;
	while(nodes--){					//nodes is number of remaining nodes
		if(temp1->post == gcall+1) fhead = temp1;				//searching for the node with next higher post 
		temp1= temp1->right;
	}
    currentmin->left->right = currentmin->right;				//deleting the current minimum from the doubly circular linked list
    currentmin=NULL;
	
	return store;
}

void init(){	
	int n,e,x;
	cin>>n;				                //taking nodes or vertex input from the file 
	cin>>e;					            //taking number of edges from file
	gvertex=n;	            			//populating global veretex =v so that this can be used in other functions
	adjlist* current;
	current=head;
	
	for(int i=0;i<n;i++){	    		//this is basically creating an adj list with v veretx which will be used to populate fibonacci heap
		current->id=i;
		adjlist* temp = new adjlist;
		current->next=temp;
		current=temp;
		current->next=NULL;
	}
	
	int u,v,weight;
	for(int i=0;i<e;i++){
		cin>>u;
		cin>>v;
		cin>>weight;
		add(u,v,weight,head);
	}
}

void prim(){
	init();
	initheap();
	int ftrack[gvertex][2];
	int maini=0,mainj=0,tempj=0,minou=1000;
	int counter=gvertex-1;
	int counter1=gvertex;
	int counter2=gvertex;
	int cost=0;
	int index = 1;
	fnode* temp2;
	temp2= fhead;      //fb heap head pointer
	temp2->value=0;    //setting it's value to 0 (distance to itself)
	temp2->post =0;    //setting it's priority to 0 (higest or first to be addes in the mst)
	
	for(int k=1;k<gvertex;k++) ftrack[k][1]=0;     //nodes other then id 0 are not in mst
	
	ftrack[0][1]=1;   //only node 0 is in the mst
	
	while(counter--){    //running prim's mst algorithm
		minou=1000;
		
		for(int i=0;i<gvertex;i++){   //loop upto global vertex
			int minin=1000;
			if(ftrack[i][1] == 1){    //ftrack to track which nodes id are already in the mst 1 for in o for out
				for(int j=0;j<gvertex;j++){
					if(ftrack[j][1] == 0){
						if(getw(i,j,head)<minin){    //getting the weight from adj list
							minin=getw(i,j,head);
							tempj=j;
						}
					}
				}
			}
			if(minin<minou){
				minou=minin;
				maini=i;
				mainj=tempj;
			}
		}
		ftrack[mainj][1]=1;   //particular id which is equal to main j has been added to the mst
			cout << maini << " -> " << mainj <<" = " << getw(maini,mainj,head) << endl;
			while(counter1--){
				if(temp2->id == mainj){     //searching for the node having id equal to mainj which prim's has selected the id of next node to be added
					temp2->value = getw(maini,mainj,head);    //storing the wegiht of newly added edge in fb heap correspoinding to the id of newly added vertex
					temp2->post = index;	//post is the parameter for storing the priority in which nodes will be accessed during remove min
					index++;  					//just a variable to populate post each time
					break;
				}
				temp2 = temp2->right;
			}
			temp2=fhead;
			counter1=gvertex;
	}
	
	while(counter2--){	
		cost = cost + removemin();			//performing remove min number of nodes times
		++gcall;
  	}
	cout<<"\n Total cost = "<< cost+1 << endl;
}


int getw(int i,int j,adjlist*& head){
	adjlist* temp1 = head;				//temp to point to main chain having all nodes it
	while(temp1->next != NULL){
			if(temp1->id == i){					//traversing to the node having id=i
				node* temp;
				temp=temp1->next2;
				while(temp!=NULL){
					if(temp->id == j){			//traversing the neighbour list of i to find j 
						return temp->w;				//returing the weight of the edge between i and j
					}
					temp= temp->next;
				}
			}
			temp1 = temp1->next;
		}
		return INT_MAX;				//if no edge is found returning infinity or a very large number compared to edges weight
}

void add(int a,int b,int c,adjlist*& head){
		adjlist* temp1=head;
		while(temp1->next!=NULL){
			if(temp1->id==a){					//traversing the main chain to find the node with id =i
				node* temp2;
				node* temp3;
				temp2=temp1->next2;				
				if(temp2 == NULL){			 //if neigbhour list is null 
					temp3 = new node;				//creating a new node with id j in neigbour list of i and putting the weight of edges between a and b in this node
					temp3->id=b;
					temp3->w=c;
					temp2=temp3;
					temp2->next=NULL;
					temp3=NULL;
					temp1->next2=temp2;
				}else{
					while(temp2->next != NULL)			//if neigbour list is not null then raversing the neighbour list of i.
						temp2=temp2->next; 
					temp3 = new node;
					temp3->id=b;
					temp3->w=c;
					temp2->next=temp3;
					temp2=temp3;
					temp2->next=NULL;
					temp3=NULL;
				}
			}
			temp1 = temp1->next;
		}
		temp1=head;
		while(temp1->next!=NULL){				//repeating the above procure now with main node as b and a as it's neighbour since 0 1 15 will 
			if(temp1->id==b){
				node* temp2;
				node* temp3;
				temp2=temp1->next2;
				if(temp2 == NULL){
					temp3 = new node;
					temp3->id=a;
					temp3->w=c;
					temp2=temp3;
					temp2->next=NULL;
					temp3=NULL;
					temp1->next2=temp2;
				}else{
					while(temp2->next != NULL)
						temp2=temp2->next; 
					temp3 = new node;
					temp3->id=a;
					temp3->w=c;
					temp2->next=temp3;
					temp2=temp3;
					temp2->next=NULL;
					temp3=NULL;
				}
			}
			temp1 = temp1->next;
		}
}

int main(int argc, char* argv[]){
    if(argc<2) cout << "Use with these args '-f < input_filename.txt'" << endl;
    else{
	cout << "u -> v = weight\n-------" << endl;
    prim();					
    }
	return 0;
}
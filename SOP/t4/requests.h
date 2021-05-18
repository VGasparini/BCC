#define MAX_BLOCKS_ALLOWED 64

// Request struct
typedef struct Request
{
    int initial_block;
    int blocks_qtd;
    char mode;

    struct Request *next;
} Request;

Request *newRequest(int initial_block, int blocks_qtd, char mode);
Request *push(Request **head, int initial_block, int blocks_qtd, char mode);
int build(Request **head, Request **element);
int isEmpty(Request **head);
int merge(Request **head);
void pop(Request **head);
void show(Request **head);
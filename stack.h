
typedef struct Cell{

	int visited;
	char walls[4];

	int x;
	int y;
} Cell;

typedef struct Node{

	struct Cell *data;
	struct Node *next;
} Node;

typedef struct Stack{

	struct Node *top;
	int length;

} Stack;

int isEmpty(struct Stack *stk);

void push(struct Stack *stk, struct Cell *cell);

struct Cell* pop(struct Stack *stk);

void setupCells(void);

void allocateCellMatrix(void);

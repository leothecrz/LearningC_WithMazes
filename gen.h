
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

void allocateCellMatrix(void);

void printCell(int x,int y);

void setSize(void);

int removeTop(struct Cell* cell);

int removeRight(struct Cell* cell);

int removeBottom(struct Cell* cell);

int removeLeft(struct Cell* cell);

int getVisited(int x, int y);

void genMaze(struct Cell* start);

void makeMaze(char wallSym);

int isEmpty(struct Stack *stk);

void push(struct Stack *stk, struct Cell *cell);

struct Cell* pop(struct Stack *stk);

void setupCells(void);

void allocateCellMatrix(void);



void allocateCellMatrix(void);

void printCell(int x,int y);

void setSize(void);

int removeTop(struct Cell* cell);

int removeRight(struct Cell* cell);

int removeBottom(struct Cell* cell);

int removeLeft(struct Cell* cell);

int getVisited(int x, int y);

void genMaze(struct Cell* start);

void makeMaze(void);

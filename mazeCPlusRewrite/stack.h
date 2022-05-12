struct Cell{
    int x;
    int y;
    short int wasVisited;

    char walls[4];
};

class Stack{
    
    public:

        struct Node{
            public:
                Cell* data;
                struct Node* next;
        };

        struct Node* top;
        int count;

        Stack();

        // Returns 1 if empty;
        int isEmpty(void);

        //Push cell to stack top;
        void push(struct Cell* cell);

        //Return the top cell, does not range check, will Crash.
        struct Cell* pop(void);
};
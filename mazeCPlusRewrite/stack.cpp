class Cell{
    public:
        int x;
        int y;

        int visited;
        int walls[4];
        
        Cell(int a, int b){
            x = a;
            y = b;
            visited = 1;
            for(int i=0;i<4;i++){
                walls[i] = 0;
            }
        }

};
/*
class Node{
    public:
        Cell* data;
        Node* next;

        Node(Cell* data, Node* next){
            this->data = data;
            this->next = next;
        }
};
*/
class Stack{
    //NODE CLASS WILL BE TURNED INTO Internal STRUCT
    public:
     int size;
     Node* top;

     Stack(){
        this->size = 0;
        this->top = NULL;
     }
};

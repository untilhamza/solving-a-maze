#include <stdio.h>
#include <stdlib.h>
#define ROW_MAX 21
#define COL_MAX 21
#define TRUE 1
#define FALSE 0
#define CHECKED 1
#define NOT_CHECKED 0
#define SP_CH 3

typedef struct node* ptrToNode;

int visited[ROW_MAX][COL_MAX] = { 0 };

typedef struct node {

    int data;
    int row;
    int col;

    //the directions already considered from this point
    int left_side;
    int right_side;
    int top_side;
    int bottom_side;

    ptrToNode next; // the node after this in the list

}Node;

ptrToNode delete_node(ptrToNode list, int maze[][COL_MAX]); // returns the new header to our list

ptrToNode insert_node(ptrToNode list, int row, int col, int maze[][COL_MAX]); // returns the new header to our list

ptrToNode make_node(int maze[][COL_MAX], int row, int col);

ptrToNode go_right(ptrToNode list, int maze[][COL_MAX]);

ptrToNode go_left(ptrToNode list, int maze[][COL_MAX]);

ptrToNode go_top(ptrToNode list, int maze[][COL_MAX]);

ptrToNode go_bottom(ptrToNode list, int maze[][COL_MAX]);

ptrToNode solve(int maze[][COL_MAX], int startx, int starty);

// program starts here

int main()
{
    ptrToNode my_list = NULL;
    int start_col = 8;
    int start_row = 14;
    // start_row = 16;


    printf("starting point (%d,%d)\n", start_col, start_row);
    //because the indicies actually start at zero
    start_row--;
    start_col--;

    int MAZE[21][21] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1},
    {1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    //visited_nodes();


    printf("the maze is: \n");
    for (int x = 0; x < ROW_MAX; x++) {
        for (int y = 0; y < COL_MAX; y++) {
            printf("%d  ", MAZE[x][y]);

        }
        printf("\n");
    }

    my_list = solve(MAZE, start_row, start_col);

    if (IsEmpty(my_list)) {
        printf("\n no path to exit found\n");
    }
    else {
        printf("\n maze was solved \n");

        printf("the solved maze is: \n");
        for (int x = 0; x < ROW_MAX; x++) {
            for (int y = 0; y < COL_MAX; y++) {
                printf("%d  ", MAZE[x][y]);

            }
            printf("\n");
        }
    }

    return 0;
}

ptrToNode solve(int maze[][COL_MAX], int startx, int starty) {


    ptrToNode list = make_node(maze, startx, starty);

    maze[list->row][list->col] = SP_CH;

    while (!IsEmpty(list) && list->data != 2)
    {

        if (list->left_side != CHECKED)
        {
            list->left_side = CHECKED;
            list = go_left(list, maze);
        }
        else if (list->right_side != CHECKED)
        {
            list->right_side = CHECKED;
            list = go_right(list, maze);
        }
        else if (list->top_side != CHECKED)
        {
            list->top_side = CHECKED;
            list = go_top(list, maze);

        }
        else if (list->bottom_side != CHECKED)
        {
            list->bottom_side = CHECKED;
            list = go_bottom(list, maze);
        }
        else {
            list = delete_node(list, maze);
        }

    }
    return list;
}


ptrToNode delete_node(ptrToNode list, int maze[][COL_MAX]) { // returns the new head position

    maze[list->row][list->col] = 0; // turn this part back to zero as it was not the right path
    ptrToNode temp = NULL;
    if (list == NULL) { // if the list is already empty
        return list;
    }
    else {
        temp = list->next;
        free(list);
        return temp;
    }
}

// to make a new node
ptrToNode make_node(int maze[][COL_MAX], int row, int col) {
    ptrToNode temp = NULL;
    temp = (ptrToNode)malloc(sizeof(Node));
    if (!temp) {
        printf("memory not enough\n");
        return NULL;
    }
    else {
        visited[row][col] = TRUE;
        temp->data = maze[row][col];
        temp->row = row;
        temp->col = col;
        temp->top_side = NOT_CHECKED;
        temp->bottom_side = NOT_CHECKED;
        temp->right_side = NOT_CHECKED;
        temp->left_side = NOT_CHECKED;
        temp->next = NULL;
        return temp;
    }
}

int IsEmpty(ptrToNode some_list) {
    if (!some_list) return TRUE;
    else return FALSE; // it is not empty
}

ptrToNode insert_node(ptrToNode list, int row, int col, int maze[][COL_MAX]) {
    ptrToNode temp = make_node(maze, row, col);
    // it is here
    maze[row][col] = SP_CH; // this is added to our right track in the maze
    if (!temp) {
        printf("note enough memory\n");
        return list;
    }
    else {
        temp->next = list;
        list = temp; // we have a new element on top of the list
        return list;
    }
}

ptrToNode go_right(ptrToNode list, int maze[][COL_MAX]) {
    ptrToNode temp = NULL;
    if ((list->col + 1) < COL_MAX && !visited[list->row][list->col + 1] && (maze[list->row][list->col + 1] == 0 || maze[list->row][list->col + 1] == 2)) // there is slot to move into on the right
    {
        // create a new node on the stack to be examined
        temp = insert_node(list, list->row, list->col + 1, maze);
        list = temp;
        return list;
    }
    else { // there is not slot to move into
        return list; // returns the same list that it received
    }
}

ptrToNode go_left(ptrToNode list, int maze[][COL_MAX]) { // can return true or false// you need to make an new node here and put it on top of the stack

    ptrToNode temp = NULL;
    if ((list->col - 1) >= 0 && !visited[list->row][list->col - 1] && (maze[list->row][list->col - 1] == 0 || maze[list->row][list->col - 1] == 2)) // there is slot to move into on the right
    {
        // create a new node on the stack to be examined
        temp = insert_node(list, list->row, list->col - 1, maze);
        list = temp;
        //  visited_nodes();
        return list;
    }
    else { // there is not slot to move into
        return list; // returns the same list that it received
    }
}

ptrToNode go_top(ptrToNode list, int maze[][COL_MAX]) {
    ptrToNode temp = NULL;
    if ((list->row - 1) >= 0 && !visited[list->row - 1][list->col] && (maze[list->row - 1][list->col] == 0 || maze[list->row - 1][list->col] == 2)) // there is slot to move into on the right
    {
        // create a new node on the stack to be examined
        temp = insert_node(list, list->row - 1, list->col, maze);
        list = temp;
        return list;

    }
    else { // there is not slot to move into
        return list; // returns the same list that it received
    }
}

ptrToNode go_bottom(ptrToNode list, int maze[][COL_MAX]) {
    ptrToNode temp = NULL;
    if ((list->row + 1) < ROW_MAX && !visited[list->row + 1][list->col] && (maze[list->row + 1][list->col] == 0 || maze[list->row + 1][list->col] == 2)) // there is slot to move into on the right
    {
        // create a new node on the stack to be examined
        temp = insert_node(list, list->row + 1, list->col, maze);
        list = temp;
        //  visited[list->row+1][list->col] = TRUE;
        //  visited_nodes();
        return list;
    }
    else { // there is not slot to move into
      //  visited_nodes();
        return list; // returns the same list that it received
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <float.h>
typedef enum 
{
    NEUTRALITATE,
    REINCERCARE,
    RENASTERE
}Ability;
typedef struct Player {
    char *full_name;
    Ability ability;
    float energy;
    int id;
} Player;

typedef struct Node {
    Player info;
    struct Node *next;
} Node;


typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;


struct positions{
    int x_i;
    int y_i;
    int x_f;
    int y_f;
};
typedef struct positions Pos;
typedef struct Stack {
    Pos poz;
    struct Stack *next;
}Stack;

struct tree
{
    struct tree *left;
    struct tree *right;
    float energy;
    int id;
};
typedef struct tree NodBTS;

typedef struct TournamentNode 
{
    int id;
    float energy;
    char *player_ids;
    bool is_battle;
    char *winner_id;
    struct TournamentNode *left;
    struct TournamentNode *right;
} TournamentNode;

typedef struct
{
    int id;
    float energy;
}HeapMaxNode;

typedef struct
{
    HeapMaxNode *arr;
    int size;
}HeapMax;

typedef struct 
{
    int x,y;
    float g;
    float f;
}HeapMinNode;
typedef struct 
{
    HeapMinNode *arr;
    int capacity;
    int size;
}HeapMin;
typedef struct 
{
    int x;
    int y;
}Coord;

typedef struct 
{
    float energy;
    Pos coord;
    char *winner_id;
}Winner;

Queue *createQueue();
void readStep1_1File(Queue *q,int *no_players);
void enQueue(Queue *q,char *nume,float energy,char *ability,int id);
const char* enumToString(int x);
void writeTask1_1File(Queue *q);
void createMatrices(bool ***m1,float ***m2,float ***m3,int *n,int *m);
void readStep1_2File(bool **m1,float **m2, float **m3,int n,int m);
void writeTask1_2File(bool **m1,float**m2, float**m3,int n,int m);
void push(Stack **s,Pos positions);
void processStep1_3File(Stack **s);
NodBTS *newNode(float energy,int id);
NodBTS *insert(NodBTS *node,float energy,int id);
TournamentNode *create_player_node(NodBTS *root);
TournamentNode *create_battle_node(TournamentNode *left, TournamentNode *right);
TournamentNode *build_tournament_tree(NodBTS *root);
void writePostOrder2_1(TournamentNode *node,FILE *file);
void executeMatch(TournamentNode *root);
void freeQueue(Queue *q);
void freeMatrix(bool **m1, float **m2, float **m3, int n);
void freeStack(Stack **s);
void freeBST(NodBTS *root);
void freeTournamentTree(TournamentNode *root);
void heapifyDown(HeapMax *h, int i);
void buildHeap(HeapMax *h);
void get_top_k_winners(TournamentNode *root,int k, FILE *file,int no_players);
void build_heap_array(TournamentNode *root,float *heap_array);
float manhattan(int x1,int y1,int x2,int y2);
float minCost(float **row_costs,float **col_costs,int n,int m);
void heapifyUp(HeapMin *h, int i);
void addHeap(HeapMin *h,HeapMinNode node);
void heapify_down_min(HeapMin *h,int i);
HeapMinNode extract_min(HeapMin *h);
int valid(int n_x,int n_y,int n,int m,bool **grid);
HeapMin *create_min_heap(int n,int m);
float AStar(int n, int m, Pos coord,float **row_costs, float **col_costs, bool **grid,float energy, Coord **parent,float min_cost);
void Step3(Stack *s, float **row_costs,float **col_costs, bool **grid,int n,int m,int no_winners);

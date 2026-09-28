#include "biblioteca.h"
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main() 
{
    Queue *q=createQueue();
    int no_players=0; //number of players
    readStep1_1File(q,&no_players);
    writeTask1_1File(q);
    bool **grid; //obstacle matrix: true=1 (obstacle), false=0 (not an obstacle)
    float **row_costs,**col_costs;
    int n,m;
    createMatrices(&grid,&row_costs,&col_costs,&n,&m);
    readStep1_2File(grid,row_costs,col_costs,n,m);
    writeTask1_2File(grid,row_costs,col_costs,n,m);

    Stack *s=NULL;
    processStep1_3File(&s);

    NodBTS *root=NULL;
    Node *p=q->front;
    while(p!=NULL)
    {
        root=insert(root,p->info.energy,p->info.id);
        p=p->next;
    }
    TournamentNode *tournament_tree=build_tournament_tree(root);
    FILE *file=fopen("Step_2/test_2_1.txt","w");
    if(file==NULL){printf("File could not be accessed!8"); exit(1);}
    writePostOrder2_1(tournament_tree,file); //Step 2.1
    fclose(file);

    int k;
    k=8;

    executeMatch(tournament_tree);

    FILE *f=fopen("Step_2/test_2_2.txt", "w");

    if(!f)
    {
        printf("File could not be accessed!9");
        exit(1);
    }

    get_top_k_winners(tournament_tree,k,f,no_players);
    fclose(f);
    Winner winner;
    Step3(s,row_costs,col_costs,grid,n,m,k);


    freeQueue(q);
    freeStack(&s);
    freeMatrix(grid,row_costs,col_costs,n);
    freeBST(root);
    freeTournamentTree(tournament_tree);
    q=NULL;
    root=NULL;
    tournament_tree=NULL;
    return 0;
}

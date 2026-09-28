#include "biblioteca.h"
void freeQueue(Queue *q)
{
    if(q==NULL) return;
    Node *node=q->front;
    while(node!=NULL) 
    {
        Node *next=node->next;
        if(node->info.full_name != NULL) 
            free(node->info.full_name);
        free(node);
        node=next;
    }
    free(q);
}
void freeMatrix(bool **m1, float **m2, float **m3, int n)
{
    if(m1!=NULL) 
    {
        for(int i=0;i<n;i++) 
            free(m1[i]);
        free(m1);
    }
    if(m2!=NULL) 
    {
        for(int i=0;i<n-1;i++) 
            free(m2[i]);
        free(m2);
    }
    if(m3!=NULL) 
    {
        for(int i=0;i<n;i++) 
            free(m3[i]);
        free(m3);
    }
}
void freeStack(Stack **s)
{
    if (s==NULL||*s==NULL) return;
    Stack *current=*s;
    while (current!=NULL) 
    {
        Stack *next=current->next;
        free(current);
        current=next;
    }
    *s=NULL;
}
void freeBST(NodBTS *root)
{
    if (root==NULL) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}
void freeTournamentTree(TournamentNode *root)
{
    if (root==NULL) return;
    freeTournamentTree(root->left);
    freeTournamentTree(root->right);
    
    if (root->player_ids!=NULL) 
    {
        free(root->player_ids);
        root->player_ids=NULL;
    }
    if (root->winner_id!=NULL) 
    {
        free(root->winner_id);
        root->winner_id=NULL;
    }
    free(root);
}
Queue *createQueue()
{
    Queue *q=malloc(sizeof(Queue));
    q->front=NULL;
    q->rear=NULL;
    return q;
}
void readStep1_1File(Queue *q,int *no_players)
{
    FILE *file=fopen("Step_1/jucatori.csv","r");
    if(!file) {printf("File could not be accessed!1 Cause: %s\n", strerror(errno)); exit(1);}
    char linie[256];
    fgets(linie,sizeof(linie),file);
    int id_cnt=0;
    while(fgets(linie,sizeof(linie),file))
    {
        char *nume=strtok(linie, ";");
        float energy=atof(strtok(NULL, ";"));
        char *ability=strtok(NULL, ";\n");
        enQueue(q,nume,energy,ability,id_cnt);
        id_cnt++;
    }
    (*no_players)=id_cnt;
    fclose(file);
}
void enQueue(Queue *q,char *nume,float energy,char *ability,int id)
{
    Node *new=malloc(sizeof(Node));
    if(!new) {printf("Nu s-a putut aloca spatiu!"); exit(1);}
    new->info.id=id;
    new->info.energy=energy;
    new->info.full_name=malloc(sizeof(char)*(strlen(nume)+1));
    if(!new->info.full_name) {printf("Nu s-a putut aloca spatiu!"); exit(1);}
    strcpy(new->info.full_name, nume);
    if (strcmp(ability, "NEUTRALITATE")==0) 
        new->info.ability=NEUTRALITATE;
    else if (strcmp(ability, "REINCERCARE")==0) 
        new->info.ability=REINCERCARE;
    else if (strcmp(ability, "RENASTERE")==0) 
        new->info.ability=RENASTERE;
    else   
        new->info.ability=NEUTRALITATE; 
    new->next=NULL;
    if(q->rear==NULL)
    {
        q->front=new;
        q->rear=new;
    }
    else
    {
        q->rear->next=new;
        q->rear=new;
    }
}
const char* enumToString(int x)
{
   if(x==0) return "NEUTRALITATE";
   if(x==1) return "REINCERCARE";
   if(x==2) return "RENASTERE";
   return "eroare";
}
void writeTask1_1File(Queue *q)
{
    FILE *file=fopen("Step_1/test_1_1.csv","w");
    if(!file) {printf("File could not be accessed!2"); exit(1);}
    fputs("PRENUME NUME;ENERGIE;ABILITATE;ID\n",file);
    Node *p=q->front;
    while(p)
    {
        if(p->next!=NULL)
        fprintf(file,"%s;%.2f;%s;%d\n",p->info.full_name, p->info.energy, enumToString(p->info.ability), p->info.id);
        else
        fprintf(file,"%s;%.2f;%s;%d",p->info.full_name, p->info.energy, enumToString(p->info.ability), p->info.id);
        p=p->next;
    }
    fclose(file);
}
void createMatrices(bool ***m1,float ***m2,float ***m3,int *n,int *m)
{
    FILE *file=fopen("Step_1/harta.txt","r");
    if(!file) {printf("File could not be accessed!3"); exit(1);}
    *n=0;*m=0;
    char sir[1000];
    while(fgets(sir,1000,file))
        (*n)++;
    rewind(file);
    fgets(sir,1000,file);
    char *p=strtok(sir," ");
    rewind(file);
    while(p)
    {
        (*m)++;
        p=strtok(NULL," ");
    }
    (*n)=((*n)+1)/2;
    (*m)=((*m)+1)/2;
    *m1=malloc((*n)*sizeof(bool*));
    *m2=malloc(((*n)-1)*sizeof(float*));
    *m3=malloc((*n)*sizeof(float*));
    if(!(*m1)||!(*m2)||!(*m3)) {printf("Nu s a putut aloca spatiu"); exit(1);}
    for(int i=0;i<*n;i++)
        (*m1)[i]=malloc((*m)*sizeof(bool));
    for(int i=0;i<((*n)-1);i++)
        (*m2)[i]=malloc((*m)*sizeof(float));
    for(int i=0;i<*n;i++)
        (*m3)[i]=malloc(((*m)-1)*sizeof(float)); 
}
void readStep1_2File(bool **m1,float **m2, float **m3,int n,int m)
{
    FILE *file=fopen("Step_1/harta.txt","r");
    if(!file) {printf("File could not be accessed!4"); exit(1);}
    int x;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            fscanf(file,"%d",&x);
            if(x==0) m1[i][j]=false;
            if(x==1) m1[i][j]=true;
            //fscanf(file,"%d",&m1[i][j]);
            if(j<m-1)
                fscanf(file,"%f",&m3[i][j]);
        }
        if(i<n-1)
        {
            for(int j=0;j<m;j++)
                fscanf(file,"%f",&m2[i][j]);
        }
    }
    fclose(file);
}   
void writeTask1_2File(bool **m1,float**m2, float**m3,int n,int m)
{
    FILE *file=fopen("Step_1/test_1_2.txt","w");
    if(!file) {printf("File could not be accessed!5"); exit(1);}
    int x=-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(m1[i][j]==true) x=1;
            if(m1[i][j]==false) x=0;
            fprintf(file, "%d ",x);
        }
        putc('\n',file);
    }
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<m;j++)
            fprintf(file, "%.2f ",m2[i][j]);
        putc('\n',file);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m-1;j++)
            fprintf(file, "%.2f ",m3[i][j]);
        if(i!=n-1) putc('\n',file);
    }
    fclose(file);
}

void push(Stack **s,Pos positions)
{
    Stack *new=malloc(sizeof(Stack));
    if(!new) exit(1);
    new->poz=positions;
    new->next=*s;
    *s=new;
}
void processStep1_3File(Stack **s)
{
    FILE *file=fopen("Step_1/misiuni.csv","r");
    if(file==NULL) {printf("File could not be accessed!6");exit(1);}
    char sir[256];
    fgets(sir,256,file);
    int x1,x2,y1,y2;
    Pos positions;
    while(fscanf(file,"%d;%d;%d;%d",&x1,&y1,&x2,&y2)==4)
    {
        positions.x_i=x1;
        positions.y_i=y1;
        positions.x_f=x2;
        positions.y_f=y2;
        push(s,positions);
    }
    fclose(file);

    FILE *f=fopen("Step_1/test_1_3.csv","w");
    if(f==NULL) {printf("File could not be accessed!7");exit(1);}
    fputs("Xi;Yi;Xf;Yf\n",f);
    Stack *temp=*s;
    while(temp!=NULL)
    {
        if(temp->next!=NULL)
        fprintf(f,"%d;%d;%d;%d\n",temp->poz.x_i,temp->poz.y_i,temp->poz.x_f,temp->poz.y_f);
        else
        fprintf(f,"%d;%d;%d;%d",temp->poz.x_i,temp->poz.y_i,temp->poz.x_f,temp->poz.y_f);
        temp=temp->next;
    }
    fclose(f);
}
NodBTS *newNode(float energy,int id)
{
    NodBTS *node=malloc(sizeof(NodBTS));
    node->energy=energy;
    node->id=id;
    node->left=node->right=NULL;
    return node;
}
NodBTS *insert(NodBTS *node,float energy,int id)
{
    if(node==NULL)
        return newNode(energy,id);
    if(energy<node->energy) 
        node->left=insert(node->left,energy,id);
    else if(energy>node->energy)
        node->right=insert(node->right,energy,id);
    return node;
}
TournamentNode *create_player_node(NodBTS *root)
{
    TournamentNode *node=malloc(sizeof(TournamentNode));
    if(!node) exit(1);
    node->energy=root->energy;
    node->id=root->id;
    node->left=NULL;
    node->right=NULL;
    node->is_battle=false;
    int x=node->id;
    int nr_cifre_id=0;
    if(x==0) nr_cifre_id=1;
    while(x>0)
    {
        nr_cifre_id++;
        x=x/10;
    }
    int lungime=nr_cifre_id+10;
    node->player_ids=malloc(lungime*sizeof(char));
    if(node->player_ids==0) exit(1);
    snprintf(node->player_ids,lungime, "J%d", node->id);

    node->winner_id=malloc(lungime*sizeof(char));
    if(node->winner_id==0) exit(1);
    strcpy(node->winner_id, node->player_ids);

    return node;
}
TournamentNode *create_battle_node(TournamentNode *left, TournamentNode *right) 
{
    if(left==NULL) return right;
    if(right==NULL) return left;
    TournamentNode *new_node=malloc(sizeof(TournamentNode));
    if(new_node==NULL) return NULL;
    new_node->left=left;
    new_node->right=right;
    new_node->is_battle=true;
    int n=strlen(left->player_ids)+strlen(right->player_ids)+1;
    new_node->player_ids=malloc(n*sizeof(char));
    snprintf(new_node->player_ids,n,"%s%s",left->player_ids,right->player_ids);
    new_node->winner_id=NULL;
    return new_node;
}
TournamentNode *build_tournament_tree(NodBTS *root)
{
    if(root==NULL) return NULL;
    TournamentNode *left=build_tournament_tree(root->left);
    TournamentNode *right=build_tournament_tree(root->right);
    TournamentNode *node=create_player_node(root);
    if(left&&right) 
    {
        TournamentNode *lupta1=create_battle_node(left,node);
        return create_battle_node(lupta1,right);
    } 
    else if(left) 
        return create_battle_node(left,node);
    else if(right) 
        return create_battle_node(node,right);
    return node;
}
void writePostOrder2_1(TournamentNode *node,FILE *file)
{
    if(node==NULL) return;
    writePostOrder2_1(node->left,file);
    writePostOrder2_1(node->right,file);
    fprintf(file,"%s\n",node->player_ids);
}
void executeMatch(TournamentNode *root)
{
    if (root==NULL) return;
    executeMatch(root->left);
    executeMatch(root->right);
    if(root->is_battle==true &&root->left!=NULL && root->right!=NULL)
    {
        float e1=root->left->energy;
        float e2=root->right->energy;
        float mx=(e1>=e2) ? e1:e2;
        root->energy=mx+fabs(e1-e2);

        TournamentNode *winner=(e1>=e2) ? root->left:root->right;
        root->id=winner->id;

        int length=strlen(winner->winner_id)+1;
        root->winner_id=malloc(sizeof(char)*length);
        if(root->winner_id==NULL) exit(1);
        strcpy(root->winner_id, winner->winner_id);
    }
}
void heapifyDown(HeapMax *h, int i)
{
    while(1)
    {
        int max=i;
        int l=2*i+1;
        int r=2*i+2;
        if(l<h->size&&h->arr[l].energy>h->arr[max].energy)
            max=l;
        if(r<h->size&&h->arr[r].energy>h->arr[max].energy)
            max=r;
        if(max!=i)
        {
            HeapMaxNode aux=h->arr[i];
            h->arr[i]=h->arr[max];
            h->arr[max]=aux;
            i=max;
        }
        else break;
    }
}
void buildHeap(HeapMax *h)
{
    for(int i=h->size/2-1;i>=0;i--)
    {
        heapifyDown(h,i);
    }
}
void build_heap_array(TournamentNode *root,float *heap_array)
{
    if(root==NULL)
        return;
    if(root->id>=0)
    {
        if(root->energy > heap_array[root->id])
        {
            heap_array[root->id]=root->energy;
        }
    }
    build_heap_array(root->left,heap_array);
    build_heap_array(root->right,heap_array);
}

void get_top_k_winners(TournamentNode *root,int k,FILE *file,int no_players)
{
    if(root==NULL || k<=0)
        return;
    float *heap_array=malloc(no_players*sizeof(float));
    if(!heap_array) exit(1);
    for(int i=0;i<no_players;i++)
        heap_array[i]=-1;
    build_heap_array(root,heap_array);
    HeapMax *h=malloc(sizeof(HeapMax));
    if(!h) exit(1);
    h->arr=malloc(no_players*sizeof(HeapMaxNode));
    if(!h->arr)  exit(1);
    h->size=0;
    for(int i=0;i<no_players;i++)
    {
        if(heap_array[i]>=0)
        {
            h->arr[h->size].id=i;
            h->arr[h->size].energy=heap_array[i];
            h->size++;
        }
    }
    buildHeap(h);
    for(int i=0;i<k && h->size>0;i++)
    {
        HeapMaxNode maxim=h->arr[0];
        fprintf(file,"J%d %.2f",maxim.id,maxim.energy);
        if(i!=k-1) fprintf(file, "\n");
        h->arr[0]=h->arr[h->size - 1];
        h->size--;
        heapifyDown(h, 0);
    }
    free(heap_array);
    free(h->arr);
    free(h);
}
float manhattan(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2)+abs(y1-y2);
}
float minCost(float **row_costs,float **col_costs,int n,int m)
{
    float mn=INT_MAX;
    for(int i=0;i<n-1;i++)
        for(int j=0;j<m;j++)
            if(row_costs[i][j]<mn) mn=row_costs[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m-1;j++)
            if(col_costs[i][j]<mn) mn=col_costs[i][j];
    return mn;
}
void heapifyUp(HeapMin *h, int i) 
{
    while (i>0 && h->arr[i].f<h->arr[(i-1)/2].f)
    {
        HeapMinNode temp = h->arr[i];
        h->arr[i]=h->arr[(i-1)/2];
        h->arr[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}
void addHeap(HeapMin *h,HeapMinNode node)
{
    if(h->size>=h->capacity) return;
    h->arr[h->size]=node;
    h->size++;
    heapifyUp(h,h->size-1);
}
void heapify_down_min(HeapMin *h,int i)
{
    while(1)
    {
        int min=i;
        int l=2*i+1;
        int r=2*i+2;
        if(l<h->size&&h->arr[l].f<h->arr[min].f)
            min=l;
        if(r<h->size&&h->arr[r].f<h->arr[min].f)
            min=r;
        if(min!=i)
        {
            HeapMinNode aux=h->arr[i];
            h->arr[i]=h->arr[min];
            h->arr[min]=aux;
            i=min;
        }
        else break;
    }
}
HeapMinNode extract_min(HeapMin *h) 
{
    HeapMinNode min=h->arr[0];
    h->arr[0]=h->arr[h->size-1];
    h->size--;
    heapify_down_min(h,0);
    return min;
}
int valid(int n_x,int n_y,int n,int m,bool **grid)
{
    if(n_x>=0 && n_x<n && n_y>=0 && n_y<m && grid[n_x][n_y]==false)
        return 1;
    return 0;
}
HeapMin *create_min_heap(int n,int m)
{
    HeapMin *h=malloc(sizeof(HeapMin));
    if(!h) exit(1);
    h->size=0;
    h->capacity=n*m;
    h->arr=malloc(h->capacity*sizeof(HeapMinNode)); 
    if(!h->arr) exit(1);
    return h;
}

float AStar(int n,int m,Pos coord,float **row_costs,float **col_costs,bool **grid,float energy,Coord **parent,float min_cost)
{
    float **dist=malloc(n*sizeof(float*));
    for(int i=0;i<n;i++)
    {
        dist[i]=malloc(m*sizeof(float));
        for(int j=0;j<m;j++)
        {
            dist[i][j]=FLT_MAX;
        }
    }
    HeapMin *h=create_min_heap(n,m);
    int dx[]={-1,1,0,0};
    int dy[]={0,0,-1,1};
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            parent[i][j].x=-1;
            parent[i][j].y=-1;
        }
    }
    HeapMinNode start;
    start.x=coord.x_i;
    start.y=coord.y_i;
    start.g=0;
    start.f=min_cost*manhattan(coord.x_i,coord.y_i,coord.x_f,coord.y_f);

    dist[coord.x_i][coord.y_i]=0;
    addHeap(h,start);

    int ok=0;
    float cost_min=0;

    while(h->size>0)
    {
        HeapMinNode current=extract_min(h);
        int u_x=current.x;
        int u_y=current.y;

        if(current.g>dist[u_x][u_y])
        {
            continue;
        }
        if(u_x==coord.x_f && u_y==coord.y_f)
        {
            ok=1;
            cost_min=dist[u_x][u_y];
            break;
        }
        for(int i=0;i<4;i++)
        {
            int n_x=u_x+dx[i];
            int n_y=u_y+dy[i];
            if(valid(n_x,n_y,n,m,grid))
            {
                float cost;
                if(dx[i]==1) cost=row_costs[u_x][u_y];
                else if(dx[i]==-1) cost=row_costs[n_x][u_y];
                else if(dy[i]==1) cost=col_costs[u_x][u_y];
                else cost=col_costs[u_x][n_y];

                float new_cost=dist[u_x][u_y]+cost;

                if(new_cost<dist[n_x][n_y] && new_cost <= energy)
                {
                    dist[n_x][n_y]=new_cost;

                    parent[n_x][n_y].x=u_x;//memorare parinte nod
                    parent[n_x][n_y].y=u_y;

                    HeapMinNode node;
                    node.x=n_x;
                    node.y=n_y;
                    node.g=new_cost;
                    node.f=node.g+min_cost*manhattan(n_x,n_y,coord.x_f,coord.y_f);
                    addHeap(h,node);
                }
            }
        }
    }
    for(int i=0;i<n;i++) free(dist[i]);
    free(dist);
    free(h->arr);
    free(h);
    if(ok) return cost_min;
    return -1;
}
void Step3(Stack *s, float **row_costs,float **col_costs, bool **grid,int n,int m,int no_winners)
{
    Winner winner;
    FILE *file1=fopen("Step_2/ref_test_2_2.txt","r");
    FILE *file2=fopen("Step_3/test_3.txt","w");
    if(!file1 || !file2) {printf("Eroare deschdere file 10");exit(1);}
    winner.winner_id=malloc(sizeof(char)*20);
    if(!winner.winner_id) exit(1);
    /*Pentru a retine drumul minim (coordonatele) si a afisa in test_3.txt folosesc matricea parent.
    Structura Pos are si coordonatele initiale, si cele finale, asa ca, pentru
    a nu mai face o alta structura, o folosesc pe aceeasi, si pun in x_i si y_i*/
    Coord **parent=malloc(n*sizeof(Coord*));
    if (!parent) exit(1);
    for (int i=0;i<n;i++)
        { parent[i]=malloc(m*sizeof(Coord));  if(!parent[i]) exit(1); }
    Coord *path=malloc(n*m*sizeof(Coord));
    if(!path) exit(1);
    int lung;//lungimea drumului de cost minim
    int k=0;
    Stack *temp=s;

    float min_cost=minCost(row_costs,col_costs,n,m);
    while(fscanf(file1,"%s %f",winner.winner_id,&winner.energy)==2 && temp!=NULL)
    {
        k++;lung=0;
        float remaining_energy;
        winner.coord=temp->poz;
        float cost=AStar(n,m,winner.coord,row_costs,col_costs,grid,winner.energy,parent,min_cost);
        if(cost!=-1 && winner.energy-cost>=0)
        {
            remaining_energy=winner.energy-cost;
            int x=winner.coord.x_f;
            int y=winner.coord.y_f;
            while(1)
            {
                path[lung].x=x; path[lung].y=y;
                lung++;
                if (x==winner.coord.x_i && y==winner.coord.y_i) break;
                int a=parent[x][y].x; int b=parent[x][y].y;
                x=a;y=b;
            }
            fprintf(file2, "%s - %.2f:", winner.winner_id, remaining_energy);
            for(int i=lung-1;i>=0;i--) 
            {
                fprintf(file2," [%d, %d]",path[i].x,path[i].y);
                if(i!=0) fputs(" --", file2);
            }
        }
        else fprintf(file2,"%s: Mission could not be executed",winner.winner_id);
        if(k<no_winners) fputs("\n", file2);
        temp=temp->next;
    }
    fclose(file1); fclose(file2);
    for(int i=0;i<n;i++)
        free(parent[i]);
    free(parent);
    free(path);
}
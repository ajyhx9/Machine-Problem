#include <stdio.h>
#include <stdlib.h>

struct node
{
    int vertex;
    struct node* next;
};
struct node* createNode(int v);
struct Graph
{
    int numVertices;
    int* visited;
    struct node** adjLists; // int** to stores two dimensional array.struct node** stores an array of Linked lists
};
struct Graph* createGraph(int);
void addEdge(struct Graph*, int, int);
void printGraph(struct Graph*);
void DFS(struct Graph*, int, int *, int *);
int main()
{
    int *bug = malloc(sizeof(int));
    int i;
    int h;
    *bug = 0;
    int verticies = 7;
    //um hu hu  nu
    int array[verticies];
    int *output;
    output = array;
    output = malloc((verticies + 1) * (sizeof(int)));

    struct Graph* graph = createGraph(verticies);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 6);
    addEdge(graph, 6, 5);
    addEdge(graph, 5, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 3, 2);
    addEdge(graph, 3, 5);
    addEdge(graph, 1, 5);

    //printGraph(graph);
    for(h=1; h<verticies; h++){
    printf("%d:", h);
    DFS(graph, h, bug, output);
    printf("\n");
    for(i=0; i<verticies; i++){
       graph->visited[i] = 0;
    }
    for(i=0; i<verticies; i++){
       output[i] = 0;
    }
    *bug = 0;
    }

    return 0;
}
void DFS(struct Graph* graph, int vertex, int *bug, int *output) {
        struct node* adjList = graph->adjLists[vertex];
        struct node* temp = adjList;
        graph->visited[vertex] = 1;
        int i;
        //printf("Visited %d \n", vertex);
        if(*bug == 2 && output[vertex] != 1){
            printf(" %d", vertex);
            output[vertex] = 1;
        }
        while(temp!=NULL) {
            int connectedVertex = temp->vertex;



            if(graph->visited[connectedVertex] == 0) {
                *bug = *bug + 1;
                DFS(graph, connectedVertex, bug, output);
            }

            temp = temp->next;
        }
        *bug = *bug - 1;
        for(i=0; i<9; i++){
       graph->visited[i] = 0;
    }
}

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from u to v
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
 /*   newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;  */
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

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
    //this pointer "bug" will keep track of the distance from one vertex to the others.
    int *bug = malloc(sizeof(int));
    *bug = 0;
    int i;
    int h;
    //the verticies integer is set here, But should be set by the user or something. Verticies is spelled wrong on purpose,
    //"verticies" should be one bigger than the actual largest vertex
    int verticies = 7;
    /*This array is passed to the DFS and is used to keep track of what vertexes have already been
       reached in case there's more than one path to a certain vertex*/
    int array[verticies];
    int *output;
    output = array;
    output = malloc((verticies + 1) * (sizeof(int)));

    //The graph is initialized here
    struct Graph* graph = createGraph(verticies);
    //There would be some variables in place of the numbers entered here the
    // the variables would have data added from the input file
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
    //the print graph function is to see the adjacency list after the edges are in the graph

    //This loop passes each vertex into the DFS algorithm
    for(h=1; h<verticies; h++){
        printf("%d:", h);
        DFS(graph, h, bug, output);
        printf("\n");

        //this clears the visited verticies just in case
      for(i=0; i<verticies; i++){
       graph->visited[i] = 0;
      }
      //this clears the vertex array that is used so no duplicates are printed
      for(i=0; i<verticies; i++){
         output[i] = 0;
        }
        //this clears the counter pointer
       *bug = 0;
    } //closes the loop

    return 0;
}
void DFS(struct Graph* graph, int vertex, int *bug, int *output) {
        struct node* adjList = graph->adjLists[vertex];
        struct node* temp = adjList;
        graph->visited[vertex] = 1;
        int i;
        //printf("Visited %d \n", vertex);
        //this is to track the dfs path
        if(*bug == 2 && output[vertex] != 1){
                                    //I print the vertexes we need as they are discovered
            printf(" %d", vertex);
            output[vertex] = 1;     //this is to prevent duplicate vertexes from being printed
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


}

void printGraph(struct Graph* graph)
{
    //print graph exists for error handling purposes
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

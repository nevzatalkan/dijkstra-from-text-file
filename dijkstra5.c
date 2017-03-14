#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include<assert.h>
 
#define MAX 100	
#define NIL -1	
#define infinity 9999
#define TEMPORARY 0
#define PERMANENT 1
 
void Path_Finder(int source, int vertex);
void Dijkstra_function(int source);
int minimum_temp();
void make_graph();
 
int vertices;
int adjacent_matrix[MAX][MAX];
int predecessor[MAX];
int vertex_status[MAX];
int pathLength[MAX];
 
int main()
{
	int source, vertex;
	make_graph();
	printf("Enter Source Vertex:\t");
	scanf("%d", &source);
	Dijkstra_function(source);
	while(1)
	{
		printf("Enter destination vertex(-1 to Quit):\t");
		scanf("%d", &vertex);
		if(vertex == -1)
		{
			break;
		}
		if(vertex < 0 || vertex >= vertices)
		{
			printf("The Entered Vertex does not exist\n");
		}
		else if(vertex == source)
		{
			printf("Source Vertex and Destination Vertex are same\n");
		}
		else if(pathLength[vertex] == infinity)
            	{
			printf("There is no path from Source vertex to Destination vertex\n");
		}
		else
		{
			Path_Finder(source, vertex);
		}
	}
	return 0;
}

int getirSatirSayisi(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int lineCount = 0;
    
    fp = fopen("mesafe.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	lineCount++;
    }
    
    
    fclose(fp);
    if (line)
        free(line);	
    
    return lineCount;
}


int getirSehirSayisi(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int lineCount = 0;
    
    fp = fopen("kod.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	lineCount++;
    }
    
    
    fclose(fp);
    if (line)
        free(line);	
    
    return lineCount;
}


int getirMesafe2(int satirNo){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int lineCount = -1;
    
    fp = fopen("mesafe.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	
    	lineCount++;
    	
    	if (lineCount != satirNo){
    		continue;
    	}  
    	
		char * nereden;
    	char * nereye;
    	char * mesafe;    
    	nereden = strtok (line," -");
		nereye = strtok (NULL, "-");
		mesafe = strtok (NULL, "\n");
		
		return atoi(mesafe);
    }
    
    
    fclose(fp);
    if (line)
        free(line);	
}

char * getirNereden(int satirNo){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int lineCount = -1;
    
    fp = fopen("mesafe.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	
    	lineCount++;
    	
    	if (lineCount != satirNo){
    		continue;
    	}  
    	
		char * nereden;
    	char * nereye;
    	char * mesafe;    
    	nereden = strtok (line," -");
		nereye = strtok (NULL, "-");
		mesafe = strtok (NULL, "\n");
		
		return nereden;
    }
    
    
    fclose(fp);
    if (line)
        free(line);	
    
    return "";
}

char * getirNereye(int satirNo){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int lineCount = -1;
    
    fp = fopen("mesafe.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	
    	lineCount++;
    	
    	if (lineCount != satirNo){
    		continue;
    	}  
    	
		char * nereden;
    	char * nereye;
    	char * mesafe;    
    	nereden = strtok (line," -");
		nereye = strtok (NULL, "-");
		mesafe = strtok (NULL, "\n");
		
		return nereye;
    }
    
    
    fclose(fp);
    if (line)
        free(line);	
    
    return "";
}

int getirSehirNo(char * sehirAdi){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int lineCount = -1;
    
    fp = fopen("kod.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	
		char * neresi;
    	char * kod;
    	neresi = strtok (line," -");
    	
    	if (strcmp(neresi, sehirAdi) != 0){
    			continue;
    	}
    	
		kod = strtok (NULL, "\n");
		
		return atoi(kod);
    }
    
    
    fclose(fp);
    if (line)
        free(line);	

    return -1;
}
 
void Dijkstra_function(int source)
{
	int count, current;
	for(count = 0; count < vertices; count++)
	{
		predecessor[count] =  NIL;   
		pathLength[count] = infinity;
		vertex_status[count] = TEMPORARY;
	}
	pathLength[source] = 0;	
	while(1)
	{
		current = minimum_temp();	
		if(current == NIL)
		{
			return;
		}
		vertex_status[current] = PERMANENT;
		for(count = 0; count < vertices; count++)
		{
			if(adjacent_matrix[current][count] != 0 && vertex_status[count] == TEMPORARY)
			{
				if( pathLength[current] + adjacent_matrix[current][count] < pathLength[count])
				{	
					predecessor[count] = current;
					pathLength[count] = pathLength[current] + adjacent_matrix[current][count];    
				}
			}
		}
	}
}
 
int minimum_temp()
{
	int count;
	int min = infinity;
	int x = NIL;  
	for(count = 0; count < vertices; count++)
	{
		if(vertex_status[count] == TEMPORARY && pathLength[count] < min)
		{
			min = pathLength[count];
			x = count;
		}
	}
	return x;
}
 
 
void Path_Finder(int source, int vertex)
{
	int count, u;
	int path[MAX];		
	int shortest_distance = 0;
	int temp = 0;	
	while(vertex != source)
	{
		temp++;
		path[temp] = vertex;
		u = predecessor[vertex];
		shortest_distance = shortest_distance + adjacent_matrix[u][vertex];
		vertex = u;	
	}
	count++;
	path[temp] = source;
	printf("Shortest Path\n");
	for(count = temp; count >= 1; count--)	
	{
		printf("%d  ", path[count]);
	}
	printf("\nShortest distance:\t%d\n", shortest_distance);
}
 
void make_graph()
{
	int count, maximum_edges, origin_vertex, destination_vertex, weight;
	printf("Enter total number of vertices:\t");
	//scanf("%d", &vertices);
	
	int lineCount = -1;

	lineCount = getirSatirSayisi();
	int sehirSayisi = getirSehirSayisi();
	vertices = sehirSayisi;
	
	maximum_edges = vertices * (vertices - 1);
	for(count = 0; count < lineCount; count++)
	{
// 		printf("Enter Edge [%d] Co-ordinates [-1 -1] to Quit\n", count + 1);
// 		printf("Enter Origin Vertex Point:\t");		
// 		scanf("%d", &origin_vertex);
// 		printf("Enter Destination Vertex Point:\t");
// 		scanf("%d", &destination_vertex);

			int mesafe = getirMesafe2(count);	
			
			char * nereden = getirNereden(count);
			char * nereye = getirNereye(count);
			
			int neredenIndex = getirSehirNo(nereden);
			int nereyeIndex = getirSehirNo(nereye);
			
			int origin_vertex = neredenIndex-1;
			int destination_vertex = nereyeIndex-1;
			int weight = mesafe;        
			
			

		if( (origin_vertex == -1) && (destination_vertex == -1) )
		{
			break;
		}
// 		printf("Enter the weight for this edge:\t");
// 		scanf("%d", &weight);
		if(origin_vertex >= vertices || destination_vertex >= vertices || origin_vertex < 0 || destination_vertex < 0)
		{
			printf("Edge Co - ordinates are Invalid\n");
			count--;
		}
		else
		{
			adjacent_matrix[origin_vertex][destination_vertex] = weight;
		}
	}
}
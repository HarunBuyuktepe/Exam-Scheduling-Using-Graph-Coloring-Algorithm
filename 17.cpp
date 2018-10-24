//Harun Büyüktepe 
//Project #3
#include <stdbool.h>
#include<stdio.h>
#include"conio.h"
#include"stdlib.h"
#include<string.h>
#define MAX 25


struct node {/*Create new data type*/
    char word[15];
    int key;
    int color;
	struct node *nextPtr;
  };

typedef struct node ListNode; /* synonym for struct listNode */
typedef ListNode *ListNodePtr; /* synonym for ListNode* */


void firstStep(void);
void insertWord( ListNodePtr *sPtr,char wrd[15] ,int k);
ListNodePtr a[15],newPtr,total,diff,refull,lastStep,LStep[15],lastestStep[15];

struct Vertex {
   char label[15];
   int color;
   int number;
   bool visited;
};
int countOfcourse=0;
int queue[MAX];
int rear = -1;
int front = 0;
int queueItemCount = 0;
//****************************************///////////////////////////////////////////
//array of vertices
struct Vertex* lstVertices[MAX];
//adjacency matrix
int adjMatrix[MAX][MAX];
//vertex count
int vertexCount = 0;
//queue functions
void insert(int data) {
   queue[++rear] = data;
   queueItemCount++;
}
int removeData() {
   queueItemCount--;
   return queue[front++]; 
}
bool isQueueEmpty() {
   return queueItemCount == 0;
}
//graph functions
//add vertex to the vertex list
void addVertex(char label[15],int num) {
   struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
   strcpy(  vertex->label,label );
   vertex->color=-1;
   vertex->number=num;
   vertex->visited = false;     
   lstVertices[vertexCount++] = vertex;
}

//add edge to edge array
void addEdge(int start,int end) {
   adjMatrix[start][end] = 1;
   adjMatrix[end][start] = 1;
}
//display the vertex
void displayVertex(int vertexIndex) {
	printf("%s   ",lstVertices[vertexIndex]->label);
}       
//get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex) {
   int i;
	
   for(i = 0; i<vertexCount; i++) {
      if(adjMatrix[vertexIndex][i] == 1 && lstVertices[i]->visited == false)
         return i;
   }
	
   return -1;
}
int maxColor=-1;
int getColor(struct Vertex* v){
	int num[MAX];
	int min=100;
	int count=0,temp;
	if(v->color==-1){
		newPtr=lastestStep[v->number];
		while(newPtr!=NULL){
			if(newPtr->color!=-1){
				if(newPtr->color<min&&newPtr->color!=-1){
					min=newPtr->color;
				}
			}
			num[count]=newPtr->color;
			count++;
			newPtr=newPtr->nextPtr;
		}
		if(min==100){
			v->color=1;
		}
		else if(min!=100){
			int c;
			for(c=0;c<count-1;c++){
				int t;
				for(t=0;t<count-c-1;t++){
					if(num[t]>num[t+1]){
					temp=num[t];
					num[t]=num[t+1];
					num[t+1]=temp;
					}
				}
			}
			/*int t;for(t=0;t<count;t++){//see the gap in the num array
				printf(" %d",num[t]);
			}*/
			int r=1;
			bool a=true;
			while(r<count){
				if(min>r){
					v->color=r;	
					break;
				}
				else if(min==r){
					int y;
					for(y=0;y<MAX;y++){
						while(num[y]==-1)y++;
						if(num[y]!=r && min<r ){
								v->color=r;
								break;
							}		
						r++;
					}		
				}
				r++;
			}
		}
	}
	int a;
	for(a=0;a<15;a++){
		lastStep=lastestStep[a];
		while(lastStep!=NULL){
			if(v->number==lastStep->key){
				lastStep->color=v->color;
			}
			lastStep=lastStep->nextPtr;
		}
	}
	lastStep=diff;
	while(lastStep!=NULL){
		if(v->number==lastStep->key){
			lastStep->color=v->color;
		}
		lastStep=lastStep->nextPtr;
	}
	if(v->color>maxColor) maxColor=v->color;
	
	return v->color;
}
void breadthFirstSearch() {
	printf("\n");
	int i;
	int clr=0;
   //mark first node as visited
	lstVertices[0]->visited = true;
	lstVertices[0]->color=getColor(lstVertices[0]);
   //display the vertex
	displayVertex(0);   
	
   //insert vertex index in queue
	insert(0);
	int unvisitedVertex;
	
	while(!isQueueEmpty()) {
    	//get the unvisited vertex of vertex which is at front of the queue
    	int tempVertex = removeData();   
    	while(((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1)){
    		lstVertices[unvisitedVertex]->visited = true;
    		lstVertices[unvisitedVertex]->color=getColor(lstVertices[unvisitedVertex]);
    		displayVertex(unvisitedVertex);
        	insert(unvisitedVertex);            
		}
    	//no adjacent vertex found	
	}   
   //queue is empty, search is complete, reset the visited flag        
	for(i = 0;i<vertexCount;i++) {
    	lstVertices[i]->visited = false;
	}    
}
int maximum=0;
int main(){
	
	firstStep();
	
	printf("\n");
	newPtr=diff;
	while(newPtr!=NULL){
		addVertex(newPtr->word,countOfcourse);
		newPtr=newPtr->nextPtr;
		countOfcourse++;
	}
	maximum=countOfcourse;
	
	int i, j;

	for(i = 0; i<maximum; i++){ // set adjacency {
		for(j = 0; j<maximum; j++) // matrix to 0
		adjMatrix[i][j] = 0;
	}
	printf("\n");
	
	int p;
	for(p=0;p<maximum;p++){
		newPtr=lastestStep[p];
		while(newPtr!=NULL){
			addEdge(p,newPtr->key);
			newPtr=newPtr->nextPtr;
		}
		
	}
	
	printf("\n\nADJANCENCY MATRIX\n\n\t");
    newPtr=diff;
    while(newPtr!=NULL){
    	printf("%s	",newPtr->word);
    	newPtr=newPtr->nextPtr;
	}
    printf("\n");
    newPtr=diff;
    for(i = 0; i<maximum; i++){ // set adjacency
    	printf("%s\t",newPtr->word);
    	newPtr=newPtr->nextPtr;
    		for(j = 0; j<maximum; j++){
      			printf("  %d\t",  adjMatrix[i][j] );
			}
        printf("\n");
         
	}
	
	printf("\nBreadth First Search: ");
	breadthFirstSearch();
	printf("\n");
	int h;
	for(h=1;h<maxColor+1;h++){
		printf("\nFinal exam Period %d -->",h);
		lastStep=diff;
		while(lastStep!=NULL){
			if(lastStep->color==h)printf(" %s",lastStep->word );
			lastStep=lastStep->nextPtr;
		}
	}
	
	return 0; /* indicates successful termination */     
}
void firstStep(void){
	
	newPtr =NULL; total=NULL;diff=NULL;refull=NULL;lastStep=NULL;
	FILE *ptr_file;	
	char buf[100];
    ptr_file =fopen("dataCenter1.txt","r");
	ListNodePtr addPtr=NULL;
	char text[15],temp[15];
	int index=0,temppp,i=0;
    while (fgets(buf,100, ptr_file)!=NULL){
		a[i]=NULL;
		int w;
		for(w=0;w<100;w++){
    		if(buf[w]==':'){
    			index=0;
    			while(buf[w+1]!=','&& buf[w+1]!='\0'){
    				text[index]=buf[w+1];
    				index++;
					w++;
					temppp=w;
				}
				text[index]='\0';		
				insertWord(&total,text,0);
				insertWord(&a[i],text,0);
				w=temppp;
			}
			else if(buf[w]==','){
    			index=0;
				while(buf[w+1]!=','&&buf[w+1]!='\n'){
					text[index]=buf[w+1];
					index++;
					w++;
					temppp=w;
				}
				text[index]='\0';
				insertWord(&total,text,0);
				insertWord(&a[i],text,0);
				w=temppp;
			}
			
		}
    	i++;
	
	}
	fclose(ptr_file);
		
	int c=0;
	while(total!=NULL){
		strcpy(text,total->word);
		if(diff==NULL){
			insertWord(&diff,text,c);
			c++;
		}
		else if(strcmp( temp , text )!=0 ){
			insertWord(&diff,text,c);
			c++;
		}
		else if( strcmp( temp , text )==0 ){
				
		}
		strcpy(temp,text);
		total=total->nextPtr;
	}

	refull=diff;
	int num=0,indexi;
	while(diff!=NULL){
		//printf("%s\n",diff->word);
		int r;
		for(r=0;r<15;r++){
			newPtr=a[r];
			while(a[r]!=NULL){
				if(strcmp(diff->word,a[r]->word)==0){
					//printf("%d\n",r);
					a[r]=newPtr;
					while(a[r]!=NULL){
						if(strcmp(diff->word,a[r]->word)!=0){
							insertWord(&LStep[num],a[r]->word,0);
						}
						a[r]=a[r]->nextPtr;
					}
					continue;
				}
				a[r]=a[r]->nextPtr;
			}
			a[r]=newPtr;
		}
		num++;
		diff=diff->nextPtr;
	}
	diff=refull;
	int d;
	for(d=0;d<15;d++){
		lastestStep[d]=NULL;
		while(LStep[d]!=NULL){
			strcpy(text,LStep[d]->word);
			if(lastestStep[d]==NULL){
				insertWord(&lastestStep[d],text,0);
			}
			else if(strcmp( temp , text )!=0 ){
				insertWord(&lastestStep[d],text,0);
			}
			else if( strcmp( temp , text )==0 ){
					
			}
			strcpy(temp,text);
			LStep[d]=LStep[d]->nextPtr;
		}	
			
	}
	printf("ADJANCENCY LIST\n");
	refull=diff;
	int t;for(t=0;t<15;t++){
		newPtr=lastestStep[t];
		if(newPtr!=NULL){
			printf("\n%s -->",refull->word);
			refull=refull->nextPtr;
		}
		while(newPtr!=NULL){
			printf("%s ",newPtr->word);
			newPtr=newPtr->nextPtr;
		}
	}
	refull=diff;
	while(refull!=NULL){
		int f;for(f=0;f<15;f++){
			newPtr=lastestStep[f];
			if(newPtr!=NULL){
				while(newPtr!=NULL){
					if(strcmp(newPtr->word,refull->word)==0){
						newPtr->key=refull->key;
					}
					newPtr=newPtr->nextPtr;
				}	
			}
		}
		refull=refull->nextPtr;	
	}
	

}

void insertWord( ListNodePtr *sPtr,char wrd[15] ,int k)/*This inserts words alphaticaly*/
{ 
    ListNodePtr newPtr;      /* pointer to new node */
    ListNodePtr previousPtr; /* pointer to previous node in list */
    ListNodePtr currentPtr;  /* pointer to current node in list */
	
	newPtr = (ListNodePtr)malloc( sizeof( ListNode )); /* create node */
    if ( newPtr != NULL ) { /* is space available */
        newPtr->key=k;
        newPtr->color=-1;
		strncpy(newPtr->word,wrd,15);
        newPtr->nextPtr = NULL; /* node does not link to another node */
        previousPtr = NULL;
        currentPtr = *sPtr;

        /* loop to find the correct location in the list */
        while ( currentPtr != NULL && strcmp(wrd,currentPtr->word)>0  ) { 
			previousPtr = currentPtr;          /* walk to ...   */
			currentPtr = currentPtr->nextPtr;  /* ... next node */ //bir sonraki icin
		} /* end while */

        /* insert new node at beginning of list */
        if ( previousPtr == NULL ) { 
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } /* end if */
        else { /* insert new node between previousPtr and currentPtr */
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } /* end else */
   	
    } /* end if */
    else {
        printf( "%s not inserted. No memory available.\n" ,wrd);
    } /* end else */

} // end function insert //

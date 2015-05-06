#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000
int queue_array[MAX][9];
int rear = - 1;
int front = - 1;

void enqueue( int add_item[9]){

    if (rear == MAX - 1){
        printf("Queue Overflow \n");
    }else{
        if (front == - 1){
            front = 0;
        }
        rear = rear + 1;

        int i;
        for(i=0;i<9;i++){
             queue_array[rear][i] = add_item[i];
        }
    }
}


void dequeue(){
    //TO DO: debug problem here
    if (front == - 1 || front > rear){
        printf("Queue Underflow \n");
        return ;
    }else{
        front = front + 1;
    }
}


int * get_first(){
    int i;
    static int fArr[9];
    if (front == - 1){
        printf("Queue is empty \n");
    }else{
        for (i = 0; i <9; i++){
            fArr[i]= queue_array[front][i];
        }
            return fArr;
    }
}


/////////////////////


void print_Arr(int arry[9]){
    int j;
    for(j=0;j<9;j++){
        if(j%3==0){
            printf("\n");
        }
        printf("%d , ",arry[j]);
    }
    printf("\n");
}


int find_Zero(int arry[9]){
    int j;
    for(j=0;j<9;j++){
        if(arry[j]==0){
        return j;
        }
    }

}

bool cmp_Arr(int ar1[9],int goalArr[9]){
    int i;
    for(i=0;i<9;i++){
        if(ar1[i]!=goalArr[i]){
            enqueue(ar1);
            return false;
        }
    }
    enqueue(ar1);
    return true;
}

int check_repeat(int ar1[9],int p){
    int i;
    int ret=0;
    for(i=0;i<=p;i++){
        int j;
        int statj=0;
        for(j=0;j<9;j++){
            if(ar1[j]!=queue_array[i][j]){
                statj +=1;
            }
        }

        if(statj==0){
            ret=1;
            break;
        }
    }

    return ret;
}


void print_sol(int par){
int q;
    for(q=0;q<9;q++){
        if(q%3==0){
            printf("\n");
        }
        printf("%d , ",queue_array[par][q]);
    }
}


main(){

int first[9];
int goal[9]={1,2,3,4,5,6,7,8,0};
int parent[1000];
bool cmpGoal=false;

printf("\n Enter values for puzzle. Please enter correct numbers (0-8). 0 corresponds to the space in the puzzle.\n");

int j;
for(j=0;j<9;j++){
    scanf("%d",&first[j]);
}

enqueue(first);

int parentNum = 0;
parent[parentNum]=0;


while(cmpGoal!=true){
    int * currArr=get_first();
    int zero = find_Zero(currArr);

    if(zero>2){
        int * currArr=get_first();
        int * tempArr = currArr;
        int tempZero = zero;
        tempZero -=3;
        int swapNum = tempArr[tempZero];
        tempArr[zero]=swapNum;
        tempArr[tempZero]=0;

        int c = check_repeat(tempArr,parentNum-1);
        if(c==0){
            cmpGoal = cmp_Arr(tempArr,goal);
            parentNum +=1;
            parent[parentNum]=front;

            if(cmpGoal==true){
               break;
            }
        }
    }

    if(zero<6){
        int * tempArr1 = get_first();
        int tempZero1 = zero;
        tempZero1 +=3;
        int swapNum = tempArr1[tempZero1];
        tempArr1[zero]=swapNum;
        tempArr1[tempZero1]=0;

        int c = check_repeat(tempArr1,parentNum-1);
        if(c==0){
            cmpGoal = cmp_Arr(tempArr1,goal);
            parentNum +=1;
            parent[parentNum]=front;
            if(cmpGoal==true){
               break;
            }
        }
    }


    if(zero != 0 && zero != 3 && zero != 6 ){
        int * tempArr2 = get_first();;
        int tempZero2 = zero;
        tempZero2 -=1;
        int swapNum = tempArr2[tempZero2];
        tempArr2[zero]=swapNum;
        tempArr2[tempZero2]=0;

        int c = check_repeat(tempArr2,parentNum-1);
        if(c==0){
            cmpGoal = cmp_Arr(tempArr2,goal);
            parentNum +=1;
            parent[parentNum]=front;

            if(cmpGoal==true){
                break;
            }
        }
    }

    if(zero != 2 && zero != 5 && zero != 8 ){
        int * tempArr3 = get_first();
        int tempZero3 = zero;
        tempZero3 +=1;
        int swapNum = tempArr3[tempZero3];
        tempArr3[zero]=swapNum;
        tempArr3[tempZero3]=0;

        int c = check_repeat(tempArr3,parentNum-1);
        if(c==0){
            cmpGoal = cmp_Arr(tempArr3,goal);
            parentNum +=1;
            parent[parentNum]=front;

            if(cmpGoal==true){
               break;
            }
        }
    }

    dequeue();
}


int parArr[500];
int parN=0;

int pN = parentNum;

while(pN > 0){
    parArr[parN]=pN;
    int par = parent[pN];
    pN= par;
    parN+=1;
}


printf("---------------------\n");
printf("   SOLUTION/PATH \n");
printf("---------------------\n");
printf("---------------------\n");

int t;
for(t = parN;t>=0;t--){
    int u = parArr[t];
    print_sol(u);
    printf("\n---------------------\n");
}


    printf("the total number of nodes expanded: %d \n",front);
    printf("the total number of nodes generated: %d \n",parentNum);
    printf("the maximum length of the queue structure: %d \n",MAX);
    printf("the length of the solution path: %d \n",parN);

int z;
printf("Do you want to see the sequence of nodes created by BFS? Type 1 if yes. Else type something else. \n");
scanf("%d",&z);

if(z==1){
    int w;
    printf("\n BFS Sequence \n");
    printf("\n---------------------\n");
    for(w=0;w<parentNum;w++){
        if(w==0){
            printf("root ;;node: %d \n",w);
        }else{
            int p = parent[w];
            printf("node: %d ;; parent: %d \n",w,p);
        }
        print_sol(w);
        printf("\n---------------------\n");
    }
}

}

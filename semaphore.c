#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <time.h>


#define StudentNum 100          //Define How many Student
#define RoomNum 10              //Define How many Room
#define Capacity 4              //Capacity
#define CreationTime 3          // For creation time can not be 0
#define CleaningTime 8          // For Cleaning Time

sem_t RoomKeeper;             //for room
sem_t waitingRoom;            //for waiting room

int insideRoom[RoomNum] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Define how many students in room 
int studentLeft=StudentNum; //Define Student Next
int nextStudent=0;          //For adding next Student
int alldone=0;              //For check finish
int remainPlace=0;          //For empty place in room
int queue=0;                //For student enter the right room


void *student(void *id){
    if(nextStudent!=StudentNum){
   int studentId = *(int *)id;
   sleep(random()%CreationTime);
   printf("Student %d is created.\n", studentId);
   printf("Student %d is waiting for room...\n",studentId);
    remainPlace=Capacity-insideRoom[queue]; //get empty place
    remainPlace--; // empty place after student placed
    printf("Student %d entering the room %d\n",studentId,queue);
    insideRoom[queue]++; //student added room
    sem_wait(&waitingRoom); 
    
    if(remainPlace==3){
        printf("Student %d waking up the RoomKeeper\n",studentId);
    }

    if(remainPlace<4){
        printf("RoomKeeper%d :'The last %d Students , Lets get up.!!'\n",queue,remainPlace);
    }

    printview();//Draw rooms 2D
    
    if(remainPlace==0){ //If room is full then make it empty
           sem_post(&RoomKeeper);
           insideRoom[queue]=0;
           queue = (queue+1)%RoomNum;
    }
    
    
    }

}


void *room(void *id){
    int roomId = *(int *)id;
    while(!alldone){ //check finish if finish sleep all keeper than finish
        printf("RoomKeeper:%d is Sleeping...\n",roomId);
        sem_wait(&RoomKeeper);
        if(!alldone){ //check finish
            printf("RoomKeeper:%d is cleaning the room \n",roomId);
            
            
            

            for (int i = 0; i < Capacity; i++)//create room and make them empty
            {
                insideRoom[roomId]=0;
                sem_post(&waitingRoom);
            }
            
            
            sleep(CleaningTime);//Sleep for cleaning time
            printf("Room:%d is now clean and ready to take student\n",roomId);
        }
        else{
            printf("There is no student left\n");
        }
    }
    
}


void printview()//for 2D visual
{
    int q = 0,r=0;// Q FOR 
    printf("----Rooms------\n");
    for (int i = 0; i < RoomNum; i++)
    {
        printf("Room:%d [",i);
        r=Capacity-insideRoom[i];
        for (int j = 0; j < insideRoom[i]; j++)
        {
            printf("S");
        }
        
        for (int j = 0; j < r; j++)
        {
            printf("*");
        }
        printf("] \n");
        
    }
    
}
int main (int argc,char *argv[]){

    pthread_t RoomThread[RoomNum];
    pthread_t StudentThread[StudentNum];

    
    int numberOfStudents[StudentNum];
    int numberOfRooms[RoomNum];

   
    for(int i=0; i < StudentNum ; i++){//For define students id
        numberOfStudents[i]=i;
    }
    for(int i=0; i < RoomNum ; i++){//For define rooms id
        numberOfRooms[i]=i;
    }
    //Create semaphores
    sem_init(&waitingRoom,0,4);
    sem_init(&RoomKeeper,0,0);

    for(int i=0 ; i<RoomNum ; i++){ //Create Room Thread
        pthread_create(&RoomThread[i],NULL,(void *)room,(void *)&numberOfRooms[i]);
        sleep(random()%CreationTime);
    }
    for(int i=0 ; i<StudentNum ; i++){ //Create Student Thread
        pthread_create(&StudentThread[i],NULL,(void *)student,(void *)&numberOfStudents[i]);
       
        sleep(random()%CreationTime);
        
    }
    for (int i = 0; i < StudentNum; i++) { //Thread Join
        pthread_join(StudentThread[i],NULL);
        
    }
    sem_post(&RoomKeeper);
    alldone=1;

    for (int i = 0; i < RoomNum; i++) { //Thread Join
        pthread_join(RoomThread[i],NULL);
        
    }
    system("System Finished!");
    return 0;
    

}



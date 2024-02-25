#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


int change = 10;



void *truc (void *vargp){
  for (int i =0; i<5; i++) {
    sleep(1);
    printf("yolo %d\n", change);
    }
}

int main(){
  pthread_t thread_id;
  printf("before thread\n");
    pthread_create(&thread_id, NULL, truc, NULL);
//    pthread_join(thread_id, NULL);
//    printf("After Thread\n");
    for (int i = 0; i < 7; i++){
      sleep(1);
      printf("bachata %d\n", i);
      change += 1;
      }
}

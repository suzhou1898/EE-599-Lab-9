#include <iostream>
#include <pthread.h>
#include <queue>
#include <sstream>
using namespace std;

struct item{
    pthread_mutex_t mutex;
    pthread_cond_t notfull;
    pthread_cond_t notempty;
    queue<int> buffer;
};

struct item pdt;
int num=0;
int n1=0;
int n2=0;
int n3=0;

void init(struct item* t){
    pthread_mutex_init(&t->mutex,NULL);
    pthread_cond_init(&t->notfull,NULL);
    pthread_cond_init(&t->notempty,NULL);
}


void put(struct item *t,int data){
    pthread_mutex_lock(&t->mutex);
    while(n2>=num){
        pthread_cond_wait(&t->notfull,&t->mutex);
    }
    int r=rand()%100;
    t->buffer.push(r);
    n1++;
    n2++;
    if(n1%3==0) {
        printf("Producer %d produces item %d at index %d\n", data, n1, n1 % num + 2);
    }
    else{
        printf("Producer %d produces item %d at index %d\n", data, n1, n1 % num - 1);
    }
    if(n2>0) {
        pthread_cond_signal(&t->notempty);
    }
    pthread_mutex_unlock(&t->mutex);
}

void *putter(void *argv){
    int s=*(int *)argv;
    if(s==1){
        for(int i=0;i<100;i++){
            put(&pdt,s);
        }
    }
    else if(s==2){
        for(int i=0;i<50;i++){
            put(&pdt,s);
        }
    }
}

void get(struct item *t){
    pthread_mutex_lock(&t->mutex);
    while(n2<=0){
        pthread_cond_wait(&t->notempty,&t->mutex);
    }
    n2--;
    n3++;
    if(n3%3==0) {
        printf("Consumer consumes item %d at index %d\n", n3, n3 % num + 2);
    }
    else{
        printf("Consumer consumes item %d at index %d\n", n3, n3 % num - 1);
    }
    if(n2<num) {
        pthread_cond_signal(&t->notfull);
    }
    pthread_mutex_unlock(&t->mutex);
}

void *getter(void *argv){
    for(int i=0;i<150;i++){
        get(&pdt);
    }
}

int main(int argv, char **argc) {
    int size;
    int a=1;
    int b=2;
    stringstream ss(argc[1]);
    ss>>size;
    num=size;

    pthread_t pd1,pd2,cs;
    item *t=&pdt;
    init(t);

    pthread_create(&pd1,NULL,putter,(void *)&a);
    pthread_create(&pd2,NULL,putter,(void *)&b);
    pthread_create(&cs,NULL,getter,NULL);

    pthread_join(pd1,NULL);
    pthread_join(pd2,NULL);
    pthread_join(cs,NULL);
    return 0;
}
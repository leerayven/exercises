#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
/*
sem_t w, readcnt_m;
static int g_count;
static int read_cnt;
 * reader first
void* writer(void* ptr){
    for(int i=0; i!=1000;++i){
//        usleep(10001);
        sem_wait(&w);
        ++ g_count;
        printf("writer: %d\n", g_count);
        sem_post(&w);
    }
}

void* reader(void* ptr){
    for(int i=0; i!=1000;++i){
//        usleep(10009);
        sem_wait(&readcnt_m);
        ++ read_cnt;
        if(read_cnt == 1) sem_wait(&w);
        sem_post(&readcnt_m);

        printf("reader: %d\n", g_count);

        sem_wait(&readcnt_m);
        -- read_cnt;
        if(read_cnt == 0) sem_post(&w);
        sem_post(&readcnt_m);
    }
}
*/
sem_t resource, rmutex, wmutex, try_read;
static int g_count;
static int read_cnt, writer_cnt;
void* writer(void* ptr){
    for(int i=0; i!=10;++i){
        usleep(10001);
        sem_wait(&wmutex);
        ++ writer_cnt;
        if(writer_cnt == 1) sem_wait(&try_read);
        sem_post(&wmutex);
        sem_wait(&resource);
        ++ g_count;
        printf("writer: %d\n", g_count);
        sem_post(&resource);
        sem_wait(&wmutex);
        -- writer_cnt;
        if(writer_cnt == 0) sem_post(&try_read);
        sem_post(&wmutex);
    }
}
void* reader(void* ptr){
    for(int i=0; i!=10;++i){
        usleep(10009);
        sem_wait(&try_read);// block if writer waiting
        sem_wait(&rmutex);
        ++ read_cnt;
        if(read_cnt == 1) sem_wait(&resource);
        sem_post(&try_read);
        sem_post(&rmutex);
        printf("reader: %d\n", g_count);
        sem_wait(&rmutex);
        -- read_cnt;
        if(read_cnt == 0) sem_post(&resource);
        sem_post(&rmutex);
    }
}
int main(){
    sem_init(&resource, 0, 1);
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&try_read, 0, 1);
    pthread_t readers[5];
    pthread_t writers[5];
    for(int i = 0; i != 5; ++i){
        pthread_create(&(readers[i]), NULL, reader, NULL);
        pthread_create(&(writers[i]), NULL, writer, NULL);
    }
    for(int i = 0; i != 5; ++i){
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }
    return 0;
}

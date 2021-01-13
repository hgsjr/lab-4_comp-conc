#include<stdio.h>
#include<pthread.h>

int controle = 0;
pthread_mutex_t lock;
pthread_cond_t cond_ex;

void *thread1(void *args){

    printf("tudo bem?\n");

    pthread_mutex_lock(&lock);
    controle++;
    if(controle == 2){
        pthread_cond_broadcast(&cond_ex);
    }
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

void *thread2(void *args){

    printf("bom dia!\n");

    pthread_mutex_lock(&lock);
    controle++;
    if(controle == 2){
        pthread_cond_broadcast(&cond_ex);
    }
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}
void *thread3(void *args){

    pthread_mutex_lock(&lock);
    if(controle < 2){
        pthread_cond_wait(&cond_ex, &lock);
    }
    printf("até mais!\n");
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}
void *thread4(void *args){

    pthread_mutex_lock(&lock);
    if(controle < 2){
        pthread_cond_wait(&cond_ex, &lock);
    }
    printf("boa tarde!\n");
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(){

    pthread_t tid[4];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_ex, NULL);

    if(pthread_create(&tid[0], NULL, thread1, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }
    if(pthread_create(&tid[1], NULL, thread2, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }
    if(pthread_create(&tid[2], NULL, thread3, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }
    if(pthread_create(&tid[3], NULL, thread4, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }

    for(int thread = 0; thread < 4; thread++) {
        if(pthread_join(tid[thread], NULL)) {
            fprintf(stderr, "Erro ao executar pthread_join().\n");
            return 2;
        }
    }

    return 0;

}
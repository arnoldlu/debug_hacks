#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int cnt = 0;

void cnt_reset(void)
{
  while(1){};
}


void *thr(void)
{
  while(1) {
    if(cnt > 2)
      cnt_reset();
    else
      cnt++;

    printf("%d\n", cnt);
    sleep(1);
  }
}

int main(void)
{
  pthread_t tid;

  pthread_create(&tid, NULL, thr, NULL);
  pthread_join(tid, NULL);

  return EXIT_SUCCESS;
}

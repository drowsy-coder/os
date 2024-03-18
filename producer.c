#include <stdio.h>
#include <stdlib.h>

int mutex=1, full=0, empty=3, x=0;

void producer();
void consumer();
int waitSem(int);
int signalSem(int);

int main() {
    int n;
    printf("\n1.PRODUCER\n2.CONSUMER\n3.EXIT\n");
    while(1) {
        printf("\nENTER YOUR CHOICE\n");
        scanf("%d",&n);
        switch(n) {
            case 1:
                if((mutex==1)&&(empty!=0))
                    producer();
                else
                    printf("BUFFER IS FULL\n");
                break;
            case 2:
                if((mutex==1)&&(full!=0))
                    consumer();
                else
                    printf("BUFFER IS EMPTY\n");
                break;
            case 3:
                exit(0);
                break;
        }
    }
    return 0;
}

int waitSem(int s) {
    return(--s);
}

int signalSem(int s) {
    return(++s);
}

void producer() {
    mutex=waitSem(mutex);
    full=signalSem(full);
    empty=waitSem(empty);
    x++;
    printf("\nProducer produces the item %d",x);
    mutex=signalSem(mutex);
}

void consumer() {
    mutex=waitSem(mutex);
    full=waitSem(full);
    empty=signalSem(empty);
    printf("\nConsumer consumes item %d",x);
    x--;
    mutex=signalSem(mutex);
}

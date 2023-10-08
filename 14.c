#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main() {
int des[2];
char buf[80];
pipe(des);
write(des[1], "JAI SHREE RAM", sizeof("JAI SHREE RAM"));
read(des[0], buf, sizeof("JAI SHREE RAM"));
printf("output of pipe- %s\n", buf);
return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    struct rlimit rlim;
     printf("this process can open maxi file= %ld\n", rlim.rlim_cur);
     printf("size of circular buffer= %ld bytes\n", rlim.rlim_cur);

    return 0;
}


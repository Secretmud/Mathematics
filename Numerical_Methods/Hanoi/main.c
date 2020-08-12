#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Function prototyping.
 * @PARAM set, takes the number set you want to check 
 * */
__uint128_t hanoi(int set);
/*
 * @PARAM argc, argument counter
 * @PARAM argv, arguments in a char pointer array
 * */
int main(int argc, char * argv[]) {
    if (argc < 1) {
        printf("Please supply a set of hanoi\n\te.g\t./hanoi 5");
        return 0;
    }
    int set = atoi(argv[1]);
    int x = 0;
    __uint128_t hanoi_number = hanoi(set);
    char han[] = {hanoi_number};
    printf("Hanoi nr:\t%lld\tSet size:\t%d\n", hanoi_number, set);
    hanoi_number = 0;
    while (hanoi_number < 1000000) {
        hanoi_number = hanoi(x);
        if (hanoi_number > 1000000)
            break;
        ++x;
    }
    printf("\nNumber of turns:\t%lld\nSet size:\t%d\n", hanoi_number, x);
    return 0;
}
/*
 * Recursive tower of hanoi.
 * @PARAM set, is the number of blocks to move in the tower of hanoi game. 
 * @RETURN uint64_t 2*hanoi(set-1)+1 if set > 0
 * */
__uint128_t hanoi(int set) {
    if (set == 0)
        return 0;
    else 
        return 2*hanoi(set-1)+1;
}

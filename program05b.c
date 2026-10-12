#include <stdio.h>

void towers(int num, char frompeg, char topeg, char auxpeg) {
    if (num <= 0) return;
    if (num == 1) {
        printf("Move disk 1 from peg %c to peg %c\n", frompeg, topeg);
        return;
    }
    towers(num - 1, frompeg, auxpeg, topeg);
    printf("Move disk %d from peg %c to peg %c\n", num, frompeg, topeg);
    towers(num - 1, auxpeg, topeg, frompeg);
}

int main(void) {
    int num;
    printf("Enter the number of disks: ");
    if (scanf("%d", &num) != 1 || num < 0) return 1;
    if (num == 0) printf("No disks\n");
    else towers(num, 'A', 'C', 'B');
    return 0;
}

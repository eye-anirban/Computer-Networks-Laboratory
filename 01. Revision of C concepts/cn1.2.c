/******************************************************************************

2. Read two integers from command line and then print its sum .

*******************************************************************************/
#include <stdio.h>

int main(int argc , char* argv[])
{
    if(argc>2)
    {
        char *s1 = argv[1];
        char *s2 = argv[2];
        int x = atoi(s1);
        int y = atoi(s2);
        printf("Sum of these integers is %d",x+y);
    }
    else
    {
        printf("Insufficient Arguments !");
    }
    return 0;
}

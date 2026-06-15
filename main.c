#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcs.h"
//#include "funcs.c"

int main()
{
    int n=0;
    char k,c;
    struct route *A=NULL;

    do
    {
        scanf("%c",&k);
        while((c=getchar())!=EOF &&
              c!='\n' &&
              c!='\r');

        switch(k)
        {
            case 'i':
                free(A);
                A=readFromInput(&n);
                break;

            case 'f':

                free(A);
                A=readFromFile(&n);
                break;

            case 'p':

                if(A)
                    printData(A,n);
                else
                    printf("No data loaded\n");
                break;

            case 'l':

                if(A)
                    findShort(A,n);
                else
                    printf("No data loaded\n");

                break;

            case 's':

                if(A)
                    findLocation(A,n);
                else
                    printf("No data loaded\n");
                break;

            case 'u':

                if(A)
                    findUpHill(A,n);
                else
                    printf("No data loaded\n");
                break;

            case 'd':

                if(A)
                    findDownHill(A,n);
                else
                    printf("No data loaded\n");
                break;

            case 'h':

                if(A)
                    findAltitude(A,n);
                else
                    printf("No data loaded\n");

                break;

            case 't':

                if(A)
                    findTimely(A,n);
                else
                    printf("No data loaded\n");

                break;

            case 'o':

                if(A)
                    saveData(A,n);
                else
                    printf("No data loaded\n");
                break;

            case 'q':
                break;
        }

    }
    while(k!='q');
    free(A);
    return 0;
}

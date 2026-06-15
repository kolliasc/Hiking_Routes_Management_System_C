#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_STR 51

struct route
{
    char start[MAX_STR];
    int length;
    int uphill;
    int downhill;
    int max_alt;
    int min_alt;
    char end[MAX_STR];
};

struct route* readFromInput(int *n);
void printData(struct route A[], int n);
void findShort(struct route A[], int n);
void findLocation(struct route A[], int n);
void findUpHill(struct route A[], int n);
void findDownHill(struct route A[], int n);
void findAltitude(struct route A[], int n);
void findTimely(struct route A[], int n);
struct route* readFromFile(int *n);
void saveData(struct route A[], int n);

#endif

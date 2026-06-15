#include "funcs.h"

static double naismith(int length,int uphill)
{
    return (double)length/65.0+(double)uphill/10.0;
}

static bool isCircular(const struct route *r)
{
    return strcmp(r->start,r->end)==0;
}

static void printRoute(const char *from,
                       const char *to,
                       int uphill,
                       int downhill,
                       int max_alt,
                       int min_alt,
                       int length)
{
    int t=(int)round(naismith(length,uphill));

    printf("From %s to %s\n",from,to);

    printf("Uphill %d, Downhill %d\n",uphill,downhill);

    printf("Max altitude %d, Min altitude %d\n",max_alt,min_alt);

    printf("Length %d, Estimated time %d min\n\n",length,t);
}

const struct route *_sort_arr=NULL;

static int cmpDesc(const void *a,const void *b)
{
    int ia=*(const int*)a;

    int ib=*(const int*)b;

    return _sort_arr[ib].length-_sort_arr[ia].length;
}

static void sortedIndices(const struct route A[],int n,int idx[])
{
    for(int i=0;i<n;i++)
    {
        idx[i]=i;
    }

    _sort_arr=A;

    qsort(idx,n,sizeof(int),cmpDesc);
}

static void clearBuffer()
{
    int ch;

    while((ch=getchar())!='\n' && ch!=EOF);
}

struct route* readFromInput(int *n)
{
    printf("Enter number of routes: ");

    if(scanf("%d",n)!=1)
    {
        return NULL;
    }

    clearBuffer();

    struct route *A=malloc((*n)*sizeof(struct route));

    if(A==NULL)
    {
        return NULL;
    }

    for(int i=0;i<*n;i++)
    {
        printf("Route %d start: ",i+1);

        fgets(A[i].start,MAX_STR,stdin);

        A[i].start[strcspn(A[i].start,"\n\r")]='\0';

        printf("Enter length, uphill, downhill, max_alt, min_alt: ");

        scanf("%d %d %d %d %d",
              &A[i].length,
              &A[i].uphill,
              &A[i].downhill,
              &A[i].max_alt,
              &A[i].min_alt);

        clearBuffer();

        printf("Route %d end: ",i+1);

        fgets(A[i].end,MAX_STR,stdin);

        A[i].end[strcspn(A[i].end,"\n\r")]='\0';
    }

    return A;
}

void printData(struct route A[],int n)
{
    int idx[500];

    sortedIndices(A,n,idx);

    for(int k=0;k<n;k++)
    {
        int i=idx[k];

        printRoute(A[i].start,
                   A[i].end,
                   A[i].uphill,
                   A[i].downhill,
                   A[i].max_alt,
                   A[i].min_alt,
                   A[i].length);

        if(!isCircular(&A[i]))
        {
            printRoute(A[i].end,
                       A[i].start,
                       A[i].downhill,
                       A[i].uphill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }
    }
}

void findShort(struct route A[],int n)
{
    int L;

    scanf("%d",&L);

    int idx[500];

    sortedIndices(A,n,idx);

    for(int k=0;k<n;k++)
    {
        int i=idx[k];

        if(A[i].length<=L)
        {
            printRoute(A[i].start,
                       A[i].end,
                       A[i].uphill,
                       A[i].downhill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);

            if(!isCircular(&A[i]))
            {
                printRoute(A[i].end,
                           A[i].start,
                           A[i].downhill,
                           A[i].uphill,
                           A[i].max_alt,
                           A[i].min_alt,
                           A[i].length);
            }
        }
    }
}

void findLocation(struct route A[],int n)
{
    char loc[MAX_STR];

    scanf(" ");

    fgets(loc,MAX_STR,stdin);

    loc[strcspn(loc,"\n\r")]='\0';

    int idx[500];

    sortedIndices(A,n,idx);

    for(int k=0;k<n;k++)
    {
        int i=idx[k];

        bool fwd=strcmp(A[i].start,loc)==0;

        bool ret=!isCircular(&A[i]) &&
                 strcmp(A[i].end,loc)==0;

        if(fwd)
        {
            printRoute(A[i].start,
                       A[i].end,
                       A[i].uphill,
                       A[i].downhill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }

        if(ret)
        {
            printRoute(A[i].end,
                       A[i].start,
                       A[i].downhill,
                       A[i].uphill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }
    }
}

void findUpHill(struct route A[],int n)
{
    int idx[500];

    sortedIndices(A,n,idx);

    for(int k=0;k<n;k++)
    {
        int i=idx[k];

        if(A[i].uphill>A[i].downhill)
        {
            printRoute(A[i].start,
                       A[i].end,
                       A[i].uphill,
                       A[i].downhill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }

        if(!isCircular(&A[i]) &&
           A[i].downhill>A[i].uphill)
        {
            printRoute(A[i].end,
                       A[i].start,
                       A[i].downhill,
                       A[i].uphill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }
    }
}

void findDownHill(struct route A[],int n)
{
    int idx[500];

    sortedIndices(A,n,idx);

    for(int k=0;k<n;k++)
    {
        int i=idx[k];

        if(A[i].downhill>A[i].uphill)
        {
            printRoute(A[i].start,
                       A[i].end,
                       A[i].uphill,
                       A[i].downhill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }

        if(!isCircular(&A[i]) &&
           A[i].uphill>A[i].downhill)
        {
            printRoute(A[i].end,
                       A[i].start,
                       A[i].downhill,
                       A[i].uphill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }
    }
}

void findAltitude(struct route A[], int n)
{
    int lo, hi;
    scanf("%d %d", &lo, &hi);

    int idx[500];
    sortedIndices(A, n, idx);

    for (int k = 0; k < n; k++) {
        int i = idx[k];

        if (A[i].min_alt >= lo && A[i].max_alt <= hi) {

            printRoute(A[i].start, A[i].end,
                       A[i].uphill, A[i].downhill,
                       A[i].max_alt, A[i].min_alt,
                       A[i].length);

            if (!isCircular(&A[i])) {

                printRoute(A[i].end, A[i].start,
                           A[i].downhill, A[i].uphill,
                           A[i].max_alt, A[i].min_alt,
                           A[i].length);
            }
        }
    }
}

void findTimely(struct route A[],int n)
{
    int T;

    scanf("%d",&T);

    int idx[500];

    sortedIndices(A,n,idx);

    for(int k=0;k<n;k++)
    {
        int i=idx[k];

        double t1=naismith(A[i].length,
                           A[i].uphill);

        double t2=naismith(A[i].length,
                           A[i].downhill);

        if(t1<=T)
        {
            printRoute(A[i].start,
                       A[i].end,
                       A[i].uphill,
                       A[i].downhill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }

        if(!isCircular(&A[i]) &&
           t2<=T)
        {
            printRoute(A[i].end,
                       A[i].start,
                       A[i].downhill,
                       A[i].uphill,
                       A[i].max_alt,
                       A[i].min_alt,
                       A[i].length);
        }
    }
}

struct route* readFromFile(int *n)
{
    char filename[256];

    printf("Enter filename: ");

    scanf("%255s", filename);

    FILE *fp = fopen(filename,"r");

    if(fp==NULL)
    {
        printf("Cannot open file\n");

        *n=0;

        return NULL;
    }

    if(fscanf(fp,"%d",n)!=1)
    {
        fclose(fp);

        *n=0;

        return NULL;
    }

    struct route *A=malloc((*n)*sizeof(struct route));

    if(A==NULL)
    {
        fclose(fp);

        return NULL;
    }

    int ch;

    while((ch=fgetc(fp))!='\n' && ch!=EOF);

    for(int i=0;i<*n;i++)
    {
        fgets(A[i].start,MAX_STR,fp);

        A[i].start[strcspn(A[i].start,"\n\r")]='\0';

        fscanf(fp,"%d %d %d %d %d",
               &A[i].length,
               &A[i].uphill,
               &A[i].downhill,
               &A[i].max_alt,
               &A[i].min_alt);

        while((ch=fgetc(fp))!='\n' && ch!=EOF);

        fgets(A[i].end,MAX_STR,fp);

        A[i].end[strcspn(A[i].end,"\n\r")]='\0';
    }

    fclose(fp);

    return A;
}

void saveData(struct route A[], int n)
{
    char filename[256];

    scanf(" ");

    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n\r")] = '\0';

    FILE *fp = fopen(filename, "w");

    if (!fp)
    {
        printf("Error opening file\n");
        return;
    }

    int idx[500];

    sortedIndices(A, n, idx);

    for (int k = 0; k < n; k++)
    {
        int i = idx[k];

        int t = (int)round(naismith(A[i].length, A[i].uphill));

        fprintf(fp, "From %s to %s\n", A[i].start, A[i].end);
        fprintf(fp, "Uphill %d, Downhill %d\n", A[i].uphill, A[i].downhill);
        fprintf(fp, "Max altitude %d, Min altitude %d\n", A[i].max_alt, A[i].min_alt);
        fprintf(fp, "Length %d, Estimated time %d min\n\n", A[i].length, t);

        if (!isCircular(&A[i]))
        {
            int t2 = (int)round(naismith(A[i].length, A[i].downhill));

            fprintf(fp, "From %s to %s\n", A[i].end, A[i].start);
            fprintf(fp, "Uphill %d, Downhill %d\n", A[i].downhill, A[i].uphill);
            fprintf(fp, "Max altitude %d, Min altitude %d\n", A[i].max_alt, A[i].min_alt);
            fprintf(fp, "Length %d, Estimated time %d min\n\n", A[i].length, t2);
        }
    }

    fclose(fp);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

float* genArray(int n,int type)
{
    float *a = (float*)calloc( n, sizeof(float) );
    srand(time(NULL));
    int cur_value = 0;
    int sign = 0;
    for(int i=0; i < n ; i++)
    {
        a[i] = (float)rand()*rand()/(rand()+1);

        sign = (rand()%2==1)?1:0; //генерация знака для числа, в случае, если сгенерированно число четное знак плюс, иначе - минус
        if(sign!=0)
            a[i] *= (-1);
    }
    if(type == 1 || type == 2)
    {
        genSort(n,a);
        if(type == 2 )
        {
            for(int i=0; i < n ; i++)
                a[i] *= (-1);
        }
    }
    return a;
}

void genSort( int n, float *a)
{
    for(int i = 0 ; i < n-1  ; i++ )
    {
        find_exchange_min(a,i,n,0);
    }
}

void PrintArray( int n,float *a)
{
    for(int i=0; i < n ; i++)
        printf("%g ",a[i]);
}

void Selection_sort( int n, float *a)
{
    int mov_count1 = 0; //число перемещений для сортировки выбора
    for(int i = 0 ; i < n-1  ; i++ )
     mov_count1 = find_exchange_min(a,i,n,mov_count1);

    PrintArray(n,a);

    int cmp_count1 = n*(n-1)/2;//число сравнений,зависит только от размера массива
    printf("\n Number of comparisons:%d \n Number of permutations:%d ",cmp_count1,mov_count1);
}

int find_exchange_min(float *a,int i,int n,int mov_count1)
{
    float cur = a[i];
    int k = i;

    for(int j = i+1; j < n; j++)
    {
        if( cur > a[j])
        {
            cur = a[j];
            k = j;
        }
    }
    if(a[k]!=a[i])
    {
        a[k] = a[i]; // один обмен между элементами
        a[i] = cur;
        mov_count1++;
    }
    return mov_count1;

}

void Shell_sort(int n, float *b)
{
    int j;
    int dist = n/2;  //интервал между сортируемыми элементами массива
    float tmp;
    int cmp_count2 = 0;//число сравнений для сортировки Шелла
    int mov_count2 = 0;//число перемещений
    for(; dist > 0; )
    {
        for (int i = dist; i < n; i++)
        {
            tmp = b[i];
            for (j = i; j >= dist; j -= dist)
            {
                cmp_count2++;
                if (tmp < b[j - dist])
                {
                    b[j] = b[j - dist];
                    mov_count2++;
                }
                else
                    break;
            }

            b[j] = tmp;
        }
        dist /= 2;
    }
    PrintArray(n,b);   //вывод отсортированного массива
    printf("\n Number of comparisons:%d \n Number of permutations:%d ",cmp_count2,mov_count2);
}



int main(int argc, char **argv)
{
    setlocale(LC_CTYPE, "rus");
    char starthelp[100];
    printf("Type --start for start or type --help for help ");
    scanf("%s", starthelp);

    if (starthelp[2] == 'h'){
        printf("Программа проводит сортировку двумя методами : ");
        printf("сортировку выбором и сортировку методом Шелла");
        printf("\nНеобходимо ввести число элементов и тип массива ");
        printf("\n1 - отсортирован по невозрастанию,");
        printf("\n2 - отсортирован по неубыванию");
        printf("\n3 и 4 - случайный массив.");
        printf("\nНа выходе программа выдает отсортированный массив");
        printf(",число сравнений и перемещений.\n");
    }
    else if(starthelp[2] != 'h' && starthelp[2] != 's'){
        printf("Oh");
        return 0;
    }
    printf("\nВведите количество элементов в массиве: ");
    int n;
    int type; //type - переменная, обозначающая тип массива, который будет сгенерирован
    scanf("%d",&n);
    printf("Введите тип массива:");
    scanf("%d",&type);

    float *a = (float*)calloc( n,sizeof(float) );
    float *b = (float*)calloc( n,sizeof(float) );
    a = genArray(n,type);
    b = a;
    printf("\nИсходный массив:   ");
    PrintArray(n,a);

    printf("\nСортировка выбора: ");
    Selection_sort(n,a);

    printf("\nМетодом Шелла:     ");
    Shell_sort(n,b);

    return 0;

}

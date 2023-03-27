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

        sign = (rand()%2==1)?1:0; //��������� ����� ��� �����, � ������, ���� �������������� ����� ������ ���� ����, ����� - �����
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
    int mov_count1 = 0; //����� ����������� ��� ���������� ������
    for(int i = 0 ; i < n-1  ; i++ )
     mov_count1 = find_exchange_min(a,i,n,mov_count1);

    PrintArray(n,a);

    int cmp_count1 = n*(n-1)/2;//����� ���������,������� ������ �� ������� �������
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
        a[k] = a[i]; // ���� ����� ����� ����������
        a[i] = cur;
        mov_count1++;
    }
    return mov_count1;

}

void Shell_sort(int n, float *b)
{
    int j;
    int dist = n/2;  //�������� ����� ������������ ���������� �������
    float tmp;
    int cmp_count2 = 0;//����� ��������� ��� ���������� �����
    int mov_count2 = 0;//����� �����������
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
    PrintArray(n,b);   //����� ���������������� �������
    printf("\n Number of comparisons:%d \n Number of permutations:%d ",cmp_count2,mov_count2);
}



int main(int argc, char **argv)
{
    setlocale(LC_CTYPE, "rus");
    char starthelp[100];
    printf("Type --start for start or type --help for help ");
    scanf("%s", starthelp);

    if (starthelp[2] == 'h'){
        printf("��������� �������� ���������� ����� �������� : ");
        printf("���������� ������� � ���������� ������� �����");
        printf("\n���������� ������ ����� ��������� � ��� ������� ");
        printf("\n1 - ������������ �� �������������,");
        printf("\n2 - ������������ �� ����������");
        printf("\n3 � 4 - ��������� ������.");
        printf("\n�� ������ ��������� ������ ��������������� ������");
        printf(",����� ��������� � �����������.\n");
    }
    else if(starthelp[2] != 'h' && starthelp[2] != 's'){
        printf("Oh");
        return 0;
    }
    printf("\n������� ���������� ��������� � �������: ");
    int n;
    int type; //type - ����������, ������������ ��� �������, ������� ����� ������������
    scanf("%d",&n);
    printf("������� ��� �������:");
    scanf("%d",&type);

    float *a = (float*)calloc( n,sizeof(float) );
    float *b = (float*)calloc( n,sizeof(float) );
    a = genArray(n,type);
    b = a;
    printf("\n�������� ������:   ");
    PrintArray(n,a);

    printf("\n���������� ������: ");
    Selection_sort(n,a);

    printf("\n������� �����:     ");
    Shell_sort(n,b);

    return 0;

}

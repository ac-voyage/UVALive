/* UVALive :: Regionals 2010 :: North America - Rocky Mountain. Problem 4886 - Page Count, by Abreto. */
#include <stdio.h>

#define MAX(a, b)   (((a)>(b))?(a):(b))
#define MIN(a, b)   (((a)<(b))?(a):(b))

#define IS_DIGIT(c) (((c)>='0')&&((c)<='9'))
int readn(int *follower)
{
    int x = 0;char ch = getchar();
    for(;!IS_DIGIT(ch);ch=getchar());
    for(;IS_DIGIT(ch)&&(x<1024);ch=getchar()) x=x*10+ch-'0';
    for(;(' '==ch)||IS_DIGIT(ch);ch=getchar());
    if( NULL != follower ) *follower = ch;
    return x;
}

int total_pages = 0;
int if_printed[1024] = {0};

int main(void)
{
    while(total_pages = readn(NULL))
    {
        int i = 0;
        int next = 0;
        for(i = 1;i <= total_pages;++i) if_printed[i] = 0;
        do
        {
            int low = readn(&next);
            if( '-' == next )
            {
                int high = readn(&next);
                if( low <= high )
                {
                    low = MAX(1, low);
                    high = MIN(high, total_pages);
                    for(i = low;i <= high;++i)
                        if_printed[i] = 1;
                }
            }
            else
                if( low >= 1 && low <= total_pages )
                    if_printed[low] = 1;
        }while('\n' != next);
        for(next = 0,i = 1;i <= total_pages;++i)
            next += if_printed[i];
        printf("%d\n", next);
    }
    return 0;
}

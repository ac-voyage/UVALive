/* UVALive :: Regionals 2010 :: North America - Rocky Mountain. Problem 4883 - Ropes, by Abreto <m@abreto.net>. */
#include <stdio.h>

int N = 0;
int P[128] = {0};
int S = 0;

#define MIN(a, b)   (((a)<(b))?(a):(b))
int ans(int len)
{
    if( S * 2 > len )
        return 0;
    else
    {
        int i = 0;
        int max_climbers = len / P[0] + 1;
        for(i = 1;i < N;++i)
            max_climbers = MIN(max_climbers, len/P[i]+1);
        return max_climbers;
    }
}

int main(void)
{
    scanf("%d", &N);
    do
    {
        int i = 0;
        S = 0;
        for(i = 0;i < N;++i)
        {
            scanf("%d", P+i);
            S += P[i];
        }
        printf("%d %d %d\n", ans(50), ans(60), ans(70));
        scanf("%d", &N);
    }while(0 != N);
    return 0;
}

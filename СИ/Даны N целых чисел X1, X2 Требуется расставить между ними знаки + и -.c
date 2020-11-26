#include <stdio.h>
#include <stdlib.h>

int pro(int * nums, int i, int sum, int s)
{
    if ( i )
    {
        if(pro(nums, i - 1, sum + nums[i - 1], s))
        {
            printf("+%d",nums[i-1]);
            return 1;
        }
        else if(pro(nums, i - 1, sum - nums[i - 1], s))
        {
            printf("-%d",nums[i-1]);
            return 1;
        }
        return 0;
    }
    return s == sum;
}

int main()
{
    while(1)
    {
        int nums[100], n, s;
        scanf("%d",&n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &nums[i]);
        scanf("%d",&s);
        int result[100];
        for(int i=0;i<n;i++)
            result[i] = nums[i+1];
        printf("%d",nums[0]);
        if(!pro(result, n-1, 0, s-nums[0]))
        {
            system("cls");
            printf("No solution\n");
        }
        else
            printf("=%d\n",s);
    }
    return 0;
}
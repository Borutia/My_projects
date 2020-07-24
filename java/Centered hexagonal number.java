import java.util.Scanner;

public class main {
    static boolean isCenteredhexagonal(int N)
    {
        float n = (float)((3 + Math.sqrt(12 * N - 3)) / 6);
        return (n - (int)n) == 0;
    }

    static int search_count(int n)
    {
        return (int)(3+Math.sqrt(12*n-3))/6;
    }

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        System.out.print("n = ");
        int N = in.nextInt();

        if (!isCenteredhexagonal(N))
        {
            System.out.print("Invalid");
        }
        else
        {
            int count = search_count(N);
            int counter = count;
            int space = count-1;
            for(int i=0;i<count*2 - 1;i++)
            {
                for(int k = 0;k<space;k++)
                    System.out.print(" ");
                for(int j = 0;j<counter;j++)
                    System.out.print("o ");
                System.out.println();
                if(i+1 < count) {
                    counter++;
                    space--;
                }
                else
                {
                    counter--;
                    space++;
                }
            }
        }
    }

}

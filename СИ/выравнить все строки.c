#include <stdio.h>

int main ()
{
    FILE *fp;
    fp=fopen ("input.txt", "r");
    int m=0, k=0, i;
    int count_str = 0;
    do
    {
        while ((getc(fp)!='\n') && (!feof(fp)))
            k++;
        if (k>m)
            m=k;
        k=0;
        count_str++;
    } while (!feof(fp));
    rewind (fp);
    FILE *fp_out;
    fp_out=fopen ("output.txt", "w");
    int space, len, beginning_line;
    char c;
    int temp_counter = 1;
    do
    {
        if(temp_counter == count_str)
        {
            while (((c=getc(fp))!='\n') && (!feof(fp)))
                fprintf (fp_out, "%c", c);
            break;
        }
        space=len=0;
        beginning_line=ftell (fp);
        //считаем количество пробелов
        while (((c=getc(fp))!='\n') && (!feof(fp)))
        {
            if (c==' ')
                space++;
            len++;
        }
        fseek (fp, beginning_line, SEEK_SET);
        while (((c=getc(fp))!='\n') && (!feof(fp)))
        {
            if (c!=' ')
                fprintf (fp_out, "%c", c);
            else
            {
                if ((m-len)%space) {
                    k=(m-len)/space+2;
                    len++;
                }
                else
                    k=(m-len)/space+1;
                for (i=0; i<k; i++)
                    fprintf (fp_out, " ");
            }
        }
        fprintf (fp_out, "\n");
        temp_counter++;
    } while (!feof(fp));
    fclose (fp);
    fclose (fp_out);
    return 0;
}
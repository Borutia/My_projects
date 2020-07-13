#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int dec2oct(int num)
{
    int out = 0, order = 1;
    while(num)
    {
        out += (num & 0x7) * order;
        num >>= 3;
        order *= 10;
    }
    return out;
}
int main()
{
    const int n = 8;
    int arr[n];
    for(int i=0;i<n;i++)
        cin >> arr[i];

    cout << "normal decimal format: ";
    for(int i=0;i<n;i++)
        cout << arr[i] << ' ';
    cout << endl;

    cout << "normal octal format: ";
    for(int i=0;i<n;i++)
        cout << dec2oct(arr[i]) << ' ';
    cout << endl;

    for(int i=0;i<n;i++)
    {
        if(arr[i]%2==0)
        {
            for(int j=0;j<8;j++)
            {
                if(j%2!=0)
                    arr[i] &= ~(1 << j);
            }
        }
        else
        {
            for(int j=0;j<8;j++)
            {
                if(j%2==0)
                    arr[i] |= (1 << j);
            }
        }
    }

    cout << "modified decimal format: ";
    for(int i=0;i<n;i++)
        cout << arr[i] << ' ';
    cout << endl;

    cout << "modified octal format: ";
    for(int i=0;i<n;i++)
        cout << dec2oct(arr[i]) << ' ';
    cout << endl;

    return 0;
}
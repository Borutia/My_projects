#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& comb)
{
    static int count = 0;
    cout << ++count << ": ";
    for (int i = 0; i < comb.size(); ++i)
    {
        cout << comb[i] << " ";
    }
    cout << endl;
}

void func(vector<int>& comb,vector<int>& A,int start, int k)
{
    if (k == 0) {
        print(comb);
        return;
    }

    for (int i = start; i <= A.size() - k; ++i)
    {
        comb.push_back(A[i]);
        func(comb,A,i+1, k-1);
        comb.pop_back();
    }
}

int main()
{
    vector<int> A;
    vector<int> comb;
    int n, k;
    cout << "n = ";
    cin >> n;
    cout << "k = ";
    cin >> k;

    cout << endl;
    int num;
    for (int i = 0; i < n; i++)
    {
        num = rand()%10;
        cout << num;
        A.push_back(num);
    }
    cout << endl;

    func(comb,A,0, k);

    system("pause");
    return 0;
}

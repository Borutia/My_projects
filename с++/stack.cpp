#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    T *stackPtr;
    int top;
public:
    Stack(int size)
    {
        stackPtr = new T[size];
        top = 0;
    }
    void push(const T &value)
    {
        stackPtr[top++] = value;
    }

    T pop()
    {
        stackPtr[--top];
    }

    void printStack()
    {
        for (int ix = top - 1; ix >= 0; ix--)
            cout << stackPtr[ix] << " ";
    }
};

int main()
{
    int size;
    cout << "Размер стека: ";
    cin >> size;
    Stack<int>my_stack(size);
    for(int i=0;i<size;i++)
        my_stack.push(i);
    cout << "Вывод стека: ";
    my_stack.printStack();
    cout << endl;
    cout << "Удаление двух элементов" << endl;
    my_stack.pop();
    my_stack.pop();
    cout << "Вывод стека: ";
    my_stack.printStack();
    return 0;
}
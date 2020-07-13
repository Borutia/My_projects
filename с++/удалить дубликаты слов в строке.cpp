#include <iostream>
#include <string>
#include <sstream>
int main()
{
    int quant = 0;
    std::string s, str, temp;
    getline(std::cin,temp);

    std::stringstream full_str(temp);

    while(full_str >> str)
    {
        quant++; //Инкрементируем количество
        s += str + " "; //"Приписываем" слово к строке s
    }

    char* chStr = new char[s.size() + 1]; //Создаём символьный массив по размеру s, плюс 1 для '\0'
    std::strcpy(chStr, s.c_str()); //Копируем s строку в массив chStr

    //Первое использование функции strtok(). В качестве указателя используем chStr.
    //Далее будем использовать NULL. Функция нужна для исключения запятых, точек, скобок и т. д.
    char* p = std::strtok(chStr, " ,.!?\"(){}:;");

    int counter = 0;
    std::string* words = new std::string[quant]; //Создаем строковый массив по размеру найденного количества
    while(p != NULL)
    {
        words[counter] = p; //Сохраняем слово в массив
        counter++; //Увеличиваем значение индекса
        p = std::strtok(NULL, " ,.!?\"(){}:;");
    }

    std::string result;
    counter = 0;
    bool check = false;
    //Поиск
    for(int i = 0; i < quant; i++)
    {
        s = words[i]; //Сохраняем слово в s
        for(int j = 0; j < quant; j++)
        {
            if(s.empty()) //Если слово пустое
                break;    //выходим из цикла
            if(s == words[j] && s.size()>5) //Если нашлось подобное слово
            {
                counter++; //Увеличиваем счётчик
                words[j].clear(); //"Очищаем" элемент массива (т. е. слово)
            }

        }
        if(counter > 1) //Если счётчик больше одного, т.е. слово наткнулось не только на себя
        {
            result += s + " ";
            check = true; //Меняем значение check на true
        }
        counter = 0; //Обнуляем счётчик
    }

    if (!check)
        std::cout << "Nothing found"<<std::endl;
    else {
        for(int i=0;i<quant;i++)
            result += words[i] + " ";
        std::cout << std::endl;
        std::cout << result << std::endl;
    }


    return 0;
}
#include "chain.h"

int main()
{
    setlocale(LC_ALL, "Russian");  
    LinkedList list;  
    try
    {
        cout << "Игра в слова!" << endl;
        list.BuildFromFile("input.txt");
        cout << "\nИсходные слова из файла input.txt:" << endl;
        list.PrintOriginal(cout);
        if (list.Solve())
        {
            cout << "\nРезультат:" << endl;
            list.Print(cout);
            ofstream output("output.txt");
            list.Print(output);
            cout << "\nЦепочка успешно построена!" << endl;
            cout << "\nСохранено в output.txt" << endl;
        }
        else
        {
            cout << "\nЦепочка не найдена" << endl;
        }
    }
    catch (const char* e)  
    {
        cerr << "\nОшибка: " << e << endl;
        return 1;
    }
    return 0;
}
#ifndef CHAIN_H
#define CHAIN_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class LinkedList
{
private:
    struct Node
    {
        string word;   
        Node* next;     
        Node(const string& w) : word(w), next(nullptr) {} // Конструктор узла
    };
    Node* head;        
    Node* chain;        
    vector<bool> flag;  
    void Add(const string& word);            // Добавление слова в список
    bool IsCorrect(const string& word);      // Проверка корректности слова
    char LastChar(const string& word);       // Получение последней буквы 
    bool FindChain(Node* currtail);          // Рекурсивный поиск цепочки
    void Clear(Node*& Head);                 // Очистка списка
public:
    // Конструктор и деструктор
    LinkedList();
    ~LinkedList();
    void BuildFromFile(const string& filename);  // Загрузка слов из файла
    void PrintOriginal(ostream& out) const;      // Вывод исходных слов
    bool Solve();                                // Построение цепочки
    void Print(ostream& out) const;              // Вывод результата
};
#endif
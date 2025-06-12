#include "chain.h"

LinkedList::LinkedList() : head(nullptr), chain(nullptr) {}// Конструктор 
LinkedList::~LinkedList()// Деструктор - очищает память
{
    Clear(head);
    Clear(chain);
}
void LinkedList::Add(const string& word)// Добавление слова в конец списка
{
    Node* newNode = new Node(word);
    if (!head)  
    {
        head = newNode;
    }
    else  
    {
        Node* temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    flag.push_back(false);  
}
bool LinkedList::IsCorrect(const string& word) // Проверка на правильный ввод
{
    for (char c : word)
    {
        if (!((c >= 'а' && c <= 'я') || c == 'ь' || c == 'ё'))
        {
            return false;
        }
    }
    return true;
}
char LinkedList::LastChar(const string& word)// Получение последней буквы слова
{
    if (word.empty())
    {
        throw "Пусто";
    }
    char last = word.back();  
    if (last == 'ь' && word.size() > 1)
    {
        return word[word.size() - 2]; 
    }
    return last;
}
bool LinkedList::FindChain(Node* currtail) // Рекурсивный поиск цепочки
{
    if (count(flag.begin(), flag.end(), false) == 0)
    {
        char last = LastChar(currtail->word);
        char first = chain->word.front();
        return last == first;
    }
    Node* curr = head;
    int i = 0;
    while (curr)
    {
        if (!flag[i])
        {
            bool canAdd = false;
            if (!currtail)
            {
                canAdd = true;
            }
            else
            {
                char needed = LastChar(currtail->word);
                char actual = curr->word.front();
                canAdd = (needed == actual);
            }
            if (canAdd)
            {
                Node* newNode = new Node(curr->word);
                if (!chain)
                {
                    chain = newNode;
                }
                else
                {
                    Node* tail = chain;
                    while (tail->next) tail = tail->next;
                    tail->next = newNode;
                }
                flag[i] = true;
                if (FindChain(newNode))
                {
                    return true;
                }
                flag[i] = false;
                if (chain == newNode)
                {
                    chain = nullptr;
                }
                else
                {
                    Node* prev = chain;
                    while (prev->next != newNode) prev = prev->next;
                    prev->next = nullptr;
                }
                delete newNode;
            }
        }
        curr = curr->next;
        i++;
    }
    return false;
}
void LinkedList::Clear(Node*& Head) // Очистка списка
{
    while (Head)
    {
        Node* temp = Head;
        Head = Head->next;
        delete temp;
    }
}
void LinkedList::BuildFromFile(const string& filename)// Загрузка слов из файла
{
    ifstream input(filename);
    if (!input.is_open())
    {
        throw "Не удалось открыть файл";
    }
    string first;
    if (!(input >> first))
    {
        throw "Файл пуст";
    }
    if (!IsCorrect(first))
    {
        throw "Недопустимые символы в первом слове";
    }
    Add(first);
    string word;
    while (input >> word)
    {
        if (!IsCorrect(word))
        {
            Clear(head);
            throw "Недопустимые символы. Используйте только нижний регистр и русские буквы!";
        }
        Add(word);
    }
}
void LinkedList::PrintOriginal(ostream& out) const // Вывод исходного списка
{
    Node* curr = head;
    while (curr)
    {
        out << curr->word;
        if (curr->next)
        {
            out << " ";
        }
        curr = curr->next;
    }
    out << endl;
}
bool LinkedList::Solve()// Построение цепочки
{
    return FindChain(nullptr);
}
void LinkedList::Print(ostream& out) const // Вывод результата
{
    Node* curr = chain;
    while (curr)
    {
        out << curr->word;
        if (curr->next)
        {
            out << " -> ";
        }
        curr = curr->next;
    }
    if (!chain)
    {
        out << "Цепочка не найдена";
    }
    out << endl;
}
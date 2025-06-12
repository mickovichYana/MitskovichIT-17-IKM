#include "chain.h"

LinkedList::LinkedList() : head(nullptr), chain(nullptr) {}// ����������� 
LinkedList::~LinkedList()// ���������� - ������� ������
{
    Clear(head);
    Clear(chain);
}
void LinkedList::Add(const string& word)// ���������� ����� � ����� ������
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
bool LinkedList::IsCorrect(const string& word) // �������� �� ���������� ����
{
    for (char c : word)
    {
        if (!((c >= '�' && c <= '�') || c == '�' || c == '�'))
        {
            return false;
        }
    }
    return true;
}
char LinkedList::LastChar(const string& word)// ��������� ��������� ����� �����
{
    if (word.empty())
    {
        throw "�����";
    }
    char last = word.back();  
    if (last == '�' && word.size() > 1)
    {
        return word[word.size() - 2]; 
    }
    return last;
}
bool LinkedList::FindChain(Node* currtail) // ����������� ����� �������
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
void LinkedList::Clear(Node*& Head) // ������� ������
{
    while (Head)
    {
        Node* temp = Head;
        Head = Head->next;
        delete temp;
    }
}
void LinkedList::BuildFromFile(const string& filename)// �������� ���� �� �����
{
    ifstream input(filename);
    if (!input.is_open())
    {
        throw "�� ������� ������� ����";
    }
    string first;
    if (!(input >> first))
    {
        throw "���� ����";
    }
    if (!IsCorrect(first))
    {
        throw "������������ ������� � ������ �����";
    }
    Add(first);
    string word;
    while (input >> word)
    {
        if (!IsCorrect(word))
        {
            Clear(head);
            throw "������������ �������. ����������� ������ ������ ������� � ������� �����!";
        }
        Add(word);
    }
}
void LinkedList::PrintOriginal(ostream& out) const // ����� ��������� ������
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
bool LinkedList::Solve()// ���������� �������
{
    return FindChain(nullptr);
}
void LinkedList::Print(ostream& out) const // ����� ����������
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
        out << "������� �� �������";
    }
    out << endl;
}
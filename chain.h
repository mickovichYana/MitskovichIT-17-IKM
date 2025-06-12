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
        Node(const string& w) : word(w), next(nullptr) {} // ����������� ����
    };
    Node* head;        
    Node* chain;        
    vector<bool> flag;  
    void Add(const string& word);            // ���������� ����� � ������
    bool IsCorrect(const string& word);      // �������� ������������ �����
    char LastChar(const string& word);       // ��������� ��������� ����� 
    bool FindChain(Node* currtail);          // ����������� ����� �������
    void Clear(Node*& Head);                 // ������� ������
public:
    // ����������� � ����������
    LinkedList();
    ~LinkedList();
    void BuildFromFile(const string& filename);  // �������� ���� �� �����
    void PrintOriginal(ostream& out) const;      // ����� �������� ����
    bool Solve();                                // ���������� �������
    void Print(ostream& out) const;              // ����� ����������
};
#endif
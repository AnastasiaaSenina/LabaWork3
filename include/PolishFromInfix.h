#ifndef __PolishFromInfix_H__
#define __PolishFromInfix_H__

#include <cstring>
#include "math.h"
using namespace std;
template < typename T >
struct CNode {
  T data;
  CNode* next;
};
struct Lexeme {
  char* data;
  Lexeme* next;
};
struct Variable {
  char var;
  double value;
  Variable* next;
};


 class PolishFromInfix{
 private :
  char* Infix;
  int LenOfInfix;
  char* PolishExp;
  double Value;
  int GetPrioritetOfOperation(char simbol);
  bool IsOperation(char simbol);
  Lexeme* Preobr(); // �������������� ��������� � ������ �������� ������

public:

  PolishFromInfix(char* a);
  PolishFromInfix();
  double GetValue() { return Value; }
  bool CheckOnCorrect();  // �������� �� ������������ ��������� ���������
 
  char* ConvertMathEXpression(); // ��������������� �� ��������� � ����������� ������ ���������
  void ValueExpression(Variable* m); // ���������� �������� ��������� �� �������� ����������

};

void pushBack(Lexeme** Head, Lexeme** Tail, char* token);  //������������ ������ ������ ��������������� ���������  
Variable* ListOfValues(Variable*, char, double);  //������������ ������ �������� ����������


#endif



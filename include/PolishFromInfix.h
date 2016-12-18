#ifndef __PolishFromInfix_H__
#define __PolishFromInfix_H__

#include <string>
#include <cstdlib>
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

template < typename T >
class stack {
  CNode < T > *top;
  int count;
public:
  int GetCount() { return count; }
  stack() { top = 0; count = 0; }
  void push(T x);
  T& GetTop();
  void pop();
  bool IsEmpty() { return count == 0; }
};


PolishFromInfix{
protected:
  char* Infix;
  int LenOfInfix;
  char* PolishExp;
  double Value;

public:

  PolishFromInfix(char* a)
  {
    LenOfInfix = strlen(a);
    int i = 0;
    Infix = new char[LenOfInfix + 1];
    while (a[i] != 0) {
      Infix[i] = a[i];
      i++;
    }
    Infix[LenOfInfix] = 0;
  }

  PolishFromInfix()
  {
    delete[] Infix;
    delete[] PolishExp;

  }
  double GetValue() { return Value; }
  bool CheckOnCorrect();  // проверка на корректность заданного выражения
  int GetPrioritetOfOperation(char simbol);
  bool IsOperation(char simbol);
  Lexeme* Preobr(); // преобразование выражение в список значимых лексем
  char* ConvertMathEXpression(); // конвертирование из инфиксной в постфиксную запись выражения
  void ValueExpression(Variable* m); // вычисление значения выражения по заданным переменным

};
template < typename T >
void stack < T > ::push(T x) {
  CNode < T > *node = new CNode < T >;
  node->data = x;
  node->next = top;
  top = node;
  count++;
}
template < typename T >
T& stack < T > ::GetTop() {
  if (top != 0) {
    return top->data;
  }
  else {
    throw 1;
  }
}
template < typename T >
void stack < T > ::pop() {
  if (top != 0) {
    CNode < T > *s = top;
    top = top->next;
    delete s;
    count--;
  }
  else {
    throw 1;
  }
}
void pushBack(Lexeme** Head, Lexeme** Tail, char* token);  //формирование списка лексем математического выражения  
Variable* ListOfValues(Variable*, char, double);  //формирование списка значения переменных


#endif



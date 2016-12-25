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
  Lexeme* Preobr(); // преобразование выражение в список значимых лексем

public:

  PolishFromInfix(char* a);
  PolishFromInfix();
  double GetValue() { return Value; }
  bool CheckOnCorrect();  // проверка на корректность заданного выражения
 
  char* ConvertMathEXpression(); // конвертирование из инфиксной в постфиксную запись выражения
  void ValueExpression(Variable* m); // вычисление значения выражения по заданным переменным

};

void pushBack(Lexeme** Head, Lexeme** Tail, char* token);  //формирование списка лексем математического выражения  
Variable* ListOfValues(Variable*, char, double);  //формирование списка значения переменных


#endif



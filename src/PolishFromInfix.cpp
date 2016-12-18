#include "PolishFromInfix.h"

int PolishFromInfix::GetPrioritetOfOperation(char simbol) {
  int priorit;
  switch (simbol) {
  case '(': priorit = 1; break;
  case '-': priorit = 2; break;
  case '+': priorit = 2; break;
  case '*': priorit = 3; break;
  case '/': priorit = 3; break;
  case '^': priorit = 4; break;
  case '|': priorit = 1; break;
  case '_': priorit = 5; break;
  default: priorit = 0;

  }
  return priorit;

}
bool PolishFromInfix::IsOperation(char simbol) {
  if (simbol == '+' || simbol == '-' || simbol == '*' || simbol == '/' || simbol == '^') return true;
  else return false;
}


Lexeme* PolishFromInfix::Preobr(){
  if (!CheckOnCorrect())
  {
    throw 1;
  }
  Lexeme* Head = NULL;
  Lexeme* Tail = NULL;
  int i = 0;
  while (Infix[i] != 0) {
    if (IsOperation(Infix[i]) || Infix[i] == '|') {
      char *str = new char[2];
      str[0] = Infix[i];
      str[1] = 0;
      pushBack(&Head, &Tail, str);
    }
    else {
      if (Infix[i] == '(') {
        char *str = new char[2];
        str[0] = Infix[i];
        str[1] = 0;
        pushBack(&Head, &Tail, str);
      }
      else {
        if (Infix[i] == ')') {
          char *str = new char[2];
          str[0] = Infix[i];
          str[1] = 0;
          pushBack(&Head, &Tail, str);
        }
      }
    }
    if (Infix[i] <= '9' && Infix[i] >= '0') {
      int j = 0;
      char *str = new char[15];
      while ((Infix[i] >= '0' && Infix[i] <= '9') || (Infix[i] == '.')) {
        str[j] = Infix[i];
        j++;
        i++;
      }
      i--;
      str[j] = 0;
      pushBack(&Head, &Tail, str);
    }
    if (Infix[i] >= 'a' && Infix[i] <= 'z') {
      char *str = new char[2];
      str[0] = Infix[i];
      str[1] = 0;
      pushBack(&Head, &Tail, str);
    }
    i++;
  }
  return Head;
}

void pushBack(Lexeme** Head, Lexeme** Tail, char* token) {
  if (*Head == 0){
    Lexeme* tmp = new Lexeme;
    tmp->next = NULL;
    tmp->data = token;
    *Tail = tmp;
    *Head = *Tail;
  }
  else {
    Lexeme* tmp = new Lexeme;
    tmp->next = NULL;
    tmp->data = token;
    (*Tail)->next = tmp;
    *Tail = (*Tail)->next;
  }
}
char* PolishFromInfix::ConvertMathEXpression() {
  Lexeme* Head = NULL;
  Lexeme* LastHead = NULL;
  bool flag = false;//true - был открывающийся модуль
  stack < char > a;
  Head = Preobr();
  int i = 0;
  PolishExp = new char[LenOfInfix * 2 + 1];
  while (Head != 0) {
    if ((Head->data[0] <= 'z'&& Head->data[0] >= 'a') || (Head->data[0] <= '9' && Head->data[0] >= '0')) {
      int j = 0;
      while (Head->data[j] != 0) {
        PolishExp[i] = Head->data[j];
        j++;
        i++;
      }
      PolishExp[i] = ' ';
      i++;
    }
    else {
      if (IsOperation(Head->data[0])) {
        if ((i == 0 || LastHead->data[0] == '(' || (LastHead->data[0] == '|' && flag == true)) && Head->data[0] == '-') {
          a.push('_');// унарный минус
        }
        else {
          if (!a.IsEmpty()) {
            if (GetPrioritetOfOperation(Head->data[0]) > GetPrioritetOfOperation(a.GetTop()))
              a.push(Head->data[0]);
            else {
              while (!a.IsEmpty() && GetPrioritetOfOperation(Head->data[0]) <= GetPrioritetOfOperation(a.GetTop())) {
                PolishExp[i] = a.GetTop();
                a.pop();
                i++;
              }
              a.push(Head->data[0]);
            }
          }
          else a.push(Head->data[0]);

        }
      }
    }

    if (Head->data[0] == '(')
      a.push('(');
    else {
      if (Head->data[0] == ')'){
        while (a.GetTop() != '(') {
          PolishExp[i] = a.GetTop();
          a.pop();
          i++;
        }
        a.pop();
      }
    }
    if (Head->data[0] == '|') {
      if (i == 0 || LastHead->data[0] == '(' || IsOperation(LastHead->data[0])) { //  тогда это открывающийся модуль
        a.push(Head->data[0]);
        flag = true;
      }
      else {
        flag = false;
        while (a.GetTop() != '|') {
          PolishExp[i] = a.GetTop();
          a.pop();
          i++;
        }
        PolishExp[i] = a.GetTop();
        a.pop();
        i++;
      }
    }
    LastHead = Head;
    Head = Head->next;
  }
  while (!a.IsEmpty()) {
    if (a.GetTop() < 0){
      PolishExp[i] = -a.GetTop();
    }
    else {
      PolishExp[i] = a.GetTop();
    }
    a.pop();
    i++;
  }
  PolishExp[i] = 0;
  return PolishExp;
}

void PolishFromInfix::ValueExpression(Variable* m) {
  double operand1;
  double operand2;
  int i = 0;
  int j = 0;
  char* tmp2 = new char[15];
  stack < double > a;
  Variable *runer = m;
  while (PolishExp[i] != 0) {
    if (PolishExp[i] <= '9' &&  PolishExp[i] >= '0') {
      j = 0;
      while (PolishExp[i] != ' ') {
        tmp2[j] = PolishExp[i];
        i++;
        j++;
      }
      tmp2[j] = 0;
      a.push(atof(tmp2));
    }
    else {
      if (PolishExp[i] <= 'z' && PolishExp[i] >= 'a') {
        while (runer->var != PolishExp[i])
          runer = runer->next;
        a.push(runer->value);
        runer = m;
      }
      else {
        switch (PolishExp[i]) {
        case '-': { operand2 = a.GetTop();
          a.pop();
          operand1 = a.GetTop();
          a.pop();
          a.push((operand1 - operand2));
          break;

        }

        case '+': {
                    operand2 = a.GetTop();
                    a.pop();
                    operand1 = a.GetTop();
                    a.pop();
                    a.push((operand1 + operand2));
                    break;
        }

        case '*': {
                    operand2 = a.GetTop();
                    a.pop();
                    operand1 = a.GetTop();
                    a.pop();
                    a.push((operand1 * operand2));
                    break;
        }

        case '/': {
                    operand2 = a.GetTop();
                    a.pop();
                    operand1 = a.GetTop();
                    a.pop();
                    a.push((operand1 / operand2));
                    break;
        }

        case '^': {
                    operand2 = a.GetTop();
                    a.pop();
                    operand1 = a.GetTop();
                    a.pop();
                    a.push(pow(operand1, operand2));
                    break;
        }
        case '_': {
                    operand1 = a.GetTop();
                    a.pop();
                    a.push(-operand1);
                    break;
        }



        case '|': {
                    operand1 = abs(a.GetTop());
                    a.pop();
                    a.push(operand1);
                    break;
        }
        }
      }

    }
    i++;
  }
  if (a.GetCount() == 1) { Value = a.GetTop(); }
  else throw 1;
}
Variable* ListOfValues(Variable* m, char simbol, double v) {
  Variable* node = new Variable;
  Variable*Head = m;
  node->value = v;
  node->var = simbol;
  node->next = NULL;
  if (Head != NULL) {
    while (Head->next != 0)
      Head = Head->next;
    Head->next = node;
  }
  else m = node;
  return m;
}

bool PolishFromInfix::CheckOnCorrect() {

  stack <char> a;
  for (int i = 0; i < LenOfInfix; i++) {
    if (Infix[i] == '(')
    {
      a.push(Infix[i]);
      continue;
    }
    if (Infix[i] == ')')
    {
      if (a.GetTop() == '(')
      {
        a.pop();
      }
      else return false;

      continue;
    }
    if (Infix[i] == '|')
    {
      if (i == 0 || Infix[i - 1] == '(' || IsOperation(Infix[i - 1]))
      {
        a.push(Infix[i]);
      }
      else
      {
        if (a.GetTop() == '|')
        {
          a.pop();
        }
        else return false;
      }


      continue;
    }
    if (IsOperation(Infix[i])){
      switch (Infix[i]) {
      case '-':
      {
                if (i == 0 || Infix[i - 1] == '(' || (Infix[i - 1] == '|' && ((i - 1) == 0 || Infix[i - 2] == '(' || IsOperation(Infix[i - 2]))))  //унарный минус 
                {
                  if (Infix[i + 1] == '(' || Infix[i + 1] == '|' || (Infix[i + 1] <= '9' && Infix[i + 1] >= '0') || (Infix[i + 1] <= 'z' && Infix[i + 1] >= 'a'))
                  {
                  }
                  else return false;
                }
                else
                { // это бинарный минус
                  if ((Infix[i - 1] == ')' || Infix[i - 1] == '|' || (Infix[i - 1] <= '9' && Infix[i - 1] >= '0') || (Infix[i - 1] <= 'z' && Infix[i - 1] >= 'a')) && (Infix[i + 1] == '|' || Infix[i + 1] == '(' || (Infix[i + 1] <= '9' && Infix[i + 1] >= '0') || (Infix[i + 1] <= 'z' && Infix[i + 1] >= 'a')))
                  {
                    ;
                  }
                  else return false;
                }

                break;
      }
      case '+':
      {
                if ((Infix[i - 1] == ')' || Infix[i - 1] == '|' || (Infix[i - 1] <= '9' && Infix[i - 1] >= '0') || (Infix[i - 1] <= 'z' && Infix[i - 1] >= 'a')) && (Infix[i + 1] == '|' || Infix[i + 1] == '(' || (Infix[i + 1] <= '9' && Infix[i + 1] >= '0') || (Infix[i + 1] <= 'z' && Infix[i + 1] >= 'a')))
                {
                  ;
                }
                else return false;

                break;
      }
      case '*':
      {
                if ((Infix[i - 1] == ')' || Infix[i - 1] == '|' || (Infix[i - 1] <= '9' && Infix[i - 1] >= '0') || (Infix[i - 1] <= 'z' && Infix[i - 1] >= 'a')) && (Infix[i + 1] == '|' || Infix[i + 1] == '(' || (Infix[i + 1] <= '9' && Infix[i + 1] >= '0') || (Infix[i + 1] <= 'z' && Infix[i + 1] >= 'a')))
                {
                  ;
                }
                else return false;

                break;
      }
      case '/':
      {
                if ((Infix[i - 1] == ')' || Infix[i - 1] == '|' || (Infix[i - 1] <= '9' && Infix[i - 1] >= '0') || (Infix[i - 1] <= 'z' && Infix[i - 1] >= 'a')) && (Infix[i + 1] == '|' || Infix[i + 1] == '(' || (Infix[i + 1] <= '9' && Infix[i + 1] >= '0') || (Infix[i + 1] <= 'z' && Infix[i + 1] >= 'a')))
                {
                  ;
                }
                else return false;

                break;
      }
      case '^':
      {
                if ((Infix[i - 1] == ')' || Infix[i - 1] == '|' || (Infix[i - 1] <= '9' && Infix[i - 1] >= '0') || (Infix[i - 1] <= 'z' && Infix[i - 1] >= 'a')) && (Infix[i + 1] == '|' || Infix[i + 1] == '(' || (Infix[i + 1] <= '9' && Infix[i + 1] >= '0') || (Infix[i + 1] <= 'z' && Infix[i + 1] >= 'a')))
                {
                  ;
                }
                else return false;

                break;
      }
      }

    }
    else
    {
      if (Infix[i] <= '9' && Infix[i] >= '0')
      {
        while ((Infix[i] <= '9' && Infix[i] >= '0') || Infix[i] == '.')
        {
          i++;
        }
        i--;
      }
      else
      {
        if (!(Infix[i] <= 'z' && Infix[i] >= 'a')) return false;
      }

    }
  }
  if (a.GetCount() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }

}


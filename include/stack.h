#ifndef __STACK_H__
#define __STACK_H__

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

#endif



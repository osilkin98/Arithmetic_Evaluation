#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <cctype>

// T will be either an operator char
// or a long long
struct tree_node {
  long double operator()(void) {
    /*if(!left || !right) {
      std::cerr << "operator node is missing a child. returning.\n";
      return data;
      }*/
    switch(op) {
    case '+':
      return (*left)() + (*right)();
    case '-':
      return (*left)() - (*right)();
    case 'x':
      return (*left)() * (*right)();
    case '*':
      return (*left)() * (*right)();
    case '/':
      return (*left)() / (*right)();
    case '%':
      return fmod((*left)(), (*right)());
    default:
      std::cout << "defaulting to regular operator.\n";
      return data;
    }
  }
  
  char op;
  long double data;
  tree_node *left, *right, *parent;
  tree_node(long double _data = 0)
    : data(_data), left(NULL), right(NULL), parent(NULL), op(' ') { }
  //tree_node(void)\
    : op(' '), data(0), left(NULL), right(NULL), parent(NULL) { }
  tree_node(char _op)
    : op(_op), data(0), left(NULL), right(NULL), parent(NULL) { }
};


bool is_valid(const std::string input) {
  std::istringstream validator(input);
  std::stack<char> S;
  char c;
  while(validator.get(c)) {
    if(c == '(') {
      S.push(c);
    } else if(c == ')') {
      S.pop();
    }
  }
  return S.empty();
}

/* 
   Expressions will come in the form of
   8 - 3
   (3 x 5) + 7
   ((3x9)/(9x1) + 7) % 23

   We need to validate before we evaluate 
*/
bool is_operator(const char c) {
  char operators[6] = {'+', '-', 'x', '*', '/', '%'};
  for(register short i = 0; i < 6; ++i) {
    if(c == operators[i]) {
      return true;
    }
  }
  return false;
}

bool is_AS(const char a) { return a == '+' or a == '-'; }

bool is_MD(const char a) { return a == 'x' or a == '/' or a == '%';}

bool is_paren(const char a) { return a == '(' or a == ')'; }

// does operator a have precedence over operator b
bool has_precedence(const char a, const char b) {
  if(is_AS(a)) {
    return false;
  } else if(is_MD(a)) {
    if(is_AS(b)) {
      return true;
    } else {
      return false;
    }
  } else { // else if it's parentheses 
    return is_AS(b) or is_MD(b) ? true : false;
  }
}

long double evaluate(std::string input) {
  if(!is_valid(input)) {
    std::cerr << "invalid expression. exiting.\n";
  } else {
    tree_node* root;
    std::istringstream expression(input);
    char c;
    expression >> c;
    while(!expression.eof()) {
      expression >> c;
      tolower(c);
      
    }
  }
}

int main(void) {
  /*
  std::cout << "enter a string: " << std::flush;
  std::string in;
  std::getline(std::cin, in);
  evaluate(in);
  std::cout << std::endl;
  */
  tree_node* root = new tree_node((long double)3.0);
  root -> parent = new tree_node('+');
  root -> parent -> left = root;
  root -> parent -> right = new tree_node('x');
  root -> parent -> right -> left = new tree_node((long double)10);
  root -> parent -> right -> right = new tree_node((long double)77);
  std::cout << "3 + 10 x 77 = " << (*(root -> parent))() << std::endl;
  return 0;
}

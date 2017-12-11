#ifndef comment_h
#define comment_h

#include <string>
#include <iostream>
#include "stringFunctions.h"

class Comment {
public:
  Comment();
  Comment(string comment, int orderID);
  string getCommentString();
  void setCommentString(string comment);
  int getOrderID();
  void setOrderID(int orderID);
  string toString();

private:
  string _comment;
  int _orderID;

  stringFunctions stringfunc;
};

#endif

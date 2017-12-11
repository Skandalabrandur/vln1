#include "Comment.h"

Comment::Comment() {
  _comment = "";
  _orderID = -1;
}

Comment::Comment(string comment, int orderID) {
  _comment = comment;
  _orderID = orderID;
}

string Comment::getCommentString() {
  return _comment;
}

void Comment::setCommentString(string comment) {
  _comment = comment;
}

int Comment::getOrderID() {
  return _orderID;
}

void Comment::setOrderID(int orderID) {
  _orderID = orderID;
}

string Comment::toString() {
  return stringfunc.intToString(_orderID) + " " + _comment;
}

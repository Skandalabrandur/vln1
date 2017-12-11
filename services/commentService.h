#ifndef commentservice_h
#define commentservice_h
#include "fileOperations.h"
#include "stringFunctions.h"
#include "commentService.h"
#include "Comment.h"
#include <vector>
#include <string>
#include <iostream>

class commentService {
public:
  void writeComment(Comment comment);
  Comment getCommentFromOrderID(int orderID);
  string getCommentTextFromOrderID(int orderID);

private:
  fileOperations fo;
  stringFunctions stringfunc;

};

#endif

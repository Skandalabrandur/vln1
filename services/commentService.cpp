#include "commentService.h"

void commentService::writeComment(Comment comment) {
  fo.appendLineToFile(comment.toString(), "data/comments.txt");
}

//orderID is a unique Identifier and by extension, the comment
Comment commentService::getCommentFromOrderID(int orderID) {
  vector<string> lines =  fo.getLinesFromFile("data/comments.txt");
  string commentText = "";
  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));
    if(stringfunc.stringToInt(words.at(0)) == orderID) {
      for(int j = 1; j < words.size(); j++) {
        commentText += words.at(j) + " ";
      }
    }
  }
  Comment newComment(commentText, orderID);
  return newComment;
}

string commentService::getCommentTextFromOrderID(int orderID) {
  Comment comment = getCommentFromOrderID(orderID);
  return comment.getCommentString();
}

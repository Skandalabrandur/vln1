#ifndef logoservice_h
#define logoservice_h
#include <vector>
#include <string>
#include "fileOperations.h"
class logoService {
public:
  vector<string> getLogo();
private:
  fileOperations fo;
};

#endif

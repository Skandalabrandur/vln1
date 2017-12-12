#include "logoService.h"

vector<string> logoService::getLogo() {
  return fo.getLinesFromFile("data/assets/logo.txt");
}

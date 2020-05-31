#include "Argument_helper.h"
#include "dataloader.h"
#include "pagerank.h"
#include <cstdlib>
#include <ctime>
#include <list>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
  string dataFile = "";
  dsr::Argument_helper ah;
  ah.new_named_string("data", "data_file", "named_string", "named_string",
                      dataFile);
  ah.process(argc, argv);
  Dataloader loader = Dataloader(dataFile);
  auto dataBuffer = loader.loadData();
  LyxUtilis::log("The Size of Data after Deduplicating: ", dataBuffer.size());
  PageRank p;
  p.compute(dataBuffer);
  return 0;
}

#ifndef PAGERANK_DATALOADER_H
#define PAGERANK_DATALOADER_H

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "utilis.h"


class Dataloader {
private:
  std::string _file_name;

  std::ifstream _in;

  void split(const std::string &s, std::vector<std::string> &tokens,
             const std::string &delimiter = " ") {
    tokens.clear();
    std::string::size_type last_pos = s.find_first_not_of(delimiter, 0);
    std::string::size_type pos = s.find_first_of(delimiter, last_pos);
    while (std::string::npos != pos || std::string::npos != last_pos) {
      tokens.push_back(s.substr(last_pos, pos - last_pos));
      last_pos = s.find_first_not_of(delimiter, pos);
      pos = s.find_first_of(delimiter, last_pos);
    }
  }

  void trim(std::string &s) {
    // s.erase(s.find_last_not_of(".") + 1);
    // s.erase(s.find_last_not_of("!") + 1);
    s.erase(s.find_last_not_of(" ") + 1);
    s.erase(s.find_last_not_of("\n") + 1);
  }

  void replaceAll(std::string &str, const std::string &from,
                  const std::string &to) {
    if (from.empty())
      return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
    }
  }

public:
  Dataloader() = default;
  Dataloader(std::string name) : _file_name(name) {}

  std::vector<std::vector<std::string>> loadData() {
    std::vector<std::vector<std::string>> res;
    res.clear();
    _in.open(_file_name);
    size_t cnt = 0;
    LyxUtilis::log("Loading data ...");
    if (!_in) {
      LyxUtilis::log("open file fail!");
    } else {
      std::vector<std::string> tokens;
      std::string line;
      std::unordered_map<string, bool> deduplicateMap;
      while (std::getline(_in, line)) {
        cnt++;
        if (deduplicateMap.find(line) == deduplicateMap.end()) {
          trim(line);
          // replaceAll(line, ",", "");
          split(line, tokens, "\t");
          res.emplace_back(tokens);
        }
        deduplicateMap[line] = true;
      }
    }
    _in.close();
    LyxUtilis::log("Raw Data Size: ", cnt);
    return res;
  }

  static std::vector<std::vector<std::string>> readData(std::ifstream &in,
                                                        std::string &fileName) {
    std::vector<std::vector<std::string>> res;
    res.clear();
    in.open(fileName);
    if (!in) {
      std::cout << "Read file fail!" << std::endl;
    } else {
      std::vector<std::string> tokens;
      std::string line;
      while (std::getline(in, line)) {
        res.emplace_back(tokens);
      }
    }
    in.close();
    return res;
  }
};

#endif // PAGERANK_DATALOADER_H

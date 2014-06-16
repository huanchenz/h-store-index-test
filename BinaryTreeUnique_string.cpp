#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <utility>
#include <time.h>
#include <sys/time.h>

#include <map>

class BinaryTreeUniqueIndex {
  typedef std::map<std::string, std::string> MapType;

public:

  BinaryTreeUniqueIndex() {
    m_entries = MapType();
  }

  ~BinaryTreeUniqueIndex() {};

  bool addEntry(std::string key, std::string value) {
    //std::cout << "PUT\tkey: " << key << "\n\tval: " << value << "\n";
    //printf("PUT\tkey: %p\n\tval: %p\n", key, value);
    std::pair<typename MapType::iterator, bool> retval =
      m_entries.insert(std::pair<std::string, std::string>(key, value));
    return retval.second;
  }

  bool deleteEntry(std::string key) {
    m_entries.erase(key);
  }

  bool getEntry(std::string key, std::string &value) {
    m_keyIter = m_entries.find(key);
    if (m_keyIter == m_entries.end()) {
      return false;
    }
    value = m_keyIter->second;
    ++m_keyIter;
    return true;
  }

  bool getNextEntry(std::string key, std::string &value) {
    if (m_keyIter == m_entries.end()) {
      return false;
    }
    key = m_keyIter->first;
    value = m_keyIter->second;
    ++m_keyIter;
    return true;
  }

  int size() {
    return m_entries.size();
  }

private:
  MapType m_entries;

  // iteration stuff
  typename MapType::const_iterator m_keyIter;
};

inline double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char *argv[]) {
  int limit = atoi(argv[1]);
  std::ifstream infile_tpcc(argv[2]);

  std::string op;
  std::string key;
  std::string val;
  unsigned count = 0;
  
  std::string put("PUT");
  std::string get("GET");
  std::string nval("NVAL");
  std::string del("DEL");
  std::string scan("SCAN");
  std::string next("NEXT");
  
  int putCount = 0;
  int getCount = 0;
  int nvalCount = 0;
  int delCount = 0;
  int scanCount = 0;
  int nextCount = 0;

  int total_memory_usage = 0;

  BinaryTreeUniqueIndex btui = BinaryTreeUniqueIndex();

  while (count < limit && infile_tpcc.good()) {
    if (count == 0) {
      infile_tpcc >> op >> key >> val;
      count++;
      continue;
    }	

    infile_tpcc >> op;
    if (op.compare(put) == 0) {
      infile_tpcc >> key >> val;
      int key_size, val_size, key_char_size, val_char_size;
      key_size = key.length();
      val_size = val.length();
      key_char_size = (key_size + 1)/2;
      val_char_size = (val_size + 1)/2;
      char* key_char = (char*)malloc(key_char_size);
      char* val_char = (char*)malloc(val_char_size);
      for (int j = 0; j < key_size; j += 2){
	key_char[j/2] = (char)(int)strtol(key.substr(j,2).c_str(), NULL, 16);
      }
      for (int j = 0; j < val_size; j += 2){
	val_char[j/2] = (char)(int)strtol(val.substr(j,2).c_str(), NULL, 16);
      }
      bool put_success = btui.addEntry(std::string(key_char, key_char_size), std::string(val_char, val_char_size));

      if (!put_success)
	std::cout << "PUT FAILED\n";
      
      free(key_char);
      free(val_char);

      putCount++;
    }
    else if (op.compare(get) == 0) {
      infile_tpcc >> key;
      getCount++;
    }
    else if (op.compare(nval) == 0) {
      nvalCount++;
    }
    else if (op.compare(del) == 0) {
      infile_tpcc >> key >> val;
      delCount++;
    }
    else if (op.compare(scan) == 0) {
      infile_tpcc >> key;
      scanCount++;
    }
    else if (op.compare(next) == 0) {
      nextCount++;
    }
    else
      std::cout << "UNRECOGNIZED CMD: " << op.c_str() << "\n";
    count++;
  }
  
  std::cout << "Index Size = " << btui.size() << "\n";

  return 0;
}

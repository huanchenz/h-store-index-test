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

  bool addEntry(std::string &key, std::string &value) {
    //std::cout << "PUT\tkey: " << key << "\n\tval: " << value << "\n";
    //printf("PUT\tkey: %p\n\tval: %p\n", key, value);
    std::pair<typename MapType::iterator, bool> retval =
      m_entries.insert(std::pair<std::string, std::string>(key, value));
    return retval.second;
  }

  bool deleteEntry(std::string &key) {
    m_entries.erase(key);
  }

  bool getEntry(std::string &key, std::string &value) {
    m_keyIter = m_entries.find(key);
    if (m_keyIter == m_entries.end()) {
      return false;
    }
    value = m_keyIter->second;
    ++m_keyIter;
    return true;
  }

  bool getNextEntry(std::string &key, std::string &value) {
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
  std::vector<std::string> ops;
  std::vector<std::string> keys;
  std::vector<std::string> vals;
  std::vector<std::string> keys_str;
  std::vector<std::string> vals_str;
  std::vector<int> keys_str_len;
  std::vector<int> vals_str_len;
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

  while (count < limit && infile_tpcc.good()) {
    if (count == 0) {
      infile_tpcc >> op >> key >> val;
      count++;
      continue;
    }	

    infile_tpcc >> op;
    if (op.compare(put) == 0) {
      infile_tpcc >> key >> val;
      ops.push_back(op);
      keys.push_back(key);
      vals.push_back(val);
      putCount++;
    }
    else if (op.compare(get) == 0) {
      infile_tpcc >> key;
      ops.push_back(op);
      keys.push_back(key);
      vals.push_back(op);
      getCount++;
    }
    else if (op.compare(nval) == 0) {
      ops.push_back(op);
      keys.push_back(op);
      vals.push_back(op);
      nvalCount++;
    }
    else if (op.compare(del) == 0) {
      infile_tpcc >> key >> val;
      ops.push_back(op);
      keys.push_back(key);
      vals.push_back(val);
      delCount++;
    }
    else if (op.compare(scan) == 0) {
      infile_tpcc >> key;
      ops.push_back(op);
      keys.push_back(key);
      vals.push_back(op);
      scanCount++;
    }
    else if (op.compare(next) == 0) {
      ops.push_back(op);
      keys.push_back(op);
      vals.push_back(op);
      nextCount++;
    }
    else
      std::cout << "UNRECOGNIZED CMD: " << op.c_str() << "\n";
    count++;
  }

  for (int i = 0; i < (int)ops.size(); i++) {
    int key_size, val_size, key_char_size, val_char_size;
    key_size = keys[i].length();
    val_size = vals[i].length();
    key_char_size = (key_size + 1)/2;
    val_char_size = (val_size + 1)/2;
    char* key_char = (char*)malloc(key_char_size);
    char* val_char = (char*)malloc(val_char_size);
    for (int j = 0; j < key_size; j += 2){
      key_char[j/2] = (char)(int)strtol(keys[i].substr(j,2).c_str(), NULL, 16);
    }
    for (int j = 0; j < val_size; j += 2){
      val_char[j/2] = (char)(int)strtol(vals[i].substr(j,2).c_str(), NULL, 16);
    }
    keys_str.push_back(std::string(key_char, key_char_size));
    vals_str.push_back(std::string(val_char, val_char_size));
    keys_str_len.push_back(key_char_size);
    vals_str_len.push_back(val_char_size);
  }

  double start = now();

  BinaryTreeUniqueIndex btui = BinaryTreeUniqueIndex();
  int nextValCount = 0;
  for (int i = 0; i < (int)ops.size(); i++) {
    op = ops[i];
    if (op.compare(put) == 0) {
      /*
      std::cout << "PUT\tkey: ";
      for (int j = 0; j < keys_str_len[i]; j++) {
	std::cout << (int)keys_str[i][j] << "\t";
      }
      std::cout << "keylen = " << keys_str_len[i];
      std::cout << "\n\tval: ";
      for (int j = 0; j < vals_str_len[i]; j++) {
	std::cout << (int)vals_str[i][j] << "\t";
      }
      std::cout << "\n";
      */
      //std::cout << "PUT\tkey: " << keys_str[i] << "\n\tval: " << vals_str[i] << "\n";
      bool put_success = btui.addEntry(keys_str[i], vals_str[i]);
      //total_memory_usage += keys_str[i].capacity();
      //total_memory_usage += vals_str[i].capacity();
      total_memory_usage += keys_str[i].size();
      total_memory_usage += vals_str[i].size();
      //std::cout << keys_str[i].capacity() << "\t" << keys_str[i].length() << "\t" << vals_str[i].capacity() << "\t" << vals_str[i].length() << "\n";
      total_memory_usage += sizeof(std::_Rb_tree_node_base);

      if (!put_success)
	std::cout << "PUT FAILED at cmd #" << i << "\n";
    }
    else if ((op.compare(get) == 0) || (op.compare(scan) == 0)) {

      std::string value_str; 
      if (!btui.getEntry(keys_str[i], value_str)) {
	if (op.compare(get) == 0)
	  std::cout << "GET FAILED at cmd #" << i << "\t" << keys[i].c_str() << "\n";
	else
	  std::cout << "SCAN FAILED at cmd #" << i << "\t" << keys[i].c_str() << "\n";
      }

    }
    else if (op.compare(nval) == 0) {
      nextValCount++;
    }
    else if (op.compare(next) == 0) {

      std::string key_str;
      std::string value_str;
      if (!btui.getNextEntry(key_str, value_str))
	std::cout << "GET_NEXT FAILED at cmd #" << i << "\n";

    }
    else if (op.compare(del) == 0) {

      bool remove_success = btui.deleteEntry(keys_str[i]);
      if (!remove_success)
	std::cout << "REMOVE FAILED at cmd #" << i << "\n";

    }
    else {
      std::cout << "CMD IGNORED: " << op.c_str() << "\n";
      continue;
    }
  }

  double end = now();
  double time = (double)(end - start);
  double ops_per_sec = (double)((ops.size() - nextValCount + 0.0) / time);

  std::cout << "ops/sec = " << ops_per_sec << "\n";

  //total_memory_usage += (sizeof(std::_Rb_tree_node_base) * ops.size());
  //total_memory_usage += sizeof(std::_Rb_tree<std::string, std::string>);
  
  std::cout << "total memory usage = " << total_memory_usage << "\n";
  
  std::cout << "Index Size = " << btui.size() << "\n";

  return 0;
}

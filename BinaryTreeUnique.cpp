#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <utility>

#include <map>

class BinaryTreeUniqueIndex {
  struct keyComparator {
    bool operator() (const char *lhs, const char *rhs) const {
      return strcmp(lhs, rhs) < 0;
    }
  };

  typedef std::map<const char*, char*, keyComparator> MapType;

public:

  BinaryTreeUniqueIndex() {
    m_entries = MapType();
  }

  ~BinaryTreeUniqueIndex() {};

  bool addEntry(const char* key, char* value) {
    //std::cout << "PUT\tkey: " << key << "\n\tval: " << value << "\n";
    //printf("PUT\tkey: %p\n\tval: %p\n", key, value);
    char* key_new = new char[strlen(key)+1];
    strcpy(key_new, key);
    char* val_new = new char[strlen(value)+1];
    strcpy(val_new, value);
    std::pair<typename MapType::iterator, bool> retval =
      m_entries.insert(std::pair<const char*, char*>(key_new, val_new));
    return retval.second;
    /*
    std::pair<typename MapType::iterator, bool> retval =
      m_entries.insert(std::pair<const char*, char*>(key, value));
    return retval.second;
    */
  }

  bool deleteEntry(const char* key) {
    m_entries.erase(key);
  }

  char* getEntry(const char* key) {
    m_keyIter = m_entries.find(key);
    if (m_keyIter == m_entries.end()) {
      return NULL;
    }
    char* retval = const_cast<char*>(m_keyIter->second);
    ++m_keyIter;
    return retval;
  }

  char* getNextEntry() {
    if (m_keyIter == m_entries.end()) {
      return NULL;
    }
    char* retval = const_cast<char*>(m_keyIter->second);
    ++m_keyIter;
    return retval;
  }

  int size() {
    return m_entries.size();
  }
  /*
  char* get(char* key) {
    return m_entries[key];
  }
  */
private:
  MapType m_entries;

  // iteration stuff
  typename MapType::const_iterator m_keyIter;
};

int main(int argc, char *argv[]) {
  int limit = atoi(argv[1]);
  std::ifstream infile_tpcc(argv[2]);

  std::string op;
  std::string key;
  std::string val;
  std::vector<std::string> ops;
  std::vector<std::string> keys;
  std::vector<std::string> vals;
  std::vector<char*> keys_str;
  std::vector<char*> vals_str;
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
    keys_str.push_back(key_char);
    vals_str.push_back(val_char);
    keys_str_len.push_back(key_char_size);
    vals_str_len.push_back(val_char_size);
  }

  BinaryTreeUniqueIndex btui = BinaryTreeUniqueIndex();

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
      //bool put_success = btui.addEntry(strdup(keys_str[i]), strdup(vals_str[i]));
      /*
      std::cout << "PUT\tkey: ";
      for (int j = 0; j < keys_str_len[i]; j++) {
	std::cout << (int)keys_str[i][j] << "\t";
      }
      std::cout << "keylen = " << keys_str_len[i];
      std::cout << "\n\tval: ";
      for (int j = 0; j < vals_str_len[i]; j++) {
	std::cout << (int)btui.get(keys_str[i])[j] << "\t";
      }
      std::cout << "\n";
      */
      if (!put_success)
	std::cout << "PUT FAILED at cmd #" << i << "\n";
      else
	std::cout << "PUT SUCCESS at cmd #" << i << "\n";
    }
    else if ((op.compare(get) == 0) || (op.compare(scan) == 0)) {
      char* value_str = btui.getEntry(keys_str[i]);
      if (value_str == NULL) {
	if (op.compare(get) == 0)
	  std::cout << "GET FAILED at cmd #" << i << "\t" << keys[i].c_str() << "\n";
	else
	  std::cout << "SCAN FAILED at cmd #" << i << "\t" << keys[i].c_str() << "\n";
      }
    }
    else if (op.compare(nval) == 0) {

    }
    else if (op.compare(next) == 0) {
      char* value_str = btui.getNextEntry();
      if (value_str == NULL)
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
  
  std::cout << "Index Size = " << btui.size() << "\n";

  return 0;
}

#include <iostream>

#include "csv.h"

namespace csv
{
CsvParser::iterator init_csv(CsvParser &p, const std::string &file,
                             const std::vector<std::string> &headers)
{
  auto it = p.begin();
  if (it == p.end()) {
    throw std::runtime_error("CSV file " + file + " is empty");
  }

  auto header = *it;

  if (header.size() != headers.size()) {
    throw std::runtime_error("CSV file " + file +
                             " contins the wrong number of fields");
  }

  for (unsigned int i = 0; i < headers.size(); i++) {
    if (headers[i] != header[i]) {
      throw std::runtime_error("CSV file " + file + " has incorrect header " +
                               headers[i] + " but expected " + header[i]);
    }
  }

  return ++it;
}
} // namespace csv


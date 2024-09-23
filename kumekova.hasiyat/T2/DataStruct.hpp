#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace kumekova
{

using KeyType = unsigned long long;

struct DataStruct
{
  KeyType key1{};
  KeyType key2{};
  std::string key3;
};

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct);

bool operator<(const DataStruct& lhs, const DataStruct& rhs);

}

#endif
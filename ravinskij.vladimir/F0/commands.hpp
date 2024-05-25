#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <map>
#include <list>
#include <string>
#include <vector>
#include "node.hpp"

namespace ravinskij
{
  void printHelp();

  using traverserTable = std::map< std::string, std::list< nodePtr > >;
  using fileTable = std::map< std::string, std::string >;
  void addText(std::istream&, fileTable&);
  void saveText(std::istream&, fileTable&);
  void deleteText(std::istream&, fileTable&);
  void printText(std::istream&, std::ostream&, const fileTable&);

  using encodeMap = std::map< char, std::vector<bool > >;
  using encodesTable = std::map< std::string, encodeMap >;
  void createEncoding(std::istream&, encodesTable&, traverserTable&, const fileTable&);
  void deleteEncoding(std::istream&, encodesTable&, traverserTable&);
  void encode(std::istream&, const encodesTable&, fileTable&);
  void decode(std::istream&, const traverserTable&, fileTable&);
  void addEncoding(std::istream&, encodesTable&, traverserTable&);
  void saveEncoding(std::istream&, const encodesTable&, const traverserTable&);

  void compareEncodings(std::istream&, const fileTable& files, const encodesTable&);
}

#endif

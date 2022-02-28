#ifndef B4_DATASTRUCT_HPP
#define B4_DATASTRUCT_HPP

#include <string>
#include <iostream>

struct data_struct_t
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& input, data_struct_t& data);
std::ostream& operator<<(std::ostream& output, const data_struct_t& data);
bool operator< (const data_struct_t& data1, const data_struct_t& data2);

#endif

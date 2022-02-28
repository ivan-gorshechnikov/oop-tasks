#include "stream-guard.hpp"
#include <istream>

StreamGuard::StreamGuard(std::istream &input):
  input_(input),
  flags_(input.flags())
{}

StreamGuard::~StreamGuard()
{
  input_.setf(flags_);
}

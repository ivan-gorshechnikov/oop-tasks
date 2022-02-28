#ifndef B4_STREAM_GUARD_HPP
#define B4_STREAM_GUARD_HPP

#include <istream>

class StreamGuard
{
public:
  StreamGuard(std::istream& input);
  ~StreamGuard();
private:
  std::istream& input_;
  std::istream::fmtflags flags_;

};

#endif

#pragma once

#include <vector>
#include <experimental/string_view>
#include <functional>

class ITextBuffer
{
public:
  using Buffer = std::vector<std::experimental::string_view>;
  using Iterator = Buffer::iterator;

public:
  virtual ~ITextBuffer() {};

  virtual unsigned size() = 0;
  virtual void applyFunctionToSlice(std::function<void(Iterator, Iterator)> function,
				    unsigned pos,
				    unsigned len) = 0;
};

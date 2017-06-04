#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>

class TextBuffer
{
public:
  using Buffer = std::vector<std::string>;
  using Iterator = std::vector<std::string>::iterator;

public:
  TextBuffer();

  unsigned size();
  bool isFull();
  void applyFunctionToSlice(std::function<void(Iterator, Iterator)> function, unsigned pos, unsigned len);
  // void waitForNewData();

  void appendData(const Buffer& data);
  void seal();

private:
  Buffer mBuffer;
  bool mFull;
  std::mutex mBufferLock;
  std::condition_variable mNewData;

private:
  TextBuffer(const TextBuffer&) = delete;
  TextBuffer& operator=(const TextBuffer&) = delete;
  TextBuffer(TextBuffer&&) = delete;
  TextBuffer& operator=(TextBuffer&&) = delete;
};
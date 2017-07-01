#include <cassert>

#include "TextBuffer.hpp"

TextBuffer::TextBuffer() :
  mFull(false)
{
}

unsigned TextBuffer::size()
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  return mBuffer.size();
}

bool TextBuffer::full()
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  return mFull;
}

void TextBuffer::applyFunctionToSlice(std::function<void(Iterator, Iterator)> function, unsigned pos, unsigned len)
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  assert(pos <= mBuffer.size());
  assert(pos+len <= mBuffer.size());
  function(mBuffer.begin()+pos, mBuffer.begin()+pos+len);
}

void TextBuffer::waitForNewSize(unsigned oldSize)
{
  std::unique_lock<std::mutex> lock(mBufferLock);
  if (mFull && oldSize >= mBuffer.size())
    return;

  mNewData.wait(lock, [&]() {
      return mBuffer.size() > oldSize;
    });
}

void TextBuffer::appendData(Buffer && data)
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  std::move(data.begin(), data.end(), std::back_inserter(mBuffer));
  mNewData.notify_all();
}

void TextBuffer::seal()
{
  std::lock_guard<std::mutex> lock(mBufferLock);
  mFull = true;
}

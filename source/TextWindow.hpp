#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>

#include "Window.hpp"
#include "ITextBuffer.hpp"
#include "Region.hpp"
#include "Event.hpp"

class TextWindow : public Window
{
public:
  TextWindow(Region region, std::shared_ptr<ITextBuffer> buffer);
  ~TextWindow();

  Event proceed();
  void render();
  void focus();

private:
  static const unsigned mWindowTimeoutMs = 100;

  void lazyRender();

  std::shared_ptr<ITextBuffer> mBuffer;
  int mCursorY;
  int mTextOffsetY;

  int mPreviousTextOffsetY;
  int mPreviousBufferSize;
};

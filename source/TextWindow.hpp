#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>

#include "Window.hpp"
#include "TextBuffer.hpp"
#include "Region.hpp"

class TextWindow : public Window
{
public:
  TextWindow(Region region, std::shared_ptr<TextBuffer> buffer);
  ~TextWindow();

  int getCh();
  void render();
  void focus();

private:
  static const unsigned mWindowTimeoutMs = 100;

  void forceRender();

  std::shared_ptr<TextBuffer> mBuffer;
  int mCursorY;
  int mTextOffsetY;

  int mPreviousTextOffsetY;
  int mPreviousBufferSize;
};

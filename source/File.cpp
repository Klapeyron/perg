#include <fstream>
#include <stdexcept>
#include <functional>

using namespace std::placeholders;

#include "File.hpp"

File::File(std::string fileName) :
  Grep(std::bind(&File::readFile, this, fileName, _1), fileName),
  mDesignations(new Designations)
{
}

std::shared_ptr<Designations> File::getDesignations()
{
  return mDesignations;
}

void File::readFile(std::string fileName, std::shared_ptr<TextBuffer> output)
{
  std::ifstream fileStream(fileName.c_str());
  if (!fileStream.is_open())
    throw std::runtime_error("Cannot open file");

  std::vector<std::experimental::string_view> view;
  std::string line;
  while (std::getline(fileStream, line))
    {
      lines.push(std::move(line));
      view.emplace_back(lines.back());
      if (view.size() >= mLinesToFlush)
        {
          output->appendData(std::move(view));
          view.clear();
        }
    }

  if (view.size() > 0)
    output->appendData(std::move(view));

  output->seal();
}

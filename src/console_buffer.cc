#include "console_buffer.h"

#include <iostream>
#include <vector>

namespace lotate_polyhedron {

void ConsoleBuffer::Draw(void) const {
  for (size_t y = 0; y < console_height_ - 1; ++y) {
    for (size_t x = 0; x < console_width_; ++x) {
      std::wcout << screen_buffer_[current_buffer_][y][x];
    }
    std::wcout << L'\n';
  }
  for (size_t x = 0; x < console_width_; ++x) {
    std::wcout << screen_buffer_[current_buffer_][console_height_ - 1][x];
  }
  std::wcout << std::endl;
}

void ConsoleBuffer::Clear(void) {
  for (size_t y = 0; y < console_height_; ++y) {
    for (size_t x = 0; x < console_width_; ++x) {
      screen_buffer_[current_buffer_][y][x] = ' ';
    }
  }
}

void ConsoleBuffer::PrintAt(size_t x, size_t y, const std::string_view& s) {
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '\n') {
      ++y;
      continue;
    } else if (s[i] == '\t') {
      x += 4;
      continue;
    }

    SetAt(x++, y, s[i]);

    if (x >= console_width_) {
      x = 0;
      ++y;
    }
    if (y >= console_height_) {
      break;
    }
  }
}

void ConsoleBuffer::PrintAt(size_t x, size_t y, const std::wstring_view& s) {
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == L'\n') {
      ++y;
      continue;
    } else if (s[i] == L'\t') {
      x += 4;
      continue;
    }

    SetAt(x++, y, s[i]);

    if (x >= console_width_) {
      x = 0;
      ++y;
    }
    if (y >= console_height_) {
      break;
    }
  }
}

}  // namespace lotate_polyhedron
#ifndef LOTATE_POLYHEDRON_CONSOLE_BUFFER_H_
#define LOTATE_POLYHEDRON_CONSOLE_BUFFER_H_

#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace lotate_polyhedron {

class ConsoleBuffer {
 public:
  inline static int GetConsoleSize(size_t& width, size_t& height) {
    winsize size;
    const int ret = ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    width = size.ws_col;
    height = size.ws_row;
    return ret;
  }

  inline static void FastIO(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }

  inline static int ClearScreen(void) { return system("clear"); }

  explicit ConsoleBuffer(void)
      : current_buffer_(0), console_width_(0), console_height_(0) {
    SyncConsoleSize();
    InitializeScreenBuffer();
  }

  ConsoleBuffer(const ConsoleBuffer& cb)
      : current_buffer_(cb.current_buffer_),
        console_width_(cb.console_width_),
        console_height_(cb.console_height_) {
    for (int i = 0; i < 2; ++i) {
      screen_buffer_[i] = cb.screen_buffer_[i];
    }
  }

  ConsoleBuffer(ConsoleBuffer&& cb)
      : current_buffer_(cb.current_buffer_),
        console_width_(cb.console_width_),
        console_height_(cb.console_height_) {
    for (int i = 0; i < 2; ++i) {
      screen_buffer_[i] = std::move(cb.screen_buffer_[i]);
    }
  }

 private:
  void InitializeScreenBuffer(void) {
    for (int i = 0; i < 2; ++i) {
      screen_buffer_[i].clear();
      screen_buffer_[i].reserve(console_height_);
      for (size_t j = 0; j < console_height_; ++j) {
        screen_buffer_[i].push_back(std::vector<wchar_t>(console_width_, ' '));
      }
    }
  }

 public:
  inline size_t GetConsoleWidth(void) const { return console_width_; }

  inline size_t GetConsoleHeight(void) const { return console_height_; }

  inline int SwapBuffer(void) { return (current_buffer_ ^= 1); }

  void Draw(void) const;

  void Clear(void);

  inline void SetAt(size_t x, size_t y, char c) {
    screen_buffer_[current_buffer_][y][x] = static_cast<wchar_t>(c);
  }

  inline void SetAt(size_t x, size_t y, wchar_t c) {
    screen_buffer_[current_buffer_][y][x] = c;
  }

  void PrintAt(size_t x, size_t y, const std::string_view& s);

  void PrintAt(size_t x, size_t y, const std::wstring_view& s);

  inline int SyncConsoleSize(void) {
    const size_t before_width = console_width_;
    const size_t before_height = console_height_;
    const int ret = GetConsoleSize(console_width_, console_height_);
    --console_height_;
    if (before_width != console_width_ || before_height != console_height_) {
      InitializeScreenBuffer();
    }
    return ret;
  }

 protected:
  std::vector<std::vector<wchar_t>> screen_buffer_[2];

 private:
  int current_buffer_;
  size_t console_width_;
  size_t console_height_;
};

}  // namespace lotate_polyhedron

#endif
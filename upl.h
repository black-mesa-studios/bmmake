#pragma once
#include <iostream>

using string = std::string; // shortened std::string
using costr = const std::string; // const string
using cstring = const char *; // cstring
using colour = const char *; // cstring but used for colours
using textdata = const char *; // even more type bullshi-

namespace Colour { // Cant forget the useful stuff
  constexpr colour Black = "\033[30m";
  constexpr colour Green = "\033[32m";
  constexpr colour Blue = "\033[34m";
  constexpr colour Red = "\033[31m";
  constexpr colour Yellow = "\033[33m";
  constexpr colour Violet = "\033[35m";
  constexpr colour Brown = "\033[38;5;94m";
  constexpr colour Orange = "\033[38;5;208m";
  constexpr colour Pink = "\033[38;5;213m";
  constexpr colour Cyan = "\033[36m";
  constexpr colour Maroon = "\033[38;5;88m";
  constexpr colour Gray = "\033[90m";
  constexpr colour DarkGray = "\033[90m";
  constexpr colour White = "\033[97m";
  constexpr colour DarkBlue = "\033[38;5;18m";
}

namespace Control {
  constexpr textdata Clear = "\033[2J";
  constexpr textdata CursorHome = "\033[H";
  constexpr textdata ClearScreen = "\033[2J\033[H";
  constexpr textdata Open = "\033[";
}

class Text {
  public:
  Text(colour c, string t) : clr(c), text(t) {}
  string clr;
  string text;
};

class Console {
  string __c_col;
  public:
  Console(){}
  ~Console()
  {
    makecolour(Colour::White);
  }

  inline void write(costr s) {
    std::cout << s;
  }

  inline void writeln(costr s) {
    std::cout << s << "\n";
  }

  inline void flush() {
    std::cout << std::flush;
  }

  void setcolour(colour c) {
    __c_col = c;
  }

  void applycolour() {
    printf("%s", __c_col.c_str());
  }

  void makecolour(colour c) {
    setcolour(c);
    applycolour();
  }

  void textwrite(const Text &t) {
    std::cout << t.clr << t.text << Colour::White;
  }

  void textwriteln(const Text &t) {
    std::cout << t.clr << t.text << '\n' << Colour::White;
  }

  void clear() {
    printf("\033[2J");
  }
};
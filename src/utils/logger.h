#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdint>
#include <string>
#include <ctime>

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

namespace logger {

  struct LogLevel {
	const std::string name;

	LogLevel(const std::string& n) : name(n) {}
	virtual ~LogLevel(void) = default;
  };

  struct Info : public LogLevel {
	Info(void) : LogLevel(GREEN"Info") {}
  };

  struct Error : public LogLevel {
	Error(void) : LogLevel(RED"Error") {}
  };

  struct Debug : public LogLevel {
	Debug(void) : LogLevel(BLUE"Debug") {}
  };

  struct Warning : public LogLevel {
	Warning(void) : LogLevel(YELLOW"Warning") {}
  };

  template <typename T>
  void print(T only) {
	std::cout << only << RESET << '\n';
  }

  template <typename T, typename ... args>
  void print(T current, args... next) {
	std::cout << current << ' ';
	print(next...);
  }

  template <typename Level, typename ... args>
  void log(args ... to_print) {

	std::time_t time = std::time(nullptr);
	std::string time_str = std::ctime(&time);
	time_str.pop_back();

	std::cout << Level().name << " [" << time_str << "] ";

	print(to_print...);
  }

}

#endif

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "singleton.h"

namespace utils {

  class Logger : public Singleton {
	private:
	  Logger();
	public:
	  static Logger& getInstance();

	  void debug(std::string &module, const std::string &message);

	  void info(const std::string &module, const std::string &message);

	  void warning(const std::string &module, const std::string &message);

	  void error(const std::string &module, const std::string &message);

	private:
	  void logMessage(const std::string &priority, const std::string &module, const std::string &message);

  };

}

#endif

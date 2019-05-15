#include "../includes.h"
#include "logger.h"

namespace utils {

  Logger::Logger() {}

  Logger& Logger::getInstance() {
	static Logger logger;
	return logger;
  }

  void Logger::debug(std::string &module, const std::string &message) {
	logMessage("DEBUG", module, message);
  }

  void Logger::info(const std::string &module, const std::string &message) {
	logMessage("INFO", module, message);
  }

  void Logger::warning(const std::string &module, const std::string &message) {
	logMessage("WARNING", module, message);
  }

  void Logger::error(const std::string &module, const std::string &message) {
	logMessage("ERROR", module, message);
  }

  void Logger::logMessage(const std::string &priority, const std::string &module, const std::string &message) {
	std::cout << priority << ' ' << module << ' ' << message << '\n';
  }

}

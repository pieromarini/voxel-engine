#pragma once

#include <string>

namespace utils { 

  class FileUtils {
	public:
	  static std::string readFile(const char *filepath);
  };

} 

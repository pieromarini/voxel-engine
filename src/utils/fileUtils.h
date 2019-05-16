#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

namespace utils { 

  class FileUtils {
	public:
	  static std::string readFile(const char *filepath);
  };

} 

#endif

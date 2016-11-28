//
// Log.hpp for mSFML in /home/mikaz3/Tek3/B5/AI/mSFML
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Mon Oct 17 15:04:48 2016 Thomas Billot
// Last update Mon Oct 17 15:18:00 2016 Thomas Billot
//

# ifndef __LOG_FILE__
#  define __LOG_FILE__

#include <fstream>

inline void		writeInLogFile(const std::string &text)
{
  std::ofstream		log_file("Log.txt", std::ios_base::out | std::ios_base::app);
  log_file << text << std::endl;
}

#endif /* !__LOG_FILE__ */

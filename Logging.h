#include <string>
#include <iostream>

enum class MessageType {
  Important,
  Log,
  Debug
};

enum class MessageColor {
  ANSI_red = 196,
  ANSI_orange = 214,
  ANSI_blue = 33
};

class Logging {
private:
  static inline int m_log_limit = 0;
  static inline bool m_ignore_log_limit = false;
  static inline bool m_debug = false;
  static inline bool m_reached_log_limit = false;

public:
  Logging() = default;
  ~Logging() = default;
  Logging(const Logging& l) = delete;
  Logging & operator=(const Logging & l) = delete;

  static void set_log_limit(int log_limit) {
    m_log_limit = log_limit;
    m_reached_log_limit = false;
  }

  static void set_ignore_log_limit(bool ignore_log_limit) {
    m_ignore_log_limit = ignore_log_limit;
  }

  static void set_debug(bool debug) {
    m_debug = debug;
  }

  static std::string get_colored_string(const MessageColor & color, const std::string & code, const std::string & msg) {
    return "\033[38;5;" + std::to_string(int(color)) + "m" + code + msg + "\033[39m";
  }

  static void print_msg(const std::string & msg, const MessageType & msg_type) {
    switch(msg_type) {
      case MessageType::Important: {
        std::cout << get_colored_string(MessageColor::ANSI_red, "Important: ", msg) << std::endl;
        break;
      }
      case MessageType::Log: {
        static int s_count = 0;
        if (s_count < m_log_limit || m_ignore_log_limit) {
          std::cout << get_colored_string(MessageColor::ANSI_blue, "Log: ", msg) << std::endl;
          s_count++;
        }
        else if (!m_reached_log_limit) {
          std::cout << "Maximum number of log messages is reached: " << s_count << std::endl;
          m_reached_log_limit = true;
        }
        break;
      }
      case MessageType::Debug: {
        if (m_debug)
          std::cout << get_colored_string(MessageColor::ANSI_orange, "Debug: ", msg) << std::endl;
        break;
      }
    }
  }
};
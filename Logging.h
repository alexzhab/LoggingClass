#include <string>
#include <iostream>

static const int ANSI_red = 196;
static const int ANSI_orange = 214;
static const int ANSI_blue = 33;

enum class MessageType {
  Important,
  Log,
  Debug
};

class Logging {
private:
  static inline int m_log_limit = 0;
  static inline bool m_ignore_log_limit = false;
  static inline bool m_debug = false;

public:
  Logging() = default;
  ~Logging() = default;
  Logging(const Logging& l) = delete;
  Logging & operator=(const Logging & l) = delete;

  static void set_log_limit(int log_limit) {
    m_log_limit = log_limit;
  }

  static void set_ignore_log_limit(bool ignore_log_limit) {
    m_ignore_log_limit = ignore_log_limit;
  }

  static void set_debug(bool debug) {
    m_debug = debug;
  }

  static std::string get_string(const int colour, const std::string & code, const std::string & msg) {
    return "\033[38;5;" + std::to_string(colour) + "m" + code + msg + "\033[39m";
  }

  static void print_msg(const std::string & msg, const MessageType & msg_type) {
    if (msg_type == MessageType::Important) {
      std::cout << get_string(ANSI_red, "Important: ", msg) << std::endl;
    }
    else if (msg_type == MessageType::Log) {
      static int s_count = 0;
      if (s_count < m_log_limit || m_ignore_log_limit) {
        std::cout << get_string(ANSI_blue, "Log: ", msg) << std::endl;
        s_count++;
      }
      if (s_count == m_log_limit && !m_ignore_log_limit) {
        std::cout << "Maximum number of log messages is reached." << std::endl;
      }
    }
    else if (msg_type == MessageType::Debug) {
      if (m_debug)
        std::cout << get_string(ANSI_orange, "Debug: ", msg) << std::endl;
    }
  }
};
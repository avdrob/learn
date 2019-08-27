#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Logger {
public:
    explicit Logger(ostream& output_stream) : os(output_stream) {}

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file = value; }
    void Log(const string& message) { os << message << endl; }
    bool get_log_file() const { return log_file; }
    bool get_log_line() const { return log_line; }

private:
    ostream& os;
    bool log_line = false;
    bool log_file = false;
};

#define LOG(logger, message) {                              \
    ostringstream os;                                       \
    if (logger.get_log_file() && logger.get_log_line()) {   \
        os << __FILE__ << ":" << __LINE__ << " ";           \
    }                                                       \
    else if (logger.get_log_file()) {                       \
        os << __FILE__ << " ";                              \
    }                                                       \
    else if (logger.get_log_line()) {                       \
        os << "Line " << __LINE__ << " ";                   \
    }                                                       \
    os << message;                                          \
    logger.Log(os.str());                                   \
}
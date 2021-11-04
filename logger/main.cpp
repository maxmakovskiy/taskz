#include "test.h"
#include <sstream>
#include <string>

class Logger {
public:
    explicit Logger(std::ostream& output_stream) 
        : os(output_stream) 
    {
    }

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file= value; }

    void Log(const std::string& message)
    {
        if (log_line && log_file) {
            os << fileName << ":" << lineNumber << " " << message << std::endl;
        } else if (log_file) {
            os << fileName << " " << message << std::endl;
        } else if (log_line) {
            os << "Line " << lineNumber << " " << message << std::endl;
        } else {
            os << message << std::endl;
        }

    }

    void SetLineNumber(int lineNumber)
    {
        this->lineNumber = lineNumber;
    }

    void SetFileName(const std::string& fileName)
    {
        this->fileName = fileName;
    }

private:
    std::ostream& os;
    bool log_line = false;
    bool log_file = false;
    std::string fileName;
    int lineNumber;
};

#define LOG(logger, message)        \
    logger.SetFileName(__FILE__);   \
    logger.SetLineNumber(__LINE__); \
    logger.Log(message)

void TestLog() {
#line 1 "logger.cpp"

    std::ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");

    l.SetLogFile(true);
    LOG(l, "hello");

    l.SetLogLine(true);
    LOG(l, "hello");

    l.SetLogFile(false);
    LOG(l, "hello");

    std::string expected = "hello\n";
    expected += "logger.cpp hello\n";
    expected += "logger.cpp:10 hello\n";
    expected += "Line 13 hello\n";
    ASSERT_EQUAL(logs.str(), expected);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestLog);
}

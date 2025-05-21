#ifndef LOG_H
#define LOG_H

#include <string>
#include <ctime>
#include <deque>
#include <iostream>
#include <iomanip>
#include <ostream>
#include "../task4/counter.hpp"

enum log_type
{
    LOG_NORMAL,
    LOG_WARNING,
    LOG_ERROR
};

namespace task_5
{
    class LogMessage
    {
        std::string msg_, time_txt_;
        log_type type_;

    public:
        friend std::ostream &operator<<(std::ostream &os, const LogMessage &lm)
        {
            os << "time: " << lm.time_txt_ << "| type: " << lm.type_ << "| message: " << lm.msg_;
            return os;
        }

        LogMessage(log_type type, std::string &msg);

        ~LogMessage() = default;
    };
}

class Log : counter<Log>
{
    size_t msg_count_ = 0, max_count_ = 0;
    std::deque<task_5::LogMessage> message_pool_{};
    Log(size_t N = 10);

public:
    static Log *Instance(size_t N = 10);

    ~Log() = default;
    Log(const Log &) = delete;
    Log(const Log &&) = delete;

    void message(log_type type, std::string msg);

    void print();
};

#endif // LOG_H

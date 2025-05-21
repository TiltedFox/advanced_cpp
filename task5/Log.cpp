#include "Log.h"
#include <sstream>

task_5::LogMessage::LogMessage(log_type type, std::string &msg) : msg_(msg), type_(type)
{
    std::time_t now = std::time(nullptr);
    std::tm *tm = std::localtime(&now);

    std::ostringstream oss{};
    oss << std::put_time(tm, "%H:%M:%S");
    time_txt_ = oss.str();
}

Log::Log(size_t N) : max_count_(N)
{
    if (N == 0)
    {
        std::cout << "max amount of log messages must be more than zero; set amount to 10\n";
        max_count_ = 10;
    }

    if (counter<Log>::count() > 1)
    {
        throw std::logic_error("log already exists");
    }
}

Log *Log::Instance(size_t N)
{
    if (N == 0)
    {
        std::cout << "max amount of log messages must be more than zero; set amount to N=10\n";
        N = 10;
    }

    return new Log(N);
}

void Log::message(log_type type, std::string msg)
{
    ++msg_count_;
    if (msg_count_ > max_count_)
    {
        message_pool_.pop_front();
        --msg_count_;
    }

    message_pool_.emplace_back(type, msg);
}

void Log::print()
{
    for (auto &msg : message_pool_)
    {
        std::cout << msg << "\n";
    }
}

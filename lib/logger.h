#ifndef LOGGER_H
#define LOGGER_H

#include "fmt/format.h"

class TrackDataFlux;
class TrackFlux;
class Sector;

struct BeginSpeedOperationLogMessage {};
struct EndSpeedOperationLogMessage
{
	nanoseconds_t rotationalPeriod;
};
	
struct DiskContextLogMessage
{
    unsigned cylinder;
    unsigned head;
};

struct SingleReadLogMessage
{
	std::shared_ptr<const TrackDataFlux> trackDataFlux;
	std::set<std::shared_ptr<const Sector>> sectors;
};

struct TrackReadLogMessage
{
	std::shared_ptr<TrackFlux> track;
};

struct BeginReadOperationLogMessage { };
struct EndReadOperationLogMessage { };
struct BeginWriteOperationLogMessage { };
struct EndWriteOperationLogMessage { };

class TrackFlux;

typedef std::variant<std::string,
	SingleReadLogMessage,
	TrackReadLogMessage,
    DiskContextLogMessage,
	BeginSpeedOperationLogMessage,
	EndSpeedOperationLogMessage,
    BeginReadOperationLogMessage,
    EndReadOperationLogMessage,
	BeginWriteOperationLogMessage,
	EndWriteOperationLogMessage>
    AnyLogMessage;

class Logger
{
public:
    Logger& operator<<(std::shared_ptr<const AnyLogMessage> message);

    template <class T>
    Logger& operator<<(const T& message)
    {
        return *this << std::make_shared<const AnyLogMessage>(message);
    }

    static void setLogger(
        std::function<void(std::shared_ptr<const AnyLogMessage>)> cb);

    static std::string toString(const AnyLogMessage&);
    static void textLogger(std::shared_ptr<const AnyLogMessage>);
};

#endif

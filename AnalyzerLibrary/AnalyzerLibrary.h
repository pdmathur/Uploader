
#pragma once

#define _ws "http://dev.trifectashot.com/trifecta/api"
#define _aws "https://tfcta.s3.amazonaws.com/"
#define _localName "\\\\192.168.0.100\\media"

#define POSTTRIG 7	// Number of samples beyond trigger needed for target trajsectory extrapolation
#define LOGINFO(x) log->Log(Logger::LogLevel::INFO, (x))
#define LOGWARN(x) log->Log(Logger::LogLevel::WARN, (x))
#define LOGERR(x)  log->Log(Logger::LogLevel::ERR, (x))

#define EXPORTALLFPS 15
#define EXPORTALL_START 20
#define EXPORTALL_END 70

#define ROLE_COACH 0x01
#define ROLE_OWNER 0x02
#define ROLE_ANALYZER 0x04
#define ROLE_PLAYER 0x08

#define STUFF_LOADVIDEO 0x0001
#define STUFF_MAXES 0x0002
#define STUFF_MAXMAP 0x0004
#define STUFF_GOODPTS 0x0008
#define STUFF_STUB 0x0010
#define STUFF_SEARCH 0x0020
#define STUFF_MASK 0x8000

#define MAX_AIMRADIUS 10000

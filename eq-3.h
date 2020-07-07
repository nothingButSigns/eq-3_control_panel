#ifndef EQ3_H
#define EQ3_H

#include <qglobal.h>

#define SERVICE_UUID "{3e135142-654f-9090-134a-a6ff5bb77046}"
#define CHAR_UUID "{3fa4585a-ce4a-3bad-db4b-b8df8179ea09}"
#define NOTIFICATION "{d0e8434d-cd29-0996-af41-6c90f4e0eb2a}"

// 0-bytes
#define SET_DATE_TIME 0x03
#define SET_TEMP 0x41
#define SET_COMFORT 0x43
#define SET_REDUCED 0x44
#define MODIFY_COMF_RED 0x11
#define BOOST 0x45
#define AUTO_1_BIT 0x40
#define AUTO_2_BIT 0x00
#define MANUAL_1_BIT 0x40
#define MANUAL_2_BIT 0x40
#define HOLIDAY 0x40
#define LOCK 0x80
#define CREATE_PROFILE 0x10
#define READ_PROFILE 0x20
#define WINDOW_MODE 0x14
#define SET_OFFSET 0x13

// generic types
#define ON 0x01
#define OFF 0x00

// weekdays code

enum Weekdays {
    SATURDAY,
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY
};



#endif // EQ3_H

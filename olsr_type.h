//
// Created by chuanyi on 16-9-11.
//

#ifndef OLSR_MIN_OLSR_TYPE_H
#define OLSR_MIN_OLSR_TYPE_H

typedef signed char    int8_t;
typedef signed short   int16_t;
typedef signed int     int32_t;

typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;

typedef struct {
    uint32_t L_local_iface_addr;
    uint32_t L_neighbor_iface_addr;
    uint32_t L_SYM_time;
    uint32_t L_ASYM_time;
    uint32_t L_time;
} Tuple;

// realtime (micro seconds, us)
typedef uint32_t RealTime;

/**
 * actual time t (s) is stored in this way
 * t = C*(1 + a/16)*2^b
 * a: Vtime[7:4], b: Vtime[3:0], C: 1/16
 */
typedef uint8_t Vtime;

RealTime Vtime_to_RealTime(Vtime);
Vtime RealTime_to_Vtime(RealTime);

struct PacketHead{
    uint16_t    PckLength;              // N byte
    uint16_t    PckSequenceNumber;
    uint8_t     MsgType;
    Vtime       PckVtime;               // valid time
    uint16_t    MsgSize;
    uint32_t    PckOriginatorAddress;
    uint8_t     PckTTL;                 // TTL: time to live
    uint8_t     PckHopCount;
    uint16_t    MsgSequenceNumber;
};

#endif //OLSR_MIN_OLSR_TYPE_H

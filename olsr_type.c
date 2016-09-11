//
// Created by chuanyi on 16-9-11.
//

#include "olsr_type.h"

/**
 * Vtime_to_RealTime - convert 8bit Vtime format to real time (micro seconds)
 * @t_v: Vtime format time, [a[3:0], b[3:0]]
 *
 * Return real time t = (1/16)*(1 + a/16)*2^b
 */
RealTime Vtime_to_RealTime(Vtime t_v)
{
    uint8_t a = t_v>>4;
    uint8_t b = t_v & 0x0F;
    /**
     * t(s) = (1+a/16)*2^b/16
     *      = (16+a)*2^(b-8)
     */
    return (b>8) ? ((16+a)<<(b-8)*1000000) : (((16+a)*1000000)>>(8-b));
}

/**
 * RealTime_to_Vtime - convert real time (micro seconds) to 8bit Vtime format
 * @t_r: real time in micro seconds (us)
 *
 * Return real time t(us) = (1/16)*(1 + a/16)*2^b * 1000'000
 */
Vtime RealTime_to_Vtime(RealTime t_r)
{
    uint32_t temp;
    uint8_t a,
            b = 0;

    if (t_r == 0)
        return 0;
    temp = (uint32_t)((t_r<<4)/1000000.0);
    while (temp>>=0x1) ++b;
    /**
     * a = 16*( t_r(us)/1000'000/(1/16*2^b) - 1 )
     *   = t_r(us)*256/1000'000/2^b - 16
     *   = t_r(us)/15625/2^(b-2) - 16
     *   = ( t_r(us) - 15625*2^(b+2) )/2^(b-2)/15625
     *   = ( t_r(us) - 15625<<(b+2) )>>(b-2)/15625
     */
    a = (b>2) ?
        (uint8_t) (( (t_r - (15625<<(b+2))) )/(double)(15625<<(b-2)) )
              : (uint8_t) (( (t_r - (15625<<(b+2)))<<(2-b) )/15625.0 );

    return (a<<4) | (b&0x0F);
}

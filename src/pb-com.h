#ifndef _PB_COM_H
#define _PB_COM_H

#include <twr.h>
#include <bcl.h>
#include <pb.h>


// PBC - Protocol Buffer Comunication

// Reasonable limits for SMT32L0 (20kB RAM)
#define PBC_MAX_PARTS   16
#define PBC_MESSAGE_LEN 32
#define PBC_MAX_LEN     (PBC_MAX_PARTS * PBC_MESSAGE_LEN)

// buffer for base64 decoded incoming data
typedef struct 
{
    uint8_t inbuff[PBC_MAX_LEN];
    uint16_t inbuff_len;
    uint8_t parsed[PBC_MAX_PARTS/8]; // flags, bit set to "1" for each parsed part on part index, up to PBC_MAX_PARTS parts
    uint16_t count_total;
    uint8_t id;
} pbc_t;

extern pbc_t pbc;


#endif

#include <pb-com.h>
#include <pb.h>
#include <pb_decode.h>

pbc_t pbc = {.id = 0xFF};


bool pbc_is_complete(pbc_t * pbt) {
    bool complete = true;
    int i = 0;
    for (; i<pbt->count_total/8; i++) {
        complete &= (pbt->parsed[i] == 0xFF);
    }
    complete &= (pbt->parsed[i] == (0xFF >> (8-pbt->count_total%8)));
    return complete;
}

// TODO error messages
bool pbc_parse(pbc_t * pbt, const char * msg) {
    uint8_t decoded[PBC_MESSAGE_LEN + 4];
    size_t decoded_len;

    // TODO check for decoded length first to prevent buffer overflow
    bool dok = twr_base64_decode(decoded, &decoded_len, msg, strlen(msg));
    if (!dok) {
        return false;
    }

    // critical! buffer overflow
    if (decoded_len > PBC_MESSAGE_LEN+2) {
        twr_log_error("PB parser: decoded part is too long, buffer overflow! (decoded=%u, max=%u)", decoded_len, PBC_MESSAGE_LEN+2);
        return false;
    }

    uint8_t idx = decoded[0];
    uint8_t id = decoded[1] & 0x7F;
    bool last = (decoded[1] & 0x80) > 0;

    // buffer is too small for whole message
    if (idx >= PBC_MAX_PARTS) {
        twr_log_error("PB parser: message too long! (parts=%u, max=%u)", idx+1, PBC_MAX_PARTS);
        return false;
    }

    // // wrong part header
    // if (idx > count-1) {
    //     twr_log_error("PB parser: invalid part header, idx=%u > parts=%u)", idx, count-1);
    //     return false;
    // }

    // count must be same across all parts, if differs, it seems we are mixing different messages
    if (pbt->id < 0x80 && pbt->id > 0 && id != pbt->id) {
        twr_log_error("PB parser: ID differs between parts, mixing different messages? (new=%u, old=%u)", id, pbt->id);
        return false;
    }

    memcpy(pbt->inbuff+idx*PBC_MESSAGE_LEN, decoded+2, decoded_len-2);

    if (last) {
        pbt->count_total = idx + 1;
    }

    // set bit for parsed part so we can check in the end we have all parts
    int parsed_bit = idx & 0x07;
    int parsed_idx = idx >> 3;
    pbt->parsed[parsed_idx] |= 1 << parsed_bit;
    pbt->inbuff_len += decoded_len-2;

    twr_log_debug("PB parser: parsed part %u, id=%x, last=%u", idx+1, id, last);

    return true;
}

/**
 * @brief nanopb input stream read callback - reads from static array
 * 
 * @param stream - input stream
 * @param buf - buffer to write data to
 * @param count - how many bytes to read
 * @return true - OK
 * @return false - error was encountered (not used)
 */
bool pb_istream_read_array(pb_istream_t *stream, uint8_t *buf, size_t count) {
    static uint16_t stream_head = 0;

    if (!stream->state) {
        stream->state = (void *)&stream_head;
        // stream->bytes_left = displaytest_bin_len;
    }
    
    if (count > pbc.inbuff_len-stream_head) {
        count = pbc.inbuff_len-stream_head;
        // twr_log_warning("PB istream: count larger than remaining data left: Count=%u > len=%u - head=%u (left=%u)", count, displaytest_bin_len, stream_head, stream->bytes_left);
    }

    // EOF
    if (count == 0) {
        stream->bytes_left = 0;
        return false;
    }
    
    // twr_log_dump(displaytest_bin+stream_head, count, "PB istream: copying %u bytes, head=%u, left=%u", count, stream_head, stream->bytes_left);
    memcpy(buf, pbc.inbuff+stream_head, count);
    stream_head += count;
    // stream->bytes_left = displaytest_bin_len - stream_head;
    // twr_log_dump(buf, count, "PB istream: copy done, new head=%u, left=%u", stream_head, stream->bytes_left);

    return true;
}

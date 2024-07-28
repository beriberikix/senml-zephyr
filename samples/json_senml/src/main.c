#include <zephyr.h>
#include <sys/printk.h>
#include "senml_codec.h"

void main(void)
{
    printk("Hello, SenML Codec Module (JSON)!\n");

    struct senml_record record = {
        .bn = "device-1",
        .bt = 0,
        .bu = "C",
        .bv = 0,
        .n = "temperature",
        .u = "C",
        .v = 25.3,
        .vs = NULL,
        .vb = 0,
        .vd = NULL,
        .s = 0,
        .ut = 0
    };

    char buffer[256];
    int ret = senml_encode_record(&record, buffer, sizeof(buffer));
    if (ret == 0) {
        printk("Encoded JSON: %s\n", buffer);
    } else {
        printk("Failed to encode JSON\n");
    }

    struct senml_record decoded_record;
    ret = senml_decode_record(buffer, sizeof(buffer), &decoded_record);
    if (ret == 0) {
        printk("Decoded JSON Record: bn=%s, bt=%f, bu=%s, bv=%f, n=%s, u=%s, v=%f, s=%f, ut=%f\n",
               decoded_record.bn, decoded_record.bt, decoded_record.bu, decoded_record.bv,
               decoded_record.n, decoded_record.u, decoded_record.v, decoded_record.s, decoded_record.ut);
    } else {
        printk("Failed to decode JSON\n");
    }
}
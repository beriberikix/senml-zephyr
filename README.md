# SenML Codec for Zephyr

The `senml-zephyr` project provides a codec for encoding and decoding Sensor Measurement Lists (SenML) as defined in [RFC 8428](https://datatracker.ietf.org/doc/html/rfc8428) & [RFC 8798](https://datatracker.ietf.org/doc/html/rfc8798). This codec supports both JSON and CBOR formats for data serialization.

## Configuration

The project provides configuration options via Kconfig:

- `SENML_CODEC`: Enable the SenML codec module.
- `SENML_FORMAT_JSON`: Enable support for JSON format.
- `SENML_FORMAT_CBOR`: Enable support for CBOR format (default).

## Usage

### Encoding and Decoding SenML Records

Include the SenML codec header in your application:
```
#include "senml_codec.h"
```

Create and encode a SenML record:
```
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
```

Decode a SenML record:
```
struct senml_record decoded_record;
ret = senml_decode_record(buffer, sizeof(buffer), &decoded_record);
if (ret == 0) {
    printk("Decoded JSON Record: bn=%s, bt=%f, bu=%s, bv=%f, n=%s, u=%s, v=%f, s=%f, ut=%f\n",
           decoded_record.bn, decoded_record.bt, decoded_record.bu, decoded_record.bv,
           decoded_record.n, decoded_record.u, decoded_record.v, decoded_record.s, decoded_record.ut);
} else {
    printk("Failed to decode JSON\n");
}
```
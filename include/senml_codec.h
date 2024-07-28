#ifndef SENML_CODEC_H
#define SENML_CODEC_H

#include <stddef.h>

#ifdef CONFIG_SENML_FORMAT_JSON
#define SENML_FORMAT_JSON 1
#endif

#ifdef CONFIG_SENML_FORMAT_CBOR
#define SENML_FORMAT_CBOR 2
#endif

struct senml_record {
    const char *bn;           // Base Name
    double bt;                // Base Time
    const char *bu;           // Base Unit
    double bv;                // Base Value
    const char *n;            // Name
    const char *u;            // Unit
    double v;                 // Value (numeric)
    const char *vs;           // Value (string)
    int vb;                   // Value (boolean)
    const char *vd;           // Value (data)
    double s;                 // Sum
    double ut;                // Update Time
};

void senml_codec_init(void);
void senml_codec_cleanup(void);

int senml_encode_record(const struct senml_record *record, char *buffer, size_t buffer_size);
int senml_encode_records(const struct senml_record *records, size_t num_records, char *buffer, size_t buffer_size);

int senml_decode_record(const char *buffer, size_t buffer_size, struct senml_record *record);
int senml_decode_records(const char *buffer, size_t buffer_size, struct senml_record *records, size_t max_records);

#endif // SENML_CODEC_H
#include "senml_codec.h"
#include <zephyr.h>

#ifdef CONFIG_SENML_FORMAT_JSON
#include <json.h>
#endif

#ifdef CONFIG_SENML_FORMAT_CBOR
#include <zcbor_encode.h>
#include <zcbor_decode.h>
#endif

void senml_codec_init(void) {
    // Initialize resources, if any
}

void senml_codec_cleanup(void) {
    // Clean up resources, if any
}

int senml_encode_record(const struct senml_record *record, char *buffer, size_t buffer_size) {
#ifdef CONFIG_SENML_FORMAT_JSON
    // JSON encoding using Zephyr's JSON library
    struct json_obj_encode_obj json_encoder;
    const struct json_obj_descr senml_record_descr[] = {
        JSON_OBJ_DESCR_PRIM(struct senml_record, bn, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bt, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bu, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bv, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, n, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, u, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, v, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vs, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vb, JSON_TOK_TRUE),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vd, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, s, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, ut, JSON_TOK_NUMBER)
    };

    json_obj_encode_init(&json_encoder, buffer, buffer_size, NULL);
    int ret = json_obj_encode(&json_encoder, senml_record_descr, ARRAY_SIZE(senml_record_descr), record);

    return ret;
#endif

#ifdef CONFIG_SENML_FORMAT_CBOR
    // CBOR encoding using zcbor library
    struct zcbor_state zcbor_encoder;
    zcbor_encoder_init(&zcbor_encoder, buffer, buffer_size);

    zcbor_start_map(&zcbor_encoder, 12); // Adjust map size based on fields
    zcbor_add_tstr(&zcbor_encoder, "bn");
    zcbor_add_tstr(&zcbor_encoder, record->bn);
    zcbor_add_tstr(&zcbor_encoder, "bt");
    zcbor_add_double(&zcbor_encoder, record->bt);
    zcbor_add_tstr(&zcbor_encoder, "bu");
    zcbor_add_tstr(&zcbor_encoder, record->bu);
    zcbor_add_tstr(&zcbor_encoder, "bv");
    zcbor_add_double(&zcbor_encoder, record->bv);
    zcbor_add_tstr(&zcbor_encoder, "n");
    zcbor_add_tstr(&zcbor_encoder, record->n);
    zcbor_add_tstr(&zcbor_encoder, "u");
    zcbor_add_tstr(&zcbor_encoder, record->u);
    zcbor_add_tstr(&zcbor_encoder, "v");
    zcbor_add_double(&zcbor_encoder, record->v);
    zcbor_add_tstr(&zcbor_encoder, "vs");
    zcbor_add_tstr(&zcbor_encoder, record->vs);
    zcbor_add_tstr(&zcbor_encoder, "vb");
    zcbor_add_bool(&zcbor_encoder, record->vb);
    zcbor_add_tstr(&zcbor_encoder, "vd");
    zcbor_add_tstr(&zcbor_encoder, record->vd);
    zcbor_add_tstr(&zcbor_encoder, "s");
    zcbor_add_double(&zcbor_encoder, record->s);
    zcbor_add_tstr(&zcbor_encoder, "ut");
    zcbor_add_double(&zcbor_encoder, record->ut);
    zcbor_end_map(&zcbor_encoder);

    return zcbor_encoder.ret;
#endif

    return -1; // Unsupported format
}

int senml_encode_records(const struct senml_record *records, size_t num_records, char *buffer, size_t buffer_size) {
#ifdef CONFIG_SENML_FORMAT_JSON
    // JSON encoding using Zephyr's JSON library
    struct json_obj_encode_obj json_encoder;
    const struct json_obj_descr senml_record_descr[] = {
        JSON_OBJ_DESCR_PRIM(struct senml_record, bn, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bt, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bu, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bv, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, n, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, u, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, v, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vs, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vb, JSON_TOK_TRUE),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vd, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, s, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, ut, JSON_TOK_NUMBER)
    };

    json_obj_encode_init(&json_encoder, buffer, buffer_size, NULL);
    int ret = 0;
    for (size_t i = 0; i < num_records; ++i) {
        ret = json_obj_encode(&json_encoder, senml_record_descr, ARRAY_SIZE(senml_record_descr), &records[i]);
        if (ret != 0) {
            return ret;
        }
    }

    return ret;
#endif

#ifdef CONFIG_SENML_FORMAT_CBOR
    // CBOR encoding using zcbor library
    struct zcbor_state zcbor_encoder;
    zcbor_encoder_init(&zcbor_encoder, buffer, buffer_size);

    zcbor_start_map(&zcbor_encoder, num_records * 12); // Adjust map size based on fields
    for (size_t i = 0; i < num_records; ++i) {
        zcbor_add_tstr(&zcbor_encoder, "bn");
        zcbor_add_tstr(&zcbor_encoder, records[i].bn);
        zcbor_add_tstr(&zcbor_encoder, "bt");
        zcbor_add_double(&zcbor_encoder, records[i].bt);
        zcbor_add_tstr(&zcbor_encoder, "bu");
        zcbor_add_tstr(&zcbor_encoder, records[i].bu);
        zcbor_add_tstr(&zcbor_encoder, "bv");
        zcbor_add_double(&zcbor_encoder, records[i].bv);
        zcbor_add_tstr(&zcbor_encoder, "n");
        zcbor_add_tstr(&zcbor_encoder, records[i].n);
        zcbor_add_tstr(&zcbor_encoder, "u");
        zcbor_add_tstr(&zcbor_encoder, records[i].u);
        zcbor_add_tstr(&zcbor_encoder, "v");
        zcbor_add_double(&zcbor_encoder, records[i].v);
        zcbor_add_tstr(&zcbor_encoder, "vs");
        zcbor_add_tstr(&zcbor_encoder, records[i].vs);
        zcbor_add_tstr(&zcbor_encoder, "vb");
        zcbor_add_bool(&zcbor_encoder, records[i].vb);
        zcbor_add_tstr(&zcbor_encoder, "vd");
        zcbor_add_tstr(&zcbor_encoder, records[i].vd);
        zcbor_add_tstr(&zcbor_encoder, "s");
        zcbor_add_double(&zcbor_encoder, records[i].s);
        zcbor_add_tstr(&zcbor_encoder, "ut");
        zcbor_add_double(&zcbor_encoder, records[i].ut);
    }
    zcbor_end_map(&zcbor_encoder);

    return zcbor_encoder.ret;
#endif

    return -1; // Unsupported format
}

int senml_decode_record(const char *buffer, size_t buffer_size, struct senml_record *record) {
#ifdef CONFIG_SENML_FORMAT_JSON
    // JSON decoding using Zephyr's JSON library
    struct json_obj_decode_obj json_decoder;
    const struct json_obj_descr senml_record_descr[] = {
        JSON_OBJ_DESCR_PRIM(struct senml_record, bn, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bt, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bu, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bv, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, n, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, u, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, v, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vs, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vb, JSON_TOK_TRUE),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vd, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, s, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, ut, JSON_TOK_NUMBER)
    };

    json_obj_decode_init(&json_decoder, buffer, buffer_size, NULL);
    int ret = json_obj_decode(&json_decoder, senml_record_descr, ARRAY_SIZE(senml_record_descr), record);

    return ret;
#endif

#ifdef CONFIG_SENML_FORMAT_CBOR
    // CBOR decoding using zcbor library
    struct zcbor_state zcbor_decoder;
    zcbor_decoder_init(&zcbor_decoder, buffer, buffer_size);

    zcbor_start_map(&zcbor_decoder, 12); // Adjust map size based on fields
    zcbor_next_element(&zcbor_decoder, "bn");
    zcbor_get_tstr(&zcbor_decoder, &record->bn);
    zcbor_next_element(&zcbor_decoder, "bt");
    zcbor_get_double(&zcbor_decoder, &record->bt);
    zcbor_next_element(&zcbor_decoder, "bu");
    zcbor_get_tstr(&zcbor_decoder, &record->bu);
    zcbor_next_element(&zcbor_decoder, "bv");
    zcbor_get_double(&zcbor_decoder, &record->bv);
    zcbor_next_element(&zcbor_decoder, "n");
    zcbor_get_tstr(&zcbor_decoder, &record->n);
    zcbor_next_element(&zcbor_decoder, "u");
    zcbor_get_tstr(&zcbor_decoder, &record->u);
    zcbor_next_element(&zcbor_decoder, "v");
    zcbor_get_double(&zcbor_decoder, &record->v);
    zcbor_next_element(&zcbor_decoder, "vs");
    zcbor_get_tstr(&zcbor_decoder, &record->vs);
    zcbor_next_element(&zcbor_decoder, "vb");
    zcbor_get_bool(&zcbor_decoder, &record->vb);
    zcbor_next_element(&zcbor_decoder, "vd");
    zcbor_get_tstr(&zcbor_decoder, &record->vd);
    zcbor_next_element(&zcbor_decoder, "s");
    zcbor_get_double(&zcbor_decoder, &record->s);
    zcbor_next_element(&zcbor_decoder, "ut");
    zcbor_get_double(&zcbor_decoder, &record->ut);
    zcbor_end_map(&zcbor_decoder);

    return zcbor_decoder.ret;
#endif

    return -1; // Unsupported format
}

int senml_decode_records(const char *buffer, size_t buffer_size, struct senml_record *records, size_t max_records) {
#ifdef CONFIG_SENML_FORMAT_JSON
    // JSON decoding using Zephyr's JSON library
    struct json_obj_decode_obj json_decoder;
    const struct json_obj_descr senml_record_descr[] = {
        JSON_OBJ_DESCR_PRIM(struct senml_record, bn, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bt, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bu, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, bv, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, n, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, u, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, v, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vs, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vb, JSON_TOK_TRUE),
        JSON_OBJ_DESCR_PRIM(struct senml_record, vd, JSON_TOK_STRING),
        JSON_OBJ_DESCR_PRIM(struct senml_record, s, JSON_TOK_NUMBER),
        JSON_OBJ_DESCR_PRIM(struct senml_record, ut, JSON_TOK_NUMBER)
    };

    json_obj_decode_init(&json_decoder, buffer, buffer_size, NULL);
    int ret = 0;
    for (size_t i = 0; i < max_records; ++i) {
        ret = json_obj_decode(&json_decoder, senml_record_descr, ARRAY_SIZE(senml_record_descr), &records[i]);
        if (ret != 0) {
            return ret;
        }
    }

    return ret;
#endif

#ifdef CONFIG_SENML_FORMAT_CBOR
    // CBOR decoding using zcbor library
    struct zcbor_state zcbor_decoder;
    zcbor_decoder_init(&zcbor_decoder, buffer, buffer_size);

    zcbor_start_map(&zcbor_decoder, max_records * 12); // Adjust map size based on fields
    for (size_t i = 0; i < max_records; ++i) {
        zcbor_next_element(&zcbor_decoder, "bn");
        zcbor_get_tstr(&zcbor_decoder, &records[i].bn);
        zcbor_next_element(&zcbor_decoder, "bt");
        zcbor_get_double(&zcbor_decoder, &records[i].bt);
        zcbor_next_element(&zcbor_decoder, "bu");
        zcbor_get_tstr(&zcbor_decoder, &records[i].bu);
        zcbor_next_element(&zcbor_decoder, "bv");
        zcbor_get_double(&zcbor_decoder, &records[i].bv);
        zcbor_next_element(&zcbor_decoder, "n");
        zcbor_get_tstr(&zcbor_decoder, &records[i].n);
        zcbor_next_element(&zcbor_decoder, "u");
        zcbor_get_tstr(&zcbor_decoder, &records[i].u);
        zcbor_next_element(&zcbor_decoder, "v");
        zcbor_get_double(&zcbor_decoder, &records[i].v);
        zcbor_next_element(&zcbor_decoder, "vs");
        zcbor_get_tstr(&zcbor_decoder, &records[i].vs);
        zcbor_next_element(&zcbor_decoder, "vb");
        zcbor_get_bool(&zcbor_decoder, &records[i].vb);
        zcbor_next_element(&zcbor_decoder, "vd");
        zcbor_get_tstr(&zcbor_decoder, &records[i].vd);
        zcbor_next_element(&zcbor_decoder, "s");
        zcbor_get_double(&zcbor_decoder, &records[i].s);
        zcbor_next_element(&zcbor_decoder, "ut");
        zcbor_get_double(&zcbor_decoder, &records[i].ut);
    }
    zcbor_end_map(&zcbor_decoder);

    return zcbor_decoder.ret;
#endif

    return -1; // Unsupported format
}
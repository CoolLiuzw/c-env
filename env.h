#ifndef __ENV__
#define __ENV__

typedef enum {
    ENV_FALSE = 0,
    ENV_TRUE = 1
} env_bool_t;

const char* env_get_string(const char* key, const char* default_value);
const int env_get_int(const char* key, const int default_value);
const env_bool_t env_get_bool(const char* key, const env_bool_t default_value);

const char* env_mustget_string(const char* key);
const int env_mustget_int(const char* key);
const env_bool_t env_mustget_bool(const char* key);

#endif
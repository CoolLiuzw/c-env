#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef enum {
    ENV_FALSE = 0,
    ENV_TRUE = 1
} env_bool_t;

#ifdef _WIN32
#define strcasecmp(s1, s2) stricmp(s1, s2)
#endif

static env_bool_t zstr(const char *s)
{
    return (s == NULL || s[0] == '\0') ? ENV_TRUE : ENV_FALSE;
}

static const char* env_get_string_imp(const char* key, const char* default_value, env_bool_t must_get)
{
    char* val = getenv(key);
    if (!zstr(val)) {
        return val;
    }

    if (must_get) {
        printf("env key \"%s\" does not find!\n", key);
        assert(NULL);
    } else {
        return default_value;
    }
}

static const int env_get_int_imp(const char* key, const int default_value, env_bool_t must_get)
{
    const char* val = getenv(key);
    if (!zstr(val)) {
        return atoi(val);
    }

    if (must_get) {
        printf("env key \"%s\" does not find!\n", key);
        assert(NULL);
    } else {
        return default_value;
    }
}

static env_bool_t env_true(const char *s)
{
    if (zstr(s)) {
        return ENV_FALSE;
    }

    if (!strcasecmp(s, "yes") ||
        !strcasecmp(s, "true") ||
        !strcasecmp(s, "y") ||
        !strcasecmp(s, "t") ||
        !strcasecmp(s, "1") ||
        !strcasecmp(s, "enabled") ||
        !strcasecmp(s, "active") ||
        !strcasecmp(s, "allow") ||
        !strcasecmp(s, "on")) {
        return ENV_TRUE;
    }

    return ENV_FALSE;
}

static const env_bool_t env_get_bool_imp(const char* key, const env_bool_t default_value, env_bool_t must_get)
{
    const char* val = getenv(key);
    if (!zstr(val)) {
        return env_true(val);
    }

    if (must_get) {
        printf("env key \"%s\" does not find!\n", key);
        assert(NULL);
    } else {
        return default_value;
    }

}

const char* env_get_string(const char* key, const char* default_value)
{
    return env_get_string_imp(key, default_value, ENV_FALSE);
}

const int env_get_int(const char* key, const int default_value)
{
    return env_get_int_imp(key, default_value, ENV_FALSE);
}

const env_bool_t env_get_bool(const char* key, const env_bool_t default_value)
{
    return env_get_bool_imp(key, default_value, ENV_FALSE);
}

const char* env_mustget_string(const char* key)
{
    return env_get_string_imp(key, NULL, ENV_TRUE);
}

const int env_mustget_int(const char* key)
{
    return env_get_int_imp(key, 0, ENV_TRUE);
}

const env_bool_t env_mustget_bool(const char* key)
{
    return env_get_bool_imp(key, ENV_FALSE, ENV_TRUE);
}

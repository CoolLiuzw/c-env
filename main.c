#include <stdio.h>
#include "env.h"

int main()
{
    const char* test_env = env_get_string("TEST_ENV", "123123");
    printf("%s\n", test_env);

    const char* test_env2 = env_mustget_string("TEST_INV2");
    printf("%s\n", test_env2);
    return 0;
}
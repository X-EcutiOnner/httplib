#include "http.h"
#include "debug.h"

int main(void)
{
    struct http_opts opts = {
        .cookies = "key1=value1;key2=value2",
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/cookies", &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

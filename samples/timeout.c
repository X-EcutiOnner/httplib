#include "http.h"
#include "debug.h"

int main(void)
{
    struct http_opts opts = {
        .timeout_secs = 1
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/delay/2", &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

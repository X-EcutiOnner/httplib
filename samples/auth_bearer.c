#include "http.h"
#include "debug.h"

int main(void)
{
    struct http_opts opts = {
        .auth = HTTP_AUTH_BEARER("token-abc123"),
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/bearer", &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

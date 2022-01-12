#include "http.h"
#include "debug.h"


int main(void) {
    struct http_opts opts = {
        .timeout_secs = 1,
        .auth = HTTP_AUTH_BEARER("token-abc123"),
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/bearer", &opts);
    response_print(resp);
    http_response_free(resp);
}

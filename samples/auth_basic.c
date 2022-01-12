#include "http.h"
#include "debug.h"

#define HTTPBIN_URL_BASIC_AUTH(user, password)      "https://httpbin.org/basic-auth/" user "/" password

int main(void) {
    struct http_auth_basic auth = HTTP_AUTH_BASIC_INIT("me", "p4$$w0rd");
    struct http_opts opts = {
        .timeout_secs = 1,
        .auth = HTTP_AUTH_CAST(&auth),
    };
    struct http_response *resp = http_request("GET", HTTPBIN_URL_BASIC_AUTH("me", "p4$$w0rd"), &opts);
    response_print(resp);
    http_response_free(resp);
}

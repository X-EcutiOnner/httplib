#include "http.h"
#include "debug.h"

#define HTTPBIN_URL_BASIC_AUTH(user, password)      "https://httpbin.org/basic-auth/" user "/" password

int main(void)
{
    struct http_opts opts = {
        .auth = HTTP_AUTH_BASIC("me", "p4$$w0rd"),
    };
    struct http_response *resp = http_request("GET", HTTPBIN_URL_BASIC_AUTH("me", "p4$$w0rd"), &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

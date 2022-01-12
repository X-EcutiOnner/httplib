#include "http.h"
#include "debug.h"

#define HTTPBIN_URL_DIGEST_AUTH(user, password)      "https://nghttp2.org/httpbin/digest-auth/x/" user "/" password

int main(void)
{
    struct http_opts opts = {
        .auth = HTTP_AUTH_DIGEST("me", "p4$$w0rd"),
    };
    struct http_response *resp = http_request("GET", HTTPBIN_URL_DIGEST_AUTH("me", "p4$$w0rd"), &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

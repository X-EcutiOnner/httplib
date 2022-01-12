#include "http.h"
#include "debug.h"

int main(void)
{
    struct http_response *resp = http_request("GET", "https://nghttp2.org/httpbin/redirect/10", NULL);
    debug_response_print(resp);
    http_response_free(resp);
}

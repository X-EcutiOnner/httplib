#include "http.h"
#include "debug.h"


int main(void) {
    struct http_response *resp = http_request("GET", "http://google.com/", NULL);
    response_print(resp);
    http_response_free(resp);
}

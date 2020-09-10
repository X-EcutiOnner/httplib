#include <stdio.h>
#include <stdlib.h>
#include "http.h"

int main(void) {
    struct http_opts opts = {
        .cookies = "key1=value1;key2=value2",
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/cookies", &opts);
    printf("CONTENT (%lu):\n%s\n\n", HTTP_RESPONSE_CONTENT_LENGTH(resp), HTTP_RESPONSE_CONTENT(resp));
    printf("HEADERS (%lu):\n%s\n\n", HTTP_RESPONSE_HEADERS_LENGTH(resp),HTTP_RESPONSE_HEADERS(resp));
    printf("Code: %d\n", resp->curl_code);
    printf("Error: %s\n", resp->curl_error);
    http_response_free(resp);
}

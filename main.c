#include <stdio.h>
#include <stdlib.h>
#include "http.h"

int main(void) {
    struct http_opts opts = {
        .cookies = "key1=value1;key2=value2",
        .timeout_secs = 1,
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/cookies", &opts);
    printf("CONTENT (%lu):\n%s\n\n", http_response_content_length(resp), http_response_content(resp));
    printf("HEADERS (%lu):\n%s\n\n", http_response_headers_length(resp), http_response_headers(resp));
    printf("URL: %s\n", http_response_url(resp));
    printf("Status Code: %d\n", http_response_status_code(resp));
    printf("Code: %d\n", resp->curl_code);
    printf("Error: %s\n", http_response_curl_error(resp));
    http_response_free(resp);
}

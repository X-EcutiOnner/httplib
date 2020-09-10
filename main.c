#include <stdio.h>
#include <stdlib.h>
#include "http.h"

#define HTTPBIN_URL_COOKIES                         "https://httpbin.org/cookies"
#define HTTPBIN_URL_BASIC_AUTH(user, password)      "https://httpbin.org/basic-auth/" user "/" password
#define HTTPBIN_URL_BEARER                          "https://httpbin.org/bearer"


void response_print(struct http_response *resp) {
    if(!resp) {
        printf("Error Code: %d\n", http_curl_error_code);
        printf("Error Text: %s\n", http_curl_error_text());
        return;
    }

    printf("CONTENT (%lu):\n%s\n\n", http_response_content_length(resp), http_response_content(resp));
    printf("HEADERS (%lu):\n%s\n\n", http_response_headers_length(resp), http_response_headers(resp));
    printf("URL: %s\n", http_response_url(resp));
    printf("Status Code: %d\n", http_response_status_code(resp));
    printf("Elapsed Seconds: %f\n", http_response_elapsed(resp));
}

void basic_usage(void) {
    struct http_response *resp = http_request("GET", "http://google.com/", NULL);
    response_print(resp);
    http_response_free(resp);
}

void cookies(void) {
    struct http_opts opts = {
        .cookies = "key1=value1;key2=value2",
        .timeout_secs = 1,
    };
    struct http_response *resp = http_request("GET", HTTPBIN_URL_COOKIES, &opts);
    response_print(resp);
    http_response_free(resp);
}

void auth_basic(void) {
    struct http_auth_basic auth = HTTP_AUTH_BASIC_INIT("me", "p4$$w0rd");
    struct http_opts opts = {
        .timeout_secs = 1,
        .auth = HTTP_AUTH_CAST(&auth),
    };
    struct http_response *resp = http_request("GET", HTTPBIN_URL_BASIC_AUTH("me", "p4$$w0rd"), &opts);
    response_print(resp);
    http_response_free(resp);
}

void auth_bearer(void) {
    struct http_auth_bearer auth = HTTP_AUTH_BEARER_INIT("token-abc123");
    struct http_opts opts = {
        .timeout_secs = 1,
        .auth = HTTP_AUTH_CAST(&auth),
    };
    struct http_response *resp = http_request("GET", HTTPBIN_URL_BEARER, &opts);
    response_print(resp);
    http_response_free(resp);
}

int main(void) {
    basic_usage();
    /* cookies(); */
    /* auth_basic(); */
    /* auth_bearer(); */
}

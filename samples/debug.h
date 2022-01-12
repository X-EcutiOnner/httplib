#include <stdio.h>
#include "http.h"

static void debug_response_print(struct http_response *resp)
{
    if (!resp) {
        printf("Error Code: %d\n", http_curl_error_code);
        printf("Error Text: %s\n", http_curl_error_text());
        return;
    }

    printf("CONTENT (%lu):\n%s\n\n", http_response_content_length(resp), http_response_content(resp));
    printf("HEADERS (%lu):\n%s\n\n", http_response_headers_length(resp), http_response_headers(resp));
    printf("URL: %s\n", http_response_url(resp));
    printf("Status Code: %d\n", http_response_status_code(resp));
    printf("Elapsed Seconds: %f\n", http_response_elapsed(resp));
    printf("Redirect Count: %d\n", http_response_redirect_count(resp));

    if (resp->next) {
        printf("***REDIRECT! (URL: %s)\n", http_response_redirect_url(resp));
        debug_response_print(resp->next);
    }
}

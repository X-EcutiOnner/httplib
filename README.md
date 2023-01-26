# httplib

Simple usage:

```
#include "http.h"

int main(void)
{
    /*
     * Call the http_request() function to make an HTTP request.
     * For the first argument, provide the HTTP method (e.g. GET, POST).
     * For the second argument, provide the URL.
     * For the third argument, provide any options needed to complete the request.
     * (When no options are needed, the third argument may be NULL.)
     *
     * This function returns a newly allocated pointer to a `struct http_response`
     * which may be used to access attributes of the server response.
     *
     * Always dispose of the response pointer with http_response_free().
     */

    struct http_response *resp = http_request("GET", "http://google.com/", NULL);

    printf("HEADERS:\n%s\n\n", http_response_headers(resp));
    printf("CONTENT:\n%s\n\n", http_response_content(resp));

    http_response_free(resp);
}
```

Things you can do with `struct http_response *`:

* `size_t http_response_headers_length(struct http_response *)`: Get the size of the response headers.

* `const char *http_response_headers(struct http_response *)`: Get the headers.

* `size_t http_response_content_length(struct http_response *)`: Get the content length.

* `const char *http_response_content(struct http_response *)`: Get the response body content.

* `int http_response_redirect_count(struct http_response *)`: Get the number of redirects.

* `const char *http_response_url(struct http_response *)`: Get the final URL.

* `int http_response_status_code(struct http_response *)`: Get the status code.

* `const char *http_response_redirect_url(struct http_response *)`: Get the redirect URL.

* `double http_response_elapsed(struct http_response *)`: Get the elapsed time from request to response.

Adding authorization:

```
#include "http.h"

int main(void)
{
    struct http_opts opts = {
        .auth = HTTP_AUTH_BEARER("token-abc123"),
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/bearer", &opts);
    ...
    http_response_free(resp);
}
```

POSTing simple form data:

```
#include "http.h"

int main(void)
{
    struct http_opts opts = {
        .data = "key1=value1&key2=value2",
    };
    struct http_response *resp = http_request("POST", "https://httpbin.org/anything", &opts);
    ...
    http_response_free(resp);
}
```

Sending JSON:

```
#include "http.h"

int main(void)
{
    struct http_opts opts = {
        .json = "{\"key1\": \"value1\", \"key2\": \"value2\"}",
    };
    struct http_response *resp = http_request("PUT", "https://httpbin.org/anything", &opts);
    ...
    http_response_free(resp);
}
```

Adding cookies:

```
#include "http.h"

int main(void)
{
    struct http_opts opts = {
        .cookies = "key1=value1;key2=value2",
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/cookies", &opts);
    ...
    http_response_free(resp);
}
```

Setting a timeout:

```
#include "http.h"

int main(void)
{
    struct http_opts opts = {
        .timeout_secs = 1
    };
    struct http_response *resp = http_request("GET", "https://httpbin.org/delay/2", &opts);
    ...
    http_response_free(resp);
}
```


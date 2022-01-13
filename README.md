# httplib

Simple usage:

```
#include "http.h"

int main(void)
{
    struct http_response *resp = http_request("GET", "http://google.com/", NULL);

    ... do something with response ...

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


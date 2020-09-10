#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>

struct http_cert {
    char *cert;
    char *key;
    char *password;
};

struct http_opts {
    char *cookies;
    char *proxy;
    struct http_cert *cert;
    int timeout_secs;
};

struct http_write_buffer {
    size_t size;
    char *data;
};

struct http_response {
    CURLcode curl_code;
    const char *curl_error;
    struct http_write_buffer headers;
    struct http_write_buffer content;
};

#define HTTP_RESPONSE_HEADERS_LENGTH(this)  ((this)->headers.size)
#define HTTP_RESPONSE_HEADERS(this)         ((this)->headers.data)
#define HTTP_RESPONSE_CONTENT_LENGTH(this)  ((this)->content.size)
#define HTTP_RESPONSE_CONTENT(this)         ((this)->content.data)

struct http_response *http_request(const char *method, const char *url, struct http_opts *opts);
void http_response_free(struct http_response *this);

#endif

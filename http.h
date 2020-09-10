#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>

extern CURLcode http_curl_error_code;

static inline const char *http_curl_error_text(void) {
    return curl_easy_strerror(http_curl_error_code);
}

enum http_authtype {
    HTTP_AUTHTYPE_BASIC,
};

struct http_auth {
    enum http_authtype type;
};

struct http_auth_basic {
    struct http_auth base;
    const char *username;
    const char *password;
};

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
    struct http_auth *auth;
};

struct http_write_buffer {
    size_t size;
    char *data;
};

struct http_response {
    CURL *curl;
    struct http_write_buffer headers;
    struct http_write_buffer content;
};

struct http_response *http_request(const char *method, const char *url, struct http_opts *opts);
void http_response_free(struct http_response *this);

static inline size_t http_response_headers_length(struct http_response *this) {
    return this->headers.size;
}

static inline const char *http_response_headers(struct http_response *this) {
    return this->headers.data;
}

static inline size_t http_response_content_length(struct http_response *this) {
    return this->content.size;
}

static inline const char *http_response_content(struct http_response *this) {
    return this->content.data;
}

static inline const char *http_response_url(struct http_response *this) {
    char *result = NULL;
    curl_easy_getinfo(this->curl, CURLINFO_EFFECTIVE_URL, &result);
    return result;
}

static inline int http_response_status_code(struct http_response *this) {
    int result = 0;
    curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &result);
    return result;
}

static inline double http_response_elapsed(struct http_response *this) {
    double result = 0;
    curl_easy_getinfo(this->curl, CURLINFO_TOTAL_TIME, &result);
    return result;
}

#endif

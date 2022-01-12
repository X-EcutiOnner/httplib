#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

CURLcode http_curl_error_code = CURLE_OK;

#define WRITE_BUFFER_INIT   ((struct http_write_buffer){.size=0, .data=NULL})

static size_t write_callback(void *contents, size_t size, size_t count, void *_buffer)
{
    struct http_write_buffer *buffer = (struct http_write_buffer *)_buffer;
    size_t new_size = size * count;
    char *new_memory = realloc(buffer->data, buffer->size + new_size + 1);
    if (new_memory == NULL)
        return 0;
    buffer->data = new_memory;
    memcpy(&buffer->data[buffer->size], contents, new_size);
    buffer->size += new_size;
    buffer->data[buffer->size] = '\0';
    return new_size;
}

static struct http_response *_http_curl_perform(CURL *curl, int redirect_count)
{
    struct http_response *result = malloc(sizeof *result);

    result->curl = curl;
    result->headers = WRITE_BUFFER_INIT;
    result->content = WRITE_BUFFER_INIT;
    result->next = NULL;
    result->redirect_count = redirect_count;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &result->headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result->content);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);

    CURLcode curl_code = curl_easy_perform(curl);
    if (curl_code != CURLE_OK)
        goto fail;

    result->next = http_request_follow_redirect(result);

    return result;

fail:
    http_curl_error_code = curl_code;
    http_response_free(result);
    return NULL;
}

struct http_response *http_request_follow_redirect(struct http_response *resp)
{
    if (!resp)
        return NULL;
    if (resp->redirect_count >= HTTP_MAX_REDIRECTS)
        return NULL;
    const char *url = http_response_redirect_url(resp);
    if (!url)
        return NULL;

    CURL *newcurl = curl_easy_duphandle(resp->curl);
    curl_easy_setopt(newcurl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(newcurl, CURLOPT_URL, url);

    return _http_curl_perform(newcurl, resp->redirect_count + 1);
}

static void _http_curl_setopts(CURL *curl, struct http_opts *opts)
{
    if (!opts)
        return;

    curl_easy_setopt(curl, CURLOPT_PROXY, opts->proxy);
    curl_easy_setopt(curl, CURLOPT_COOKIE, opts->cookies);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, opts->timeout_secs);

    if (opts->auth) {
        switch(opts->auth->type) {
        case HTTP_AUTHTYPE_BASIC:
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_USERNAME, ((struct http_auth_basic *)opts->auth)->username);
            curl_easy_setopt(curl, CURLOPT_PASSWORD, ((struct http_auth_basic *)opts->auth)->password);
            break;
        case HTTP_AUTHTYPE_BEARER:
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
            curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, ((struct http_auth_bearer *)opts->auth)->token);
            break;
        case HTTP_AUTHTYPE_X509:
            curl_easy_setopt(curl, CURLOPT_SSLCERT, ((struct http_auth_x509 *)opts->auth)->cert);
            curl_easy_setopt(curl, CURLOPT_SSLKEY, ((struct http_auth_x509 *)opts->auth)->key);
            curl_easy_setopt(curl, CURLOPT_KEYPASSWD, ((struct http_auth_x509 *)opts->auth)->password);
            break;
        }
    }
}

struct http_response *http_request(const char *method, const char *url, struct http_opts *opts)
{
    if (!method)
        return NULL;
    if (!url)
        return NULL;

    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
    curl_easy_setopt(curl, CURLOPT_URL, url);

    _http_curl_setopts(curl, opts);

    return _http_curl_perform(curl, 0);
}

void http_response_free(struct http_response *this)
{
    curl_easy_cleanup(this->curl);
    if (this->headers.data)
        free(this->headers.data);
    if (this->content.data)
        free(this->content.data);
    if (this->next)
        http_response_free(this->next);
    free(this);
}

#HTTP Requests
Currently, the only http requests that are supported are GET requests and HTTPS is __NOT__ supported

```
void get()
{
    std::string data = libpsutil::network::http_get("http://google.com", "", 80);
}

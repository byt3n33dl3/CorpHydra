#ifndef _HYDRA_SERVICE_HTTP_PROXY_URLENUM_H_
#define _HYDRA_SERVICE_HTTP_PROXY_URLENUM_H_

void service_http_proxy_urlenum(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char *hostname);
int service_http_proxy_urlenum_init(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char *hostname);
void usage_http_proxy_urlenum(const char* service);

#endif /* _HYDRA_SERVICE_HTTP_PROXY_URLENUM_H_ */

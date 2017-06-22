#ifndef _HYDRA_SERVICE_CVS_H_
#define _HYDRA_SERVICE_CVS_H_

void service_cvs(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char *hostname);
int service_cvs_init(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char *hostname);
void usage_cvs(const char* service);

#endif /* _HYDRA_SERVICE_CVS_H_ */

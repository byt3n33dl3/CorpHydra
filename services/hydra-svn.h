#ifndef _HYDRA_SERVICE_SVN_H_
#define _HYDRA_SERVICE_SVN_H_

void service_svn(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char *hostname);
int service_svn_init(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char *hostname);
void usage_svn(const char* service);

#endif /* _HYDRA_SERVICE_SVN_H_ */

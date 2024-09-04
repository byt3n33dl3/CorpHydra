#ifdef PALM
#include "palm/hydra-mod.h"
#else
#include "hydra-mod.h"
#endif

extern char *HYDRA_EXIT;

unsigned char adam6500_req1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x01, 0x10, 0x27, 0x0f, 0x00, 0x08, 0x10, 0x24, 0x30, 0x31, 0x50, 0x57, 0x30, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0d, 0x00};
unsigned char adam6500_resp1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0x10, 0x27, 0x0f, 0x00, 0x08};
unsigned char adam6500_req2[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x27, 0x0f, 0x00, 0x7d};
unsigned char adam6500_resp2[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x01, 0x03, 0xfa, 0x3f, 0x30, 0x31, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

int32_t start_adam6500(int32_t s, char *ip, int32_t port, unsigned char options, char *miscptr, FILE *fp) {
  char *empty = "";
  char *pass;
  unsigned char buffer[300];
  int32_t i;

  if (strlen(pass = hydra_get_next_password()) == 0)
    pass = empty;

  memcpy(buffer, adam6500_req1, sizeof(adam6500_req1));

  for (i = 0; i < 8 && i < strlen(pass); i++)
    buffer[19 + i] = pass[i] ^ 0x3f;

  if (hydra_send(s, buffer, sizeof(adam6500_req1), 0) < 0)
    return 1;

  if (recv(s, buffer, sizeof(buffer), 0) == 12 && memcmp(buffer, adam6500_resp1, sizeof(adam6500_resp1)) == 0) {
    if (hydra_send(s, adam6500_req2, sizeof(adam6500_req2), 0) < 0)
      return 1;
    if (recv(s, buffer, sizeof(buffer), 0) == 259 && memcmp(buffer, adam6500_resp2, sizeof(adam6500_resp2)) == 0) {
      hydra_completed_pair();
      if (memcmp(hydra_get_next_pair(), &HYDRA_EXIT, sizeof(HYDRA_EXIT)) == 0)
        return 3;
      return 1;
    }
  }

  hydra_report_found_host(port, ip, "adam6500", fp);
  hydra_completed_pair_found();

  return 1;
}

void service_adam6500(char *ip, int32_t sp, unsigned char options, char *miscptr, FILE *fp, int32_t port, char *hostname) {
  int32_t run = 1, next_run = 1, sock = -1;
  int32_t myport = PORT_ADAM6500, mysslport = PORT_ADAM6500_SSL;

  hydra_register_socket(sp);
  if (memcmp(hydra_get_next_pair(), &HYDRA_EXIT, sizeof(HYDRA_EXIT)) == 0)
    return;
  while (1) {
    next_run = 0;
    switch (run) {
    case 1: /* connect and service init function */
    {
      if (sock >= 0)
        sock = hydra_disconnect(sock);
      //        usleepn(275);
      if ((options & OPTION_SSL) == 0) {
        if (port != 0)
          myport = port;
        sock = hydra_connect_tcp(ip, myport);
        port = myport;
      } else {
        if (port != 0)
          mysslport = port;
        sock = hydra_connect_ssl(ip, mysslport, hostname);
        port = mysslport;
      }
      if (sock < 0) {
        hydra_report(stderr, "[ERROR] Child with pid %d terminating, can not connect\n", (int32_t)getpid());
        hydra_child_exit(1);
      }

      next_run = 2;
      break;
    }
    case 2: /* run the cracking function */
      next_run = start_adam6500(sock, ip, port, options, miscptr, fp);
      break;
    case 3: /* clean exit */
      if (sock >= 0)
        sock = hydra_disconnect(sock);
      hydra_child_exit(0);
      return;
    default:
      hydra_report(stderr, "[ERROR] Caught unknown return code, exiting!\n");
      hydra_child_exit(0);
#ifdef PALM
      return;
#else
      hydra_child_exit(2);
#endif
    }
    run = next_run;
  }
}

int32_t service_adam6500_init(char *ip, int32_t sp, unsigned char options, char *miscptr, FILE *fp, int32_t port, char *hostname) {
  // called before the childrens are forked off, so this is the function
  // which should be filled if initial connections and service setup has to be
  // performed once only.
  //
  // fill if needed.
  //
  // return codes:
  //   0 all OK
  //   -1  error, hydra will exit, so print a good error message here

  return 0;
}
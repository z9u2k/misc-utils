#include <stdio.h>
#include <unistd.h>

int redirect_fd(const char *cmd, int newd) {
  FILE *stream;
  int fd;
  int res;

  stream = popen(cmd, "w");
  if (NULL == stream) {
    fprintf(stderr, "cannot start %s\n", cmd);
    return -1;
  }

  fd = fileno(stream);
  if (0 >= fd) {
    fprintf(stderr, "cannot get fd of %s\n", cmd);
    return -1;
  }

  res = dup2(fd, newd);
  if (-1 == res) {
    fprintf(stderr, "cannot replace fd %d\n", newd);
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int err;

  if (argc < 4) {
    fprintf(stderr,
        "usage: %s <stdout_cmd> <stderr_cmd> <cmd> <cmd args...>\n"
        "example: %s \"logger -p daemon.info\" \"logger -p daemon.err\" "
        "./some_server --param --param2 param2_value\n",
        argv[0], argv[0]);
    return -1;
  }

  err = redirect_fd(argv[1], 1);
  if (err) {
    return err;
  }

  err = redirect_fd(argv[2], 2);
  if (err) {
    return err;
  }

  execvp(argv[3], &argv[3]);

  /* exec should not return - if it did, an error occured */
  return -1;
}

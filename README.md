# Misc Utils
A repo for random utilities.

# Building
```bash
$ make all
```

# What's in here?
## STDIO redirection to pipes
It is sometimes usedful to be able to redirect `stdin` and `stdout` to processes instead of files, without forking a process.

While this can be achieved with Bash [process substitution](http://tldp.org/LDP/abs/html/process-sub.html):
```bash
#!/bin/bash
STDOUT_PIPE_CMD="logger -p daemon.info"
STDERR_PIPE_CMD="logger -p daemon.err"
PROC_EXE="some_service"
PROC_PARAMS="-p --param2 param2_value"

exec $PROC_EXE $PROC_PARAMS 1> >($STDOUT_PIPE_CMD) 2> >($STDERR_PIPE_CMD)
```
This is a non-standard extension and isn't always available (e.g. on FreeBSD).

`stdio-redir` is a small, portable program which uses `popen`, `dup2` and `execvp` to achieve the same effect.

Basic usage:
```bash
$ stdio-redir <stdout-command> <stderr-command> <cmd> <cmd args...>
```

Example usage correlating to the above Bash code:
```bash
$ stdio-redir "logger -p daemon.info" "logger -p daemon.err" some_service -p --param2 param2_value
```

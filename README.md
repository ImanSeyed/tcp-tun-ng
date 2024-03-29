## Description

This repository is an implementation of TCP stack with C++ language. In order not to get bothered by the Linux kernel TCP implementation, it's over a `tun` interface.

## How To Run It

You just need to run `secure_run.sh` with bash:

```shell
$ bash secure_run.sh
```

- Don't stress about the 'sudo' stuff. It helps control certain things with the 'tcp-tun' file. But you can also do this process yourself.
- If you want to set the IP Address manually (192.168.20.1), check out [this part of the 'main.cpp' file](https://github.com/ImanSeyed/tcp-tun/blob/main/Source/main.cpp#L19).
- You can use `nc` to make a connection with the program.
```shell
$ nc 192.168.20.10 123
```

## Warning

Don't mess with routing stuff if you don't know what you're doing, otherwise, your connection to the Internet may get lost. This program is under development and it's not a complete TCP implementation, therefore just test it on a `tun` device without changing your routing table.

## Specs

- [RFC 791](https://datatracker.ietf.org/doc/html/rfc791) (IPv4)
- [RFC 793](https://datatracker.ietf.org/doc/html/rfc793) (TCP)
- [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071) (Checksum calculation)
- [RFC 7414](https://datatracker.ietf.org/doc/html/rfc7414#section-2) (A roadmap for TCP implementation)

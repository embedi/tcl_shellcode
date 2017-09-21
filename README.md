# tcl_shellcode
A template project for creating a shellcode for the Cisco IOS in the C language

It implements the concept of `TclShellcode`. Namely, this shellcode look for a Tcl subsystem within the `Cisco IOS` image and reuses the [Tcl API](https://www.tcl.tk/man/tcl/TclLib/contents.htm).

This project also includes a version of `libc` as well as the structures for working with `Cisco IOS` scheduler.

Although this shellcode is designed for `Cisco IOS`, you can use it to create a `PIC` code for other devices on the `PowerPC` architecture.

To compile the shellcode simply enter the command:

```bash
> make
```

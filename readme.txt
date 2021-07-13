This is a very simple password generator script, written for the TinyC Compiler, which can generate a list of one or more random passwords of a default or given length.

For example, the following would be an example of it's invokation and results.
If this example is confusing, see the raw file.

$ genpass 5 3
yAwAb
d3yHj
sT6Tv

These are all onto stdout so you can pipe them wherever you want.
You can also invoke without arguments to generate a single password of 8 characters.
Defaults are changed within the script itself, as it is JiT compiled C.

If you want to make the code pre-compiled, for whatever reason, just comment out the interpreter invocation at the top of the file.

Like so:
//#!/bin/tcc -run

The make system is very simple if you are fine with a script: just "sudo make install" to install and "sudo make uninstall" to uninstall.

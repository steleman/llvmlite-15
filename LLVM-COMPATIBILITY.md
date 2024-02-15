LLVM Compatibility
==================

This is a port of numba/llvmlite to LLVM 15.x.x. Tested and verified on Linux
x86_64 (Fedora 37, which comes with LLVM 15.0.7 out of the box). There are two
tests for RISCV that fail. LLVM 15 emits significantly different opcodes on
RISCV, and two RISCV test assertions fail.

I don't have access to a RISCV box to test this on, so I am unable to debug,
test and correct the RISCV failures at this time.

There are two incompatible API changes in this port of `llvmlite`, related to
LLVM's Opaque Pointers. Removing the pointee type information from LLVM's
`llvm::PointerType` was not a good decision IMO. Just because the LLVM IR
doesn't care about, or use, the Pointee type information, and treats all
pointers opaquely, does not mean that other consumers of the LLVM API don't
need or use this information.

I am actually seriously considering re-inserting the Pointee type information
back into the `llvm::PointerType` type. The justification for this reversal is
that the removal of this information is causing too many headaches, and requires
too many and unnecessary code acrobatics for the consumers of LLVM's API.

The drawback of doing that is that I'd be forking LLVM, and I am quite skeptical
that this reversal change will be accepted upstream.

`llvmlite` does not compile out-of-the-box with either LLVM 16.x.x or LLVM
17.x.x.  The higher the LLVM Version, the worse it gets.

There's been significant API compatibility changes between LLVM 15 and LLVM 16.

For the transition from LLVM 15 to LLVM 17, the incompatible changes are major.
The most notable one being that LLVM 17 uses the New Pass Manager.

What I Am Doing About All Of This
=================================

I am currently working on ports of `llvmlite` to LLVM 16 and LLVM 17.  Why?
Just 'cuz. For fun.

This is the main reason why I changed the name of this repo from simply
`llvmlite` to `llvmlite-15`. The repo name now reflects the LLVM version
compatibility.

Current Status of `llvmlite` on LLVM 16 and LLVM 17
===================================================

`llvmlite` with LLVM 16 now compiles, but fails several tests. Also due to
incompatible changes in the LLVM API.

`llvmlite` with LLVM 17 is a complete FAIL at this point. I have gotten it
to the point where it compiles. But the reality is that it needs a thorough
re-design and rewrite in `passmanager.{h|cpp}`.

What's Next
===========

I will create separate repos for `llvmlite-16` and `llvmlite-17` as soon as
I get them in a working state. That's a convoluted way of saying `stay tuned`.



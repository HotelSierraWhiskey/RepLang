# The Replang Compiler

## What is this?

The Replang Compiler is the first and only implementation of the humble Rep programming language. All of its components are written in C

***

## How does it work?

To compile the compiler source code use the makefile provided. The command 

```make compile``` 

Will generate the ```rep``` executable which can be run against a .rep file. Assuming you've written a file ```test.rep```, you can compile this file with the command 

```./rep test.rep```

This will produce an ```out.py``` file. Yes, that's right, Replang compiles to python. Python 3 to be exact. And of course you can run your program with the command 

```python3 out.py```

And wallah. You've just compiled and executed your first rep program.

***

## Who uses Replang?

Nobody. Just me.

## Documentation

Documentation coming soon.

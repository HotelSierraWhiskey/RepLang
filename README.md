# The Replang Compiler

## What is this?

The Replang Compiler is the first and only implementation of the humble Rep programming language.

***

## How does it work?

To compile the replang source code use the makefile provided. The command 

```make compile``` 

Will generate the ```rep``` executable which can be run against a .rep file. Assuming you've written a file ```test.rep```, you can compile this file with the command 

```./rep test.rep```

This will produce an ```out.py``` file. Yes, that's right, Replang compiles to python. Hence, you can run your program with the command 

```python3 out.py```

And wallah. You've just compiled and executed your first rep program.

***

## Who uses Replang?

Nobody. Just me.

## Documentation

<u>**Basic Types**</u>

Replang supports the following basic data types:

- Integers
- Floating point numbers
- Strings

<u>**The ```show``` Builtin Function:**</u>

The builtin function ```show``` takes one expression type parameter and displays the resulting evaluation to the console.

Examples:

```javascript
show("Hello, world!");
```

```javascript
show(3.14159 * (r * r));
```


<u>**Identifiers:**</u>

Identifiers in Rep require a ```let``` binding and may not begin with a number. Underscores are permitted in identifier names, but other special characters are not.

Examples:

```javascript
let update_time = 86400;
``` 

```javascript
let _filename = "secret.txt";
```
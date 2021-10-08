# The Replang Compiler

## What is this?

The Replang Compiler is the first and only implementation of the humble Rep programming language.

***

## How does it work?

To compile the replang source code use the makefile provided. The command 

```make compile``` 

will generate the ```rep``` executable which can be run against a .rep file. Assuming you've written a file ```test.rep```, you can compile this file with the command 

```./rep test.rep```

This will produce an ```out.py``` file. Yes, that's right, Replang compiles to python. Hence, you can run your program with the command 

```python3 out.py```

And wallah. You've just compiled and executed your first rep program.
<br>
<br>
<u>Note:</u> To compile your .rep file with the lexer and/ or parser subsystem in debug mode add the ```-ldebug``` and/ or ```-pdebug``` flag. For example:

 ```./rep test.rep -ldebug -pdebug```
<br>
<br>

***
## Who uses Replang?

Nobody. Just me.

<br>

***
## Documentation
<br>

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

<u>**The ```loop``` and ```endloop``` Keywords:**</u>

In lieu of the common for-loop Rep makes use of the builtin ```loop``` function. ```loop``` takes two parameters: an integer literal representing the number of iterations desired, and an identfier whose value is the current loop iteration. All instructions placed after a call to ```loop``` (including other calls to ```loop```) will be repeated until ```endloop``` is called. 

Examples:

```javascript
loop(10 count);
show(count);
endloop;
```

```javascript
loop(10 i);
loop(10 j);
show(i + j)
endloop;
endloop;
show("done");
```
# Lip Interpreter

Lip is a small functional programming language and interpreter implemented in C++, designed to explore core concepts of functional languages such as first-class functions, lazy evaluation, recursion, higher-order functions, and expression-based control flow.

The interpreter supports both interactive (REPL) execution and file-based execution, and the language is powerful enough to express non-trivial programs such as recursive algorithms, function composition, higher-order list processing, and user-defined control structures.

## Language Overview

Lip is an expression-oriented, functional language with the following core characteristics:
* Everything is evaluated as an expression
* Functions are first-class values
* Functions can be passed as arguments and returned as results
* Control flow (`if`, logical operators) is implemented as ordinary functions
* Evaluation is lazy where needed, allowing short-circuiting and recursion
* Variables are immutable by default via shadowing (no mutation by reference)

## Data Types

### Numbers

`5.5`, `-3.14`, `3`

Used for arithmetic, comparisons, and boolean-like conditions<br>
`0` is treated as `false`, non-zero as `true`

### Strings

Strings can be written using single or double quotes: `'abc'`, `"hello world"`

Both quote styles are equivalent<br>
Strings may contain spaces and escaped characters (`'\n'`, `'\t'`, ...)

### Lists

Lists may contain expressions, not just values

Literal lists:<br>
`[1, 2, 3]`, `[]`, `[12, add(1, 2), ['hello', 6.7]]`

Supports infinite lazy lists via generators

Lists are evaluate to `false` if empty, `true` otherwise

### Function Objects

In Lip, functions are first-class values<br>
This means functions can be:<br>
* stored in variables
* passed as arguments to other functions
* returned as results
* called dynamically via expressions

A function object represents a callable value together with its defining environment

A function name evaluates to a function object, not a call
```
def inc(1) = add($1, 1)

let f = inc
f(10) -> 11
```

## Expressions and Evaluation

The language distinguishes between:
* Expressions - syntax trees that can be evaluated
* Values - results of evaluation (numbers, strings, lists, functions)

Evaluation follows a call-by-expression model:
* Function arguments are passed as expressions
* A function decides which arguments to evaluate
* This enables lazy semantics for control constructs like `if`, `and`, `or`

## Built-in Functions

### Arithmetic

`add` equivalent to `a + b`<br>
`sub` equivalent to `a - b`<br>
`mul` equivalent to `a * b`<br>
`div` equivalent to `a / b`<br>
`mod` equivalent to `a % b`<br>
`sqrt` equivalent to `√a`

### Comparison

`eq` equivalent to `a == b`<br>
`ne` equivalent to `a != b`<br>
`lt` equivalent to `a < b`<br>
`le` equivalent to `a <= b`<br>
`gt` equivalent to `a > b`<br>
`ge` equivalent to `a >= b`

### Logic

`not` equivalent to `!(a)`<br>
`and` equivalent to `a && b`<br>
`or` equivalent to `a || b`

### Control Flow

`if(condition, thenExpr, elseExpr)`

Only the selected branch is evaluated

### Conversion

`int` casts a real number to an integer<br>
`bool` casts an expression to its boolean interpretation

### String

`length` returns the element count<br>
`concat` joins two lists together<br>
`reverse` reverses the characters of the string

### List

`length` returns the element count<br>
`head` returns the first element<br>
`tail` returns the list without the first element<br>
`concat` joins two lists together<br>
`list` generates (lazy) lists based on initial element and step, infinite if no element count is provided<br>
`reverse` reverses the elements of the list

### Function Object

`compose`<br>
`and_then`

These functions are explained in another section below

### I/O

`input()` reads an expression from `stdin`<br>
`print(<exprs>)` prints the expressions to `stdout` and returns `1`<br>
`read(<filename>)` reads the lines of a file<br>
`write(<filename>, <expr>, <should_overwrite>)` writes an expression to a file, overrides or appends

## Function Definitions

### Definition

Functions are defined using the `def` keyword:<br>
`def <func_name>(<arg_count>) = <func_body>`

Function arguments are referenced as `$1`, `$2`, `$3`, ...

Examples:
```
def ref(1) = $1
def add3(3) = add(add($1, $2), $3)
def pi(0) = 3.1415

let a = 5.5
def add_with_a(2) = add(add($1, $2), a)
```

### Redefinition

Redefinition is allowed and does not affect already-constructed closures<br>
It is done using the `redef` keywork: 
`redef <func_name>(<arg_count>) = <func_body>`

Examples:
```
def one(0) = 1
def f(1) = add($1, one())
f(42) -> 43
redef one(0) = 5
f(42) -> 43
```

### Undefinition

Functions can be undefined using the `undef` keyword: 
`undef <func_name>(<arg_count>)`

## Recursion

Recursive functions are fully supported:
```
def fac(1) = if(lt($1, 1), 1, mul(int($1), fac(sub($1, 1))))
fac(5) -> 120
```

This works because:<br>
if evaluates only one branch and expressions and function calls are evaluated lazily

## First-Class Functions

Functions are values and can be:
* stored in variables
* passed as arguments
* returned from other functions
* called dynamically

Example:
```
def call(2) = $1($2)
call(fac, 4) -> 24
```

## Functions Returning Functions

Functions may return other functions
```
def ref(1) = $1

ref(add)(3, 4) -> 7
ref(ref(add))(3, 4) -> 7
```

## Function Composition

The language includes function combinators:

`compose(f, g)(x)` does f(g(x))<br>
`and_then(f, g)(x)` does g(f(x))

Example:
```
def inc(1) = add($1, 1)
def sqr(1) = mul($1, $1)

compose(inc, sqr)(3) -> 10
and_then(inc, sqr)(3) -> 16
```

## Higher-Order Functions

Functions may accept other functions as arguments and apply them dynamically

Example: higher-order recursion

for_each applies a function to every element of a list, supporting lazy and infinite lists
```
def for_each(2) = if($1, and($2(head($1)), for_each(tail($1), $2)), 1)
```
do_inc applies a function to every number from `1` to `$1` in increasing order (from `1` to `$1`)
```
def do_inc(2) = if(lt($1, 1), 1, and(do_inc(sub($1, 1), $2), $2($1)))
```

## Currying and partial aplication

Arguments may be bound to functions

Example:
```
curry(add, 42)(1000) -> 1042
```

## Variables and Bindings

### Variable creation

`let a = 10`

Once a variable is created, it cannot be reassigned

### Shadowing (no mutation)

`let a = 5`

Creates a new binding that shadows the old one

### Constants

`const PI = 3.1415`

Variable that cannot be shadowed or removed

### Variable removal

`rm a`

Removes the binding of a variable

## Environments and Scoping

The language uses lexical (static) scoping<br>
Environments are immutable and chained<br>
Function closures capture the environment they were defined in

## Comments

Single-line comments are supported:
```
// this is a comment
```

## Execution Modes

REPL mode — evaluate expressions interactively<br>
File mode — execute a file and print results

## Implementation Notes

Written in modern C++<br>
AST-based interpreter

Separate hierarchies for:
* Expressions
* Values
* Functions

Supports lazy lists with caching

Recursion implemented via environment chaining<br>

## Goals of the Project

This project was created to:
* understand functional language semantics
* experiment with lazy evaluation
* explore first-class functions and closures
* design a minimal but expressive interpreter

It is not intended to be fast or production-ready, but to be correct, expressive, and educational

## Future Extensions

Possible future improvements:
* Pipeline syntax sugar
* Tail-call optimization

## License
This project is provided for educational purposes.

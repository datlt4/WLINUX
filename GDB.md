# GNU Debugger (d)

## Make executable binary file

- Build in `Release` mode

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
```

- Build in `Debug` mode

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## Running the program under GDB

```bash
gdb ./my-app
```

## Starting the debugging process

```bash
(gdb) start
```

- Debugger will automatically set the breakpoint in the main block of code, stopping the program if it reaches that point, if we start with the `start` command.

```bash
(gdb) run
```

- If we have not yet set the breakpoint, the program will run as usual if we call the `run` command

## The continuing and stepping debugging process

```bash
(gdb) continue
(gdb) c
(gdb) next
(gdb) n
(gdb) step
(gdb) s
```

## Printing the source code

```bash
(gdb) show listsize
(gdb) set listsize 20
(gdb) show listsize
(gdb) l
(gdb) list
(gdb) list <linenumber>
(gdb) list <functionname>
(gdb) list <first, last>
(gdb) list <, last>
(gdb) list <first,>
(gdb) list +
(gdb) list -
```

## Setting and deleting the breakpoint

- Set breakpoint

```bash
(gdb) break <#linenumber>
```

- List checkpoints

```bash 
(gdb) info break
```

- Delete breakpoint

```bash
(gdb) delete <#orderbreakpoint>
```

## Printing a variable value

```bash
(gdb) print <variablename>
```

## Modifying a variable value

- Reassign variable value

```bash
(gdb) set var <variablename>=<newvalue>
```

- Get type of variable

```bash
(gdb) whatis <variablename>
```




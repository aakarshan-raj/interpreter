# interpreter

To run tests: 
Build: `cmake --build build -j8`

Test: `ctest --test-dir build --output-on-failure`

Trace Segmentation faults: `valgrind --leak-check=full --track-origins=yes ./monkey`

Use flag `--debug` for debug mode

Adding support for a new Type:

1. Add its class in AST
2. inherit from main parent classes
3. implement virtual functions
4. implement class specific functions
5. write basic tests
6. create parser function
7. register the function
8. write parsing tests
9. create a Object class that represents this new type in new language if necessary. Example: INTEGER, NULL, BOOLEAN,   RETURN VALUE, FUNCTION. For example IntegerLiteral from AST is converted into Integer of Object
10. eval source(parsed) into desnt(eval)

Lots of steps in between....

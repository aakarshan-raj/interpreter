# interpreter

To run tests: 
Build: `cmake --build build -j8`

Test: `ctest --test-dir build --output-on-failure`

Trace Segmentation faults: `valgrind --leak-check=full --track-origins=yes ./monkey`


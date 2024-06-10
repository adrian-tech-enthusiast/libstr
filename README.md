## Lib Str: A versatile C library for efficient manipulation of character arrays.

This C library provides provides a comprehensive set of functions for common string operations including concatenation, splitting, searching, and more. The library also includes utility functions for checking numeric tokens and converting integers to strings. Simplify your string handling tasks with this collection of versatile functions designed to streamline your C programming experience.

### Key Features

- Navigate through tokens in a string.
- Extract substrings, numbers, and boolean values from strings.
- Append strings and values to the tokenizer buffer.
- Check and expand tokenizer buffer capacity.
- Check numeric tokens.
- Convert integers to strings.

### Prerequisites

Ensure you have a C compiler installed on your system, such as `gcc` or `clang`.

### Installation

To make sure you obtain the most updated stable version
of [shared library](https://en.wikipedia.org/wiki/Library_(computing)#Shared_libraries)(a DLL in Windows or .so in
Unix/Linux), you’ll download this software from
its [official Github repository](https://github.com/adrian-tech-enthusiast/libstr).

First, confirm the latest version available in
their [releases page](https://github.com/adrian-tech-enthusiast/libstr/releases). At the time of this writing,
the most current stable version is `1.0.0`.

1. The following command will download the `1.0.0` release and save the shared library file at
   /usr/local/lib/libstr.so, which will make this library globally accessible to clients:

    ```bash
    sudo curl -L "https://github.com/adrian-tech-enthusiast/libstr/releases/download/v1.0.0/libstr.so" -o /usr/local/lib/libstr.so
    ```

2. Next, We need to tell the loader it is available for use, so let us update the cache, invoke the `ldconfig` utility,
   which configures the system's dynamic loader. This configuration ensures that the loader will find the newly
   published library:

    ```bash
    sudo ldconfig;
    ```

   That should create a link to our shared library and update the cache so it is available for immediate use. To verify
   you can run:

    ```bash
    ldconfig -p | grep file
    ```

3. Copy the library header file(`strutils.h`) to where it can be included in one of the C compiler's search path.
   Typical locations are `/usr/include` and `/usr/local/include`;

    ```bash
    sudo curl -L "https://raw.githubusercontent.com/adrian-tech-enthusiast/libstr/v1.0.0/include/strutils.h" -o /usr/local/include/strutils.h;
    ```

   This allows the library header file to be included in your C project as follows:

    ```c
    #include <stdio.h>  /* standard input/output functions */
    #include <strutils.h> /* C String Utils Library functions */
    ```
   Without this `#include`, the compiler would complain about missing declarations for functions provided by the C
   File Library.

4. Finally, in order to compile your code with the library, add the link flag to the library during the compilation of
   your C project:

    ```bash
    gcc -o tester tester.c -lactivation
    ```

##### Compiling the Code

To compile your program, you might use a command like this, depending on your setup:

```bash
gcc -o my_program my_program.c -lstrutils
```

Replace `my_program.c` with the name of your source file. Make sure that the libfile is correctly linked.

### Contributions

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any
contributions you make are greatly appreciated.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### License

This library is licensed under the `GNU General Public License v3.0` License. See the LICENSE file for details.

### Contact

Mr. Adrián Morelos - adrian.tech.enthusiast@gmail.com

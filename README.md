# ft_containers

A learning C++ project implementing selected STL-like containers and utilities, with test harnesses and comparison outputs against the STL.

---

## Short Description

ft_containers implements core STL-like containers and utilities (vector, map, stack, iterators, type traits, algorithms, etc.) for learning purposes and to validate behavior against the standard library. It contains the implementation, samples/tests, and scripts to build and compare outputs between the custom containers and the STL.

---

## Features

-   Custom STL-like containers:
    -   vector, map, stack
    -   iterator support
    -   type_traits utilities
    -   utility helpers
    -   some standard algorithms
-   Test harness (`main.cpp`) to exercise containers and compare outputs.
-   Shell script (`tester.sh`) to automate building and running tests.
-   Logs comparing STL vs custom implementations (`stlOutput.log`, `ftOutput.log`).

---

## Tech Stack

-   Language: C++98
-   Build: Make (`Makefile`)
-   Shell scripting: `tester.sh`
-   Compiler: g++ / clang++ (POSIX environment)

---

## Project Structure

-   `algorithm/` — algorithm implementations
-   `iterator/` — iterator classes / utilities
-   `map/` — map container
-   `stack/` — stack container
-   `vector/` — vector container
-   `type_traits/` — type traits utilities
-   `utility/` — helpers (pair, swap, etc.)
-   `samples/` — usage examples
-   `tests/` — test cases
-   `main.cpp` — test runner / example usage
-   `Makefile` — build rules
-   `tester.sh` — runs build/tests automatically
-   `stlOutput.log`, `ftOutput.log` — comparison logs

---

## Installation

### Prerequisites

-   POSIX-compatible system (Linux, macOS, WSL)
-   C++ compiler (C++98 compliant)
-   make, bash/sh

### Build & Run

```bash
git clone https://github.com/procrastinator-101/ft_containers.git
cd ft_containers
make
```

Run tests:

```bash
./tester.sh
```

Or run compiled test binary:

```bash
./ft_containers
```

---

## Usage Examples

Compare STL vs custom containers:

```bash
make
./tester.sh
less stlOutput.log
less ftOutput.log
```

Quick manual test:

```bash
./ft_containers
```

Include headers from `vector/`, `map/`, etc. in your code to exercise individual containers.

---

## Scripts

**Makefile** — build/clean targets

**tester.sh** — automates compilation and logs outputs

Common targets:

```bash
make        # build
make clean  # remove object files
make fclean # remove binaries
make re     # fclean + build
```

---

## How It Works

Container code is implemented in named directories (vector, map, stack, iterator, type_traits, utility, algorithm).

`main.cpp` runs tests comparing custom containers vs STL equivalents.

`tester.sh` builds both versions, runs tests, and logs output to `stlOutput.log` and `ftOutput.log`.

Comparing the logs highlights behavioral differences for validation.

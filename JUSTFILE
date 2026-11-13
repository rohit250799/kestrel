# Kestrel task runner. Install: `sudo dnf install just` (or `cargo install just`).

# Usage examples:
#   just build            -> release build (default)
#   just build debug      -> debug build
#   just test             -> run all tests (debug)
#   just valgrind         -> leak check on main binary
#   just bench            -> run the benchmark
# Run `just --list` to see every recipe.

set shell := ["bash", "-uc"]

# ---- configure / build -------------------------------------------------

configure preset="release":
    cmake --preset {{preset}}

build preset="release": (configure preset)
    cmake --build --preset {{preset}}

debug: (build "debug")

# ---- run -----------------------------------------------------------------

run preset="release": (build preset)
    sudo build/{{preset}}/kestrel

# ---- debug -----------------------------------------------------------------

find-error preset="debug": (build preset)
    sudo gdb -batch -ex run -ex backtrace -ex quit build/{{preset}}/kestrel

# ---- housekeeping -----------------------------------------------------------------

format: (configure "debug")
    cmake --build --preset debug --target format

clean:
    rm -rf build

clean-preset preset:
    rm -rf build/{{preset}}

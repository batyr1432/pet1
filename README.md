# C++ From-Scratch Database Engine

A lightweight C++ command-line application that simulates how real-world database engines (like SQLite) organize, store, and retrieve data directly from disk without loading the entire file into memory.

## Features

- **Fixed-Size Records:** Uses a strict 40-byte `struct` layout to guarantee identical spacing for every entry on the hard drive.
- **Binary File I/O:** Writes raw memory blocks directly to a `.dat` file, skipping slow text-parsing (like CSV or JSON).
- **O(1) Random Access:** Instantly jumps to any record using mathematical byte offsets, completely bypassing linear file scanning.
- **Boundary Safety:** Automatic validation to handle missing files and prevent out-of-bounds memory reading.

## Tech Stack

**Language:** C++11 / C++17

**Standard Libraries:** `<fstream>` (Binary File I/O), `<iostream>`, `<cstring>`

## Lessons Learned

- **Low-Level Memory Layout:** I learned how compilers handle data structures in memory and how to use `reinterpret_cast` to stream raw bytes directly to storage.
- **The Power of Fixed Sizes:** I discovered why databases avoid dynamic-length data (like standard strings) in primary storage files; fixed-size blocks make navigation predictable and fast.
- **Disk I/O Optimization:** Moving the file pointer via `seekg()` helped me understand the physical and algorithmic shift from slow **O(n)** sequential text-scanning to instant **O(1)** direct disk lookups.
- **State Management:** Overcoming challenges with empty files and tracking file sizes (`tellg()`) taught me the importance of strict boundary checking in backend systems.

## Run Locally

Clone the project

```bash
  git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)

# GitLite

This repository contains a C++ data-structures project built as a Visual Studio solution for a local purpose focused version control.

## Overview

The project reads CSV data, stores it in a custom 2D linked structure, and supports indexing/search-tree style organization using custom implementations of:

- AVL Tree
- B-Tree
- Red-Black Tree
- Custom String class
- Custom utility file I/O helpers

The solution is configured as a **Visual Studio C++ project** (`.sln` + `.vcxproj`).

## Repository Structure

- `Data structure project.sln` — Visual Studio solution
- `Data structure project/Data structure project.vcxproj` — C++ project definition
- `Data structure project/Source.cpp` — program entry point and CSV ingestion flow
- `Data structure project/String.h` — custom `String` implementation with overloaded operators
- `Data structure project/LinkedList.h` — custom doubly-linked row/column structure
- `Data structure project/AVL.h` — AVL tree logic (file-backed nodes)
- `Data structure project/Btree.h` — in-memory B-Tree implementation
- `Data structure project/RedBlack.h` — Red-Black tree logic (file-backed nodes)
- `Data structure project/Utility_functions.h` — helper functions for line-based file updates/reads

## How the Program Works

1. The main program opens a CSV file path hardcoded in `Source.cpp`.
2. It reads rows and splits fields by comma.
3. Data is inserted into a custom linked matrix (`DoublyLinkedList<String>`).
4. The user is prompted to:
   - select a column
   - select a tree type:
     1. Red-Black
     2. B-Tree
     3. AVL
5. The AVL path is currently wired in `Source.cpp`; some other paths are partial/in-progress.

## Build & Run

### Prerequisites

- Windows
- Visual Studio 2022 (v143 toolset / C++ desktop workload)

### Build (Visual Studio)

1. Open `Data structure project.sln` in Visual Studio.
2. Select `Debug` or `Release`.
3. Build the solution.
4. Run the executable from Visual Studio.

### Note on Linux/macOS

`dotnet build` on this repository fails because this is a Visual Studio C++ project requiring MSBuild C++ targets (`Microsoft.Cpp.Default.props`) from Visual Studio tooling.

## Current Limitations / Notes

- CSV path is hardcoded to a local Windows path in `Source.cpp` and should be updated for your environment.
- Tree integrations are not fully unified in the entry flow.
- There is no automated test suite in the repository yet.

## Suggested Next Improvements

- Replace hardcoded CSV path with command-line/file input.
- Standardize tree interfaces and connect all tree options end-to-end.
- Add sample datasets in-repo.
- Add unit tests for custom `String`, linked list, and tree operations.
- Add cross-platform build support (e.g., CMake).

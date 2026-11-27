# NLib

**NLib** is a pure NURBS library, extracted from NVIDIA's **usd-brep** project.

It provides an exhaustive set of functions for designing and manipulating NURBS (Non-Uniform Rational B-Spline) curves and surfaces. This repository contains the NURBS algorithm core only — it does **not** include the solid-modeling / B-Rep kernel of SMLib.

## History

An American company IntegrityWare has been developing libraries for geometric calculations since 1996. In 1998 it reached an agreement with Solid Modeling Solutions to develop SMLib – a solid modeling kernel, the first version of which was ready the same year.

SMLib is a sort of “nested-doll”, where every nesting level is a separate library of functions or classes. The most “nested-doll” is NLib - a library of functions (NURBS Library), developed by a partner company GeomWare. NLib is an exhaustive set of functions for designing and manipulating NURBS curves and surfaces. NLib algorithms are based on a classic monograph [Piegl 1997], and one of its authors - Wayne Tiller is the founder and President of GeomWare. NLib is used by more than 85 companies involved in engineering software development.

<p align="center">
  <img src="asset/The NURBS Book.jpg" alt="The NURBS Book" width="330"><br>
  <em>The NURBS Book</em> — Les Piegl &amp; Wayne Tiller (2nd Edition, Springer), the classic monograph on which NLib's algorithms are based.
</p>

An object-oriented library GSNlib (General Surface NURBS Library) is based on NLib; it is a set of methods for creating, editing, obtaining information and intersecting NURBS curves and surfaces. IntegrityWare distributed this library under the name of GSLib and licensed it to such companies as Robert McNeel & Associates (for developing Rhino 3D) and Ford Motor Company.

## Building

Requirements: [CMake](https://cmake.org) 3.16+ and a C++17 compiler (Visual Studio, GCC or Clang).

**Windows** (generates a Visual Studio project):

```bat
build.bat
```

or manually:

```bat
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --open build
cmake --build build --config Release
```

**Linux / macOS:**

```sh
chmod +x build.sh
./build.sh
```

The built library is written to `build\Release\NLib.lib` on Windows (multi-config generators) and `build/lib/libNLib.a` elsewhere.

Optional CMake options:

| Option | Default | Description |
| --- | --- | --- |
| `NLIB_BUILD_SHARED` | `OFF` | Build as a shared library (DLL / `.so`) instead of static. |
| `NLIB_ENABLE_PCH` | `OFF` | Use a precompiled header (`StdAfx.h`) to speed up builds. |
| `NLIB_USE_TBB` | `OFF` | Enable the Intel TBB scalable allocator (`SM_USE_TBB_SCALABLE`). |

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for details.

# Mesh skeletonization

Written with: PMP, C++, CGAL

## Compilation

### Dependancies
Eigen3, CGAL

* Ubuntu : `sudo apt-get install libcgal-dev libeigen3-dev`
* Windows : `vcpkg.exe install cgal:x64-windows eigen3:x64-windows`
`git submodule update --init --recursive`

Compile PMP:
```
cd externals/pmp-library/
mkdir build
cd build
cmake -S ../ -B ./
cmake --build ./
```

Compile the project from the project's root::
```
cd ../
mkdir build/
cd build/
cmake ../squelettisation
cmake --build ./
```

## Execution

`SKGen [-h] [-p <path_to_mesh>] [-x <width>] [-y <height>]`

```
Available parameters:

  -h    --help
   Show help and exit.
   
  -p    --path
   Path to the requested mesh
   This parameter is optional. The default value is ''.

  -y    --height
   Height of the window
   This parameter is optional. The default value is '800'.

  -x    --width
   Width of the window
   This parameter is optional. The default value is '800'.
```

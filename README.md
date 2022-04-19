# Squelettisation

Technologies utilisées : PMP, C++

## Compilation

Télécharger les dépendances : `git submodule update --init --recursive`

Compiler PMP :
```
cd externals/pmp-library/
mkdir build
cd build
cmake -S ../ -B ./
cmake --build ./
```

Compiler le projet :
```
cd ../
mkdir build/
cd build/
cmake ../squelettisation
cmake --build ./
```

## Exécution

Pour lancer le programme : `SKGen [-h] [-p <path_to_mesh>] [-x <width>] [-y <height>]`

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

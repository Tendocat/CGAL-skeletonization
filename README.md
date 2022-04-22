# Géométrie Numérique - Projet 'Squelettisation'

Technologies utilisées : PMP, C++, CGAL

## Compilation

### Installation des dépendances externes au projet 
Dépendances : Eigen3, CGAL

* Sous Ubuntu : `sudo apt-get install libcgal-dev libeigen3-dev`
* Sous Windows : Utiliser vcpkg `vcpkg.exe install cgal:x64-windows eigen3:x64-windows`

### Télécharger et compiler les dépendances internes : `git submodule update --init --recursive`

Compiler PMP depuis la racine du projet :
```
cd externals/pmp-library/
mkdir build
cd build
cmake -S ../ -B ./
cmake --build ./
```

Compiler le projet depuis la racine du projet :
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

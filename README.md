# MiniRT

MiniRT is a simple ray tracer developed as part of the 42/School Hive curriculum. It renders 3D scenes from a `.rt` configuration file using fundamental ray tracing algorithms written in C. This project includes support for various geometric primitives, camera setup, lighting, object transformations, and real-time interaction.

![Alt text](imgs/scene1.png)

## Features

* Ray tracing engine written in C
* Real-time rendering using MLX42 library
* Support for `.rt` scene files
* Basic primitives:

  * Sphere (`sp`)
  * Plane (`pl`)
  * Cylinder (`cy`)
* Lighting:

  * Ambient (`A`)
  * Point light (`L`)
* Camera with FOV and view matrix (`C`)
* Color rendering with shadows
* Object transformations: translation, rotation, scaling
* Interactive camera and object manipulation via keyboard

## Installation

### Dependencies

* [MLX42](https://github.com/codam-coding-college/MLX42)
* C compiler (`gcc`)
* CMake (if using MLX42)
* Linux or macOS

### Build

```bash
git clone https://github.com/iliamunaev/RayTracer
cd RayTracer
make bonus
```

## Scene File Format (.rt)

Example:

```
A 0.2 255,255,255
C -50,0,20 0,0,0 70
L -40,0,30 0.7 255,255,255

sp 0,0,20 20 255,0,0
pl 0,0,0 0,1,0 0,255,0
cy 50,0,20 0,0,1 14.2 21.42 10,0,255
```

### Element Details

| Identifier | Description      | Parameters                                |
| ---------- | ---------------- | -------------------------------------- |
| `A`        | Ambient lighting | `A 0.2 255,255,255`                    |
| `C`        | Camera           | `C -50,0,20 0,0,0 70`                  |
| `L`        | Light source     | `L -40,0,30 0.7 255,255,255`           |
| `sp`       | Sphere           | `sp 0,0,20 20 255,0,0`                 |
| `pl`       | Plane            | `pl 0,0,0 0,1,0 0,255,0`               |
| `cy`       | Cylinder         | `cy 50,0,20 0,0,1 14.2 21.42 10,0,255` |

## Controls

### 1. Choose the object on the screen by using mouse.
### 2. Manipulation

| Key | Mode | Key | Manipulation |
| --- | ---- | --- | ------------ |
| `C` | Camera | `Up`/`Down`/`Left`/`Right`| Move camera
| `C` | Camera | `Ctrl+Up`/`Ctrl+Down`| Change camera fild of view (FOV)
| `T` | Translate | `Up`/`Down`/`Left`/`Right` | Move selected object
| `R` | Rotate | `Up`/`Down`/`Left`/`Right` | Rotate selected object
| `S` | Scale | `+`/`-`| Scale selected object
| `ESC` | Exit program |

## Running
Choos any map and run, for example
```bash
./miniRT maps/map.rt
```

Test scenes are located in the `maps/` directory.

## Project Structure

```
RayTracer/
├── include/
│   └── minirt.h
│   └── other_header_files.h
├── lib/
│   └── MLX42/
│   └── libft/
├── maps/
│   └── map.rt
│   └── other_maps.rt
├── src/
│   ├── camera/
│   ├── colors/
│   ├── lightning/
│   └── loop/
│   └── math/
│   └── matrix/
│   └── parsing/
│   └── primitives/
│   └── ray/
│   └── render/
│   └── utils/
│   └── validation/
├── minirt.c
├── tests/
├── .gitignore
├── LICENSE
├── Makefile
└── README.md
```

## Mandatory Requirements

* Only `.rt` files are accepted
* `A`, `C`, and `L` must appear exactly once
* Normals must be normalized
* RGB values must be in \[0, 255]
* Supports shadows and basic shading

##  Authors

* Ilia Munaev — [LinkedIn](https://www.linkedin.com/in/iliamunaev/)
* Laurens Haas — [LinkedIn](https://www.linkedin.com/in/laurens-haas-598b64218/)

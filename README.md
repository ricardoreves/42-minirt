
# 42 MiniRT
![Language](https://img.shields.io/static/v1?label=language&message=c&color=blue) ![Licence](https://img.shields.io/badge/license-MIT-green) ![Score](https://42-project-badge.glitch.me/users/rpinto-r/project/minirt) [![norminette](https://github.com/ricardoreves/42-minirt/actions/workflows/norminette.yml/badge.svg)](https://github.com/ricardoreves/42-minirt/actions/workflows/norminette.yml) 

## 🪧 Overview
### Description
This project is an introduction to the beautiful world of Raytracing.
Once completed you will be able to render simple Computer-Generated-Images and you
will never be afraid of implementing mathematical formulas again.

### Goal
The goal of the program is to generate images using the Raytracing protocol. Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

## 📷 Preview
![preview](imgs/preview/wolf.png)
![preview](imgs/preview/room.png)
![preview](imgs/preview/earth.png)
![preview](imgs/preview/balls.png)
![preview](imgs/preview/checkboard.png)
![preview](imgs/preview/shadows.png)
![preview](imgs/preview/atom.png)


## 🚀 Getting Started

### Prerequisites

MiniLibX for Linux requires xorg, x11 and zlib, therefore you will need to install the following dependencies: xorg, libxext-dev and zlib1g-dev. Installing these dependencies on Ubuntu can be done as follows:
```
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

### Installation
1. Clone the project.
```
git clone git@github.com:ricardoreves/42-minirt.git
```
2. Navigate to the project directory.
```
cd 42-minirt
```
3. Compile the MiniRT. (You can ignore the Minilibx compilation warning)
```
make
```

## 🕹 Usage
1. Run the MiniRT with a [scenes](scenes/).
```
./minirt scenes/wolf.rt
```
2. Press key `A` to enable `Antialising`
3. Press key `ESC` to quit 


## 📚 References


## 🧰 Tools
- [ImageMagick](https://imagemagick.org/) - Command-line tool to convert, edit, or compose digital images


## 📝 License
Distributed under the MIT License. See [LICENSE](LICENSE) for more information.



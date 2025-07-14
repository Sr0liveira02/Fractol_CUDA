# Fractol Viewer

A small project where I explore and visualize fractals using a codebase originally written by [namejojo](https://github.com/namejojo).

## Overview

This application generates mesmerizing fractal visuals using low-level graphics programming in C. It's based on [namejojo's](https://github.com/namejojo/fractol) implementation, with my own tweaks and explorations, to better understand the NVidia's CUDA Toolkit

## Requirements

```bash
sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev nvidia-cuda-toolkit
make libx
```

## Running 
execute the command to see the options u have to look at the fractals based on CPU or GPU(cuda) version

```bash
make
```
or
```bash
make cuda
```
then
```bash
./fractol_cuda
```
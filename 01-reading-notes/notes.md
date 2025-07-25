# Study Notes

- [Study Notes](#study-notes)
  - [\*Presentations list link](#presentations-list-link)
  - [Document1: TouchGFX Technical Introduction](#document1-touchgfx-technical-introduction)
      - [Teamwork in parallel](#teamwork-in-parallel)
  - [Document2: Embedded Graphics - Basic Concepts](#document2-embedded-graphics---basic-concepts)
      - [Hardware](#hardware)
      - [Pixel format](#pixel-format)
      - [Framebuffer](#framebuffer)
      - [Graphic Engine (model)](#graphic-engine-model)
      - [Main Loop](#main-loop)
      - [Performance](#performance)


## [*Presentations list link](https://support.touchgfx.com/docs/resources/presentations)


## Document1: TouchGFX Technical Introduction

<image src="image.png" width="500">

> 1. By using the development kit, you skip the first 3 hard steps and build your UI directly.
> 2. Start a project from CubeMX when working on a **custom** hardware. refer to the "Board Bring Up presentation".

#### Teamwork in parallel
It's possible to work on the GUI and board bring up in parallel, they are independent with each other.
1. Team1 configures the hardware and AL development through CubeMX
2. Team2 develops the GUI on Designer on the simulator.



## Document2: Embedded Graphics - Basic Concepts
#### Hardware

<image src="image-1.png" width="500">

#### Pixel format

Corlor depth/dithering:

<image src="image-2.png" width="500">

#### Framebuffer

<image src="image-3.png" width="500">

#### Graphic Engine (model)
User code changes the model, and model will affect the display automatically by the engine. 

<image src="image-4.png" width="500">

#### Main Loop
read inputs --> change model --> render model to framebuffer and then display

<image src="image-5.png" width="500">

#### Performance 

<image src="image-6.png" width="500">

















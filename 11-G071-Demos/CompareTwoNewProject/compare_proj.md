# Compare Two New Project

Here I compare two project, one is the rice cooker demo, one is an empty project I created from Designer with G071B board setup. They are compared after I compiled and flashed the board. Those two projects use the same hardware, the difference is that the 'empty' one is almost empty with user code.


<img src="image.png" border=1 width=350>

![empty](image-1.png)


## I use WinMerge to compare the two folders


<img src="image-2.png" border=1 width=600>

From the comparing result, most are identical, differences are only in STM32CubeIDE and TouchGFX folders.

### 1. The IDE folders have little difference

<img src="image-3.png" border=1 width=300>

Note that, the .project stores all the file paths for the project, .cproject stores the configuration for the project.

### 2. The TouchGFX folders have more difference


<img src="image-4.png" border=1 width=350>

1. `App/app_touchgfx.c/h` has the main touchgfx entry for main(), code is simple and stays all the same across projects.

![a](image-5.png)


2. `assets` store all the media resources for the project.

<img src="image-6.png" border=1 width=350>

3. `build` holds all the project outputs


<img src="image-7.png" border=1 width=350>

4. `config` for touchgfx in those two are same 

<img src="image-8.png" border=1 width=350>

5. `generated` folders are different, since it holds the source and media data

<img src="image-9.png" border=1 width=350>

6. `gui` is half generated and half user coded, it holds all the screens source code, e.g. `screen1Presenter.cpp/.hpp`, `screen1View.cpp/hpp`.

<img src="image-10.png" border=1 width=350>

7. `simulator` is different, because `simulator` compiles the source code files, it means different paths set.

<img src="image-11.png" border=1 width=350>



8. `target` holds the Designer's setting for the board


<img src="image-12.png" border=1 width=350>

application.config:

<img src="image-13.png" border=1 width=550>

`.touchgfx.part` set the starting point of the project for Designer

<img src="image-14.png" border=1 width=550>


`target.config` looks like part of the `.touchgfx.part`.


<img src="image-15.png" border=1 width=550>



#This is The End
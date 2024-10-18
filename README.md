# Gunslinger Project Template

This is a minimum and premade configuration that you need in order to get started with gunslinger. It provides all the necessary dependencies and the shell scripts for compiling it on Windows, Mac and Linux.

You can also check the main **Gunslinger** repository here, where you'll find documentation on how to get started:
[Gunlinger repository](https://github.com/MrFrenik/gunslinger)
 
And you can also find a complete list of examples for you to learn from and test on your machine here: 
[Gunslinger examples](https://github.com/MrFrenik/gs_examples)

## Cloning instructions: 
- Use the following command to clone the repo and init the gunslinger submodule
```bash
git clone --recursive https://github.com/MrFrenik/gs_project_template
```

## Updating GS instructions (updates gunslinger submodule and rebases to main branch): 
```bash
git submodule update --remote --rebase --recursive
```

## Build Instructions:

for building the normie way refer to the upstream readme

for building the _cool_ way compile `nobuild.c` with whatever compiler you use, then run the resulting binary

so far it works on linux and windows, and hasn't been tested on any other platforms

### pros and cons of using nobuild for this
- cross-platform (pro)
- written in c (pro and con)
  - i tried to show the merit of this by getting the output file name from the source code that's being compiled, however i had to add a little header file to the source code and get the variable from there
- cool (pro)

to clarify: i dont intend to contribute upstream with this repo. i'm doing this for me, just to see how silly and over-engineered i can make building gunslinger

## Aknowledgements
- john for making gunslinger and everything else
- rexim for making nobuild

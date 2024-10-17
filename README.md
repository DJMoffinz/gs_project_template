# Gunslinger Project Template

This is a minimum and premade configuration that you need in order to get started with gunslinger. It provides all the necessary dependencies and the bash/batch scripts for compiling it on Windows, Mac and Linux.

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

works on linux, not yet tested on windows (if someone who uses windows tries this and it works make a PR to this readme and change this line)

# Awful Engine

## What is this mess?
Just something I'm playing with... It's not really meant for the light of day lol

## Why C99?
Because screw you! I do what I want!

In reality, it's just a fun challenge. I'm pretty used to C++11 and greater, so going back to C99 has been fun.

## I fOuNd A bUg!
I don't care... Go fix it and then leave me a PR I guess.

## Build Instructions
This project uses CMake as it's build configurator. If you don't have CMake installed, install it via apt/homebrew/manual install

If you don't already have one, make a build folder. This will keep all the cmake files in one tidy folder

`mkdir build`

Then build it!

`cd build`

`cmake ..`

`make`

There should now be two executable files in the repo root folder. 'game' is just a testbed app used for development and 'sh3d'. 'sh3d' is the command line tool you'll want to use.

## Usage
sh3d [path to .obj file]


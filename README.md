# InstantInstaPhoto
A tool to create slides for Instagram (and other social media) that flow into each other

# State

This is technically feature-complete, meaning it is fully ready to create posts with. However, there are still some quality-of-life features that are yet to be added before this is ready for a full 1.0 version.

# Contributing

If you so desire, just make whatever changes you want, and send a pull request. I would be surprised if anyone actually puts in any time into this thing.

# Building

In order to build, please use my custom branch of SFML, available here: https://github.com/justanobdy/SFML

clone using this command:
```
git clone https://github.com/justanobdy/SFML --branch justacustom
```

And then proceed to build and install SFML using this tutorial: https://www.sfml-dev.org/tutorials/3.0/getting-started/build-from-source/

Or you could try to mess with this template: https://github.com/SFML/cmake-sfml-project, using my repository instead

After that, you should be good to go! 

Just build using CMake and turn on LINK_OPENGL if need to.
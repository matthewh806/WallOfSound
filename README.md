# WallOfSound

This is my repository of code ideas that I've picked up while reading [The Computer Music Tutorial](https://mitpress.mit.edu/books/computer-music-tutorial)

I've also heavily leant upon the [Maximillian Library](https://github.com/micknoise/Maximilian) for inspiration and clues when
I've been stuck along the way. 

I will see how this develops, but for now I've only tested on macOS, clone the repository and compile with the command:
```
g++ -Wall -D__MACOSX_CORE__ -o WallOfSound main.cpp RtAudio.cpp Oscillator.cpp AudioSettings.cpp -framework CoreAudio -framework CoreFoundation -lpthread
```

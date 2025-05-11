# Jar Runner

DISCLAMER: Don't use on serius projects. I bearly know C++ so AI helped with lot's of things. I will try to make it more usable in the future but right now it works just enough for my needs.


This app/wrapper allows basic jar file execution and java validation.


## Features

- Configurable java args
- Java presence check (Checks if java is installed)
    - OS specific instructions (WIP)


### Todo

- More configs
- Java version check
- Better UI framework/handler (Native popups at best currently uses FLTK)
- Better Config Reader (Current implementation is already bit unstable)


## Usage

Build/Download Release



## Config

Runner **REQUIRES** a config file in the same directory named `jr.cfg`

config format is `<key>=<value>`.


- `file` - Main Jar file (Paths not allowed. Example: `/file.jar` errors out)
- `java_args` - Java arguments (If set app will warn user and wait for confirmation. Recommended to not use this yet)


## Libs uses:

- FLTK - GUI Framework

*Yes that's all. I tried to make it as small as possible.*


## License

Project is MIT licensed.
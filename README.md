# [Super Scribblenauts (EU) reverse-engineering](https://xortroll.github.io/super-scribblenauts-re/)

This repository contains my reverse-engineering work of the *European version* of [**Super Scribblenauts**](https://scribblenauts.fandom.com/es/wiki/Super_Scribblenauts) (game code `BH2P`): ASM-hacking, documenting game logic/formats, command-line utilities and hopefully a proper object/adjective editor ;)

Due to similarities in structure/codebase/formats with the mobile game [**Scribblenauts Remix**](https://scribblenauts.fandom.com/wiki/Scribblenauts_Remix), many of the findings in this work are common to both games, which is wonderful news for everyone!

- [Super Scribblenauts (EU) reverse-engineering](#super-scribblenauts-eu-reverse-engineering)
  - [Libraries: `libobjectnaut`](#libraries-libobjectnaut)
  - [Command-line utility: `scribbletool`](#command-line-utility-scribbletool)
  - [ASM-hacking](#asm-hacking)
  - [Credits](#credits)

## Libraries: `libobjectnaut`

In order to make any PC tools, [libobjectnaut](libobjectnaut) are C++ libraries to work with game formats. Any further tools in this repository are made thanks to these base libraries. [Why this name?](https://xortroll.github.io/super-scribblenauts-re/objnaut/objnaut/)

Like the tools themselves, these libraries are in constant changes, plus only a handful of (relevant) formats are implemented there.

## Command-line utility: `scribbletool`

For practical purposes (and originally, to make my life easier) I made a simple but powerful command-line tool: [scribbletool](scribbletool)

It currently has the following features:

- Print a specific text file (by providing its [file ID](https://xortroll.github.io/super-scribblenauts-re/fs/)), printing all its messages

- List list of objects/adjectives of a given language

- Print a given object file (all its fields, etc.)

- Export a given texture file to an output PNG

- Generate HTML pages for all the objects of a given language

All these commands work as well for Scribblenauts Remix files (read about file differences [here](https://xortroll.github.io/super-scribblenauts-re/fs/))!

For further information about its usage, download/compile it and run it to show help/usage info.

You will need [CMake](https://cmake.org/) in order to compile it, without any external dependencies other than standard C++ and [editwl](https://github.com/XorTroll/editwl).

## ASM-hacking

The [ASM-hacking tests](asmhacks) serve as examples on how to inject custom code in the game, using generated [headers](re-export/include) and [symbols](re-export/mkds-eu-decomp-symbols.x) of my reverse-engineering work on this game.

## Credits

- **ovf** for helping me a lot with their related reversing work on Scribblenauts Remix.

- [GBATEK](https://problemkaputt.de/gbatek.htm) for its great (although sometimes limited/outdated) DS docs

- [Pokémon Diamond decompilation](https://github.com/pret/pokediamond) as a helpful reference for already (partially) understood DS SDK code

- ['Hacking Nintendo DS' EnHacklopedia page](https://doc.kodewerx.org/hacking_nds.html) as the only (and great) specifications I found regarding DS cheat codes

- [NCPatcher](https://github.com/TheGameratorT/NCPatcher) as a great tool for simplifying the process of making DS ASM hacks
